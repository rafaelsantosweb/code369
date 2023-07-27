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
        $vars['attributes']['class'][] = 'authenticated-modal';
        $vars['attributes']['data-togle'] = 'modal';
        $vars['attributes']['data-target'] = '#authenticatedModal';
      }
    }
  }

}

function observatorio_preprocess_views_view_field(&$vars) {
  if (!\Drupal::currentUser()->id() && $node = $vars['row']->_entity) {
    if ($vars['field']->field == 'view_node' && $node->field_teaser->value == 1) {
      $vars['field']->options['element_class'] .= ' authenticated-modal';
    }
  }
}
