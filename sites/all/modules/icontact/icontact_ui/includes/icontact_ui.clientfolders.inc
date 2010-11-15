<?php
// $Id: icontact_ui.clientfolders.inc,v 1.1.2.2 2010/05/03 19:49:35 greenskin Exp $

/**
 * iContact client folder administrative section.
 */
function icontact_ui_clientfolders_list(&$account) {
  return theme('icontact_ui_clientfolders_list', $account);
}

function icontact_ui_clientfolders_form(&$form_state, $clientFolder) {
  if (get_class($clientFolder) == 'iContactAccount') {
    $user = new iContactClientFolder($clientFolder);
  }

  icontact_ui_breadcrumb('clientFolder', array('accountId' => $clientFolder->account->accountId));

  if (is_array($clientFolder)) $clientFolder = (object)$clientFolder;

  $form_state['clientFolder'] = $clientFolder;
  $form = array('clientFolder' => array('#tree' => TRUE));
  if (isset($clientFolder->clientFolderId) && $clientFolder->clientFolderId > 0) {
    $form['clientFolder']['clientFolderId'] = array(
      '#type' => 'hidden',
      '#value' => $clientFolder->clientFolderId
    );
  }
  $form['clientFolder']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $clientFolder->name,
    '#required' => TRUE
  );
  $form['clientFolder']['fromName'] = array(
    '#type' => 'textfield',
    '#title' => t('From name'),
    '#default_value' => $clientFolder->fromName,
    '#required' => TRUE
  );
  $form['clientFolder']['fromEmail'] = array(
    '#type' => 'textfield',
    '#title' => t('From email'),
    '#default_value' => $clientFolder->fromEmail,
    '#required' => TRUE
  );
  $form['clientFolder']['street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street'),
    '#default_value' => $clientFolder->street,
    '#required' => TRUE
  );
  $form['clientFolder']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $clientFolder->city,
    '#required' => TRUE
  );
  $form['clientFolder']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#default_value' => $clientFolder->state,
    '#required' => TRUE
  );
  $form['clientFolder']['postalCode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => $clientFolder->postalCode,
    '#required' => TRUE
  );
  $form['clientFolder']['country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#default_value' => $clientFolder->country,
    '#required' => TRUE
  );
  /*$form['clientFolder']['logoId'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $clientFolder->logoId
  );*/
  $form['clientFolder']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => $clientFolder->enabled
  );
  $form['clientFolder']['footerLogoUrl'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer logo URL'),
    '#default_value' => $clientFolder->footerLogoUrl
  );
  $form['clientFolder']['useLogoInFooter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use logo in footer'),
    '#default_value' => $clientFolder->useLogoInFooter
  );
  $form['clientFolder']['emailRecipient'] = array(
    '#type' => 'textfield',
    '#title' => t('Email recipient'),
    '#default_value' => $clientFolder->emailRecipient
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  return $form;
}

function icontact_ui_clientFolders_form_submit($form, &$form_state) {
  $clientFolder = $form_state['clientFolder'];

  if ($result = $clientFolder->save($form_state['values']['clientFolder'])) {
    if (isset($form_state['values']['clientFolder']['clientFolderId']) && $form_state['values']['clientFolder']['clientFolderId'] > 0) {
      drupal_set_message(t('Client folder successfully updated.'));
    }
    else {
      drupal_set_message(t('Client folder successfully added.'));
      $form_state['redirect'] = array('admin/icontact/clientFolder', array('accountId' => $clientFolder->account->accountId));
    }
  }
}

/*******************************************************************************
 * Theme Functions
 ******************************************************************************/

function theme_icontact_ui_clientfolders_list($account) {
  icontact_ui_breadcrumb('icontact');

  $headers = array(
    t('ID'),
    t('Actions')
  );
  $rows = array();
  $actions = array(
    /*'edit' => array(
      'title' => t('Edit'),
      'href' => '',
      'query' => drupal_get_destination()
    )*/
  );
  $clientfolder_ids = $account->getResourceIds('clientFolders');
  if (!empty($clientfolder_ids)) {
    foreach ($clientfolder_ids as $id) {
      $clientFolder = &$account->getClientFolder($id);

      // $actions['edit']['href'] = 'admin/icontact/clientfolders/'. $clientFolder->clientFolderId .'/edit';
      $actions['contacts'] = array(
        'title' => t('Contacts'),
        'href' => 'admin/icontact/contacts/'. $clientFolder->accountId .'/'. $clientFolder->clientFolderId
      );
      $actions['lists'] = array(
        'title' => t('Lists'),
        'href' => 'admin/icontact/lists/'. $clientFolder->accountId .'/'. $clientFolder->clientFolderId
      );
      // Not using 'messages' as the key since it is used as a class
      $actions[] = array(
        'title' => t('Messages'),
        'href' => 'admin/icontact/messages/'. $clientFolder->accountId .'/'. $clientFolder->clientFolderId
      );
      $row = array(
        array('data' => (string)$clientFolder->clientFolderId),
        array('data' => theme('links', $actions))
      );
      $rows[] = array('data' => $row);
    }
  }

  $output = '<div>'. theme('table', $headers, $rows) .'</div>';
  return $output;
}
