<?php
// $Id: icontact_ui.contacts.inc,v 1.1.2.5 2010/05/03 19:49:35 greenskin Exp $

/**
 * iContact accounts administrative section.
 */
function icontact_ui_contacts_list($clientfolder) {
  icontact_ui_breadcrumb('clientFolder', array('accountId' => $clientfolder->accountId));

  $filter = (isset($_SESSION['icontact_ui_contacts_filter'])) ? $_SESSION['icontact_ui_contacts_filter'] : NULL;
  $contacts = (!empty($filter)) ? $clientfolder->requestContacts($filter) : $clientfolder->requestContacts();;

  if (!empty($contacts) && count($contacts) >= 1) {
    return drupal_get_form('icontact_ui_contacts_filter_form') . theme('icontact_ui_contacts_list', $clientfolder, $contacts);
  }
  if ($filter != NULL) {
    return drupal_get_form('icontact_ui_contacts_filter_form') . t('Search returned no contacts');
  }
  return (empty($filter)) ? t('No contacts have yet been added.') : t('Search returned no contacts');
}

function icontact_ui_contacts_filter_form() {
  drupal_add_css(drupal_get_path('module', 'icontact_ui') .'/css/contacts_filter.css');

  $session = &$_SESSION['icontact_ui_contacts_filter'];
  $session = is_array($session) ? $session : array();
  $filters = icontact_ui_contacts_filters();
  $textfields = array('bounceCount', 'business', 'city', 'contactId', 'createDate', 'email', 'fax', 'firstName', 'lastName', 'phone', 'postalCode', 'prefix', 'state', 'street', 'street2', 'suffix');

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only contacts where'),
    '#collapsible' => TRUE,
    '#collapsed' => (empty($session)) ? TRUE : FALSE,
    '#theme' => 'user_filters'
  );
  foreach ($session as $type => $value) {
    if (in_array($type, $textfields)) {
      $params = array('%property' => $filters[$type]['title'] , '%value' => $value);
    }
    else {
      // Merge an array of arrays into one if necessary.
      $options = $filters[$type]['options'];
      $params = array('%property' => $filters[$type]['title'] , '%value' => $options[$value]);
    }

    if ($i++ > 0) {
      $form['filters']['current'][] = array('#value' => t('<em>and</em> where <strong>%property</strong> is <strong>%value</strong>', $params));
    }
    else {
      $form['filters']['current'][] = array('#value' => t('<strong>%property</strong> is <strong>%value</strong>', $params));
    }
  }

  foreach ($filters as $key => $filter) {
    $names[$key] = $filter['title'];
    if (in_array($key, $textfields)) {
      $form['filters']['status'][$key] = array(
        '#type' => 'textfield',
        '#size' => 20
      );
    }
    else {
      $form['filters']['status'][$key] = array(
        '#type' => 'select',
        '#options' => $filter['options'],
      );
    }
  }

  $form['filters']['filter'] = array(
    '#type' => 'radios',
    '#options' => $names,
  );
  $form['filters']['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => (count($session) ? t('Refine') : t('Filter')),
  );
  if (count($session)) {
    $form['filters']['buttons']['undo'] = array(
      '#type' => 'submit',
      '#value' => t('Undo'),
    );
    $form['filters']['buttons']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
    );
  }

  drupal_add_js('misc/form.js', 'core');

  return $form;
}

function icontact_ui_contacts_filter_form_validate($form, &$form_state) {
  $textfields = array('bounceCount', 'business', 'city', 'contactId', 'createDate', 'email', 'fax', 'firstName', 'lastName', 'phone', 'postalCode', 'prefix', 'state', 'street', 'street2', 'suffix');
  if (isset($form_state['values']['filter'])) {
    $filter = $form_state['values']['filter'];
    if (in_array($filter, $textfields)) {
      switch ($filter) {
        case 'bounceCount':
        case 'contactId':
          if (!is_numeric($form_state['values'][$filter]) || empty($form_state['values'][$filter])) {
            $error = t('Numbers only for contact ID');
          }
          break;
        case 'email':
          if (!valid_email_address($form_state['values'][$filter])) {
            $error = t('Invalid email address.');
          }
          break;
        default:
          if (empty($form_state['values'][$filter])) {
            $error = t('No criteria was specified.');
          }
          break;
      }
      if (isset($error)) {
        form_set_error($filter, $error);
      }
    }
  }
}

function icontact_ui_contacts_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = icontact_ui_contacts_filters();
  $textfields = array('bounceCount', 'business', 'city', 'contactId', 'createDate', 'email', 'fax', 'firstName', 'lastName', 'phone', 'postalCode', 'prefix', 'state', 'street', 'street2', 'suffix');

  switch ($op) {
    case t('Filter'): case t('Refine'):
      if (isset($form_state['values']['filter'])) {
        $filter = $form_state['values']['filter'];
        if (in_array($filter, $textfields)) {
          $_SESSION['icontact_ui_contacts_filter'][$filter] = $form_state['values'][$filter];
        }
        else {
          // Merge an array of arrays into one if necessary.
          $options = $filters[$filter]['options'];
          if (isset($options[$form_state['values'][$filter]])) {
            $_SESSION['icontact_ui_contacts_filter'][$filter] = $form_state['values'][$filter];
          }
        }
      }
      break;
    case t('Undo'):
      array_pop($_SESSION['icontact_ui_contacts_filter']);
      break;
    case t('Reset'):
      $_SESSION['icontact_ui_contacts_filter'] = array();
      break;
    case t('Update'):
      return;
  }
}

function icontact_ui_contacts_form(&$form_state, $contact) {
  if (get_class($contact) == 'iContactClientFolder') {
    $contact = new iContactContact($contact);
  }

  icontact_ui_breadcrumb('contact', array('accountId' => $contact->accountId, 'clientFolderId' => $contact->clientFolderId));

  if (is_array($contact)) $contact = (object)$contact;

  $form_state['contact'] = $contact;
  $form = array('contact' => array('#tree' => TRUE));
  if (isset($contact->contactId) && $contact->contactId > 0) {
    $form['contact']['contactId'] = array(
      '#type' => 'hidden',
      '#value' => $contact->contactId
    );
  }
  $form['contact']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address'),
    '#default_value' => $contact->email,
    '#required' => TRUE
  );
  switch ($contact->status) {
    case 'donotcontact':
    case 'pending':
    case 'invitable':
      $form['contact']['status'] = array(
        '#type' => 'item',
        '#title' => t('Status'),
        '#value' => $contact->status
      );
      break;
    case 'bounced':
      $form['contact']['status'] = array(
        '#type' => 'select',
        '#title' => t('Status'),
        '#default_value' => $contact->status,
        '#options' => array('bounced' => t('Bounced'), 'normal' => t('Normal'))
      );
    default:
      $form['contact']['status'] = array(
        '#type' => 'select',
        '#title' => t('Status'),
        '#default_value' => $contact->status,
        '#options' => array('normal' => t('Normal'), 'donotcontact' => t('Do not contact'))
      );
      break;
  }
  $form['contact']['prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix'),
    '#default_value' => $contact->prefix
  );
  $form['contact']['firstName'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => $contact->firstName
  );
  $form['contact']['lastName'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => $contact->lastName
  );
  $form['contact']['suffix'] = array(
    '#type' => 'textfield',
    '#title' => t('Suffix'),
    '#default_value' => $contact->suffix
  );
  $form['contact']['street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street 1'),
    '#default_value' => $contact->street
  );
  $form['contact']['street2'] = array(
    '#type' => 'textfield',
    '#title' => t('Street 2'),
    '#default_value' => $contact->street2
  );
  $form['contact']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $contact->city
  );
  $form['contact']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State or Providence'),
    '#default_value' => $contact->state
  );
  $form['contact']['postalCode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => $contact->postalCode
  );
  $form['contact']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => $contact->phone
  );
  $form['contact']['fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#default_value' => $contact->fax
  );
  $form['contact']['business'] = array(
    '#type' => 'textfield',
    '#title' => t('Business'),
    '#default_value' => $contact->business
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  return $form;
}

function icontact_ui_contacts_form_validate($form, &$form_state) {
  $contact = $form_state['values']['contact'];
  switch ($contact['status']) {
    case 'bounced':
      form_set_value($form['contact']['status'], NULL, $form_state);
      break;
  }
}

function icontact_ui_contacts_form_submit($form, &$form_state) {
  $contact = $form_state['contact'];

  if ($result = $contact->save($form_state['values']['contact'])) {
    if (isset($form_state['values']['contact']['contactId']) && $form_state['values']['contact']['contactId'] > 0) {
      drupal_set_message(t('Contact successfully updated.'));
    }
    else {
      drupal_set_message(t('Contact successfully added.'));
      $form_state['redirect'] = array('admin/icontact/contacts', array('clientFolderId' => $_GET['clientFolderId']));
    }
  }
}

function icontact_ui_contacts_history($contact) {
  $data = $contact->requestActions();
  if (isset($data['actions']) && !empty($data['actions']) && $actions = $data['actions']) {
    icontact_ui_breadcrumb('contact', array('accountId' => $contact->accountId, 'clientFolderId' => $contact->clientFolderId));
    return theme('icontact_ui_contacts_history', $contact, $actions);
  }
  return t('No actions have yet been recorded.');
}

function icontact_ui_contacts_filters() {
  $filters = array();
  $statuses = array(
    'normal' => t('Normal'),
    'donotcontact' => t('Do not contact'),
    'bounced' => t('Bounced'),
    'invitable' => t('Invitable'),
    'pending' => t('Pending'),
    'unlisted' => t('Unlisted')
  );
  $filters['status'] = array(
    'title' => t('Status'),
    'options' => $statuses
  );
  $filters['bounceCount'] = array(
    'title' => t('Bounce count')
  );
  $filters['business'] = array(
    'title' => t('Business')
  );
  $filters['city'] = array(
    'title' => t('City')
  );
  $filters['contactId'] = array(
    'title' => t('Contact ID')
  );
  $filters['createDate'] = array(
    'title' => t('Create date')
  );
  $filters['email'] = array(
    'title' => t('Email')
  );
  $filters['fax'] = array(
    'title' => t('Fax')
  );
  $filters['firstName'] = array(
    'title' => t('First name')
  );
  $filters['lastName'] = array(
    'title' => t('Last name')
  );
  $filters['phone'] = array(
    'title' => t('Phone')
  );
  $filters['postalCode'] = array(
    'title' => t('Postal code')
  );
  $filters['prefix'] = array(
    'title' => t('Prefix')
  );
  $filters['state'] = array(
    'title' => t('State or Providence')
  );
  $filters['street'] = array(
    'title' => t('Street')
  );
  $filters['street2'] = array(
    'title' => t('Street 2')
  );
  $filters['suffix'] = array(
    'title' => t('Suffix')
  );
  return $filters;
}

/*******************************************************************************
 * Theme Functions
 ******************************************************************************/

function theme_icontact_ui_contacts_list($clientfolder, $contacts) {
  $output = '';
  $headers = array(
    t('Email address'),
    t('First name'),
    t('Last name'),
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
    $contact = &$clientfolder->initContact($contactId);

    $actions['edit']['href'] = 'admin/icontact/contacts/'. $clientfolder->accountId .'/'. $clientfolder->clientFolderId .'/'. $contact->contactId .'/edit';
    $actions['history']['href'] = 'admin/icontact/contacts/'. $clientfolder->accountId .'/'. $clientfolder->clientFolderId .'/'. $contact->contactId .'/history';
    $row = array(
      array('data' => $contact->email),
      array('data' => $contact->firstName),
      array('data' => $contact->lastName),
      array('data' => theme('links', $actions))
    );
    $rows[] = array('data' => $row);
  }

  $output = '<div>'. theme('table', $headers, $rows) .'</div>';
  return $output;
}

function theme_icontact_ui_contacts_history($contact, $actions) {
  $headers = array(
    t('Type'),
    t('Time'),
    t('Details')
  );
  $rows = array();

  foreach ($actions->children() as $action) {
    $details = array();

    foreach ($action->details->children() as $key => $detail) {
      switch ($key) {
        case 'listId':
        if ($clientfolder = $contact->getClientFolder()) {
          $list = $clientfolder->getList((int)$detail);
        }
          if (!empty($list)) {
            $link = l($list->name, 'admin/icontact/lists/'. $list->accountId .'/'. $list->clientFolderId .'/'. $list->listId .'/view');
            $details[] = '<strong>List:</strong> '. $link;
          }
          else {
            $details[] = '<strong>'. $key .':</strong> '. $detail;
          }
          break;
        default:
          $details[] = '<strong>'. $key .':</strong> '. $detail;
          break;
      }
    }
    $row = array(
      array('data' => $action->actionType),
      array('data' => format_date(strtotime($action->actionTime), 'large')),
      array('data' => theme('item_list', $details))
    );
    $rows[] = array('data' => $row);
  }

  $output = '<div>'. theme('table', $headers, $rows) .'</div>';
  return $output;
}
