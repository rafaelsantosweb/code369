<?php

/**
 * @file
 * Theme and preprocess functions for paragraphs.
 */

use Drupal\paragraphs\Entity\Paragraph;

/**
 * Implements hook_preprocess().
 */
function observatorio_preprocess_paragraph(&$vars) {
  $node = \Drupal::routeMatch()->getParameter('node');
    if ($paragraph = $vars['paragraph']) {
      $paragraph_type = $paragraph->getType();
      $paragraph_id = $paragraph->id();
      $paragraph_view_mode = $vars['view_mode'];
    }
}
