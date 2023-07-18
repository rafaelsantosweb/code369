<?php

/**
 * @file
 * Custom theme hooks.
 */

use Drupal\Component\Serialization\Json;
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

    $settings = [
      // 'row_class' => '',
      'default_row_class' => true,
      'uses_fields' => false,
      'items' => 1,
      'margin' => 1,
      'nav' => true,
      'navPosition' => 'bottom',
      'autoplay' => true,
      'autoplayButtonOutput' => false,
      // 'autoplayTextStart' => 'start',
      // 'autoplayTextStop' => 'stop',
      'autoplayHoverPause' => true,
      'autoplayPosition' => 'top',
      'controls' => false,
      // 'controlsTextPrev' => 'prev',
      // 'controlsTextNext' => 'next',
      // 'controlsPosition' => 'bottom',
      'arrowKeys' => true,
      'mouseDrag' => false,
      'loop' => true,
      'speed' => 450,
      // 'dimensionMobile' => '',
      // 'itemsMobile' => '1',
      // 'dimensionDesktop' => '',
      // 'itemsDesktop' => '1',
      // 'autoplayText' => [
      //   '0' => 'start',
      //   '1' => 'stop',
      // ],
      // 'controlsText' => [
      //   '0' => 'prev',
      //   '1' => 'next',
      // ],
      // 'responsive' => [
      //   '0' => [
      //     'items' => 1,
      //   ],
      // ],
    ];
    $vars['slider_settings'] = json::encode($settings);
  }

  $user = \Drupal::currentUser();
  if ($user->id() < 1 && $node?->hasField('field_teaser') && $node?->field_teaser->value) {
    $vars['teaser'] = 1;
  }
}

/**
 * Look for the hero_banner (sub)paragraph to get its images
 * @param mixed $entity
 * @return string
 */
function nested_content($entity, &$vars) {
  $filepath = '';
  // Check if its a node with field_content, or a paragraph with the other 2.
  if (method_exists($entity, 'hasField')) {
    if ($entity->hasField('field_content')) {
      return nested_content($entity->field_content, $vars);
    }
    elseif ($entity->hasField('field_hero_banners')) {
      return nested_content($entity->field_hero_banners, $vars);
    }
  }

  // We have the desired paragraph, get its image(s).
  foreach ($entity as $item) {
    $paragraph = $item->entity;
    if ($paragraph->bundle() == 'hero_slider') {
      nested_content($paragraph, $vars);
    }
    if ($paragraph->bundle() == 'hero_banner') {
      $hero['title'] = $paragraph->field_title->value;
      $hero['body'] = $paragraph->field_body->value;
      $hero['img']['src'] = $img = $paragraph->field_image->entity->field_media_image->entity;
      $hero['img']['alt'] = $paragraph->field_image->entity->field_media_image->alt;

      if ($cta = $paragraph->field_paragraph_cta->entity) {
        $hero['cta']['title'] = $cta->field_link?->title;
        $hero['cta']['url'] = Url::fromUri($cta->field_link?->uri);
      }

      $filepath = $img?->getFileUri();
      $filepath = \Drupal::service('file_system')->realpath($filepath);
      $hero['filepath'] = $filepath;
      // Call our custom function to get the brightness of the image.
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
