(function ($) {

/**
 * Provide the search capability to the variable entry form.
 */
Drupal.behaviors.variableFieldSearch = {
  attach: function (context) {
    $('input[type=datetime]').datetimepicker({
      changeMonth: true,
      changeYear: true,
      dateFormat: 'yy-mm-dd',
      timeFormat: 'HH:mm',
      separator: 'T'
    });
  }
};

})(jQuery);
