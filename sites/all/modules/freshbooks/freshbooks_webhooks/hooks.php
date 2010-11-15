<?php
// $Id: hooks.php,v 1.1 2010/06/01 21:15:13 guypaddock Exp $
/**
 * @file
 *  Signatures and documentation for all known FreshBooks Webhooks API hooks.
 *
 *  Any of these hooks can be implemented by copying them to a separate custom module and renaming them per standard
 *  Drupal conventions ("hook_" in the function name gets replaced with custom module name).
 *
 * @author Guy Paddock (guy.paddock@redbottledesign.com)
 */

  /**
   * FreshBooks callback hook for the <code>category.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $categoryId
   *        The numeric identifier for the category being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_category_create($system, $categoryId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>category.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $categoryId
   *        The numeric identifier for the category being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_category_update($system, $categoryId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>category.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $categoryId
   *        The numeric identifier for the category being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_category_delete($system, $categoryId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>client.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $clientId
   *        The numeric identifier for the client being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_client_create($system, $clientId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>client.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $clientId
   *        The numeric identifier for the client being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_client_update($system, $clientId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>client.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $clientId
   *        The numeric identifier for the client being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_client_delete($system, $clientId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>estimate.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $estimateId
   *        The numeric identifier for the estimate being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_estimate_create($system, $estimateId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>estimate.sendByEmail</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $estimateId
   *        The numeric identifier for the estimate being sent by e-mail.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_estimate_sendByEmail($system, $estimateId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>estimate.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $estimateId
   *        The numeric identifier for the estimate being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_estimate_update($system, $estimateId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>estimate.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $estimateId
   *        The numeric identifier for the estimate being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_estimate_delete($system, $estimateId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>expense.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $expenseId
   *        The numeric identifier for the expense being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_expense_create($system, $expenseId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>expense.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $expenseId
   *        The numeric identifier for the expense being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_expense_update($system, $expenseId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>expense.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $expenseId
   *        The numeric identifier for the expense being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_expense_delete($system, $expenseId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_create($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.dispute</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice being disputed.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_dispute($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.pastdue.1</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice that is past due by one payment cycle.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_pastdue_1($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.pastdue.2</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice that is past due by two payment cycles.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_pastdue_2($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.pastdue.3</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice that is past due by three payment cycles.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_pastdue_3($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.sendByEmail</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice that is being sent by e-mail.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_sendByEmail($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.sendBySnailMail</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice that is being sent by regular postal mail.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_sendBySnailMail($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_update($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>invoice.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $invoiceId
   *        The numeric identifier for the invoice that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_invoice_delete($system, $invoiceId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>item.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $itemId
   *        The numeric identifier for the item that is being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_item_create($system, $itemId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>item.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $itemId
   *        The numeric identifier for the item that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_item_update($system, $itemId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>item.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $itemId
   *        The numeric identifier for the item that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_item_delete($system, $itemId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>payment.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $paymentId
   *        The numeric identifier for the payment that is being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_payment_create($system, $paymentId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>payment.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $paymentId
   *        The numeric identifier for the payment that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_payment_update($system, $paymentId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>payment.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $paymentId
   *        The numeric identifier for the payment that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_payment_delete($system, $paymentId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>project.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $projectId
   *        The numeric identifier for the project that is being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_project_create($system, $projectId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>project.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $projectId
   *        The numeric identifier for the project that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_project_update($system, $projectId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>project.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $projectId
   *        The numeric identifier for the project that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_project_delete($system, $projectId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>recurring.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $recurringId
   *        The numeric identifier for the recurring subscription that is being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_recurring_create($system, $recurringId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>recurring.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $recurringId
   *        The numeric identifier for the recurring subscription that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_recurring_update($system, $recurringId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>recurring.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $recurringId
   *        The numeric identifier for the recurring subscription that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_recurring_delete($system, $recurringId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>staff.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $staffId
   *        The numeric identifier for the staff member account that is being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_staff_create($system, $staffId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>staff.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $staffId
   *        The numeric identifier for the staff member account that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_staff_update($system, $staffId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>staff.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $staffId
   *        The numeric identifier for the staff member account that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_staff_delete($system, $staffId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>task.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $taskId
   *        The numeric identifier for the task that is being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_task_create($system, $taskId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>task.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $taskId
   *        The numeric identifier for the task that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_task_update($system, $taskId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>task.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $taskId
   *        The numeric identifier for the task that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_task_delete($system, $taskId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>time_entry.create</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $timeEntryId
   *        The numeric identifier for the time entry that is being created.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_time_entry_create($system, $timeEntryId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>time_entry.update</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $timeEntryId
   *        The numeric identifier for the time entry that is being updated.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_time_entry_update($system, $timeEntryId, $userId) {

  }

  /**
   * FreshBooks callback hook for the <code>time_entry.delete</code> event.
   *
   * @param $system
   *        The address of the FreshBooks site that is providing the event notification.
   *
   * @param $timeEntryId
   *        The numeric identifier for the time entry that is being deleted.
   *
   * @param $userId
   *        The numeric identifier for the user who initiated the event.
   */
  function hook_freshbooks_callback_time_entry_delete($system, $timeEntryId, $userId) {

  }
