<?php
// $Id: iContact.class.inc,v 1.1.2.3 2010/05/03 21:48:44 greenskin Exp $

define('ICONTACT_CODE_SUCCESS', 200);
define('ICONTACT_CODE_BAD_REQUEST', 400);
define('ICONTACT_CODE_NOT_AUTHORIZED', 401);
define('ICONTACT_CODE_PAYMENT_REQUIRED', 402);
define('ICONTACT_CODE_FORBIDDEN', 403);
define('ICONTACT_CODE_NOT_FOUND', 404);
define('ICONTACT_CODE_METHOD_NOT_ALLOWED', 405);
define('ICONTACT_CODE_NOT_ACCEPTABLE', 406);
define('ICONTACT_CODE_UNSUPPORTED_FORMAT', 415);
define('ICONTACT_CODE_INTERAL_SERVER_ERROR', 500);
define('ICONTACT_CODE_NOT_IMPLEMENTED', 501);
define('ICONTACT_CODE_SERVICE_UNAVAILABLE', 503);
define('ICONTACT_CODE_INSUFFICIENT_SPACE', 507);

class iContact extends iContactResource {
  protected $url = '';
  protected $app_id = '';
  protected $username = '';
  protected $password = '';
  protected $dataType = 'XML';
  protected $type = 'iContact';
  protected $accounts = NULL;

  public function __construct($refresh = FALSE) {
    // The iContactResource object sets a protected parameter for $iContact
    // that we don't need so unset it.
    unset($this->iContact);

    if ($refresh) {
      cache_clear_all(NULL, 'cache_icontact');
    }

    $this->init();
  }

  protected function init() {
    $this->app_id = variable_get('icontact_app_id', ICONTACT_TEST_APP_ID);
    if ($this->app_id == ICONTACT_APP_ID) {
      $this->url = ICONTACT_URL;
      $this->username = variable_get('icontact_username', '');
      $this->password = variable_get('icontact_password', '');
    }
    else {
      $this->url = ICONTACT_TEST_URL;
      $this->username = variable_get('icontact_test_username', '');
      $this->password = variable_get('icontact_test_password', '');
    }

    $this->getData();
  }

  public function initResource($type, $id = NULL) {
    switch ($type) {
      case 'accounts':
        return new iContactAccount($this, $id);
    }
    return FALSE;
  }

  public function initAccount($id = NULL) {
    return $this->initResource('accounts', $id);
  }

  protected function cacheId() {
    return $this->type .':'. $this->username;
  }

  protected function setCache() {
    if ($this->username) {
      parent::setCache();
    }
  }

  public function checkLoggedIn() {
    static $loggedIn = NULL;

    if ($loggedIn !== NULL) {
      return $loggedIn;
    }

    $result = $this->request('/a');
    $loggedIn = ($result->code != ICONTACT_CODE_NOT_AUTHORIZED) ? TRUE : FALSE;
    return $loggedIn;
  }

  protected function subResources() {
    return array('accounts');
  }

  protected function requestResource() {
    
  }

  protected function accountsRequestIds() {
    $this->accounts = array();
    $result = $this->requestData('/a');
    foreach ($result['accounts']->children() as $account) {
      $this->accounts[(int)$account->accountId] = (int)$account->accountId;
    }
  }

  public function getAccount($accountId) {
    return $this->getResource('accounts', $accountId);
  }

  public function request($uri, $method = 'GET', $data = NULL, $retry = 3) {
    $url = $this->url . $uri;
    $headers = array(
      'API-Version' => '2.0',
      'Accept' => 'application/'. $this->dataType,
      'API-AppId' => $this->app_id,
      'API-Username' => $this->username,
      'API-Password' => $this->password,
      'Content-Type' => 'application/'. $this->dataType
    );
    return drupal_http_request($url, $headers, $method, $data, $retry);
  }

  public function requestData($uri, $method = 'GET', $data = NULL, $retry = 3) {
    $result = $this->request($uri, $method, $data, $retry);
    if ($result->code != ICONTACT_CODE_SUCCESS) {
      drupal_set_message(t('iContact error: %error', array('%error' => $this->statusMessage($result->code))), 'error');
      return FALSE;
    }
    $func = 'requestData'. ucwords($this->dataType);
    return $this->requestDataXml($result->data);
  }

  protected function requestDataXml($data) {
    if ($result = simplexml_load_string($data)) {
      return (array)$result;
    }
    return FALSE;
  }

  protected function requestDataJson($data) {
    if (is_string($data) && $result = json_decode($data)) {
      return (array)$array;
    }
    return FALSE;
  }

  protected function statusMessage($code) {
    switch ($code) {
      case ICONTACT_CODE_SUCCESS:
        return 'Your request was processed successfully.';
      case ICONTACT_CODE_BAD_REQUEST:
        return 'Your data could not be parsed or your request contained invalid data.';
      case ICONTACT_CODE_NOT_AUTHORIZED:
        return 'You are not logged in.';
      case ICONTACT_CODE_PAYMENT_REQUIRED:
        return 'You must pay your iContact bill before we can process your request.';
      case ICONTACT_CODE_FORBIDDEN:
        return 'You are logged in, but do not have permission to perform that action.';
      case ICONTACT_CODE_NOT_FOUND:
        return 'You have requested a resource that cannot be found.';
      case ICONTACT_CODE_METHOD_NOT_ALLOWED:
        return 'You cannot perform that method on the requested resource.';
      case ICONTACT_CODE_NOT_ACCEPTABLE:
        return 'You have requested that iContact generate data in an unsupported format. The iContact API can only return data in XML or JSON.';
      case ICONTACT_CODE_UNSUPPORTED_FORMAT:
        return 'Your request was not in a supported format. You can make requests in XML or JSON.';
      case ICONTACT_CODE_INTERAL_SERVER_ERROR:
        return "An error occurred in iContact's code.";
      case ICONTACT_CODE_NOT_IMPLEMENTED:
        return 'You have requested a resource that has not been implemented or you have specified an incorrect version of the iContact API.';
      case ICONTACT_CODE_SERVICE_UNAVAILABLE:
        return 'You cannot perform the action because the system is experiencing extremely high traffic or you cannot perform the action because the system is down for maintenance.';
      case ICONTACT_CODE_INSUFFICIENT_SPACE:
        return 'You have used up all of your allotted storage (for example, in the image library).';
      default:
        return 'An error occurred.';
    }
  }
}
