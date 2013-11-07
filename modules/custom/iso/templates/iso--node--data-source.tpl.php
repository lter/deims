<gmd:contentInfo>
  <gmx:name><?php print $label; ?></gmx:name>
  <gmx:scope gco:nilReason='unknown'/>
  <gmx:versionNumber gco:nilReason='unknown'/>
  <gmx:versionDate gco:nilReason='unknown'/>
  <gmx:language>
    <gco:CharacterString>eng; US</gco:CharacterString>
  </gmx:language>
  <gmx:characterSet>
    <gmd:MD_CharacterSetCode codeList='http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_CharacterSetCode' codeListValue='utf8' codeSpace='004'/>
  </gmx:characterSet>
  <gfc:producer>
    <gmd:CI_ResponsibleParty>
    <!-- hard code it to the site, as we have no access to creator, etc -->
      <gmd:organisationName>
        <gco:CharacterString></gco:CharacterString>
      </gmd:organisationName>
      <gmd:contactInfo>
        <gmd:CI_Contact/>
      </gmd:contactInfo>
    </gmd:CI_ResponsibleParty>
  </gfc:producer>
  <gfc:featureType>
    <gfc:FC_FeatureType>
      <gfc:typeName>
        <gco:LocalName><?php print $label; ?></gco:LocalName>
      </gfc:typeName>
      <gfc:definition>
        <?php if (!empty($content['field_description'])): ?>
          Data Source Definition : <?php print render($content['field_description']); ?>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_record_delimiter'])): ?>
          Record Delimiter : <?php print render($content['field_csv_record_delimiter']);?>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_header_lines'])): ?>
         Number of Header Lines : <?php print render($content['field_csv_header_lines']); ?>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_footer_lines'])): ?>
         Number of Footer Lines : <?php print render($content['field_csv_footer_lines']); ?>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_orientation'])): ?>
         Orientation : <?php print render($content['field_csv_orientation']); ?>
        <?php endif; ?>
        <?php if (!empty($content['field_csv_quote_character'])): ?>
          Quote Character : <?php print render($content['field_csv_quote_character']); ?>
        <?php endif; ?>
        Field Delimiter : <?php print render($content['field_csv_field_delimiter']); ?>
      </gfc:definition>
      <gfc:isAbstract>false</gfc:isAbstract>
      <gfc:featureCatalogue href="<?php print render($content['field_data_source_file']); ?>" title="data source : <?php print $label; ?>" />
      <?php print render($content['field_variables']); ?>
    </gfc:FC_FeatureType>   
  </gfc:featureType>
</gmd:contentInfo>
