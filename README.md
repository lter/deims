Install:

* git clone --branch 7.x-1.x git@github.com:palantirnet/deims-profile.git
* cd deims-profile
* drush make build-deims.make www --prepare-install
* cd www
* drush

Rebuild existing site:

* cd ..
* git pull
* cd www
* drush make ../build-deims.make --prepare-install
* drush si deims

Update existing site:

* cd ..
* git pull
* cd www
* drush make ../build-deims.make
* drush updatedb
