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

* `git clone --branch 7.x-1.x git@github.com:palantirnet/deims-profile.git`
* `cd deims-profile`
* `drush make build-deims.make www --prepare-install --contrib-destination=profiles/deims`
* `cd www`
* `drush si deims`

Optionally, you can configure the database during the site installation by running
the following command *instead* of `drush si deims`:

`drush si deims --db-url=mysql://dbusername:dbpassword@dbhost/databasename`

If you've created a database with the name "databasename" this will install all the
necessary Drupal tables in that database.

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
