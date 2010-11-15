<?php
// $Id: Extended_Callback.php,v 1.1 2010/06/01 21:15:13 guypaddock Exp $
/**
 * @file
 *  The FreshBooks_Extended_Callback class, part of the FreshBooks Extended API module.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */

/**
 * Extended API for working with FreshBooks Callbacks.
 *
 * Callback functionality is entirely new, and allows a Drupal site to respond to events that happen on the FreshBooks
 * site (new invoice, completed payment, etc). This class also implements sane handling of empty field values.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */
class FreshBooks_Extended_Callback
extends FreshBooks_ElementAction
implements FreshBooks_Element_Interface, FreshBooks_ElementAction_Interface {
  /**
   * The name for the XML element that corresponds to callbacks. This is used internally to generate the tag
   * when this object is converted to XML.
   *
   * @var string
   */
  protected $_elementName = "callback";

  /**
   * The numeric identifier for this callback.
   *
   * @var int
   */
  public $callbackId = NULL;

  /**
   * The name of the event (i.e. <code>client.create</code>, <code>payment.update</code>, etc).
   *
   * @var string
   */
  public $event = NULL;

  /**
   * The URI that this callback will notify when the associated event occurs.
   *
   * @var string
   */
  public $uri = NULL;

  /**
   * A unique verification code that was sent when the callback was first created. This is used with the verify
   * operation.
   *
   * @var string
   */
  public $verifier = NULL;

  /**
   * Whether or not this callback has been verified and will fire when the associated event occurs.
   *
   * @var bool
   */
  public $verified = FALSE;

  /**
   * The filters to apply as part of the current listing operation.
   *
   * See _internalListing() for why this is currently necessary.
   *
   * @see Extended_Callback::_internalListing()
   * @var array
   */
  protected $listingFilters = NULL;

  /**
   * Verify this callback using a unique verification code that was sent when the callback was first created.
   *
   * NOTE: $this->verifier must be set before calling this method.
   */
  public function verify() {
    $this->_internalPrepareVerify($content);

    $responseXML      = $this->_sendRequest($content, "verify");
    $responseStatus   = $this->_processResponse($responseXML);

    $this->_internalVerify($responseStatus, $responseXML);

    return $responseStatus;
  }

  /**
   * Resend a verification code if this is an un-verified callback.
   *
   * NOTE: No token will be sent if this callback is already verified.
   */
  public function resendToken() {
    $this->_internalPrepareResendToken($content);

    $responseXML      = $this->_sendRequest($content, "resendToken");
    $responseStatus   = $this->_processResponse($responseXML);

    $this->_internalResendToken($responseStatus, $responseXML);

    return $responseStatus;
  }

  /**
   * Override of the get() operation.
   *
   * This operation is not supported for Callbacks and will always return <code>FALSE</code>.
   *
   * @return  Whether or not the operation succeeded. This is always <code>FALSE</code> for Callback instances,
   *          as FreshBooks does not support a callback.get operation.
   */
  public function get($id) {
    // Operation not supported
    return false;
  }

  /**
   * Override of the update() operation.
   *
   * This operation is not supported for Callbacks and will always return <code>FALSE</code>.
   *
   * @return  Whether or not the operation succeeded. This is always <code>FALSE</code> for Callback instances,
   *          as FreshBooks does not support a callback.update operation.
   */
  public function update() {
    // Operation not supported
    return false;
  }

  /**
   * Converts the information in this callback to an XML string.
   *
   * @return  An XML string containing the information in this object.
   */
  public function asXML() {
    $content =
      $this->_getTagXML("callback_id", $this->callbackId) .
      $this->_getTagXML("event", $this->event) .
      $this->_getTagXML("uri", $this->uri) .
      $this->_getTagXML("verifier", $this->verifier);

    return $this->_getTagXML($this->_elementName, $content);
  }

  /**
   * Internal function for populating this instance with information from a SimpleXML object.
   *
   * @param $XMLObject
   *        The SimpleXML object containing the information with which this object will be populated.
   */
  protected function _internalLoadXML(&$XMLObject) {
    $this->callbackId = (string)$XMLObject->callback_id;
    $this->event      = (string)$XMLObject->event;
    $this->uri        = (string)$XMLObject->uri;
    $this->verified   = ((string)$XMLObject->verified == "1");

    $this->_clearEmptyFields();
  }

  /**
   * Internal function for preparing the XML content to send to the FreshBooks server for a
   * <code>callback.verify</code> operation, which verifies a callback.
   *
   * @param $content
   *        Reference to the content string that is to be populated with the XML content for this object.
   */
  protected function _internalPrepareVerify(&$content) {
    $innerContent =
      $this->_getTagXML("callback_id", $this->callbackId) .
      $this->_getTagXML("verifier", $this->verifier);

    $content = $this->_getTagXML($this->_elementName, $innerContent);
  }

  /**
   * Internal function for handling the result of performing a <code>callback.verify</code> operation.
   *
   * @param $responseStatus
   *        A boolean value that indicates that the operation was successful (<code>TRUE</code>), or unsuccessful
   *        (<code>FALSE</code>).
   *
   * @param $XMLObject
   *        A SimpleXML object containing the information that was parsed from the server response to the operation.
   */
  protected function _internalVerify($responseStatus, &$XMLObject) {
    if ($responseStatus) {
      // Assume verified if response was positive
      $this->verified = TRUE;
    }
  }

  /**
   * Internal function for preparing the XML content to send to the FreshBooks server for a
   * <code>callback.resendToken</code> operation, which resends the verification code for a callback.
   *
   * @param $content
   *        Reference to the content string that is to be populated with the XML content for this object.
   */
  protected function _internalPrepareResendToken(&$content) {
    $content  = $this->_getTagXML("callback_id", $this->callbackId);
  }

  /**
   * Internal function for handling the result of performing a <code>callback.resendToken</code> operation.
   *
   * @param $responseStatus
   *        A boolean value that indicates that the operation was successful (<code>TRUE</code>), or unsuccessful
   *        (<code>FALSE</code>).
   *
   * @param $XMLObject
   *        A SimpleXML object containing the information that was parsed from the server response to the operation.
   */
  protected function _internalResendToken($responseStatus, &$XMLObject) {
    // Nothing to do.
  }

  /**
   * Internal function for preparing the XML content to send to the FreshBooks server for a
   * <code>callback.create</code> operation, which creates a new callback.
   *
   * @param $content
   *        Reference to the content string that is to be populated with the XML content for this object.
   */
  protected function _internalPrepareCreate(&$content) {
    $content = $this->asXML();
  }

  /**
   * Internal function for handling the result of performing a <code>callback.create</code> operation.
   *
   * @param $responseStatus
   *        A boolean value that indicates that the operation was successful (<code>TRUE</code>), or unsuccessful
   *        (<code>FALSE</code>).
   *
   * @param $XMLObject
   *        A SimpleXML object containing the information that was parsed from the server response to the operation.
   */
  protected function _internalCreate($responseStatus, &$XMLObject) {
    if ($responseStatus) {
      $this->callbackId = (string)$XMLObject->callback_id;
    }
  }

  /**
   * Internal function for preparing the XML content to send to the FreshBooks server for a
   * <code>callback.delete</code> operation, which deletes an existing callback.
   *
   * @param $content
   *        Reference to the content string that is to be populated with the XML content for this object.
   */
  protected function _internalPrepareDelete(&$content) {
    $content  = $this->_getTagXML("callback_id", $this->callbackId);
  }

  /**
   * Internal function for handling the result of performing a <code>callback.delete</code> operation.
   *
   * @param $responseStatus
   *        A boolean value that indicates that the operation was successful (<code>TRUE</code>), or unsuccessful
   *        (<code>FALSE</code>).
   *
   * @param $XMLObject
   *        A SimpleXML object containing the information that was parsed from the server response to the operation.
   */
  protected function _internalDelete($responseStatus, &$XMLObject) {
    if ($responseStatus) {
      unset($this->callbackId);
      unset($this->event);
      unset($this->uri);
      unset($this->verifier);
      unset($this->verified);
    }
  }

  /**
   * Internal function for preparing the XML content to send to the FreshBooks server for a
   * <code>callback.list</code> operation, which lists callbacks that match optionally-provided criteria.
   *
   * @param $filters
   *        An optional array of filters to apply to the listing.
   *
   * @param $content
   *        Reference to the content string that is to be populated with the XML content for this object.
   */
  protected function _internalPrepareListing($filters, &$content) {
    if (!empty($filters) && is_array($filters)) {
      // NOTE: We're dropping the content we've already been provided because "page" and "perPage" aren't supported.
      $content = $this->_getTagXML("event", $filters['event']) . $this->_getTagXML("uri", $filters['uri']);

      // See _internalListing() for why this is necessary.
      $this->listingFilters = $filters;
    }
    else {
      $this->listingFilters = array();
    }
  }

  /**
   * Internal function for handling the result of performing a <code>callback.list</code> operation.
   *
   * @param $responseStatus
   *        A boolean value that indicates that the operation was successful (<code>TRUE</code>), or unsuccessful
   *        (<code>FALSE</code>).
   *
   * @param $XMLObject
   *        A SimpleXML object containing the information that was parsed from the server response to the operation.
   *
   * @param $rows
   *        A reference to the array that should be populated with the resulting rows of the listing.
   *
   * @param $resultInfo
   *        A reference to the array that should be populated with metadata about the listing.
   */
  protected function _internalListing($responseStatus, &$XMLObject, &$rows, &$resultInfo) {
    $rows       = array();
    $resultInfo = array();

    $callbacks  = $XMLObject->callbacks;

    $resultInfo['page']     = (string)$callbacks['page'];
    $resultInfo['perPage']  = (string)$callbacks['per_page'];
    $resultInfo['pages']    = (string)$callbacks['pages'];
    $resultInfo['total']    = (string)$callbacks['total'];

    foreach ($callbacks->children() as $key => $currXML) {
      $thisCallback = new FreshBooks_Extended_Callback();

      $thisCallback->_internalLoadXML($currXML);

      $matches = TRUE;

      /**
       * This workaround is currently necessary because of a bug in the FreshBooks API for callback.list that causes
       * it to disregard filters.
       *
       * Support ticket #86186 has been filed about this issue. Once this bug has been addressed, this workaround
       * can be removed.
       */
      foreach ($this->listingFilters as $field => $filterValue) {
        if (!empty($filterValue) && ($thisCallback->$field != $filterValue)) {
          $matches = FALSE;
          break;
        }
      }

      if ($matches) {
        $rows[] = $thisCallback;
      }
    }
  }

  /**
   * Internal function that forces any class fields that are empty strings to be <code>NULL</code> so that they
   * are properly ignored by our custom _getTagXML() implementation.
   */
  protected function _clearEmptyFields() {
    foreach (get_object_vars($this) as $name => $value) {
      if ($value === "") {
        $this->{$name} = NULL;
      }
    }
  }

  /**
   * Override of FreshBooks_Element::__getTagXML(), to correct how it knows a field should be excluded.
   *
   * The default FreshBooks PHP behavior of omitting values that have an empty string value makes it nearly impossible
   * to clear the value of a previously-populated field in a FreshBooks object. When <code>$strict</code> is the
   * default value of <code>TRUE</code>, this version of the method considers a string empty only if it is strictly
   * equal to <code>NULL</code>. When <code>FALSE</code> is provided for the value of <code>$strict</code>, the old
   * behavior is used.
   *
   * @param $tag
   *        The name of the tag for the XML fragment to generate.
   *
   * @param $value
   *        The value to enclose in the generated XML tag.
   *
   * @param $excludeIfEmpty
   *        An optional parameter that specifies whether or not the XML fragment should be omitted if
   *        <code>$value</code> is <code>NULL</code>. The default is <code>TRUE</code>, which means that
   *        <code>NULL</code> will be returned if <code>$value</code> is empty.
   *
   * @param $strict
   *        An optional parameter that specifies whether <code>$value</code> will be considered empty
   *        only if it strictly equals <code>NULL</code>. The default value is <code>TRUE</code>.
   */
  protected function _getTagXML($tag, $value, $excludeIfEmpty = TRUE, $strict = TRUE) {
    if ($excludeIfEmpty && (($value === NULL) || (!$strict && empty($value)))) {
      $result = NULL;
    }
    else {
      $result = "<$tag>$value</$tag>";
    }

    return $result;
  }

  /**
   * This would be an internal function for preparing the XML content to send to the FreshBooks server for a
   * <code>callback.update</code> operation, except that the FreshBooks API does not currently support a
   * <code>callback.update</code> operation, so this function does nothing.
   *
   * @param $content
   *        Reference to the content string that is to be populated with the XML content for this object.
   *        This implementation will not modify this value because the FreshBooks API does not currently support a
   *        <code>callback.update</code> operation.
   */
  protected function _internalPrepareUpdate(&$content) {
    // "Update" operation not supported
  }

  /**
   * This would be an internal function for handling the result of performing a <code>callback.update</code>
   * operation, except that the FreshBooks API does not currently support a <code>callback.update</code> operation, so
   * this function does nothing.
   *
   * @param $responseStatus
   *        A boolean value that indicates that the operation was successful (<code>TRUE</code>), or unsuccessful
   *        (<code>FALSE</code>).
   *
   * @param $XMLObject
   *        A SimpleXML object containing the information that was parsed from the server response to the operation.
   */
  protected function _internalUpdate($responseStatus,&$XMLObject) {
    // "Update" operation not supported
  }

  /**
   * This would be an internal function for preparing the XML content to send to the FreshBooks server for a
   * <code>callback.get</code> operation, except that the FreshBooks API does not currently support a
   * <code>callback.get</code> operation, so this function does nothing.
   *
   * @param $content
   *        Reference to the content string that is to be populated with the XML content for this object.
   *        This implementation will not modify this value because the FreshBooks API does not currently support a
   *        <code>callback.get</code> operation.
   */
  protected function _internalPrepareGet($id,&$content) {
    // "Get" operation not supported
  }

  /**
   * This would be an internal function for handling the result of performing a <code>callback.get</code>
   * operation, except that the FreshBooks API does not currently support a <code>callback.get</code> operation, so
   * this function does nothing.
   *
   * @param $responseStatus
   *        A boolean value that indicates that the operation was successful (<code>TRUE</code>), or unsuccessful
   *        (<code>FALSE</code>).
   *
   * @param $XMLObject
   *        A SimpleXML object containing the information that was parsed from the server response to the operation.
   */
  protected function _internalGet($responseStatus, &$XMLObject) {
    // "Get" operation not supported
  }
}