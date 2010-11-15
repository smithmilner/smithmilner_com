// $Id: icontact_api.js,v 1.1.2.1 2009/08/17 23:33:50 greenskin Exp $

Drupal.behaviors.icontactAPI = function() {
  var live = '4AuXFcTZc6MSKIhekSCFJOAmJrnoYHWT';
  var sandbox = 'aGhF9JgPtDvQqzCtgGMKfNprUNm5i7Dj';

  if ($("#edit-icontact-app-id").val() == live) {
    $("#icontact-sandbox-help").hide();
  }
  else {
    $("#icontact-live-help").hide();
  }

  if ($("#edit-icontact-app-id:not('.icontact-app-id-processed')").size()) {
    $("#edit-icontact-app-id").change(function() {
      if (live == $(this).val()) {
        $("#icontact-live-help").show();
        $("#icontact-sandbox-help").hide();
      }
      else {
        $("#icontact-live-help").hide();
        $("#icontact-sandbox-help").show();
      }
    });
    $("#edit-icontact-app-id").addClass('icontact-app-id-processed');
  }
}
