<?php
// $Id: iContactUser.class.inc,v 1.1.2.3 2010/04/26 20:59:50 greenskin Exp $

class iContactUser extends iContactResource {
  protected $type = 'user';

  public $accountId;
  public $userId;
  public $userName = '';
  public $password = '';
  public $firstName = '';
  public $lastName = '';
  public $enabled = 1;
  public $editor = 3;

  protected function init($accountId, $userId = NULL) {
    $this->accountId = $accountId;
    if ($userId) {
      $this->userId = $userId;
      $this->getData();
    }
  }

  protected function cacheId() {
    return $this->type .':'. $this->accountId .':'. $this->userId;
  }

  protected function setCache() {
    if ($this->userId) {
      parent::setCache();
    }
  }

  protected function getURI() {
    return '/a/'. $this->accountId .'/users/'. $this->userId;
  }
}
