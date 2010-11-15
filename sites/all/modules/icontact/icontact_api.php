<?php

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

class iContact {
  var $url = 'https://app.icontact.com/icp';
  var $app_id = '';
  var $username = '';
  var $password = '';
  var $dataType = 'XML';

  function __construct($api_key, $shared_secret, $username, $password) {
    $this->api_key = $api_key;
    $this->shared_secret = $shared_secret;
    $this->username = $username;
    $this->password = $password;
  }

  function request($uri, $method = 'GET', $data = NULL) {
    $url = $this->url . $uri;
    $headers = array(
      'API-Version' => '2.0',
      'Accept' => 'application/'. strtolower($this->dataType),
      'API-AppId' => $this->app_id,
      'API-Username' => $this->username,
      'API-Password' => $this->password,
      'Content-Type' => 'application/'. strtolower($this->dataType)
    );

    $handler = curl_init();
    curl_setopt($handler, CURLOPT_URL, $url);
    curl_setopt($handler, CURLOPT_HTTPHEADER, $headers);
    curl_setopt($handler, CURLOPT_RETURNTRANSFER, TRUE);

    if ($method == 'POST') {
      curl_setopt($handler, CURLOPT_POST, TRUE);
      curl_setopt($handler, CURLOPT_POSTFIELDS, $data);
    }

    if ($method == 'PUT') {
      curl_setopt($handler, CURLOPT_PUT, TRUE);
      $file_handler = fopen($data, 'r');
      curl_setopt($handler, CURLOPT_INFILE, $file_handler);
    }

    $response = curl_exec($handler);
    $code = curl_getinfo($handler, CURLINFO_HTTP_CODE);

    curl_close($handler);

    $return = new stdClass();
    $return->code = $code;
    $return->message = $this->statusMessage($code);
    $return->data = $response;
    return $return;
  }

  function statusMessage($code) {
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
?>
