<?php

/**
 * @file
 * Theme and preprocess functions for fields.
 */

use Drupal\Component\Serialization\Json;

function observatorio_preprocess_field(&$vars) {
  $field = $vars['element'];

  $fields = [
    'field_paragraph_cta',
    'field_link',
  ];

  // dump($field['#field_name']);
  // Verifica se o link precisa de autenticação para ser acessado.
  if (in_array($field['#field_name'], $fields)) {
    if (!\Drupal::currentUser()->id()) {
      $node = $vars['element']['#object']->getParentEntity();
      if ($node?->field_teaser?->value) {
      // if (!$element['#object']->getParentEntity()->field_access->entity->name->value == 'Privado') {
        $vars['attributes']['class'][] = 'authenticated-modal';
        $vars['attributes']['data-togle'] = 'modal';
        $vars['attributes']['data-target'] = '#authenticatedModal';
      }
    }
  }
  /*
  elseif ($field['#field_name'] == 'field_hero_banners') {
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
  } /* */
}

function observatorio_preprocess_views_view_field(&$vars) {
  if (!\Drupal::currentUser()->id() && $node = $vars['row']->_entity) {
    if ($vars['field']->field == 'view_node' && $node->field_teaser->value == 1) {
      $vars['field']->options['element_class'] .= ' authenticated-modal';
    }
    // dump($node->field_teaser->value, $node->id());
    // dump($vars['field']->options['element_class']);
  }
}
