<?php
// $Id: freshbooks.admin.inc,v 1.1 2010/06/01 21:15:13 guypaddock Exp $

/**
 * @file
 *  The logic and form builder for the FreshBook settings page.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */

/**
 * Form builder callback for the FreshBooks settings form.
 */
function freshbooks_settings_form() {
  $form = array();

  $form['api_access'] = array(
    '#type'           => 'fieldset',
    '#title'          => t('FreshBooks API access'),
    '#description'    => t('Here you will need to specify the Service URL and Authentication token for '.
                           'your FreshBooks account, as described in the !docs.',
                           array('!docs' => l('FreshBooks API documentation', 'http://developers.freshbooks.com/'))),
  );

  $form['api_access'][FRESHBOOKS_VAR_API_URL] = array(
    '#type'             => 'textfield',
    '#title'            => t('API Service URL'),
    '#default_value'    => variable_get(FRESHBOOKS_VAR_API_URL, ''),
    '#element_validate' => array('freshbooks_trim_value'),
  );

  $form['api_access'][FRESHBOOKS_VAR_TOKEN] = array(
    '#type'             => 'textfield',
    '#title'            => t('API Authentication Token'),
    '#default_value'    => variable_get(FRESHBOOKS_VAR_TOKEN, ''),
    '#element_validate' => array('_freshbooks_trim_value'),
  );

  $form['api_access']['test'] = array(
    '#type'             => 'button',
    '#value'            => 'Test Settings',
    '#prefix'           => '<div id="freshbooks_test_result_wrapper"></div>',
    '#element_validate' => array('_freshbooks_settings_filter_button'), // Callback to prevent saving the button as a variable
    '#validate'         => array('_freshbooks_run_settings_test'),      // Only used when AJAX is not available
    '#ahah'   => array(
      'path'      => FRESHBOOKS_PATH_SETTINGS_TEST,
      'wrapper'   => 'freshbooks_test_result_wrapper',
      'method'    => 'replace',
      'effect'    => 'fade',
    ),
  );

  return system_settings_form($form);
}

/**
 * FAPI validation callback that trims the values the user enters, removing any whitespace that may have resulted from
 * copying and pasting values from the FreshBooks site.
 *
 * @param $element
 *        The form element containing a value that needs to be trimmed.
 *
 * @param $form_state
 *        The settings form state.
 */
function _freshbooks_trim_value($element, &$form_state) {
  form_set_value($element, trim($element['#value']), $form_state);
}

/**
 * The AHAH callback for the "Test Settings" button.
 *
 * This performs a simple test of the API settings that the user has provided, and returns the result as
 * a status message that is rendered in-place.
 */
function freshbooks_settings_test_callback() {
  _freshbooks_run_settings_test();

  // Render the resulting status messages
  $output = theme('status_messages');

  drupal_json(
    array(
      'status'  => TRUE,
      'data'    => $output,
    )
  );
}

/**
 * Runs the FreshBooks API settings test with the specified API URL and authorization token.
 *
 * @param $apiUrl
 *        The service URL for processing FreshBooks requests.
 *
 * @param $apiToken
 *        The unique authentication token FreshBooks assigns for authenticating requests.
 */
function _freshbooks_run_settings_test() {
  $apiUrl   = trim($_POST[FRESHBOOKS_VAR_API_URL]);
  $apiToken = trim($_POST[FRESHBOOKS_VAR_TOKEN]);

  if (empty($apiUrl) || empty($apiToken)) {
    drupal_set_message(t('Please specify both the API Service URL and API Authentication Token.'));
  }
  else {
    if (!freshbooks_is_loaded()) {
      // Load the FreshBooks API and attempt to initialize it with the data the user provided.
      $loaded = _freshbooks_load($apiUrl, $apiToken);
    }
    else {
      // Re-initialize the FreshBooks HTTP client with the data the user provided.
      FreshBooks_HttpClient::init($apiUrl, $apiToken);

      $loaded = TRUE;
    }

    if (!$loaded) {
      drupal_set_message(
        t('Could not load the FreshBooks-PHP library. Please ensure that it is !installed.',
          array('!installed' => l('installed properly', 'admin/reports/status'))),
        'error');
    }
    else {
      $client = new FreshBooks_Client();

      // Silence errors. The API doesn't seem to handle them well...
      @$client->listing($rows, $resultInfo);

      // Note that we handle the case where the user could have zero clients.
      if (empty($resultInfo['total']) && ($resultInfo['total'] !== 0)) {
        drupal_set_message(
          t('Could not connect to FreshBooks. Please check the API settings you have provided.'),
          'error');
      }
      else {
        drupal_set_message(
          t('Connected to FreshBooks successfully. The API settings you have provided appear correct; remember to '.
            'save them!'));
      }
    }
  }
}

/**
 * This function is registered as an #element_validate callback by any buttons that the FreshBooks settings form
 * generates, and is fired before the form submit handler, system_settings_form_submit(), to avoid the odd behavior of
 * saving button values as system variables.
 *
 * For example, this prevents the "Test Settings" button from being saved to the "variable" table with a variable name
 * of "test" and value of "Test Settings".
 *
 * Honestly, it feels like this behavior is a Drupal bug (see #753242).
 *
 * @param $element
 *        The form element being removed from the form state.
 *
 * @param $form_state
 *        A reference to the form state.
 */
function _freshbooks_settings_filter_button($element, &$form_state) {
  $elementName = $element['#parents'][0];

  unset($form_state['values'][$elementName]);
}