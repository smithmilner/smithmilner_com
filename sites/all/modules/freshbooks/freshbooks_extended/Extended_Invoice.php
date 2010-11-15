<?php
// $Id: Extended_Invoice.php,v 1.1 2010/06/01 21:15:13 guypaddock Exp $
/**
 * @file
 *  The FreshBooks_Extended_Invoice class, part of the FreshBooks Extended API module.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */

/**
 * Extended API for working with FreshBooks Invoices. This class provides several new pieces of functionality over the
 * FreshBooks_Invoice class, including the ability to set the return URI and sane handling of empty field values.
 *
 * The ability to set the return URI allows a Drupal site to send a user off to pay for a recurring subscription on the
 * FreshBooks site, and then have the user return to the Drupal site afterwards.
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */
class FreshBooks_Extended_Invoice extends FreshBooks_Invoice {
  /**
   * The optional return-to-merchant link that is presented to the user after he or she has made a payment.
   *
   * @var string
   */
  public $returnUri = NULL;

  /**
   * Default constructor for FreshBooks_Extended_Invoice.
   */
  public function __construct() {
    // Clear fields provided by parent class
    $this->_clearEmptyFields();
  }

  /**
   * Override of FreshBooks_Invoice::_internalXMLContent() to supply the return URI information during submission of
   * a FreshBooks Invoice API request (invoice.create, invoice.update).
   *
   * @param $XMLObject
   *        The XML object representing the invoice information returned by the FreshBooks site.
   */
  protected function _internalXMLContent() {
    // Workaround limitations of FreshBooks-PHP
    $this->_removeReadonlyFieldsBeforeUpdate();

    $content = $this->_getTagXML("return_uri", $this->returnUri) . parent::_internalXMLContent();

    return $content;
  }

  /**
   * Override of FreshBooks_Invoice::_internalLoadXML() to load the return URI information during processing of the
   * response from a FreshBooks Invoice API request (invoice.get, invoice.list).
   *
   * @param $XMLObject
   *        The XML object representing the invoice information returned by the FreshBooks site.
   */
  protected function _internalLoadXML(&$XMLObject) {
    parent::_internalLoadXML($XMLObject);

    $this->returnUri = (string)$XMLObject->return_uri;

    $this->_clearEmptyFields();
  }

  /**
   * Override of FreshBooks_Invoice::_internalLoadXML() to delete return URI information when an invoice is deleted.
   *
   * @param $responseStatus
   *        The status returned by the FreshBooks site for the delete request.
   *
   * @param $XMLObject
   *        The XML object representing the invoice information returned by the FreshBooks site.
   */
  protected function _internalDelete($responseStatus, &$XMLObject) {
    parent::_internalDelete($responseStatus, $XMLObject);

    if ($responseStatus) {
      unset($this->returnUri);
    }
  }

  /**
   * Override of FreshBooks_Invoice::_internalListing() to return rows of FreshBooks_Extended_Invoice objects instead
   * of FreshBooks_Invoice objects.
   *
   * @param $responseStatus
   *        The status returned by the FreshBooks site for the listing request.
   *
   * @param $XMLObject
   *        The XML object representing the invoice information returned by the FreshBooks site.
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

    $invoices               = $XMLObject->invoices;
    $resultInfo['page']     = (string)$invoices['page'];
    $resultInfo['perPage']  = (string)$invoices['per_page'];
    $resultInfo['pages']    = (string)$invoices['pages'];
    $resultInfo['total']    = (string)$invoices['total'];

    foreach ($invoices->children() as $key => $currXML) {
      $thisInvoice = new FreshBooks_Extended_Invoice();

      $thisInvoice->_internalLoadXML($currXML);

      $rows[]     = $thisInvoice;
    }
  }

  /**
   * Remove data for read-only fields in this object.
   *
   * This is a workaround for odd implementation choices in FreshBooks-PHP that cause update() to fail if it is
   * performed on an object that was previously-populated with get().
   */
  protected function _removeReadonlyFieldsBeforeUpdate() {
    unset($this->amount);
    unset($this->amountOutstanding);

    unset($this->linkClientView);
    unset($this->linkView);
    unset($this->linkEdit);

    unset($this->recurringId);

    foreach ($this->lines as &$line) {
      unset($line->amount);
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
   * Override of FreshBooks_Element::_getTagXML(), to correct how it knows a field should be excluded.
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
   * Override of FreshBooks_BaseInvoice::_linksAsXML() to return an empty string, since links should never be sent over
   * to FreshBooks (they're read-only).
   *
   * This is a frustrating bug in FreshBooks-PHP.
   */
  protected function _linksAsXML() {
    return "";
  }
}