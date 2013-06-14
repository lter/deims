(function ($) {
  $.fn.data_source_preview_show_modal = function(data) {
    $('#source_preview_modal').dialog({
      title: 'Data Source Preview',
      height: 682,
      width: 990,
      autoOpen: false,
      closeOnEscape: false
    });

    $('#source_preview_modal').dialog('open');
  };
})(jQuery);
