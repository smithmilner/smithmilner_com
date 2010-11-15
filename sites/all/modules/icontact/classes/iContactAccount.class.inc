<?php
// $Id: iContactAccount.class.inc,v 1.1.2.3 2010/04/26 20:59:50 greenskin Exp $

class iContactAccount extends iContactResource {
  protected $type = 'account';

  public $accountId = 0;
  public $subscriberLimit = 5000;
  public $accountType = 0;
  public $firstName = '';
  public $lastName = '';
  public $title = '';
  public $phone = '';
  public $fax = '';
  public $email = '';
  public $companyName = '';
  public $street = '';
  public $city = '';
  public $state = '';
  public $postalCode = '';
  public $billingStreet = '';
  public $billingCity = '';
  public $billingState = '';
  public $billingPostalCode = '';

  protected $clientFolders = NULL;
  protected $users = NULL;

  protected function init($id = NULL) {
    if ($id) {
      $this->accountId = $id;
      $this->getData();
    }
  }

  public function initResource($type, $id = NULL) {
    switch ($type) {
      case 'clientFolders':
        return new iContactClientFolder($this->iContact, $this->accountId, $id);
      case 'users':
        return new iContactUser($this->iContact, $this->accountId, $id);
    }
    return FALSE;
  }

  public function initClientFolder($id = NULL) {
    return $this->initResource('clientFolders', $id);
  }

  public function initUser($id = NULL) {
    return $this->initResource('users', $id);
  }

  protected function cacheId() {
    return $this->type .':'. $this->accountId;
  }

  protected function setCache() {
    if ($this->accountId) {
      parent::setCache();
    }
  }

  protected function getURI() {
    return '/a/'. $this->accountId;
  }

  public function getClientFolder($clientFolderId) {
    return $this->getResource('clientFolders', $clientFolderId);
  }

  public function getUser($userId) {
    return $this->getResource('users', $userId);
  }

  protected function subResources() {
    return array('clientFolders', 'users');
  }

  protected function clientFoldersRequestIds() {
    $this->clientFolders = array();
    $result = $this->requestData($this->getURI() .'/c');
    foreach ($result['clientfolders']->children() as $clientFolder) {
      $this->clientFolders[(int)$clientFolder->clientFolderId] = (int)$clientFolder->clientFolderId;
    }
  }

  protected function usersRequestIds() {
    $this->users = array();
    $result = $this->requestData($this->getURI() .'/users');
    foreach ($result['users']->children() as $user) {
      $this->users[(int)$user->userId] = (int)$user->userId;
    }
  }

  public function update($data) {
    $xmlObject = simplexml_load_string('<account></account>');
    if (isset($data['billing']) && is_array($data['billing'])) {
      $data += $data['billing'];
      unset($data['billing']);
    }
    foreach ($data as $name => $value) {
      $xmlObject->addChild($name, $value);
    }
    return $this->updateResource('account', $xmlObject->asXML());
  }
}
