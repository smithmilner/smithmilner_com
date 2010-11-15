<?php
// $Id: icontact_ui.messages.inc,v 1.1.2.4 2010/04/27 00:36:06 greenskin Exp $

/*******************************************************************************
 * Callback Functions, Forms, and Tables
 ******************************************************************************/

/**
 * iContact accounts administrative section.
 */
function icontact_ui_messages_list($clientfolder) {
  return theme('icontact_ui_messages_list', $clientfolder);
}

function icontact_ui_messages_form(&$form_state, $message) {
  if (get_class($message) == 'iContactClientFolder') {
    $message = $message->initMessage();
  }

  icontact_ui_breadcrumb('message', array('accountId' => $message->accountId, 'clientFolderId' => $message->clientFolderId));

  $form_state['message'] = $message;

  $form = array('message' => array('#tree' => TRUE));

  if (isset($message->messageId) && $message->messageId > 0) {
    $form['message']['messageId'] = array(
      '#type' => 'hidden',
      '#value' => $message->messageId
    );
  }

  $form['message']['messageType'] = array(
    '#type' => 'select',
    '#title' => t('Message type'),
    '#default_value' => $message->messageType,
    '#options' => array(
      'normal' => t('Normal'),
      'autoresponder' => t('Auto-responder'),
      'confirmation' => t('Confirmation'),
      'welcome' => t('Welcome')
    ),
    '#required' => TRUE
  );
  $form['message']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => $message->subject,
    '#required' => TRUE
  );

  if (module_exists('icontact_campaigns')) {
    $campaign_options = array();
    if (!empty($campaign_options)) {
      $form['message']['campaignId'] = array(
        '#type' => 'select',
        '#title' => t('Campaign'),
        '#default_value' => $message->campaignId,
        '#options' => array()
      );
    }
  }

  $form['message']['htmlBody'] = array(
    '#type' => 'textarea',
    '#title' => t('HTML body'),
    '#default_value' => $message->htmlBody
  );
  $form['message']['textBody'] = array(
    '#type' => 'textarea',
    '#title' => t('Text body'),
    '#default_value' => $message->textBody
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  return $form;
}

function icontact_ui_messages_form_submit($form, &$form_state) {
  if (isset($form_state['values']['message']['messageId']) && $form_state['values']['message']['messageId'] > 0) {
    if ($form_state['message']->update($form_state['values']['message'])) {
      drupal_set_message(t('Message successfully updated.'));
    }
  }
  else {
    drupal_set_message(t('Message successfully created.'));
    $form_state['redirect'] = array('admin/icontact/messages', array('clientFolderId' => $message->clientFolderId));
  }
}

/*******************************************************************************
 * Theme Functions
 ******************************************************************************/

function theme_icontact_ui_messages_list($clientfolder) {
  icontact_ui_breadcrumb('clientFolder', array('accountId' => $clientfolder->accountId));

  $output = '';
  $headers = array(
    t('Type'),
    t('Subject'),
    t('Created'),
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

  $message_ids = $clientfolder->getResourceIds('messages');
  foreach ($message_ids as $messageId) {
    $message = $clientfolder->getMessage($messageId);

    $actions['edit']['href'] = 'admin/icontact/messages/'. $message->accountId .'/'. $message->clientFolderId .'/'. $message->messageId .'/edit';
    $row = array(
      array('data' => check_plain($message->messageType)),
      array('data' => check_plain($message->subject)),
      array('data' => format_date(strtotime($message->createDate), 'small')),
      array('data' => theme('links', $actions))
    );
    $rows[] = array('data' => $row);
  }

  $output = '<div>'. theme('table', $headers, $rows) .'</div>';
  return $output;
}
