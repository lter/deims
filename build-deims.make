api = 2
core = 7.x

; Include building core
includes[] = "drupal-org-core.make"

; Download the DEIMS install profile.
projects[deims][type] = profile
projects[deims][download][type] = "git"
projects[deims][download][url] = "git@github.com:lter/deims.git"
projects[deims][download][branch] = "45-core-and-contrib-updates"
projects[deims][subdir] = ""
