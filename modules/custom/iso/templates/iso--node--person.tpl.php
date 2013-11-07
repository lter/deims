<?php
/**
 * This template does not have a surrounding XML element because it is re-used
 * by other elements.
 */
?>
<gmd:CI_ResponsibleParty>
<?php print render($content['field_name']); ?>
<?php if (!empty($content['field_organization'])): ?>
<gmd:organisationName>
  <!--only need organization node title here-->
  <?php print render($content['field_organization']); ?>
</gmd:organisationName>
<?php endif; ?>
<gmd:contactInfo>
  <gmd:CI_Contact>
    <!--may be an issue with phones, fax+phone seem to be rendered together
     unless the cardinality is 1->infyt. ALSO, facsimile thing is not working --> 
    <?php print render($content['field_phone']); ?>
    <?php print render($content['field_fax']); ?>
    <!-- nest email inside address in field formatter -->
    <?php print render($content['field_address']); ?>
    <?php print render($content['field_email']); ?>
  </gmd:CI_Contact>
</gmd:contactInfo>
<?php print render($content['field_url']); ?>
</gmd:CI_ResponsibleParty>
