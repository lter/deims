# DEIMS Install Profile #

## Requirements ##

* [Base Drupal 7 requirements](http://drupal.org/requirements)
* PHP 5.3+
* [Drush](http://drush.ws/)
* [Git](http://git-scm.com/)

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

*Note: updating an existing site from the profile is not yet supported. You must rebuild the site not using an existing database install.*

* `git pull`
* `cd www`
* `drush make ../build-deims.make`
* `drush updatedb`
