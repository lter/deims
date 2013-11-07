<gmd:description>
  <?php print render($content['field_description']); ?>
</gmd:description>
<gmd:geographicElement>
  <gmd:EX_GeographicBoundingBox>
    <?php print render($content['field_coordinates']); ?>
  </gmd:EX_GeographicBoundingBox>
</gmd:geographicElement>
