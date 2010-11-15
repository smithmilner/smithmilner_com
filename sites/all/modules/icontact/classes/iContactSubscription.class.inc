<?php
// $Id: iContactSubscription.class.inc,v 1.1.2.5 2010/05/03 19:49:35 greenskin Exp $

class iContactSubscription extends iContactResource {
  protected $type = 'subscription';

  public $accountId;
  public $clientFolderId;
  public $subscriptionId;
  public $confirmationMessageId = 0;

  protected function init($accountId, $clientFolderId, $subscriptionId = NULL) {
    $this->accountId = $accountId;
    $this->clientFolderId = $clientFolderId;
    if ($subscriptionId) {
      $this->subscriptionId = $subscriptionId;
      $this->getData();
    }
  }

  protected function cacheId() {
    return $this->type .':'. $this->accountId .':'. $this->clientFolderId .':'. $this->subscriptionId;
  }

  protected function setCache() {
    if ($this->subscriptionId) {
      parent::setCache();
    }
  }

  protected function getURI() {
    return '/a/'. $this->accountId .'/c/'. $this->clientFolderId .'/subscriptions/'. $this->subscriptionId;
  }

  public function getClientFolder() {
    if ($account = $this->iContact->getAccount($this->accountId)) {
      return $account->getClientFolder($this->clientFolderId);
    }
    return FALSE;
  }

  public function create($data) {
    if ($this->update($data)) {
      // This is a new subscription resource so add it to the clientFolder.
      $clientFolder = &$this->getClientFolder();
      if (is_array($clientFolder->subscriptions)) {
        $clientFolder->subscriptions[$this->subscriptionId] = $this;
      }
      return $this;
    }
  }

  public function request() {
    return $this->requestResource();
  }

  public function update($data) {
    if (!$this->subscriptionId && isset($data['listId']) && isset($data['contactId'])) {
      $xmlObject = simplexml_load_string('<subscriptions><subscription></subscription></subscriptions>');
      foreach ($data as $name => $value) {
        $xmlObject->subscription->addChild($name, $value);
      }
      $this->getClientFolder()->clearCache();

      // Save resource.
      $result = $this->updateResource('subscriptions', $xmlObject->asXML());
      if (!isset($result['warnings'])) {
        return $this;
      }
    }
    return FALSE;
  }
}
