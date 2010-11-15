<?php
// $Id: icontact_ui.lists.inc,v 1.1.2.3 2010/04/27 00:36:06 greenskin Exp $

/*******************************************************************************
 * Callback Functions, Forms, and Tables
 ******************************************************************************/

/**
 * iContact lists administrative section.
 */
function icontact_ui_lists_list($clientfolder) {
  return theme('icontact_ui_lists_list', $clientfolder);
}

function icontact_ui_lists_view($list) {
  $contacts = array();
  foreach ($list->iContact->accounts[$list->accountId]->clientFolders[$list->clientFolderId]->contacts as $contactId => $contact) {
    if (isset($list->iContact->accounts[$list->accountId]->clientFolders[$list->clientFolderId]->subscriptions[$list->listId .'_'. $contactId])) {
      $contacts[$contactId] = $contactId;
    }
  }
  return theme('icontact_ui_lists_view', $list, $contacts);
}

function icontact_ui_lists_form(&$form_state, $list) {
  if (get_class($list) == 'iContactClientFolder') {
    $list = new iContactList($list);
  }

  icontact_ui_breadcrumb('list', array('accountId' => $list->accountId, 'clientFolderId' => $list->clientFolderId));

  if (is_array($list)) $list = (object)$list;

  $form_state['list'] = $list;
  $form = array('list' => array('#tree' => TRUE));
  if (isset($list->listId) && $list->listId > 0) {
    $form['list']['listId'] = array(
      '#type' => 'hidden',
      '#value' => $list->listId
    );
  }
  $form['list']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $list->name,
    '#required' => TRUE
  );
  $form['list']['emailOwnerOnChange'] = array(
    '#type' => 'checkbox',
    '#title' => t('Email owner on change'),
    '#default_value' => $list->emailOwnerOnChange
  );
  $form['list']['welcomeOnManualAdd'] = array(
    '#type' => 'checkbox',
    '#title' => t('Welcome on manual add'),
    '#default_value' => $list->welcomeOnManualAdd
  );
  $form['list']['welcomeOnSignupAdd'] = array(
    '#type' => 'checkbox',
    '#title' => t('Welcome on signup add'),
    '#default_value' => $list->welcomeOnSignupAdd
  );
  $message_options = array();
  foreach ($list->clientFolder->listMessages('welcome') as $message) {
    $message_options[$message['messageId']] = $message['subject'];
  }
  $form['list']['welcomeMessageId'] = array(
    '#type' => 'select',
    '#title' => t('Welcome message'),
    '#default_value' => $list->welcomeMessageId,
    '#options' => $message_options,
    '#required' => TRUE
  );
  $form['list']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $list->description
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  return $form;
}

function icontact_ui_lists_form_submit($form, &$form_state) {
  $list = $form_state['list'];

  if ($result = $list->save($form_state['values']['list'])) {
    if (isset($form_state['values']['list']['listId']) && $form_state['values']['list']['listId'] > 0) {
      drupal_set_message(t('List successfully updated.'));
    }
    else {
      drupal_set_message(t('List successfully created.'));
      $form_state['redirect'] = array('admin/icontact/lists', array('clientFolderId' => $list->clientFolder->clientFolderId));
    }
  }
}

/*******************************************************************************
 * Theme Functions
 ******************************************************************************/

function theme_icontact_ui_lists_list($clientfolder) {
  icontact_ui_breadcrumb('clientFolder', array('accountId' => $clientfolder->accountId));

  $output = '';
  $headers = array(
    t('Name'),
    t('Actions')
  );
  $rows = array();
  $destination = drupal_get_destination();
  $actions = array(
    'view' => array(
      'title' => t('View contacts'),
      'href' => '',
      'query' => $destination
    ),
    'edit' => array(
      'title' => t('Edit'),
      'href' => '',
      'query' => $destination
    )
  );

  $list_ids = $clientfolder->getResourceIds('lists');
  foreach ($list_ids as $listId) {
    $list = $clientfolder->getList($listId);

    $actions['view']['href'] = 'admin/icontact/lists/'. $list->accountId .'/'. $list->clientFolderId .'/'. $list->listId .'/view';
    $actions['edit']['href'] = 'admin/icontact/lists/'. $list->accountId .'/'. $list->clientFolderId .'/'. $list->listId .'/edit';
    $row = array(
      array('data' => check_plain($list->name)),
      array('data' => theme('links', $actions))
    );
    $rows[] = array('data' => $row);
  }

  $output = '<div>'. theme('table', $headers, $rows) .'</div>';
  return $output;
}

function theme_icontact_ui_lists_view($list, $contacts) {
  icontact_ui_breadcrumb('list', array('accountId' => $list->accountId, 'clientFolderId' => $list->clientFolderId));

  $headers = array(
    t('First name'),
    t('Last name'),
    t('Status'),
    t('Actions')
  );
  $rows = array();
  $actions = array(
    'edit' => array(
      'title' => t('Edit'),
      'href' => '',
      'query' => drupal_get_destination()
    ),
    'history' => array(
      'title' => t('History'),
      'href' => ''
    )
  );
  foreach ($contacts as $contactId) {
    $actions['edit']['href'] = 'admin/icontact/contacts/'. $contactId .'/edit';
    $actions['history']['href'] = 'admin/icontact/contacts/'. $contactId .'/history';
    $row = array(
      array('data' => $list->iContact->accounts[$list->accountId]->clientFolders[$list->clientFolderId]->contacts[$contactId]->firstName),
      array('data' => $list->iContact->accounts[$list->accountId]->clientFolders[$list->clientFolderId]->contacts[$contactId]->lastName),
      array('data' => $list->iContact->accounts[$list->accountId]->clientFolders[$list->clientFolderId]->subscriptions[$list->listId .'_'. $contactId]->status),
      array('data' => theme('links', $actions))
    );
    $rows[] = $row;
  }

  $output = theme('table', $headers, $rows);
  return $output;
}
