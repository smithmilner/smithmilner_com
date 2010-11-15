<?php
// $Id: Extended_Client.php,v 1.1 2010/06/01 21:15:13 guypaddock Exp $
/**
 * @file
 *  The FreshBooks_Extended_Client class, part of the FreshBooks Extended API module.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */

/**
 * The key for a FreshBook link that a client uses to access his or her account.
 * This link is returned as part of the request for a Client's information.
 *
 * @var string
 */
define('FRESHBOOKS_LINK_CLIENT_VIEW', 'client_view');

/**
 * The key for a FreshBook link that a staff member users to view a client's account.
 * This link is returned as part of the request for a Client's information.
 *
 * @var string
 */
define('FRESHBOOKS_LINK_VIEW', 'view');

/**
 * Extended API for working with FreshBooks Clients.
 *
 * This class provides several new pieces of functionality over the FreshBooks_Client class, including the ability to
 * access client-specific links via getLink(), the ability to access the last update timestamp, and sane handling of
 * empty field values.
 *
 * The getLink() functionality allows a Drupal site to provide a client with direct access to his or her account on a
 * FreshBooks site by way of the unique link that FreshBooks generates for them.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */
class FreshBooks_Extended_Client extends FreshBooks_Client {
  /**
   * The date and time, as a UNIX timestamp, of the last update to this object.
   *
   * This field is read-only.
   *
   * @var int
   */
  public $updated = NULL;

  /**
   * The associative array of links for this client.
   *
   * @var array
   */
  private $links = array();

  /**
   * Default constructor for FreshBooks_Extended_Client.
   */
  public function __construct() {
    // Clear fields provided by parent class
    $this->_clearEmptyFields();
  }

  /**
   * Get the client-specific link that is identified by the specified key. This information will only be available
   * after a call to get() with a valid client identifier.
   *
   * @param   $key
   *          The unique name/key for the desired client-specific link. This will be either FRESHBOOKS_LINK_CLIENT_VIEW
   *          or FRESHBOOKS_LINK_VIEW.
   *
   * @return
   */
  public function getLink($key) {
    return $this->links[$key];
  }

  /**
   * Override of FreshBooks_Client::_internalLoadXML() to load the update date and link information during processing
   * of the response from a FreshBooks Client API request.
   *
   * @param $XMLObject
   *        The XML object representing the client information returned by the FreshBooks site.
   */
  protected function _internalLoadXML(&$XMLObject) {
    parent::_internalLoadXML($XMLObject);

    $this->updated  = strtotime((string)$XMLObject->updated);
    $this->links    = (array)$XMLObject->links;

    $this->_clearEmptyFields();
  }

  /**
   * Override of FreshBooks_Client::_internalLoadXML() to delete link information when a client is deleted.
   *
   * @param $responseStatus
   *        The status returned by the FreshBooks site for the delete request.
   *
   * @param $XMLObject
   *        The XML object representing the client information returned by the FreshBooks site.
   */
  protected function _internalDelete($responseStatus, &$XMLObject) {
    parent::_internalDelete($responseStatus, $XMLObject);

    if ($responseStatus) {
      unset($this->updated);
      unset($this->links);
    }
  }

  /**
   * Override of FreshBooks_Client::_internalListing() to return rows of FreshBooks_ExtendedClient objects instead
   * of FreshBooks_Client objects.
   *
   * @param $responseStatus
   *        The status returned by the FreshBooks site for the listing request.
   *
   * @param $XMLObject
   *        The XML object representing the client information returned by the FreshBooks site.
   *
   * @param $rows
   *        An output parameter that will be filled with an array containing the rows of the listing.
   *
   * @param $resultInfo
   *        An output parameter that will be filled with an array of status information about the listing results.
   */
  protected function _internalListing($responseStatus, &$XMLObject, &$rows, &$resultInfo) {
    $rows                   = array();
    $resultInfo             = array();

    $clients                = $XMLObject->clients;
    $resultInfo['page']     = (string)$clients['page'];
    $resultInfo['perPage']  = (string)$clients['per_page'];
    $resultInfo['pages']    = (string)$clients['pages'];
    $resultInfo['total']    = (string)$clients['total'];

    foreach ($clients->children() as $key => $currXML) {
      $thisClient = new FreshBooks_Extended_Client();

      $thisClient->_internalLoadXML($currXML);

      $rows[]     = $thisClient;
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
}