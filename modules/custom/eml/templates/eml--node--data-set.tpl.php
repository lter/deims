<eml:eml<?php print $namespaces; ?> <?php print $attributes; ?>>
  <access scope="document" order="allowFirst" authSystem="knb">
    <allow>
      <principal><?php print $pasta_user; ?></principal>
      <permission>all</permission>
    </allow>
    <allow>
      <principal>public</principal>
      <permission>read</permission>
    </allow>
  </access>
  <dataset>
    <title><?php print $label; ?></title>

    <creator>
      <?php print render($content['field_person_creator']); ?>
    </creator>

    <?php if (!empty($content['field_person_metadata_provider'])): ?>
    <metadataProvider>
      <?php print render($content['field_person_metadata_provider']); ?>
    </metadataProvider>
    <?php endif; ?>

    <?php print render($content['field_project_roles']); ?>

    <pubDate><?php print $pubDate; ?></pubDate>

    <language><?php print $language; ?></language>

    <?php if (!empty($content['field_abstract'])): ?>
    <abstract>
      <section>
        <?php print render($content['field_abstract']); ?>
      </section>
    </abstract>
    <?php endif; ?>

    <?php print render($content['keywordSets']); ?>

    <?php if (!empty($content['field_additional_information'])): ?>
    <additionalInfo>
      <?php print render($content['field_additional_information']); ?>
    </additionalInfo>
    <?php endif; ?>

    <?php if (!empty($data_policies)): ?>
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
        <url function="information"><?php print $url; ?></url>
      </online>
    </distribution>

    <?php if (!empty($content['field_related_sites']) || !empty($content['field_date_range'])): ?>
    <coverage>
      <?php print render($content['field_related_sites']); ?>
      <?php print render($content['field_date_range']); ?>
    </coverage>
    <?php endif; ?>

    <?php if (!empty($content['field_purpose'])): ?>
    <purpose>
      <?php print render($content['field_purpose']); ?>
    </purpose>
    <?php endif; ?>

    <?php if (!empty($content['field_maintenance'])): ?>
    <maintenance>
      <description>
        <?php print render($content['field_maintenance']); ?>
      </description>
    </maintenance>
    <?php endif; ?>

    <contact>
      <?php print render($content['field_person_contact']); ?>
    </contact>

    <?php if (!empty($content['field_person_publisher'])): ?>
    <publisher>
      <?php print render($content['field_person_publisher']); ?>
    </publisher>
    <?php endif; ?>

    <pubPlace><?php print $pubPlace; ?></pubPlace>

    <?php if (!empty($content['methods'])): ?>
    <methods>
      <?php print render($content['methods']); ?>
    </methods>
    <?php endif; ?>

    <?php print render($content['field_data_sources']); ?>
  </dataset>

  <?php if (!empty($content['additionalMetadata'])): ?>
  <additionalMetadata>
    <metadata>
      <?php print render($content['additionalMetadata']); ?>
    </metadata>
  </additionalMetadata>
  <?php endif; ?>
</eml:eml>
