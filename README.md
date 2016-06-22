# DEIMS Install Profile #
<a href="https://codeclimate.com/github/lter/deims"><img src="https://codeclimate.com/github/lter/deims/badges/gpa.svg" /></a>
## Requirements ##

* [Base Drupal 7 requirements](http://drupal.org/requirements)
* PHP 5.3+
* [Drush](http://drush.ws/)
* [Git](http://git-scm.com/)

## Tested Hardware

DEIMS can run in a modern laptop (say a MacPro), for testing/devel purposes.  For production,
we suggest you use a machine running a Linux distro, with at least 4Gb of RAM, specially if 
you are going to build DEIMS using `drush make`. Early versions on DEIMS running on PHP 5.3.8 
ran on old PC Desktops with just 2Gb of RAM. However, with PHP 5.5.* or above, you may run into
trouble with limited RAM.  The more RAM the better!

We installed DEIMS in Solaris, using a pre-built LAMP, but generally speaking, according
to our tests, Linux has better tuned in LAMPs or LEMPs, and runs those stacks more 
efficiently out of the box. We do not know enough Solaris to make LAMPs fly. 

We heard of cases when DEIMS was installed in a WAMP stack (Windows). Folks (in Taiwan) installed 
DEIMS using a PostGres backend (see patches/issues to make that happen). Please tell us your
experiences.


## Instructions ##

The following instructions assume that you clone this profile into a directory
'above' your web server root. The web server root directory in these examples
is _www_.

### Installing ###

Installing the profile involved 4 steps.

1.  Clone the profile.
2.  Build the profile into your web root.
3.  Create a database for your site to connect to.
4.  Navigate to your site in your web browser to complete the install process.

For the example commands below, 'www' represents the complete path to your site's desired webroot.

[Fork the repo](https://help.github.com/articles/fork-a-repo/), then clone your forked copy with this:

* `git clone --branch 7.x-1.x git@github.com:lter/deims.git`

Optionally, you can specify the destination folder by adding the folder name to the end of the line above.
Build the site into your webroot:

* `cd deims`
* `drush make build-deims.make '/path/to/your-site/www' --prepare-install --contrib-destination=profiles/deims`

Hint: Make use of symbolink links, so you dont have to use prepend all your command line work with sudo. For example,
clone DEIMS to your home dir, then your drush make would may be like this just be:
* `drush make build-deims.make www --prepare-install --contrib-destination=profiles/deims`
After which, you would simply create your link. For example, in Debian Ubuntu:

* sudo ln -s /home/myusername/deims/www /var/www/html/deims

At this point, it is advisable you visit your installed DEIMS profile using the browser to complete the install. There are some configuration steps that are best deal with when using the UI wizard (as oppossed to `drush si deims`)

### Update existing site ###

Updates of Drupal Profiles often follow a different timeline and workflow than your typical Drupal Site.  In our case, the DEIMS Profile Drupal has a few enhancements that are lost if updated without care to carry these enhacements. We advise to wait for a new release of DEIMS before updating on your own - but if you do, make sure the enhancements are ported, otherwise you may experience issues after the update.

*Note: updating an existing site from the profile is not yet supported. You must rebuild the site not using an existing database install.*  The following may work only on specific updates - best to wait for a bundle or Read advisories and guidelines per update, for that check the [DEIMS google groups](https://groups.google.com/forum/#!forum/deims). 

* `git pull`
* `cd www`
* `drush make ../build-deims.make`
* `drush updatedb`

### Further documentation:
Check out videos on YouTube as well as [the Book of DEIMS](https://docs.google.com/document/d/1zf5O56_WjMTRngSzY7vuDIT-lMLS0DljoGBqiAM5lAw).

