<eml:eml<?php print $namespaces; ?> <?php print $attributes; ?>>
  <access scope="document" order="allowFirst" authSystem="knb">
    <allow>
      <principal>uid=<?php print $station; ?>,o=LTER,dc=ecoinformatics,dc=org</principal>
      <permission>all</permission>
    </allow>
    <allow>
      <principal>public</principal>
      <permission>read</permission>
    </allow>
  </access>
  <dataset>
    <title><?php print $title; ?></title>
    <pubPlace><?php print $pubPlace; ?></pubPlace>
    <language><?php print $language; ?></language>
    <?php if ($data_policies): ?>
    <intellectualRights>
      <section>
        <title>Data Policies</title>
        <para>
          <literalLayout>
            <?php print $data_policies; ?>
          </literalLayout>
        </para>
      </section>
    </intellectualRights>
    <?php endif; ?>
    <distribution>
      <online>
        <url function="information"><?php print $node_url; ?></url>
      </online>
    </distribution>
    <coverage />
    <?php if (!empty($node->eml_elements)) { print format_xml_elements($node->eml_elements); } ?>
  </dataset>
  <?php if (!empty($content['additionalMetadata'])): ?>
  <additionalMetadata>
    <?php print render($content['additionalMetadata']); ?>
  </additionalMetadata>
  <?php endif; ?>
</eml:eml>
