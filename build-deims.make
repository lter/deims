222api = 2
core = 7.x

; Include building core
includes[] = "drupal-org-core.make"

; @todo When the DEIMS install profile is available on Drupal.org, remove this and uncomment the next part.
includes[] = "drupal-org.make"

; Dependencies
dependencies[] = views

; Enable the custom modules
dependencies[] = data_set_content_type

; Download the DEIMS install profile.
projects[deims][type] = profile
projects[deims][download][type] = "git"
projects[deims][download][url] = "git@github.com:palantirnet/deims-profile.git"
projects[deims][download][branch] = "7.x-1.x"
projects[deims][subdir] = ""