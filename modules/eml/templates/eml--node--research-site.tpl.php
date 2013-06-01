<geographicCoverage>
  <geographicDescription>
    <?php print strip_tags(render($content['field_description'])); ?>
  </geographicDescription>
  <?php if (!empty($content['field_coordinates'])): ?>
    <boundingCoordinates>
      <?php print render($content['field_coordinates']); ?>
      <?php if (!empty($content['field_elevation'])): ?>
        <boundingAltitudes>
          <altitudeMinimum><?php print render($content['field_elevation']); ?></altitudeMinimum>
          <altitudeMaximum><?php print render($content['field_elevation']); ?></altitudeMaximum>
          <altitudeUnits>meter</altitudeUnits>
        </boundingAltitudes>
      <?php endif; ?>
    </boundingCoordinates>
  <?php endif; ?>
</geographicCoverage>
