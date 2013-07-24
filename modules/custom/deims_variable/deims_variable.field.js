(function ($) {

/**
 * Provide the summary information for the variable entry field widget.
 */
Drupal.behaviors.variableFieldSummary = {
  attach: function (context) {

    // Construct the text for the variable entry form.
    $('details.variable-entry', context).drupalSetSummary(function (context) {
      var summary = [];
      var name = $('input.variable-name', context).val() || Drupal.t('Unnamed');
      var type = $('select.variable-type option:selected', context).text();
      summary.push(name);
      summary.push(type);

      return Drupal.checkPlain(summary.join(' - '));
    });

    // Update the <summary> with the summary text whenever something is changed.
    $('details.variable-entry').bind('summaryUpdated', function() {
      $(this).children('summary').text($(this).drupalGetSummary());
    })
    .trigger('summaryUpdated');

    // If a 'closed' <details> element contains an error inside of it, force it
    // to display open.
    $('details:not([open])').has('.error').attr("open", "open");
  }
};

})(jQuery);
