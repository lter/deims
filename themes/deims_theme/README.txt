
-- SUMMARY --

FOOTHEMES ARE GO!

Footheme is a stater sub-theme for Corolla 7.x-2.x and can be easily
modified to use Pixture Reloaded 7.x-2.x or Sky 7.x-2.x, which are all
sub-themes of Adaptivetheme 7.x-2.x.


-- REQUIREMENTS --

Corolla 7.x-2.x is a sub-theme of Adaptivetheme, you must download and install
Adaptivetheme 7.x-2.x first. If you are planning on sub-theming Sky or Pixture Reloaded
you need to install those first, including the base theme:

http://drupal.org/project/adaptivetheme
http://drupal.org/project/corolla
http://drupal.org/project/sky
http://drupal.org/project/pixture_reloaded


-- INSTALLATION --

Install as usual, see http://drupal.org/node/70151 for further information.


-- BUILDING THE SUB-THEME --

Mostly this is all done for you and if you have Corolla 7.x-2.x installed and running you
can just enable this theme and it will work! Hooray!

If you want to subtheme Pixture Reloaded or Sky, or you really want to change the
name from Footheme, then read on.

1. Copy this entire theme and change the name of the folder. Currently the name of the folder
   is "footheme", so you might choose "bartheme". In the next step we will use this name for
   the info file so this is very important because as far as Drupal is concerned the name of the
   info file is the "machine name" of your theme. Don't use spaces or any punctuation other than
   underscores. E.g "bar_theme" is OK, but "bar theme" is not OK.

2. footheme.info - first rename this file to match the folder name you chose in step one. Next you
   can change the "name", "description" and "version" to whatever you want. Then you need to copy and
   paste in some stuff from your base themes info file - the "regions list" and "theme settings list"
   from your chosen base theme. The ones there now are from Corolla so just replace them. If you're
   using Corolla then you can do nothing, or just change the name and description.

3. Color module stuff - using Corolla? No issue, do nothing. If you're using Pixture Reloaded or Sky
   then you need to delete the color folder from this theme and copy/paste in the color folder from
   your chosen base theme.

   Pixture Reloaded uses images as part of the color process - they are all in the /images folder
   in Pixture Reloaded - you should copy and paste that folder in as well.

4. template.php - open up this file and make some changes - search and replace "footheme" for your
   themes name.

   In footheme_preprocess_html() you will find some stuff about responsive stylesheets and IE conditional
   stylesheets - follow those instructions carefully - they are easy and involve renaming some CSS files
   to match your theme name.

   Done? OK, enable your new theme, go to the theme settings form and make sure it all looks normal,
   then save the theme settings at least once. Done - have some fun.


