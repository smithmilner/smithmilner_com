<?php
// $Id: icontact_subscribe.admin.inc,v 1.1.2.1 2010/05/03 19:49:35 greenskin Exp $

/*******************************************************************************
 * Callback Functions, Forms, and Tables
 ******************************************************************************/

function icontact_subscribe_admin_form(&$form_state) {
  $icontact = icontact_load();
  if (!$icontact) {
    return array('#type' => 'item', '#value' => t('The iContact object is not available.'));
  }

  $form_state['lists'] = $options = array();
  $account_ids = $icontact->getResourceIds('accounts');
  foreach ($icontact->getResourceIds('accounts') as $accountId) {
    if ($account = $icontact->getAccount($accountId)) {
      foreach ($account->getResourceIds('clientFolders') as $clientFolderId) {
        if ($clientfolder = $account->getClientFolder($clientFolderId)) {
          foreach ($clientfolder->getResourceIds('lists') as $listId) {
            if ($list = $clientfolder->getList($listId)) {
              $form_state['lists'][$listId] = array('accountId' => $list->accountId, 'clientFolderId' => $list->clientFolderId, 'listId' => $listId, 'name' => $list->name);
              $options[$listId] = $list->name;
            }
          }
        }
      }
    }
  }

  // Determine enabled blocks.
  $default_value = array();
  foreach (variable_get('icontact_subscribe_enabled_blocks', array()) as $list) {
    $default_value[$list['listId']] = $list['listId'];
  }

  $form['icontact_subscribe_enabled_blocks'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Subscribe blocks'),
    '#description' => t('Choose which lists to provide a subscribe block for.'),
    '#default_value' => $default_value,
    '#options' => $options
  );

  $form['#submit'][] = '_icontact_subscribe_admin_form_submit';

  return system_settings_form($form);
}

function icontact_subscribe_admin_form_validate($form, &$form_state) {
  $blocks = array();
  foreach (array_filter($form_state['values']['icontact_subscribe_enabled_blocks']) as $key => $list) {
    $blocks[$key] = $form_state['lists'][$key];
  }

  form_set_value($form['icontact_subscribe_enabled_blocks'], $blocks, $form_state);
}

function _icontact_subscribe_admin_form_submit($form, &$form_state) {
  foreach ($form_state['values']['icontact_subscribe_enabled_blocks'] as $key => $list) {
    if (!is_array($list) || empty($list)) {
      db_query("UPDATE {blocks} SET status = %d WHERE module = '%s' AND delta = %d", 0, 'icontact_subscribe', $key);
    }
    else {
      db_query("UPDATE {blocks} SET status = %d WHERE module = '%s' AND delta = %d", 1, 'icontact_subscribe', $key);
    }
  }
}
