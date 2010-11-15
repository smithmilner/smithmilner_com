<?php
// $Id: icontact.admin.inc,v 1.1.2.12 2010/05/03 21:48:44 greenskin Exp $

/**
 * iContact Settings Page
 */
function icontact_api_settings(&$form_state) {
  drupal_add_js(drupal_get_path('module', 'icontact') .'/js/icontact_api.js');

  $form = system_settings_form(array());
  $app_id = (isset($form_state['post']['icontact_app_id'])) ? $form_state['post']['icontact_app_id'] : variable_get('icontact_app_id', ICONTACT_TEST_APP_ID);
  $form['icontact_app_id'] = array(
    '#type' => 'select',
    '#title' => t('Mode'),
    '#default_value' => $app_id,
    '#options' => array(ICONTACT_APP_ID => t('Live'), ICONTACT_TEST_APP_ID => t('Sandbox')),
    '#required' => TRUE
  );
  $form['live'] = array(
    '#type' => 'fieldset',
    '#title' => t('Live'),
    '#collapsible' => TRUE,
    '#collapsed' => ($app_id == ICONTACT_APP_ID) ? FALSE : TRUE
  );
  $form['live']['icontact_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('icontact_username', ''),
    '#size' => 25,
    '#maxlength' => 25
  );
  $form['live']['icontact_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => t('Use the password set when registering the API key with your iContact account.'),
    '#default_value' => variable_get('icontact_password', 'Nt638HT8VQ'),
    '#size' => 25,
    '#maxlength' => 25
  );
  $form['sandbox'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sandbox'),
    '#collapsible' => TRUE,
    '#collapsed' => ($app_id == ICONTACT_TEST_APP_ID) ? FALSE : TRUE
  );
  $form['sandbox']['icontact_test_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('icontact_test_username', ''),
    '#size' => 25,
    '#maxlength' => 25
  );
  $form['sandbox']['icontact_test_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => t('Use the password set when registering the API key with your iContact account.'),
    '#default_value' => variable_get('icontact_test_password', 'Nt638HT8VQ'),
    '#size' => 25,
    '#maxlength' => 25
  );
  $form['buttons']['#weight'] = 10;
  $form['#submit'][] = 'icontact_api_settings_submit';
  return $form;
}

function icontact_api_settings_validate($form, &$form_state) {
  switch ($form_state['values']['icontact_app_id']) {
    case ICONTACT_APP_ID:
      if (empty($form_state['values']['icontact_username'])) {
        form_set_error('icontact_username', t('!name field is required.', array('!name' => $form['live']['icontact_username']['#title'])));
      }
      if (empty($form_state['values']['icontact_password'])) {
        $password = variable_get('icontact_password', '');
        if ($password == '') {
          form_set_error('icontact_password', t('!name field is required.', array('!name' => $form['live']['icontact_password']['#title'])));
        }
        else {
          form_set_value($form['live']['icontact_password'], $password, $form_state);
        }
      }
      break;
    case ICONTACT_TEST_APP_ID:
      if (empty($form_state['values']['icontact_test_username'])) {
        form_set_error('icontact_test_username', t('!name field is required.', array('!name' => $form['sandbox']['icontact_test_username']['#title'])));
      }
      if (empty($form_state['values']['icontact_test_password'])) {
        $password = variable_get('icontact_test_password', '');
        if ($password == '') {
          form_set_error('icontact_test_password', t('!name field is required.', array('!name' => $form['sandbox']['icontact_test_password']['#title'])));
        }
        else {
          form_set_value($form['sandbox']['icontact_test_password'], $password, $form_state);
        }
      }
      break;
  }
}

function icontact_api_settings_submit($form, &$form_state) {
  $icontact = icontact_load();
  if (!$icontact) {
    drupal_set_message(t('Incorrect log in credentials.'), 'warning');
  }
}

function icontact_flush_cache() {
  cache_clear_all("*", 'cache_icontact', TRUE);
  drupal_goto();
}
