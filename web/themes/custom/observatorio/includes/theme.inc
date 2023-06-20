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
  $node = \Drupal::routeMatch()->getParameter('node');
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
          $vars['hero_img'] = $paragraph->field_media_image;
          break;
        }
      }
    }
  }
  // Add a default light blue image as background if none is set from the content.
  if (!key_exists('hero_img', $vars)) {
    $vars['default_hero_img'] = '/images/light-blue-bg.png';
  }
}
