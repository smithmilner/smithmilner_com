<?php
// $Id: iContactContact.class.inc,v 1.1.2.8 2010/05/03 19:49:35 greenskin Exp $

class iContactContact extends iContactResource {
  protected $type = 'contact';

  public $accountId;
  public $clientFolderId;
  public $contactId;
  public $email = '';
  public $status = 'normal';
  public $prefix = '';
  public $firstName = '';
  public $lastName = '';
  public $suffix = '';
  public $street = '';
  public $street2 = '';
  public $city = '';
  public $state = '';
  public $postalCode = '';
  public $phone = '';
  public $fax = '';
  public $business = '';

  protected function init($accountId, $clientFolderId, $contactId = NULL) {
    $this->accountId = $accountId;
    $this->clientFolderId = $clientFolderId;
    if ($contactId) {
      $this->contactId = $contactId;
      $this->getData();
    }
  }

  protected function cacheId() {
    return $this->type .':'. $this->accountId .':'. $this->clientFolderId .':'. $this->contactId;
  }

  protected function setCache() {
    if ($this->contactId) {
      parent::setCache();
    }
  }

  protected function getURI() {
    return '/a/'. $this->accountId .'/c/'. $this->clientFolderId .'/contacts/'. $this->contactId;
  }

  public function getClientFolder() {
    if ($account = $this->iContact->getAccount($this->accountId)) {
      return $account->getClientFolder($this->clientFolderId);
    }
    return FALSE;
  }

  public function requestActions($reload = FALSE) {
    if ($this->contactId) {
      static $actions = FALSE;
      if ($actions == FALSE || $reload) {
        $actions = $this->requestData($this->getURI() .'/actions');
      }
      return $actions;
    }
    return FALSE;
  }

  public function subscribe($listId) {
    if ($this->contactId) {
      $subscriptionId = $listId .'_'. $this->contactId;
      $clientFolder = &$this->getClientFolder();
      if ($subscription = $clientFolder->getSubscription($subscriptionId)) {
        if ($subscription->status != 'normal') {
          $subscription->update(array('status' => 'normal'));
        }
        return $subscription;
      }
      else {
        $subscription = $clientFolder->initSubscription();
        return $subscription->create(array('listId' => $listId, 'contactId' => $this->contactId, 'status' => 'normal'));
      }
    }
    return FALSE;
  }

  public function create($data) {
    if (!$this->contactId) {
      $xmlObject = simplexml_load_string('<contacts><contact></contact></contacts>');

      // Make sure a contactId is not given.
      unset($data['contactId']);

      foreach ($data as $name => $value) {
        $xmlObject->contact->addChild($name, $value);
      }
      return $this->updateResource('contact', $xmlObject->asXML());
    }
    return FALSE;
  }

  public function request() {
    return $this->requestResource();
  }

  public function update($data) {
    if ($this->contactId) {
      $xmlObject = simplexml_load_string('<contact></contact>');

      $data['contactId'] = $this->contactId;

      foreach ($data as $name => $value) {
        $xmlObject->addChild($name, $value);
      }
      return $this->updateResource('contact', $xmlObject->asXML());
    }
    return FALSE;
  }

  public function delete() {
    // TODO: Remove contact from clientFolder and update its cache. This helps
    // to ensure the clientfolder does not try to load a contact that does not
    // actually exist.
    return $this->deleteResource();
  }
}
