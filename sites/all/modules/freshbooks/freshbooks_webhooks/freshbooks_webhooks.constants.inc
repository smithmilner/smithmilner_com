<?php
// $Id: freshbooks_webhooks.constants.inc,v 1.1 2010/06/01 21:15:13 guypaddock Exp $
/**
 * @file
 *  Constants used by the FreshBooks Webhooks module.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */
  // Miscellaneous constants
  /**
   * The pattern for domain names that are trusted as sources for FreshBooks call-backs.
   *
   * @var string
   */
  define('FBWH_FB_SAFE_DOMAIN', '*.2ndsiteinc.com');

  // Menu paths
  /**
   * The relative URL path to the FreshBooks callback.
   *
   * @var string
   */
  define('FBWH_PATH_CALLBACK', 'freshbooks/callback');

  // Callback request parameter names
  /**
   * The name of the value in the POST data that contains the name of the callback event.
   *
   * @var string
   */
  define('FBWH_PARAM_EVENT_NAME', 'name');

  /**
   * The name of the value in the POST data that contains the address of the FreshBooks site that is providing the event
   * notification.
   *
   * @var string
   */
  define('FBWH_PARAM_SYSTEM', 'system');

  /**
   * The name of the value in the POST data that contains the object being created, updated, deleted, etc.
   *
   * @var string
   */
  define('FBWH_PARAM_OBJECT_ID', 'object_id');

  /**
   * The name of the value in the POST data that contains the numeric identifier for the user who initiated the event.
   *
   * @var string
   */
  define('FBWH_PARAM_USER_ID', 'user_id');

  /**
   * The name of the value in the POST data for <code>callback.verify</code> events that contains the unique
   * verification code that must be sent back to the FreshBooks site to verify the callback is functioning.
   * @var string
   */
  define('FBWH_PARAM_VERIFIER', 'verifier');