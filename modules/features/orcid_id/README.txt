orcid feature module by Jim Laundre Jan 20017


This feature adds a field to persons called "ORCID ID (machine name field_orcid_id) as field type of URL.


For this field to be included in EML you will need to enabled it in the EML tab of the Person content Managed Display (admin/structure/types/manage/person/display/eml) as "EML onlineUrl" and moved it below the URL field.

And modified the eml--node--person.tpl.php (file in profiles/deims/modules/custom/eml/templates) by adding the following:

<?php $orcid=render($content['field_orcid_id']);
      $onlineurl_tags = array("<onlineUrl>","</onlineUrl>");
      $userid_tags = array("<userId directory=\"http://orcid.org\">","</userId>");
      print str_replace($onlineurl_tags,$userid_tags,$orcid); ?>

Note: the above code puts the correct tags on since "EML onlineURL" format will use an <onlineUrl> tag.