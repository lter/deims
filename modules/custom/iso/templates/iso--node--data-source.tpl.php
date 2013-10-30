<gmd:contentInfo>
  <gmd:MD_FeatureCatalogueDescription>
    <gmd:includedWithDataset>
      <gco:Boolean>true</gco:Boolean>
    </gmd:includedWithDataset>
    <gmd:featureTypes>
      <gco:LocalName codeSpace="Header"/>
    </gmd:featureTypes>
    <gmd:featureTypes>
      <gco:LocalName codeSpace=<"?php print $label; ?>"/>
    </gmd:featureTypes>
    <gmd:featureCatalogueCitation>
      <gmd:CI_Citation>
        <gmd:title>
          <gco:CharacterString> </gco:CharacterString>
        </gmd:title>
        <gmd:date gco:nilReason="unknown"/>
        <gmd:citedResponsibleParty>
          <gmd:CI_ResponsibleParty>
            <gmd:organisationName>
              <gco:CharacterString>$site</gco:CharacterString>
            </gmd:organisationName>
            <gmd:contactInfo>
              <gmd:CI_Contact>
                <gmd:onlineResource>
                  <gmd:CI_OnlineResource>
                    <gmd:linkage>
                      <gmd:URL><?php print render($content['field_data_source_file']); ?></gmd:URL>
                    </gmd:linkage>
                    <gmd:protocol>
                      <gco:CharacterString>http</gco:CharacterString>
                    </gmd:protocol>
                  </gmd:CI_OnlineResource>
                </gmd:onlineResource>
	      </gmd:CI_Contact>
            </gmd:contactInfo>
            <gmd:role>
              <gmd:CI_RoleCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#CI_RoleCode" codeListValue="pointOfContact" codeSpace="007">pointOfContact</gmd:CI_RoleCode>
            </gmd:role>
          </gmd:CI_ResponsibleParty>
        </gmd:citedResponsibleParty>
        <gmd:otherCitationDetails>
          <gco:CharacterString>Entity and Attribute Semi-structured description -- 
           <?php if (!empty($content['field_csv_record_delimiter'])): ?>
            Record Delimiter: <?php print render($content['field_csv_record_delimiter']);?>
           <?php endif; ?>
           <?php if (!empty($content['field_csv_header_lines'])): ?>
            Number of Header Lines: <?php print render($content['field_csv_header_lines']); ?>
           <?php endif; ?>
           <?php if (!empty($content['field_csv_orientation'])): ?>
            Orientation: <?php print render($content['field_csv_orientation']); ?>
           <?php endif; ?>
           <?php if (!empty($content['field_csv_quote_character'])): ?>
             Quote Character:<?php print render($content['field_csv_quote_character']); ?>
           <?php endif; ?>
           Field Delimiter: <?php print render($content['field_csv_field_delimiter']); ?>   
           Data URL: <?php print render($content['field_data_source_file']); ?>
           Variable descriptions: <?php print render($content['field_variables']); ?>
          </gco:CharacterString>
        </gmd:otherCitationDetails>
      </gmd:CI_Citation>
    </gmd:featureCatalogueCitation>
  </gmd:MD_FeatureCatalogueDescription>
</gmd:contentInfo>

