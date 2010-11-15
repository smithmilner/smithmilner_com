<?php
// $Id: icontact_ui.accounts.inc,v 1.1.2.1 2010/04/26 06:45:21 greenskin Exp $

/**
 * iContact accounts administrative section.
 */
function icontact_ui_accounts_list() {
  $icontact = icontact_load();
  return theme('icontact_ui_accounts_list', $icontact);
}

/**
 * iContact account form.
 */
function icontact_ui_accounts_form(&$form_state, $account = NULL) {
  icontact_ui_breadcrumb('account');

  $form = array();
  $form['account'] = array('#tree' => TRUE);

  if (empty($account)) {
    $icontact = icontact_load();
    $account = $icontact->initAccount();

    _user_password_dynamic_validation();
    $form['account']['userName'] = array(
      '#type' => 'textfield',
      '#title' => t('User name'),
      '#required' => TRUE
    );
    $form['account']['password'] = array(
      '#type' => 'password_confirm',
      '#required' => TRUE
    );
  }
  else {
    $form['account']['accountId'] = array(
      '#type' => 'value',
      '#value' => $account->accountId
    );
  }

  $form_state['account'] = &$account;

  $form['account']['subscriberLimit'] = array(
    '#type' => 'textfield',
    '#title' => t('Subscriber limit'),
    '#default_value' => $account->subscriberLimit,
    '#required' => TRUE
  );
  $form['account']['accountType'] = array(
    '#type' => 'value',
    '#value' => $account->accountType
  );

  $form['account']['firstName'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => $account->firstName,
    '#required' => TRUE
  );
  $form['account']['lastName'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => $account->lastName,
    '#required' => TRUE
  );
  $form['account']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $account->title,
  );
  $form['account']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => $account->phone,
  );
  $form['account']['fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#default_value' => $account->fax,
  );
  $form['account']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address'),
    '#default_value' => $account->email,
    '#required' => TRUE
  );
  $form['account']['companyName'] = array(
    '#type' => 'textfield',
    '#title' => t('Company name'),
    '#default_value' => $account->companyName
  );
  $form['account']['street'] = array(
    '#type' => 'textarea',
    '#title' => t('Street address'),
    '#default_value' => $account->street,
    '#rows' => 2
  );
  $form['account']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $account->city
  );
  $form['account']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State or Province'),
    '#default_value' => $account->state
  );
  $form['account']['postalCode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => $account->postalCode
  );
  /*$form['country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#default_value' => ''
  );*/

  $form['account']['billing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Billing'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['account']['billing']['billingStreet'] = array(
    '#type' => 'textarea',
    '#title' => t('Street address'),
    '#default_value' => $account->billingStreet,
    '#rows' => 2
  );
  $form['account']['billing']['billingCity'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $account->billingCity
  );
  $form['account']['billing']['billingState'] = array(
    '#type' => 'textfield',
    '#title' => t('State or Province'),
    '#default_value' => $account->billingState
  );
  $form['account']['billing']['billingPostalCode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => $account->billingPostalCode
  );
  /*$form['billing']['billingCountry'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#default_value' => ''
  );*/
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  return $form;
}

function icontact_ui_accounts_form_submit($form, &$form_state) {
  if (isset($form_state['values']['account']['accountId']) && $form_state['values']['account']['accountId'] > 0) {
    if ($form_state['account']->update($form_state['values']['account'])) {
      drupal_set_message(t('Account successfully updated.'));
    }
  }
  else {
    drupal_set_message(t('Account successfully added.'));
    $form_state['redirect'] = array('admin/icontact/accounts');
  }
}

/*******************************************************************************
 * Theme Functions
 ******************************************************************************/

function theme_icontact_ui_accounts_list($icontact) {
  $headers = array(
    t('First name'),
    t('Last name'),
    t('Email address'),
    t('Actions')
  );
  $rows = array();
  $actions = array(
    'edit' => array(
      'title' => t('Edit'),
      'href' => '',
      'query' => drupal_get_destination()
    )
  );
  $account_ids = $icontact->getResourceIds('accounts');
  if (!empty($account_ids)) {
      foreach ($account_ids as $id) {
        $account = &$icontact->getAccount($id);

        $actions['edit']['href'] = 'admin/icontact/accounts/'. $account->accountId .'/edit';
        $actions['clientfolders'] = array(
          'title' => t('Client folders'),
          'href' => 'admin/icontact/clientfolders/'. $account->accountId
        );
        $actions['users'] = array(
          'title' => t('Users'),
          'href' => 'admin/icontact/users/'. $account->accountId
        );
        $row = array(
          array('data' => (string)$account->firstName),
          array('data' => (string)$account->lastName),
          array('data' => (string)$account->email),
          array('data' => theme('links', $actions))
        );
        $rows[] = array('data' => $row);
      }
  }

  $output = '<div>'. theme('table', $headers, $rows) .'</div>';
  return $output;
}
