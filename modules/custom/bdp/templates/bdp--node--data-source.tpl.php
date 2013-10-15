<eainfo>

  <detailed>

    <enttyp>
      <enttypl><?php print $label; ?></enttypl>
      <?php if (!empty($content['field_description'])): ?>
        <enttypd><?php print render($content['field_description']); ?> </enttypd>
      <?php endif; ?>
    </enttyp>

 <?php print render($content['field_variables']); ?>

  </detailed>

</eainfo>

<distinfo>

    <distrib>
      <cntinfo>
       <cntporgp>
         <cntorg>
          <?php print $pubPlace; ?>
         </cntorg>
       </cntporgp>
      </cntinfo>
    </distrib>
    <!-- resdesc (object name) -->
    <distliab>The data distributor shall not be liable for innacuracies in the content</distliab>
    <stdorder>
      <digform>
        <digtinfo>
          <formname>http</formname>
          <formvern>1</formvern>
          <formverd>0</formverd>
          <asciistr>
           <?php if (!empty($content['field_csv_record_delimiter'])): ?>
            <recdel><?php print render($content['field_csv_record_delimiter']);?></recdel>
           <?php endif; ?>
          <?php if (!empty($content['field_csv_header_lines'])): ?>
            <numheadl><?php print render($content['field_csv_header_lines']); ?></numheadl>
           <?php endif; ?>
           <?php if (!empty($content['field_csv_orientation'])): ?>
             <orienta><?php print render($content['field_csv_orientation']); ?></orienta>
           <?php endif; ?>
           <?php if (!empty($content['field_csv_quote_character'])): ?>
             <quotech><?php print render($content['field_csv_quote_character']); ?></quotech>
           <?php endif; ?>
           <datafiel>
           <dfwidthd><?php print render($content['field_csv_field_delimiter']); ?></dfwidthd>
           </datafiel>
          </asciistr>
        </digtinfo>
        <digtopt>
         <onlinopt>
           <computer>
             <networka>
               <networkr><?php print render($content['field_data_source_file']); ?></networkr>
             </networka>
           </computer>
         </onlinopt>
        </digtopt>
      </digform>
      <fees>None</fees>
    </stdorder>
  </distinfo>

