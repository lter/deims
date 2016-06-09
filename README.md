# DEIMS Install Profile #
<a href="https://codeclimate.com/github/lter/deims"><img src="https://codeclimate.com/github/lter/deims/badges/gpa.svg" /></a>
## Requirements ##

* [Base Drupal 7 requirements](http://drupal.org/requirements)
* PHP 5.3+
* [Drush](http://drush.ws/)
* [Git](http://git-scm.com/)

## Tested Hardware

DEIMS can run in a modern laptop (say a MacPro), for testing/devel purposes.  For production,
we suggest you use a machine running a Linux distro, with at least 2Gb of RAM, specially if 
you are going to build DEIMS using `drush make`. Having said that, we have built DEIMS on 
old PC Desktops with just 1Gb of RAM running PHP 5.3.*. However, with PHP 5.5.*, you will need 
more that 1.5Gb of RAM, most likely 2.5Gb at least.

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

Clone the repo:

* `git clone --branch 7.x-1.x git@github.com:lter/deims.git`

Build the site into your webroot:

* `cd deims`
* `drush make build-deims.make '/path/to/your-site/www' --prepare-install --contrib-destination=profiles/deims`

At this point, it is advisable you visit your installed DEIMS profile using the browser to complete the install. There are some configuration steps that are best deal with when using the UI wizard (as oppossed to `drush si deims`)

### Rebuilding an existing site ###

### NOTE: Rebuilding has not been implemented yet. ##

* `git pull`
* `cd www`
* `drush make ../build-deims.make`
* `drush si deims`

### Update existing site ###

Updates of Drupal Profiles often follow a different timeline and workflow than your typical Drupal Site.  In our case, the DEIMS Profile Drupal has a few enhancements that are lost if updated without care to carry these enhacements. We advise to wait for a new release of DEIMS before updating on your own - but if you do, make sure the enhancements are ported, otherwise you may experience issues after the update.

*Note: updating an existing site from the profile is not yet supported. You must rebuild the site not using an existing database install.*  The following may work only on specific updates - best to wait for a bundle or Read advisories and guidelines per update.

* `git pull`
* `cd www`
* `drush make ../build-deims.make`
* `drush updatedb`
