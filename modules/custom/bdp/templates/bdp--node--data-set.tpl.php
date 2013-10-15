<metadata>
  <idinfo>
    <citation>
      <citeinfo>          

       <origin><?php print render($content['field_person_creator']); ?></origin>

        <pubdate><?php print $pubDate; ?></pubdate>

        <title><?php print $label; ?></title>
       
        <!-- edition -->
        <geoform>tabular digitial data</geoform>
        <!-- serinfo -->
        <pubinfo>
          <pubplace><?php print $pubPlace; ?></pubplace>
          <publish>
          <?php if (!empty($content['field_person_publisher'])): ?>
           <?php print render($content['field_person_publisher']); ?>
          <?php endif; ?>
          </publish>
        </pubinfo>
        <?php if (!empty($content['field_doi'])): ?>
          <othercit>
            <?php print render($content['field_doi']); ?>
          </othercit>
        <?php endif; ?>        
        <onlink><?php print $url; ?></onlink>
        <!--lworkcit -->
      </citeinfo>
      <descript>

       <?php if (!empty($content['field_abstract'])): ?>
        <abstract>
          <?php print render($content['field_abstract']); ?>
        </abstract>
       <?php endif; ?>
        
       <?php if (!empty($content['field_purpose'])): ?>
         <purpose>
           <?php print render($content['field_purpose']); ?>
         </purpose>
       <?php endif; ?>

       <?php if (!empty($content['field_additional_information'])): ?>
        <supplinf>
          <?php print render($content['field_additional_information']); ?>
        </supplinf>
       <?php endif; ?>

      </descript>
    
      <timeperd>
        <?php print render($content['field_date_range']); ?>
        <current>ground condition</current>
      </timeperd>

      <status>
       <?php if (!empty($content['field_maintenance'])): ?>
         <progress> <?php print render($content['field_maintenance']); ?></progress>
       <?php endif; ?>
       <update>As needed</update>
      </status>

      <?php if (!empty($content['field_related_sites']) || !empty($content['field_date_range'])): ?>
       <?php print render($content['field_related_sites']); ?>
      <?php endif; ?>
  
      <?php print render($content['keywordSets']); ?>

      <accconst>None</accconst>
      <?php if (!empty($data_policies)): ?>
        <useconst>
          <?php print $data_policies; ?>
        </useconst>
      <?php endif; ?>
 
      <ptcontact><?php print render($content['field_person_contact']); ?></ptcontact>
      <?php if (!empty($content['field_project_roles'])): ?>
       <datacred>
         <?php print render($content['field_project_roles']); ?>       
       </datacred>
      <?php endif; ?>
  </idinfo>

  <?php if (!empty($content['methods'])): ?>
    <dataqual>
      <logic>Not Applicable</logic>
      <complete>Not Applicable</complete>
      <lineage>
        <method>
          <methtype>Field and/or Lab Methods</methtype>
          <?php print render($content['methods']); ?>
        </method>
        <procstep> 
          <procdesc><?php print(render($content['field_methods'])); ?></procdesc>
          <procdate>unknown</procdate>
        </procstep>
      </lineage>
    </dataqual>
  <?php endif; ?>

  <?php print render($content['field_data_sources']); ?>

  <metainfo>
    <metd><?php print $pubDate; ?></metd>
    <metrd><?php print $pubDate; ?></metrd>
    <metc> 
     <cntinfo><?php print render($content['field_person_metadata_provider']); ?></cntinfo> 
    </metc>
    <metstdn>Biological Data Profile of the Content Standards for Digital Geospatial Metadata devised by the Federal Geographic Data Committee.</metstdn>
    <metstdv>Drupal Ecological information Management Systems, version D7, Biological Data Profile module</metstdv>
  </metainfo>

</metadata>
