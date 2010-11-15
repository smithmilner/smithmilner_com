<?php
// $Id: iContactList.class.inc,v 1.1.2.5 2010/04/26 19:45:47 greenskin Exp $

class iContactList extends iContactResource {
  protected $type = 'list';

  public $accountId;
  public $clientFolderId;
  public $listId;
  public $name = '';
  public $emailOwnerOnChange = 1;
  public $welcomeOnManualAdd = 0;
  public $welcomeOnSignupAdd = 0;
  public $welcomeMessageId = 0;
  public $description = '';

  protected function init($accountId, $clientFolderId, $listId = NULL) {
    $this->accountId = $accountId;
    $this->clientFolderId = $clientFolderId;
    if ($listId) {
      $this->listId = $listId;
      $this->getData();
    }
  }

  protected function cacheId() {
    return $this->type .':'. $this->accountId .':'. $this->clientFolderId .':'. $this->listId;
  }

  protected function setCache() {
    if ($this->listId) {
      parent::setCache();
    }
  }

  protected function getURI() {
    return '/a/'. $this->accountId .'/c/'. $this->clientFolderId .'/lists/'. $this->listId;
  }
}
