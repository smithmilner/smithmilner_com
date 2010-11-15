<?php
// $Id: freshbooks.constants.inc,v 1.1 2010/06/01 21:15:13 guypaddock Exp $

/**
 * @file
 *  All constants that are used throughout the FreshBooks module code.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */

  /**
   * The name of the folder containing the FreshBooks-PHP library.
   *
   * @var string
   */
  define("FRESHBOOKS_LIBRARY_NAME", 'freshbooks-php');

  /**
   * The prefix applied to all FreshBooks-PHP classes. This is used by the auto-load callback to determine which classes
   * need to be loaded out of the FreshBooks-PHP library package.
   *
   * @var string
   */
  define("FRESHBOOKS_CLASS_PREFIX", 'FreshBooks_');

// Variables
  /**
   * The name of the variable that contains the service URL for processing FreshBooks requests.
   *
   * @var string
   */
  define('FRESHBOOKS_VAR_API_URL', 'freshbooks_api_url');

  /**
   * The name of the variable that contains the unique authentication token FreshBooks assigns for authenticating
   * requests.
   *
   * @var string
   */
  define('FRESHBOOKS_VAR_TOKEN', 'freshbooks_token');

// Paths
  /**
   * Menu path for FreshBooks module settings.
   *
   * @var string
   */
  define('FRESHBOOKS_PATH_SETTINGS', 'admin/settings/freshbooks');

  /**
   * Callback for running a test of FreshBooks settings.
   *
   * @var string
   */
  define('FRESHBOOKS_PATH_SETTINGS_TEST', 'admin/settings/freshbooks/js/test');

// FreshBooks invoice statuses
  /**
   * The status for an invoice that has neither been sent to a client nor that is publicly accessible (similar to an
   * unpublished Drupal node).
   *
   * @var string
   */
  define('FRESHBOOKS_INVOICE_STATUS_DRAFT', 'draft');

  /**
   * The status for an invoice that has been sent to a client.
   *
   * @var string
   */
  define('FRESHBOOKS_INVOICE_STATUS_SENT', 'sent');

  /**
   * The status for an invoice that has been viewed by a client.
   *
   * @var string
   */
  define('FRESHBOOKS_INVOICE_STATUS_VIEWED', 'viewed');

  /**
   * The status for an invoice that has been paid by a client.
   *
   * @var string
   */
  define('FRESHBOOKS_INVOICE_STATUS_PAID', 'paid');
