(function ($) {

/**
 * Provide the search capability to the variable entry form.
 */
Drupal.behaviors.variableFieldSearch = {
  attach: function (context) {

    $('select.variable-type.autocomplete-item-process').each(function() {
      $(this).removeClass('autocomplete-item-process');

      var base = $(this).attr('name');
      base = base.substr(0, base.length - 6);
      var item = $(this).data('autocomplete-item');

      switch (item.type) {
        case 'physical':
          if ($(this).parents('.variable-entry').find('select[name="' + base + '[data][unit][select]"] option[value="' + item.data.unit + '"]').length) {
            $(this).parents('.variable-entry').find('select[name="' + base + '[data][unit][select]"]').val(item.data.unit).change().trigger('liszt:updated');
          }
          else {
            $(this).parents('.variable-entry').find('select[name="' + base + '[data][unit][select]"]').val('select_or_other').change().trigger('liszt:updated');
            $(this).parents('.variable-entry').find('input[name="' + base + '[data][unit][other]"]').val(item.data.unit).change();
          }
          $(this).parents('.variable-entry').find('input[name="' + base + '[data][maximum]"]').val(item.data.maximum).change();
          $(this).parents('.variable-entry').find('input[name="' + base + '[data][minimum]"]').val(item.data.minimum).change();
          $(this).parents('.variable-entry').find('input[name="' + base + '[data][precision]"]').val(item.data.precision).change();
          break;

        case 'date':
          $(this).parents('.variable-entry').find('input[name="' + base + '[data][pattern]"]').val(item.data.pattern).change();
          break;

        case 'codes':
          $(this).parents('.variable-entry').find('textarea[name="' + base + '[data][codes][options_field]"]').val(item.data.codes_text).trigger('manual-change');
          break;
      }
    }).removeData('autocomplete-item');

    $('input.deims-variable-search-autocomplete', context).once('deims-variable-search-autocomplete', function() {
      //var base = $(this).data('form-parent');
      $(this).autocomplete({
        source: $(this).data('source'),
        minLength: 3,
        select: function(event, ui) {
          var base = $(this).data('form-parent');
          $(this).parents('.variable-entry').find('input[name="' + base + '[name]"]').val(ui.item.name).change();
          $(this).parents('.variable-entry').find('input[name="' + base + '[label]"]').val(ui.item.label).change();
          $(this).parents('.variable-entry').find('textarea[name="' + base + '[definition]"]').val(ui.item.definition).change();
          $(this).parents('.variable-entry').find('textarea[name="' + base + '[missing_values][options_field]"]').val(ui.item.missing_values_text).trigger('manual-change');
          $(this).parents('.variable-entry').find('select[name="' + base + '[type]"]').val(ui.item.type).change().data('autocomplete-item', ui.item).addClass('autocomplete-item-process');
          $(this).val('').blur();
          return false;
        }
      })
      .data('autocomplete')._renderItem = function(ul, item) {
        return $('<li>')
          .data('item.autocomplete', item)
          .append('<a>' + item.summary + '</a>')
          .appendTo(ul);
      };
    });
  }
};

})(jQuery);
