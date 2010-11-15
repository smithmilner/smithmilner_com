<?php
// $Id: icontact_ui.users.inc,v 1.1.2.1 2010/04/26 20:59:50 greenskin Exp $

/**
 * iContact user administrative section.
 */
function icontact_ui_users_list(&$account) {
  return theme('icontact_ui_users_list', $account);
}

/*******************************************************************************
 * Theme Functions
 ******************************************************************************/

function theme_icontact_ui_users_list($account) {
  icontact_ui_breadcrumb('account');

  $headers = array(
    t('Username'),
    t('First name'),
    t('Last name'),
    t('E-mail'),
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
  $user_ids = $account->getResourceIds('users');
  if (!empty($user_ids)) {
    foreach ($user_ids as $id) {
      $user = &$account->getUser($id);

      $row = array(
        array('data' => check_plain($user->userName)),
        array('data' => check_plain($user->firstName)),
        array('data' => check_plain($user->lastName)),
        array('data' => check_plain($user->email)),
        array('data' => theme('links', $actions))
      );
      $rows[] = array('data' => $row);
    }
  }

  $output = '<div>'. theme('table', $headers, $rows) .'</div>';
  return $output;
}
