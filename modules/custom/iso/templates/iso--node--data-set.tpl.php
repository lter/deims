<gmi:MI_Metadata<?php print $namespaces; ?> >

   <gmd:fileIndentifier>
     <?php print render($content['field_short_name']); ?>
   </gmd:fileIndentifier>
   <gmd:language>
      <gco:CharacterString> <?php print $language; ?></gco:CharacterString>
   </gmd:language>

   <gmd:characterSet>
     <gmd:MD_CharacterSetCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_CharacterSetCode" codeListValue="utf8" codeSpace="004">utf8</gmd:MD_CharacterSetCode>
   </gmd:characterSet>

   <gmd:hierarchyLevel>
      <gmd:MD_ScopeCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#MD_ScopeCode" codeListValue="dataset" codeSpace="005">dataset</gmd:MD_ScopeCode>
   </gmd:hierarchyLevel>

   <gmd:contact>
     <?php print render($content['field_person_contact']); ?>
     <!-- solve role needs to be in person template, perhaps person-role -->
     <gmd:role>
       <gmd:CI_RoleCode codeList="URL-to-NSF-roles" codeListValue="pointOfContact">pointOfContact</gmd:CI_RoleCode>
     </gmd:role>
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
               <gmd:title><gco:CharacterString><?php print $label; ?></gco:CharacterString></gmd:title>
               <gmd:date>
                 <gmd:CI_Date>
                   <gmd:date><gco:Date><?php print $pubDate; ?></gco:Date></gmd:date>
                   <gmd:dateType>
                     <gmd:CI_DateTypeCode codeList="http://www.isotc211.org/2005/resources/Codelist/gmxCodelists.xml#CI_DateTypeCode" codeListValue="publication" codeSpace="002">publication</gmd:CI_DateTypeCode>
                   </gmd:dateType>
                 </gmd:CI_Date>
               </gmd:date>
              <!--creator(s) HERE -->
               <gmd:citedResponsibleParty>
                 <?php print render($content['field_person_creator']); ?>
               </gmd:citedResponsibleParty>
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
         <?php if (!empty($content['field_project_roles'])): ?>
           <gmd:credit>
             <?php print render($content['field_project_roles']); ?>
           </gmd:credit>
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
                </gmd:maintenanceNote>
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
           <!-- aggregationInfo -->
         <?php endif; ?>

         <gmd:language>
            <?php print $language; ?>
         </gmd:language>
         <gmd:extent>
            <gmd:EX_Extent>
               <?php print render($content['field_related_sites']); ?>
               <?php print render($content['field_date_range']); ?>
               <!-- vertical info here as verticalElement/Ex_VerticalExtent/minimum|maximumValue/gcp:Real..-->
            </gmd:EX_Extent>
         </gmd:extent>

         <?php if (!empty($content['field_additional_information'])): ?>
          <gmd:supplementalInformation>
            <?php print render($content['field_additional_information']); ?>
          </gmd:supplementalInformation>
         <?php endif; ?>
      </gmd:MD_DataIdentification>
   </gmd:identificationInfo>

   <?php print render($content['field_data_sources']); ?>

   <!-- data qual info -->
    <?php if (!empty($content['methods'])): ?>
    <gmd:dataQualityInfo>
      <gmd:DQ_DataQuality>
        <gmd:scope>
          <gmd:DQ_Scope>
            <gmd:level>
              <gmd:MD_ScopeCode codeList="http://www.ngdc.noaa.gov/metadata/published/xsd/schema/resources/Codelist/gmxCodelists.xml#MD_ScopeCode" codeListValue="dataset">dataset</gmd:MD_ScopeCode>
            </gmd:level>
          </gmd:DQ_Scope>
        </gmd:scope>
        <gmd:lineage>
          <?php print render($content['methods']); ?>
        </gmd:lineage>
      </gmd:DQ_DataQuality>
    </gmd:dataQualityInfo>
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

   <gmd:metadataMaintenance>
     <gmd:MD_MaintenanceInformation>
       <gmd:maintenanceAndUpdateFrequency>
         <gmd:MD_MaintenanceFrequencyCode codeList="http://www.ngdc.noaa.gov/metadata/published/xsd/schema/resources/Codelist/gmxCodelists.xml#MD_MaintenanceFrequencyCode" codeListValue="annually">annually</gmd:MD_MaintenanceFrequencyCode>
       </gmd:maintenanceAndUpdateFrequency>
       <?php if (!empty($content['field_person_metadata_provider'])): ?>
         <gmd:contact>
           <gmd:CI_ResponsibleParty>
             <?php print render($content['field_person_metadata_provider']); ?>
             <gmd:role>
               <gmd:CI_RoleCode codeList="http://www.ngdc.noaa.gov/metadata/published/xsd/schema/resources/Codelist/gmxCodelists.xml#CI_RoleCode" codeListValue="pointOfContact">pointOfContact</gmd:CI_RoleCode>           
             </gmd:role>
           </gmd:CI_ResponsibleParty>
         </gmd:contact>
       <?php endif; ?>
     </gmd:MD_MaintenanceInformation>
   </gmd:metadataMaintenance>
</gmi:MI_Metadata>
