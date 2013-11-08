<gmd:contentInfo>
 <gmd:featureCatalogue>  
  <gmd:MD_FeatureCatalogue>

  <gmd:featureCatalogueLink>
    <gmd:CI_OnlineResource>
      <gmd:linkage>
        <gmd:URL><?php print render($content['field_data_source_file']); ?></gmd:URL>
      </gmd:linkage>
    </gmd:CI_OnlineResource>
  </gmd:featureCatalogueLink>
  
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
      <gmd:organisationName>
        <gco:CharacterString><?php print $pubPlace; ?></gco:CharacterString>
      </gmd:organisationName>
      <gmd:role/>
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
 </gmd:MD_FeatureCatalogue>
</gmd:featureCatalogue>  

</gmd:contentInfo>
<gmd:distributionInfo>
   <gmd:MD_Distribution>
      <gmd:distributionFormat>
         <gmd:MD_Format>
           <gmd:name>
             <gco:CharacterString>DBF</gco:CharacterString>
           </gmd:name>
           <gmd:version gco:nilReason="unknown"/>
         </gmd:MD_Format>
      </gmd:distributionFormat>
      <gmd:transferOptions>
          <gmd:MD_DigitalTransferOptions>
             <gmd:onLine>
                <gmd:CI_OnlineResource>
                   <gmd:linkage>
                      <gmd:URL><?php print render($content['field_data_source_file']); ?></gmd:URL>
                   </gmd:linkage>
                </gmd:CI_OnlineResource>
             </gmd:onLine>
           </gmd:MD_DigitalTransferOptions>
      </gmd:transferOptions>
    </gmd:MD_Distribution>
  </gmd:distributionInfo>
