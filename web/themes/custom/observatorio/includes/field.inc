<?php

/**
 * @file
 * Theme and preprocess functions for fields.
 */

use Drupal\Component\Serialization\Json;

function observatorio_preprocess_field(&$vars) {
  $field = $vars['element'];
  if ($field['#field_name'] == 'field_hero_banners') {
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
}
