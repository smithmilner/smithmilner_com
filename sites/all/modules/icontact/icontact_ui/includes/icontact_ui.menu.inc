<?php
// $Id: icontact_ui.menu.inc,v 1.1.2.6 2010/04/27 00:36:06 greenskin Exp $

function icontact_ui_accounts_menu_items() {
  $items['admin/icontact'] = array(
    'title' => 'iContact accounts',
    'description' => 'Manage iContact accounts.',
    'page callback' => 'icontact_ui_accounts_list',
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact accounts'),
    'file' => 'includes/icontact_ui.accounts.inc',
    'weight' => -10
  );
  $items['admin/icontact/accounts'] = array(
    'title' => 'Accounts',
    'description' => 'Manage iContact accounts.',
    'page callback' => 'icontact_ui_accounts_list',
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact accounts'),
    'file' => 'includes/icontact_ui.accounts.inc',
    'type' => MENU_DEFAULT_LOCAL_TASK
  );
  /*$items['admin/icontact/accounts/add'] = array(
    'title' => 'Add account',
    'description' => 'Add an iContact account.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_accounts_form'),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact accounts'),
    'file' => 'includes/icontact_ui.accounts.inc',
    'type' => MENU_LOCAL_TASK
  );*/
  $items['admin/icontact/accounts/%icontact_account/edit'] = array(
    'title' => 'Account',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_accounts_form', 3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact accounts'),
    'file' => 'includes/icontact_ui.accounts.inc',
    'type' => MENU_CALLBACK
  );
  return $items;
}

function icontact_ui_clientfolders_menu_items() {
  $items['admin/icontact/clientfolders/%icontact_account'] = array(
    'title' => 'Client folders',
    'description' => 'Manage iContact client folders.',
    'page callback' => 'icontact_ui_clientfolders_list',
    'page arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact client folders'),
    'file' => 'includes/icontact_ui.clientfolders.inc',
    'type' => MENU_CALLBACK
  );
  /*$items['admin/icontact/clientfolders/add'] = array(
    'title' => 'Add client folder',
    'description' => 'Add an iContact client folders.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_clientfolders_form'),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact client folders'),
    'file' => 'includes/icontact_ui.clientfolders.inc',
    'type' => MENU_CALLBACK
  );*/
  $items['admin/icontact/clientfolders/%/%icontact_clientfolder/edit'] = array(
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_clientfolders_form', 4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact client folders'),
    'file' => 'includes/icontact_ui.clientfolders.inc',
    'type' => MENU_CALLBACK
  );
  return $items;
}

function icontact_ui_users_menu_items() {
  $items['admin/icontact/users/%icontact_account'] = array(
    'title' => 'Client folders',
    'description' => 'Manage iContact users.',
    'page callback' => 'icontact_ui_users_list',
    'page arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact users'),
    'file' => 'includes/icontact_ui.users.inc',
    'type' => MENU_CALLBACK
  );
  /*$items['admin/icontact/users/add'] = array(
    'title' => 'Add client folder',
    'description' => 'Add an iContact client folders.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_clientfolders_form'),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact client folders'),
    'file' => 'includes/icontact_ui.clientfolders.inc',
    'type' => MENU_CALLBACK
  );*/
  $items['admin/icontact/users/%/%icontact_user/edit'] = array(
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_users_form', 4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact users'),
    'file' => 'includes/icontact_ui.users.inc',
    'type' => MENU_CALLBACK
  );
  return $items;
}

function icontact_ui_contacts_menu_items() {
  $items['admin/icontact/contacts/%/%icontact_clientfolder'] = array(
    'title' => 'Contacts',
    'description' => 'Manage iContact contacts.',
    'page callback' => 'icontact_ui_contacts_list',
    'page arguments' => array(4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact contacts'),
    'file' => 'includes/icontact_ui.contacts.inc',
    'type' => MENU_CALLBACK
  );
  $items['admin/icontact/contacts/%/%icontact_clientfolder/list'] = array(
    'title' => 'List',
    'description' => 'Manage iContact contacts.',
    'page callback' => 'icontact_ui_contacts_list',
    'page arguments' => array(4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact contacts'),
    'file' => 'includes/icontact_ui.contacts.inc',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10
  );
  $items['admin/icontact/contacts/%/%icontact_clientfolder/add'] = array(
    'title' => 'Add',
    'description' => 'Add an iContact contact.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_contacts_form', 4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact contacts'),
    'file' => 'includes/icontact_ui.contacts.inc',
    'type' => MENU_LOCAL_TASK
  );
  $items['admin/icontact/contacts/%/%/%icontact_contact/edit'] = array(
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_contacts_form', 5),
    'load arguments' => array(3, 4),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact contacts'),
    'file' => 'includes/icontact_ui.contacts.inc',
    'type' => MENU_CALLBACK
  );
  $items['admin/icontact/contacts/%/%/%icontact_contact/history'] = array(
    'title' => 'Contact history',
    'page callback' => 'icontact_ui_contacts_history',
    'page arguments' => array(5),
    'load arguments' => array(3, 4),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('view iContact contact history'),
    'file' => 'includes/icontact_ui.contacts.inc',
    'type' => MENU_CALLBACK
  );
  return $items;
}

function icontact_ui_lists_menu_items() {
  $items['admin/icontact/lists/%/%icontact_clientfolder'] = array(
    'title' => 'Lists',
    'description' => 'Manage iContact lists.',
    'page callback' => 'icontact_ui_lists_list',
    'page arguments' => array(4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact lists'),
    'file' => 'includes/icontact_ui.lists.inc',
    'type' => MENU_CALLBACK
  );
  $items['admin/icontact/lists/%/%icontact_clientfolder/list'] = array(
    'title' => 'Lists',
    'description' => 'Manage iContact lists.',
    'page callback' => 'icontact_ui_lists_list',
    'page arguments' => array(4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact lists'),
    'file' => 'includes/icontact_ui.lists.inc',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10
  );
  $items['admin/icontact/lists/%/%icontact_clientfolder/add'] = array(
    'title' => 'Add list',
    'description' => 'Add an iContact list.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_lists_form', 4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact lists'),
    'file' => 'includes/icontact_ui.lists.inc',
    'type' => MENU_LOCAL_TASK
  );
  $items['admin/icontact/lists/%/%/%icontact_list/view'] = array(
    'title' => 'List contacts',
    'page callback' => 'icontact_ui_lists_view',
    'page arguments' => array(5),
    'load arguments' => array(3, 4),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact lists'),
    'file' => 'includes/icontact_ui.lists.inc',
    'type' => MENU_CALLBACK
  );
  $items['admin/icontact/lists/%/%/%icontact_list/edit'] = array(
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_lists_form', 5),
    'load arguments' => array(3, 4),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact lists'),
    'file' => 'includes/icontact_ui.lists.inc',
    'type' => MENU_CALLBACK
  );
  return $items;
}

function icontact_ui_messages_menu_items() {
  $items['admin/icontact/messages/%/%icontact_clientfolder'] = array(
    'title' => 'Messages',
    'description' => 'Manage iContact messages.',
    'page callback' => 'icontact_ui_messages_list',
    'page arguments' => array(4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact messages'),
    'file' => 'includes/icontact_ui.messages.inc',
    'type' => MENU_CALLBACK
  );
  $items['admin/icontact/messages/%/%icontact_clientfolder/list'] = array(
    'title' => 'List',
    'description' => 'Manage iContact messages.',
    'page callback' => 'icontact_ui_messages_list',
    'page arguments' => array(4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact messages'),
    'file' => 'includes/icontact_ui.messages.inc',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10
  );
  $items['admin/icontact/messages/%/%icontact_clientfolder/add'] = array(
    'title' => 'Add',
    'description' => 'Add an iContact message.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_messages_form', 4),
    'load arguments' => array(3),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact messages'),
    'file' => 'includes/icontact_ui.messages.inc',
    'type' => MENU_LOCAL_TASK
  );
  $items['admin/icontact/messages/%/%/%icontact_message/edit'] = array(
    'page callback' => 'drupal_get_form',
    'page arguments' => array('icontact_ui_messages_form', 5),
    'load arguments' => array(3, 4),
    'access callback' => 'icontact_admin_perm',
    'access arguments' => array('manage iContact messages'),
    'file' => 'includes/icontact_ui.messages.inc',
    'type' => MENU_CALLBACK
  );
  return $items;
}
