<?php

/**
 * @file
 * Custom theme hooks.
 */

use Drupal\Core\Url;

/**
 * Implements hook_library_info_build().
 * Automatically creates components libraries (Not visible in theme's libraries.yml file)
 * You can directly use the component name as a library, f.x
 *  {{ attach_library('observatorio/block') }}.
 */
function observatorio_library_info_build() {
  $extensions = ['css', 'js'];
  $directory = 'themes/custom/observatorio/build/components';
  $extensions = array_map('preg_quote', $extensions);
  $extensions = implode('|', $extensions);
  if (!is_dir($directory)) {
    return [];
  }
  $file_scan = \Drupal::service('file_system')->scanDirectory($directory, "/{$extensions}$/");
  $libraries = [];
  foreach ($file_scan as $file) {
    $parts = explode('.', $file->filename);
    $extension = end($parts);
    switch ($extension) {
      case 'css':
        $libraries[$file->name][$extension] = [
          'component' => [
            '/' . $file->uri => [],
          ],
        ];
        break;

      case 'js':
        $libraries[$file->name][$extension] = [
          '/' . $file->uri => [],
        ];
        break;
    }
  }
  return $libraries;
}

function observatorio_preprocess(&$vars, $hook) {
  $user = \Drupal::currentUser();
  $node = \Drupal::routeMatch()->getParameter('node');
  switch ($hook) {
    case 'html':
      if ($user->id() < 1 && $node?->hasField('field_teaser') && $node?->field_teaser->value) {
        $vars['attributes']['class'][] = 'teaser';
      }
      break;
  }
}

function observatorio_preprocess_page(&$vars) {
  // get the current theme folder using D10 api
  $theme_path = \Drupal::service('theme.initialization')->getActiveThemeByName('observatorio')->getPath();
  $node = \Drupal::routeMatch()->getParameter('node');
  if (!key_exists('heros', $vars)) {
    $filepath = nested_content($node, $vars);
    // Add a default light blue image as background if none is set from the content.
    if (!key_exists('heros', $vars)) {
      $filepath = $theme_path . $vars['default_hero_img'] = '/images/light-blue-bg.png';
      $vars['heros'][]['class'] = image_brightness($filepath);
    }
  } else {
    // $vars['hero_class'][] = 'dark';
  }
  $user = \Drupal::currentUser();
  if ($user->id() < 1 && $node?->hasField('field_teaser') && $node?->field_teaser->value) {
    $vars['teaser'] = 1;
  }
  // dpm($vars['hero_class'], 'hero');
}

/**
 * Look for the hero_banner (sub)paragraph to get its images
 * @param mixed $entity
 * @return string
 */
function nested_content($entity, &$vars) {
  $filepath = '';
  // If the entity has our method
  if (method_exists($entity, 'hasField')) {
    // Check if its a node with field_content, or a paragraph with the other 2.
    if ($entity?->hasField('field_content')) {
      return nested_content($entity->field_content->entity, $vars);
    } elseif ($entity?->hasField('field_hero_banners')) {
      return nested_content($entity->field_hero_banners, $vars);
    } elseif ($entity?->hasField('field_banner')) {
      return nested_content($entity->field_banner, $vars);
    }
  }

  foreach ($entity as $item) {
    $paragraph = $item->entity;

    if ($paragraph && !method_exists($paragraph, 'bundle')) {
      continue;
    }
    elseif ($paragraph && method_exists($paragraph, 'hasField') && $paragraph->hasField('field_image')) {
      $hero['img'] = $img = $paragraph->field_image->entity->field_media_image->entity;
      $hero['title'] = $paragraph->field_title->value;
      $hero['body'] = $paragraph->field_body->value;

      // prepare the field_paragraph_cta to be used in the template
      if ($cta = $paragraph->field_paragraph_cta->entity) {
        $hero['cta']['title'] = $cta->field_link?->title;
        $hero['cta']['url'] = Url::fromUri($cta->field_link?->uri);
      }

      $filepath = $img?->getFileUri();
      $filepath = \Drupal::service('file_system')->realpath($filepath);
      $hero['filepath'] = $filepath;
      $hero['class'] = image_brightness($filepath);

      $vars['heros'][] = $hero;
    }
  }
  return $filepath;
}

/**
 * Summary of image_brightness
 * @param mixed $filepath
 * @return string
 */
function image_brightness($filepath) {
  if ($filepath && $im = @imagecreatefrompng($filepath)) {
    // get the first pixel color from the $filepath image
    $rgb = imagecolorat($im, 0, 0);
    // get each color component's value
    $r = ($rgb >> 16) & 0xFF;
    $g = ($rgb >> 8) & 0xFF;
    $b = $rgb & 0xFF;
    // calculate the brightness using the formula: sqrt(0.299*R^2 + 0.587*G^2 + 0.114*B^2)
    $brightness = sqrt(0.299 * pow($r, 2) + 0.587 * pow($g, 2) + 0.114 * pow($b, 2));
    // if the brightness is greater than 150, we'll set the text color to black
    // otherwise, white
    return $brightness > 80 ? 'bright' : 'dark';
  }
  return 'dark';
}
