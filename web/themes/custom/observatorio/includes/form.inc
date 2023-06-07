<?php

/**
 * @file
 * Theme and preprocess functions for forms.
 */

function observatorio_form_search_block_form_alter(&$form, $form_state) {
  $form['keys']['#placeholder'] = 'Quais estudos você está buscando?';
}
