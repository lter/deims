(function ($) {

/**
 * Provide the search capability to the variable entry form.
 */
Drupal.behaviors.dataSourcePreview = {
  attach: function (context) {
    $('#data-source-preview .data-source-preview-modal', context).dialog({
      title: Drupal.t('Data Source Preview'),
      height: 682,
      width: 990,
      closeOnEscape: false,
      open: function(event, ui) {
        // Disable the 'Preview source' button from being clicked again while
        // the modal is open.
        $('input.data-source-preview-button').attr('disabled', 'disabled');
      },
      close: function(event, ui) {
        $(this).dialog('destroy').remove();
        // Enable the 'Preview source' button now that the modal is closed.
        $('input.data-source-preview-button').removeAttr('disabled');
      }
    });
  }
};

})(jQuery);
