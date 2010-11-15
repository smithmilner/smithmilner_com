<?php
// $Id: iContactResource.class.inc,v 1.1.2.11 2010/05/03 19:49:35 greenskin Exp $

abstract class iContactResource {
  protected $iContact;
  protected $type;

  abstract protected function cacheId();

  public function __construct(iContact $iContact) {
    $this->iContact = $iContact;
    $args = array_splice(func_get_args(), 1);
    call_user_func_array(array($this, 'init'), $args);
  }

  protected function init() {
    $this->getData();
  }

  protected function getURI() {
    return '/a';
  }

  public function getData() {
    if (($cache_id = $this->cacheId()) && $data = cache_get($cache_id, 'cache_icontact')) {
      $this->setData($data->data);
    }
    else {
      $this->requestResource();
      $this->setCache();
    }
  }

  protected function setData($data) {
    foreach ($data as $key => $value) {
      $this->$key = (is_array($value)) ? $value : ((is_numeric($value)) ? (int)$value : (string)$value);
    }
  }

  public function getResource($type, $id) {
    if ($this->$type == NULL) {
      $this->getResourceIds($type);
    }

    if (!empty($this->{$type}[$id])) {
      if (is_numeric($this->{$type}[$id]) || is_string($this->{$type}[$id])) {
        $this->{$type}[$id] = $this->initResource($type, $id);
      }
      return $this->{$type}[$id];
    }
    return FALSE;
  }

  public function getResourceIds($type) {
    if (!empty($this->$type)) {
      return drupal_map_assoc(array_keys($this->$type));
    }
    else if ($this->$type == NULL) {
      $method = $type .'RequestIds';
      if (method_exists($this, $method)) {
        $this->$method();
        $this->setCache();
        return $this->$type;
      }
    }
    return FALSE;
  }

  protected function createResource() {
    
  }

  protected function requestResource() {
    // We request this objects resource data.
    $result = $this->requestData($this->getURI());
    // Use strtolower because iContact's API uses all lowercase for the key.
    $this->setData($result[strtolower($this->type)]->children());
    return $result;
  }

  protected function updateResource($type, $data) {
    $result = $this->requestData($this->getURI(), 'POST', $data);
    if ($result) {
      $this->setData($result[$type]);
      $this->setCache();
    }
    return $result;
  }

  protected function deleteResource() {
    
  }

  protected function setCache() {
    $data = array();
    foreach ($this as $key => $value) {
      if (!is_object($value)) {
        $data[$key] = $value;
      }
    }
    if (method_exists($this, 'subResources')) {
      foreach ($this->subResources() as $type) {
        if (is_array($this->$type)) {
          $data[$type] = drupal_map_assoc(array_keys($this->$type));
        }
      }
    }
    cache_set($this->cacheId(), $data, 'cache_icontact');
  }

  protected function clearCache($wildcard = FALSE) {
    $cid = ($wildcard) ? $this->cacheId() .'*' : $this->cacheId();
    cache_clear_all($cid, 'cache_icontact', $wildcard);
  }

  public function request($uri, $method = 'GET', $data = NULL, $retry = 3) {
    return $this->iContact->request($uri, $method, $data, $retry);
  }

  public function requestData($uri, $method = 'GET', $data = NULL, $retry = 3) {
    return $this->iContact->requestData($uri, $method, $data, $retry);
  }
}
