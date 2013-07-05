<dataTable>
  <entityName><?php print $label; ?></entityName>
  <?php if (!empty($content['field_description'])): ?>
  <entityDescription>
    <?php print render($content['field_description']); ?>
  </entityDescription>
  <?php endif; ?>
  <physical>
    <objectName><?php print check_plain($entity->field_data_source_file[LANGUAGE_NONE][0]['filename']); ?></objectName>
    <size><?php print check_plain($entity->field_data_source_file[LANGUAGE_NONE][0]['filesize']); ?>
    </size>
    <dataFormat>
      <textFormat>
        <?php if (!empty($content['field_csv_header_lines'])): ?>
        <numHeaderLines><?php print render($content['field_csv_header_lines']); ?></numHeaderLines>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_footer_lines'])): ?>
        <numFooterLines><?php print render($content['field_csv_footer_lines']); ?></numFooterLines>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_record_delimiter'])): ?>
        <recordDelimiter><?php print render($content['field_csv_record_delimiter']); ?></recordDelimiter>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_orientation'])): ?>
        <attributeOrientation><?php print render($content['field_csv_orientation']); ?></attributeOrientation>
        <?php endif; ?>
        <simpleDelimited>
          <fieldDelimiter><?php print render($content['field_csv_field_delimiter']); ?></fieldDelimiter>
          <?php if (!empty($content['field_csv_quote_character'])): ?>
            <quoteCharacter><?php print render($content['field_csv_quote_character']); ?></quoteCharacter>
          <?php endif; ?>
        </simpleDelimited>
      </textFormat>
    </dataFormat>
    <distribution>
      <online>
        <url><?php print render($content['field_data_source_file']); ?></url>
      </online>
    </distribution>
  </physical>
  <?php if (!empty($content['field_date_range'])): ?>
  <coverage>
    <?php print render($content['field_date_range']); ?>
  </coverage>
  <?php endif; ?>
  <?php if (!empty($content['methods'])): ?>
  <methods>
    <?php print render($content['methods']); ?>
  </methods>
  <?php endif; ?>
  <attributeList>
    <?php print render($content['field_variables']); ?>
  </attributeList>
</dataTable>
