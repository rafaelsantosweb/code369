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
  if ($paragraph = $vars['paragraph']) {
    // $node = \Drupal::routeMatch()->getParameter('node');
    // $paragraph_type = $paragraph->getType();
    // $paragraph_id = $paragraph->id();
    // $paragraph_view_mode = $vars['view_mode'];

    //* ******************************************* *//
    // Tratamento especial para os conteúdos restritos.
    if ($paragraph->hasField('field_restrito') && $paragraph->field_restrito->value && !\Drupal::currentUser()->id()) {
      $remove = ['field_iframe', 'field_body', ];

      $content = &$vars['content'];

      if (isset($content['field_body_resume']) && $paragraph->field_body_resume->summary) {
        // Substitui o conteúdo com o resumo.
        $content['field_body_resume'] = ['#markup' => '<div>' . $paragraph->field_body_resume->summary . '<div>'];
      }

      if (isset($content['field_file'])) {
        // Substitui o link do anexo com nosso link pra modal.
        $remove[] = 'field_file';
        $desc = $content['field_file'][0]['#description'];
        $content[]['#markup'] = '<div><b class="authenticated-modal"><a href="" class="button">' . $desc . '</a></b></div>';
      }
      else {
        // Caso contrário, adiciona um link genérico pra modal.
        $content[]['#markup'] = '<div><b class="authenticated-modal"><a href="" class="button">Acessar os dados do estudo.</a></b></div>';
      }
      // dump($content);
      $content = array_diff_key($content, array_flip($remove));
    }
  }
}
