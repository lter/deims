(function ($) {
  $.fn.data_source_preview_show_modal = function(data) {
    $('#source_preview_modal').dialog({
      title: Drupal.t('Data Source Preview'),
      height: 682,
      width: 990,
      closeOnEscape: false,
      close: function(event, ui) {
        $(this).dialog('destroy').remove();
      }
    });
  };
})(jQuery);
