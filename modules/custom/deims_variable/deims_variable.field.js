(function ($) {

/**
 * Provide the summary information for the block settings vertical tabs.
 */
Drupal.behaviors.variableFieldSummary = {
  attach: function (context) {

    $('details.variable-entry', context).drupalSetSummary(function (context) {
      var summary = [];
      var label = $('input.variable-label', context).val() || Drupal.t('Unlabeled');
      var type = $('select.variable-type option:selected', context).text();
      summary.push(label);
      summary.push(type);

      return Drupal.checkPlain(summary.join(' - '));
    });

    $('details.variable-entry').bind('summaryUpdated', function() {
      $(this).children('summary').text($(this).drupalGetSummary());
    })
    .trigger('summaryUpdated');

    $('details:not([open])').has('.error').attr("open", "open");
  }
};

})(jQuery);
