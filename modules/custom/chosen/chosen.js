(function($) {
  Drupal.behaviors.chosen = {
    attach: function(context) {
      var minWidth = Drupal.settings.chosen.minimum_width;
      //define options
      var options = {};
      options.search_contains = Drupal.settings.chosen.search_contains;
      options.placeholder_text_multiple = Drupal.t('Choose some options');
      options.placeholder_text_single = Drupal.t('Choose an option');
      options.no_results_text = Drupal.t('No results match');

      if (Drupal.settings.chosen.selector.length) {
        $(Drupal.settings.chosen.selector, context)
          .not('#field-ui-field-overview-form select, #field-ui-display-overview-form select') //disable chosen on field ui
          .not('.chzn-done')
          .filter(function() {
            return !Drupal.settings.chosen.minimum || $(this).find('option').length >= Drupal.settings.chosen.minimum;
          })
          .each(function() {
            var elementOptions = options;
            if ($(this).width() < minWidth) {
              elementOptions.width = minWidth + 'px';
            }
            else {
              elementOptions.width = $(this).width() + 'px';
            }
            $(this).chosen(elementOptions);
          });
      }

      // Enable chosen on for forced widgets.
      $('.chosen-widget', context)
        .not('chzn-done')
        .each(function() {
          var elementOptions = options;
          if ($(this).width() < minWidth) {
            elementOptions.width = minWidth + 'px';
          }
          else {
            elementOptions.width = $(this).width() + 'px';
          }
          $(this).chosen(elementOptions);
        });

      // Integrate select or other elements with Chosen
      $('select.select-or-other-select.chzn-done').each(function() {
        var chosen = $(this).data('chosen');
        chosen.persistent_create_option = true;
        chosen.skip_no_results = true;
        chosen.create_option = function(value) {
          this.form_field_jq.val('select_or_other').change().trigger('liszt:updated');
          this.form_field_jq.parents('.select-or-other').find('input.select-or-other-other').val(value).change();
        }
      });
    }
  }
})(jQuery);
