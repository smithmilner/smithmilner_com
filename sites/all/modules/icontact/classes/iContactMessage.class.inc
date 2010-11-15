<?php
// $Id: iContactMessage.class.inc,v 1.1.2.6 2010/05/03 19:49:35 greenskin Exp $

class iContactMessage extends iContactResource {
  protected $type = 'message';

  public $accountId;
  public $clientFolderId;
  public $messageId;
  public $messageType = 'normal';
  public $subject = '';
  public $campaignId = 0;
  public $htmlBody = '';
  public $textBody = '';

  protected function init($accountId, $clientFolderId, $messageId = NULL) {
    $this->accountId = $accountId;
    $this->clientFolderId = $clientFolderId;
    if ($messageId) {
      $this->messageId = $messageId;
      $this->getData();
    }
  }

  protected function cacheId() {
    return $this->type .':'. $this->accountId .':'. $this->clientFolderId .':'. $this->messageId;
  }

  protected function setCache() {
    if ($this->messageId) {
      parent::setCache();
    }
  }

  protected function getURI() {
    return '/a/'. $this->accountId .'/c/'. $this->clientFolderId .'/messages/'. $this->messageId;
  }

  public function create($data) {
    $xmlObject = ($this->contactId) ? simplexml_load_string('<message></message>') : simplexml_load_string('<messages><message></message></messages>');
    if (isset($xmlObject->messages)) {
      foreach ($data as $name => $value) {
        $xmlObject->messages->message->addChild($name, $value);
      }
    }
    else if (isset($xmlObject->message)) {
      foreach ($data as $name => $value) {
        $xmlObject->message->addChild($name, $value);
      }
    }
    return $this->updateResource('contact', $xmlObject->asXML());
  }

  public function request() {
    return $this->requestResource();
  }

  public function update($data) {
    $xmlObject = simplexml_load_string('<message></message>');
    foreach ($data as $name => $value) {
      $xmlObject->addChild($name, $value);
    }
    return $this->updateResource('message', $xmlObject->asXML());
  }
}
