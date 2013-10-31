<gmi:MI_Metadata<?php print $namespaces; ?> >

   <gmd:fileIndentifier>
    <?php print $shortname; ?>
   </gmd:fileIndentifier>
   <gmd:language>
     <?php print $language; ?>
   </gmd:language>

   <gmd:characterSet>
     <gmd:MD_CharacterSetCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_CharacterSetCode" codeListValue="utf8" codeSpace="004">utf8</gmd:MD_CharacterSetCode>
   </gmd:characterSet>

   <gmd:hierarchyLevel>
      <gmd:MD_ScopeCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_ScopeCode" codeListValue="dataset" codeSpace="005">dataset</gmd:MD_ScopeCode>
   </gmd:hierarchyLevel>

   <gmd:contact>
     <?php print render($content['field_person_contact']); ?>
   </gmd:contact>

   <gmd:dateStamp><gco:Date><?php print $pubDate; ?></gco:Date></gmd:dateStamp>

   <gmd:metadataStandardName>
      <gco:CharacterString>ISO 19115-2 Geographic Information - North American Profile Metadata - Data with Biological Extensions</gco:CharacterString>
   </gmd:metadataStandardName>
   <gmd:metadataStandardVersion>
      <gco:CharacterString>ISO 19115-2:2009(E)</gco:CharacterString>
   </gmd:metadataStandardVersion>

   <gmd:identificationInfo>
      <gmd:MD_DataIdentification>
         <gmd:citation>
            <gmd:CI_Citation>
               <gmd:title><?php print $label; ?></gmd:title>
               <gmd:date>
                 <gmd:CI_Date>
                   <gmd:date><gco:Date><?php print $pubDate; ?></gco:Date></gmd:date>
                   <gmd:dateType>
                     <gmd:CI_DateTypeCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#CI_DateTypeCode" codeListValue="publication" codeSpace="002">publication</gmd:CI_DateTypeCode>
                   </gmd:dateType>
                 </gmd:CI_Date>
               </gmd:date>
              <!--creator HERE -->
               <?php print render($content['field_person_creator']); ?>
               <gmd:presentationForm>
                  <gmd:CI_PresentationFormCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#CI_PresentationFormCode" codeListValue="documentDigital" codeSpace="001">documentDigital</gmd:CI_PresentationFormCode>
               </gmd:presentationForm>
            </gmd:CI_Citation>
         </gmd:citation>
         <?php if (!empty($content['field_abstract'])): ?>
          <gmd:abstract>
            <?php print render($content['field_abstract']); ?>
          </gmd:abstract>
         <?php endif; ?>
         <?php if (!empty($content['field_purpose'])): ?>
          <gmd:purpose>
            <?php print render($content['field_purpose']); ?>
          </gmd:purpose>
         <?php endif; ?>
         <gmd:status>
           <gmd:MD_ProgressCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_ProgressCode" codeListValue="completed" codeSpace="001">completed</gmd:MD_ProgressCode>
         </gmd:status>    
         <gmd:pointOfContact>
            <?php print render($content['field_person_contact']); ?>
         </gmd:pointOfContact>
         <?php if (!empty($content['field_maintenance'])): ?>
          <gmd:resourceMaintenance>
             <gmd:MD_MaintenanceInformation>
                <gmd:maintenanceAndUpdateFrequency>
                   <gmd:MD_MaintenanceFrequencyCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_MaintenanceFrequencyCode" codeListValue="unknown" codeSpace="012">unknown</gmd:MD_MaintenanceFrequencyCode>
                </gmd:maintenanceAndUpdateFrequency>
                <gmd:maintenanceNote>
                   <?php print render($content['field_maintenance']); ?>
                <gmd:maintenanceNote>
             </gmd:MD_MaintenanceInformation>
          </gmd:resourceMaintenance>
         <?php endif; ?>

         <?php print render($content['keywordSets']); ?>
  
         <?php if (!empty($data_policies)): ?>
           <gmd:resourceConstraints>
             <gmd:MD_LegalConstraints>
               <gmd:accessConstraints>
                  <gmd:MD_RestrictionCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_RestrictionCode" codeListValue="otherRestrictions" codeSpace="008">otherRestrictions</gmd:MD_RestrictionCode>
               </gmd:accessConstraints>
               <gmd:useConstraints>
                 <gmd:MD_RestrictionCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_RestrictionCode" codeListValue="otherRestrictions" codeSpace="008">otherRestrictions</gmd:MD_RestrictionCode>
               </gmd:useConstraints>
               <gmd:otherConstraints>
                  <gco:CharacterString>
                    <?php print $data_policies; ?>
                  </gco:CharacterString>
	       </gmd:otherConstraints>
	     </gmd:MD_LegalConstraints>
           </gmd:resourceConstraints>
         <?php endif; ?>
         <gmd:language>
            <?php print $language; ?>
         </gmd:language>
         <gmd:extent>
            <gmd:EX_Extent>
               <?php print render($content['field_related_sites']); ?>
               <?php print render($content['field_date_range']); ?>
            </gmd:EX_Extent>
         </gmd:extent>

         <?php if (!empty($content['field_additional_information'])): ?>
          <gmd:supplementalInformation>
            <?php print render($content['field_additional_information']); ?>
          </gmd:supplementalInformation>
         <?php endif; ?>
      </gmd:MD_DataIdentification>
   </gmd:identificationInfo>

   <!-- gmd:contentInfo -->
   <?php print render($content['field_data_sources']); ?>

  <!-- distrib. info -->
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
       <gmd:distributor>
         <gmd:MD_Distributor>
            <gmd:distributorContact>
		<gmd:CI_ResponsibleParty>
			<gmd:organisationName>
			<gco:CharacterString>U.S. Environmental Protection Agency</gco:CharacterString>
			</gmd:organisationName>
                  <gmd:contactInfo>
 		  </gmd:contactInfo>
		  <gmd:role>
		   <gmd:CI_RoleCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#CI_RoleCode" codeListValue="distributor" codeSpace="005">distributor</gmd:CI_RoleCode>
		  </gmd:role>
		</gmd:CI_ResponsibleParty>
            </gmd:distributorContact>
            <gmd:distributionOrderProcess>
              <gmd:MD_StandardOrderProcess>
                <gmd:fees>
                  <gco:CharacterString>None</gco:CharacterString>
                </gmd:fees>
              </gmd:MD_StandardOrderProcess>
            </gmd:distributionOrderProcess>
            <gmd:distributionOrderProcess>
               <gmd:MD_StandardOrderProcess>
                 <gmd:fees>
                    <gco:CharacterString>None</gco:CharacterString>
                 </gmd:fees>
               </gmd:MD_StandardOrderProcess>
            </gmd:distributionOrderProcess>
         </gmd:MD_Distributor>
       </gmd:distributor>
       <gmd:transferOptions>
          <gmd:MD_DigitalTransferOptions>
             <gmd:onLine>
                <gmd:CI_OnlineResource>
                   <gmd:linkage>
                      <gmd:URL>http://www.epa.gov/ost/fish/mercurydata.html</gmd:URL>
                   </gmd:linkage>
                </gmd:CI_OnlineResource>
             </gmd:onLine>
           </gmd:MD_DigitalTransferOptions>
        </gmd:transferOptions>
     </gmd:MD_Distribution> 
   </gmd:distributionInfo>

   <!-- data qual info -->
    <?php if (!empty($content['methods'])): ?>
    <methods>
      <?php print render($content['methods']); ?>
    </methods>
    <?php endif; ?>

   <gmd:metadataConstraints>
     <gmd:MD_LegalConstraints>
       <gmd:accessConstraints>
         <gmd:MD_RestrictionCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_RestrictionCode" codeListValue="otherRestrictions" codeSpace="008"/>
       </gmd:accessConstraints>
       <gmd:useConstraints>
         <gmd:MD_RestrictionCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_RestrictionCode" codeListValue="otherRestrictions" codeSpace="008"/>
       </gmd:useConstraints>
       <gmd:otherConstraints>
         <gco:CharacterString>Metadata Access Constraints: none Metadata Use Constraints: none</gco:CharacterString>
       </gmd:otherConstraints>
     </gmd:MD_LegalConstraints>
   </gmd:metadataConstraints>

   <!-- metadata maintenance -->

   <?php print render($content['field_person_metadata_provider']); ?>

    <?php print render($content['field_project_roles']); ?>

    <?php if (!empty($content['field_person_publisher'])): ?>
    <publisher>
      <?php print render($content['field_person_publisher']); ?>
    </publisher>
    <?php endif; ?>

    <pubPlace><?php print $pubPlace; ?></pubPlace>

</gmi:MI_Metadata>
