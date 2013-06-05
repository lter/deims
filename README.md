# DEIMS Install Profile #

## Requirements ##

* Base Drupal 7 requirements (http://drupal.org/requirements)
* PHP 5.3+
* Drush
* Git

## Instructions ##

The following instructions assume that you clone this profile into a directory
'above' your web server root. The web server root directory in these examples
is _www_.

### Installing ###

* `git clone --branch 7.x-1.x git@github.com:palantirnet/deims-profile.git`
* `cd deims-profile`
* `drush make build-deims.make www --prepare-install --contrib-destination=profiles/deims`
* `cd www`
* `drush si deims`

### Rebuilding an existing site ###

* `git pull`
* `cd www`
* `drush make ../build-deims.make`
* `drush si deims`

### Update existing site: ###

* `git pull`
* `cd www`
* `drush make ../build-deims.make`
* `drush updatedb`
