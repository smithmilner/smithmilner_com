<?php
// $Id: iContactClientFolder.class.inc,v 1.1.2.12 2010/05/03 19:49:35 greenskin Exp $

class iContactClientFolder extends iContactResource {
  protected $type = 'clientFolder';

  public $accountId;
  public $clientFolderId;
  // public $name = '';
  // public $fromName = '';
  // public $fromEmail = '';
  // public $street = '';
  // public $city = '';
  // public $state = '';
  // public $postalCode = '';
  // public $country = '';
  public $logoId = 0;
  // public $enabled = 1;
  // public $footerLogoUrl = '';
  // public $useLogoInFooter = 0;
  public $emailRecipient = '';

  protected $contacts = NULL;
  protected $lists = NULL;
  protected $messages = NULL;
  protected $subscriptions = NULL;

  protected function init($accountId, $clientFolderId = NULL) {
    $this->accountId = $accountId;
    if ($clientFolderId) {
      $this->clientFolderId = $clientFolderId;
      $this->getData();
    }
  }

  public function initResource($type, $id = NULL) {
    switch ($type) {
      case 'contacts':
        return new iContactContact($this->iContact, $this->accountId, $this->clientFolderId, $id);
      case 'lists':
        return new iContactList($this->iContact, $this->accountId, $this->clientFolderId, $id);
      case 'messages':
        return new iContactMessage($this->iContact, $this->accountId, $this->clientFolderId, $id);
      case 'subscriptions':
        return new iContactSubscription($this->iContact, $this->accountId, $this->clientFolderId, $id);
    }
    return FALSE;
  }

  public function initContact($id = NULL) {
    return $this->initResource('contacts', $id);
  }

  public function initMessage($id = NULL) {
    return $this->initResource('messages', $id);
  }

  public function initSubscription($id = NULL) {
    return $this->initResource('subscriptions', $id);
  }

  protected function cacheId() {
    return $this->type .':'. $this->accountId .':'. $this->clientFolderId;
  }

  protected function setCache() {
    if ($this->clientFolderId) {
      parent::setCache();
    }
  }

  protected function getURI() {
    return '/a/'. $this->accountId .'/c/'. $this->clientFolderId;
  }

  protected function subResources() {
    return array('contacts', 'lists', 'messages', 'subscriptions');
  }

  public function getContact($param) {
    if (is_numeric($param)) {
      return $this->getContactById($param);
    }
    else if (is_array($param)) {
      return $this->getContactByFields($param);
    }
    return FALSE;
  }

  protected function getContactById($contactId) {
    if (is_array($this->contacts) && isset($this->contacts[$contactId])) {
      return $this->getResource('contacts', $contactId);
    }

    // Either the contacts array has not been populated yet or the requested
    // $contactId does not exist in the contacts array. Request the specific
    // data that pertains to the $contactId.
    if ($contact = $this->initResource('contacts', $contactId)) {
      $this->contacts[$contactId] = $contact;
      return $this->contacts[$contactId];
    }
    return FALSE;
  }

  protected function getContactByFields($fields) {
    $result = $this->contactsRequestIds($fields);
    if (!empty($result)) {
      $contact_id = current($result);
      return $this->getContact($contact_id);
    }
    return FALSE;
  }

  public function getList($listId) {
    return $this->getResource('lists', $listId);
  }

  public function getMessage($messageId) {
    return $this->getResource('messages', $messageId);
  }

  public function getSubscription($subscriptionId) {
    return $this->getResource('subscriptions', $subscriptionId);
  }

  protected function contactsRequestIds($filter = array('status' => 'total', 'limit' => 0)) {
    if ($this->contacts == NULL) {
      $this->contacts = array();
    }

    $query = drupal_query_string_encode($filter);
    $result = $this->requestData($this->getURI() .'/contacts?'. $query);
    $ids = array();
    foreach ($result['contacts']->children() as $contact) {
      $ids[(int)$contact->contactId] = (int)$contact->contactId;
    }

    // Add any new IDs to $contacts parameter without overwriting
    // preexisting ones.
    $this->contacts += $ids;
    return $ids;
  }

  protected function listsRequestIds() {
    $this->lists = array();
    $result = $this->requestData($this->getURI() .'/lists');
    foreach ($result['lists']->children() as $list) {
      $this->lists[(int)$list->listId] = (int)$list->listId;
    }
  }

  protected function messagesRequestIds() {
    $this->messages = array();
    $result = $this->requestData($this->getURI() .'/messages');
    foreach ($result['messages']->children() as $message) {
      $this->messages[(int)$message->messageId] = (int)$message->messageId;
    }
  }

  protected function subscriptionsRequestIds() {
    $this->subscriptions = array();
    $result = $this->requestData($this->getURI() .'/subscriptions');
    foreach ($result['subscriptions']->children() as $subscription) {
      $this->subscriptions[(string)$subscription->subscriptionId] = (string)$subscription->subscriptionId;
    }
  }

  public function requestContacts($filter = array('status' => 'total', 'limit' => 0)) {
    if (isset($filter['limit']) && $filter['limit'] == 0) {
      $query = drupal_query_string_encode($filter);
      $result = $this->requestData($this->getURI() .'/contacts?'. $query);
      $filter['limit'] = $result['total'];
    }
    $this->contactsRequestIds($filter);
    return $this->contacts;
  }
}
