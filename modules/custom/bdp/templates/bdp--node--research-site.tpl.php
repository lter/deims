<spdom>
  <descgeog>
    <?php print render($content['field_description']); ?>
  </descgeog>
  <?php if (!empty($content['field_coordinates'])): ?>
    <bounding>
      <?php print render($content['field_coordinates']); ?>
      <?php if (!empty($content['field_elevation'])): ?>
        <boundingalt>
          <altmin><?php print render($content['field_elevation']); ?></altmin>
          <altmax><?php print render($content['field_elevation']); ?></altmax>
          <altunits>meter</altunits>
        </boundingalt>
      <?php endif; ?>
    </bounding>
  <?php endif; ?>
</spdom>
