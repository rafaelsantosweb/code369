<?php

/**
 * @file
 * Theme and preprocess functions for forms.
 */

/**
 * Summary of observatorio_form_search_block_form_alter
 * @param mixed $form
 * @param mixed $form_state
 * @return void
 */
function observatorio_form_search_block_form_alter(&$form, $form_state) {
  $form['keys']['#placeholder'] = 'Quais estudos você está buscando?';
}

function observatorio_form_user_login_form_alter(&$form, $form_state) {
  $form['name']['#placeholder'] = 'E-mail';
  $form['pass']['#placeholder'] = 'Senha';
  $form['actions']['submit']['#value'] = t('Acessar >');
}