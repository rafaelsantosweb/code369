<?php

/**
 * @file
 * Custom theme hooks.
 */

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

function observatorio_preprocess_page(&$vars) {
  // get the current theme folder using D10 api
  $theme_path = \Drupal::service('theme.initialization')->getActiveThemeByName('observatorio')->getPath();
  $node = \Drupal::routeMatch()->getParameter('node');
  $filepath = '';
  if ($node && $node->hasField('field_content')) {
    // Look for a hero image.
    foreach($node->field_content->entity as $item) {
      $paragraph = $item->entity;
      if ($paragraph_type = $paragraph?->bundle()) {
        // foreach ($item->entity as $i)
          // dpm($i);
        // dpm($node->field_content);
        // break;
        // dpm($item);
        if ($paragraph_type == 'image') {
          $img = $vars['hero_img'] = $paragraph->field_media_image;
          $filepath = $img->entity->getFileUri();
          $filepath = \Drupal::service('file_system')->realpath($filepath);
          break;
        }
      }
    }
  }

  // Add a default light blue image as background if none is set from the content.
  if (!key_exists('hero_img', $vars)) {
    $filepath = $theme_path . $vars['default_hero_img'] = '/images/light-blue-bg.png';
  }

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
    $vars['hero_class'] = $brightness > 80 ? 'bright' : 'dark';
    $vars['brightness'] = $brightness;

    // $text_color = $brightness > 150 ? '#000' : '#fff';
    // $vars['hero_text_color'] = $text_color;
  }
}
