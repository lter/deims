api = "2"
core = "7.x"

; -----------------------------------------------------------------------------
; Contributed modules
; -----------------------------------------------------------------------------

projects[addressfield][version] = "1.0-beta4"
projects[addressfield][subdir] = "contrib"

projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][subdir] = "contrib"

projects[admin_select][version] = "1.3"
projects[admin_select][subdir] = "contrib"

projects[auto_entitylabel][version] = "1.2"
projects[auto_entitylabel][subdir] = "contrib"

projects[autosave][version] = "2.2"
projects[autosave][subdir] = "contrib"

projects[backup_migrate][version] = "2.7"
projects[backup_migrate][subdir] = "contrib"

projects[biblio][version] = "1.0-rc5"
projects[biblio][subdir] = "contrib"

projects[ctools][version] = "1.3"
projects[ctools][subdir] = "contrib"

projects[context][version] = "3.0-beta6"
projects[context][subdir] = "contrib"

projects[chosen][type] = module
projects[chosen][download][type] = "git"
projects[chosen][download][url] = "http://git.drupal.org/sandbox/davereid/2029921.git"
projects[chosen][download][branch] = "7.x-1.x"
projects[chosen][subdir] = "contrib"

projects[custom_breadcrumbs][version] = "2.0-alpha3"
projects[custom_breadcrumbs][subdir] = "contrib"

projects[datatables][version] = "1.2"
projects[datatables][subdir] = "contrib"
; Correct errors blocking the install.
projects[datatables][patch][2021741] = "https://drupal.org/files/2021741-installation-blocked-database-errors-requirement-errors.patch"

projects[date][version] = "2.6"
projects[date][subdir] = "contrib"

projects[date_facets][version] = "1.x-dev"
projects[date_facets][subdir] = "contrib"

projects[devel][version] = "1.x-dev"
projects[devel][subdir] = "contrib"

projects[diff][version] = "3.2"
projects[diff][subdir] = "contrib"

projects[ds][version] = "2.4"
projects[ds][subdir] = "contrib"

projects[eck][version] = "2.0-rc2"
projects[eck][subdir] = "contrib"
; Add entity access alter for ECK entities.
projects[eck][patch][1969394] = "http://drupal.org/files/1969394-eck-entity-access-alter.patch"
; Add IEF clone button support
projects[eck][patch][1979686] = "http://drupal.org/files/1979686-eck-ief-clone-button.patch"
; Temporary patch to make the inline form display actual useful fields.
projects[eck][patch][] = "https://gist.github.com/davereid/0014f396fed3f20a66ca/raw/e4f54f8a026dbd1ef4d8981e898ed9782b12a826/deims-eck.patch"

projects[elements][version] = "1.x-dev"
projects[elements][subdir] = "contrib"

projects[email][version] = "1.2"
projects[email][subdir] = "contrib"

projects[entity][version] = "1.1"
projects[entity][subdir] = "contrib"
; Fix for entity_metadata_no_hook_node_access() and new entity objects (required to work with inline_entity_form).
projects[entity][patch][1780646] = "http://drupal.org/files/entity-entity_access-1780646-107.patch"

projects[entitycache][version] = "1.x-dev"
projects[entitycache][subdir] = "contrib"

projects[entityreference][version] = "1.0"
projects[entityreference][subdir] = "contrib"

projects[entity_view_mode][version] = "1.0-rc1"
projects[entity_view_mode][subdir] = "contrib"

projects[extlink][version] = "1.12"
projects[extlink][subdir] = "contrib"

projects[facetapi][version] = "1.3"
projects[facetapi][subdir] = "contrib"

projects[features][version] = "1.x-dev"
projects[features][subdir] = "contrib"

projects[field_permissions][version] = "1.0-beta2"
projects[field_permissions][subdir] = "contrib"

projects[field_referenced_delete][version] = "1.0-rc4"
projects[field_referenced_delete][subdir] = "contrib"

projects[field_validation][version] = "2.3"
projects[field_validation][subdir] = "contrib"

projects[file_download_count][version] = "1.0-beta1"
projects[file_download_count][subdir] = "contrib"

; Dave Reid maintains this, ok to use dev for now.
projects[file_entity][version] = "2.x-dev"
projects[file_entity][subdir] = "contrib"

projects[media][version] = "2.x-dev"
projects[media][subdir] = "contrib"

projects[filefield_sources][version] = "1.8"
projects[filefield_sources][subdir] = "contrib"
; Ensure files that already exist in the files directory are left alone.
projects[filefield_sources][patch][1492374] = "http://drupal.org/files/1492374-ffs-attach-file-same-path.patch"
; Only show files with relevant extensions in the attach select list.
projects[filefield_sources][patch][1492374] = "http://drupal.org/files/2006436-file-attach-extension-filter.patch"

; The field group module has mannnny updates since 7.x-1.1
projects[field_group][version] = "1.x-dev"
projects[field_group][subdir] = "contrib"
; Fix nested vertical/horizontal tabs cause unwanted fieldset labels.
projects[field_group][patch][1945848] = "http://drupal.org/files/1945848-field-group-nested-fieldset-unwanted-labels.patch"

projects[flag][version] = "3.0-rc1"
projects[flag][subdir] = "contrib"

projects[flexslider][version] = "2.0-alpha1"
projects[flexslider][subdir] = "contrib"

projects[geofield][version] = "1.1"
projects[geofield][subdir] = "contrib"

projects[geophp][version] = "1.7"
projects[geophp][subdir] = "contrib"

projects[google_analytics][version] = "1.3"
projects[google_analytics][subdir] = "contrib"

; Dave maintains this module, dev is ok.
projects[helper][version] = "1.x"
projects[helper][subdir] = "contrib"

projects[inline_entity_form][version] = "1.x-dev"
projects[inline_entity_form][subdir] = "contrib"
; Add a 'Clone' button to the widget
projects[inline_entity_form][patch][1590146] = "http://drupal.org/files/ief_clone_button-1590146-18-default-off.patch"
; Limit 'Add new' bundle options when entityreference uses a view for selection
projects[inline_entity_form][patch][1872316] = "http://drupal.org/files/1872316-ief-bundle-selection-node-view_0.patch"

projects[libraries][version] = "2.1"
projects[libraries][subdir] = "contrib"

projects[link][version] = "1.1"
projects[link][subdir] = "contrib"

projects[menu_block][version] = "2.3"
projects[menu_block][subdir] = "contrib"

projects[migrate][version] = "2.6-beta1"
projects[migrate][subdir] = "contrib"
; Rebuild menus when registering or deregistering groups and migrations.
projects[migrate][patch][2011024] = "http://drupal.org/files/2011024-menu-rebuilds_0.patch"

projects[migrate_d2d][version] = "2.1-beta1"
projects[migrate_d2d][subdir] = "contrib"

projects[migrate_extras][version] = "2.x-dev"
projects[migrate_extras][subdir] = "contrib"

projects[module_filter][version] = "1.7"
projects[module_filter][subdir] = "contrib"

projects[name][version] = "1.9"
projects[name][subdir] = "contrib"

projects[noggin][version] = "1.1"
projects[noggin][subdir] = "contrib"

projects[options_element][version] = "1.9"
projects[options_element][subdir] = "contrib"
; For empty values, only show two key/value fields instead of three
projects[options_element][patch][2012198] = "http://drupal.org/files/2012198-options-element-only-two-blank-values-do-not-test.patch"

projects[pathauto][version] = "1.2"
projects[pathauto][subdir] = "contrib"

projects[pathauto_persist][version] = "1.3"
projects[pathauto_persist][subdir] = "contrib"

projects[print][version] = "2.x-dev"
projects[print][subdir] = "contrib"

; Dave Reid maintains this D8 backport, dev release is ok.
projects[responsive_tables][version] = "2.x-dev"
projects[responsive_tables][subdir] = "contrib"

projects[rules][version] = "2.3"
projects[rules][subdir] = "contrib"

projects[schema][version] = "1.0-rc1"
projects[schema][subdir] = "contrib"

projects[schema_reference][version] = "1.0-beta3"
projects[schema_reference][subdir] = "contrib"

projects[search_api][version] = "1.6"
projects[search_api][subdir] = "contrib"

projects[search_api_db][version] = "1.0-rc1"
projects[search_api_db][subdir] = "contrib"

projects[search_api_ranges][version] = "1.4"
projects[search_api_ranges][subdir] = "contrib"

projects[search_api_page][version] = "1.x-dev"
projects[search_api_page][subdir] = "contrib"

projects[select_or_other][version] = "2.17"
projects[select_or_other][subdir] = "contrib"

projects[strongarm][version] = "2.0"
projects[strongarm][subdir] = "contrib"

projects[superfish][version] = "1.9"
projects[superfish][subdir] = "contrib"

projects[taxonomy_csv][version] = "5.10"
projects[taxonomy_csv][subdir] = "contrib"

projects[taxonomy_manager][version] = "1.0"
projects[taxonomy_manager][subdir] = "contrib"

; Dave Reid maintains this D8 backport, dev release is ok.
projects[telephone][version] = "1.x-dev"
projects[telephone][subdir] = "contrib"

projects[term_reference_tree][version] = "1.10"
projects[term_reference_tree][subdir] = "contrib"
; Add filtering to the widget
projects[term_reference_tree][patch][2007164] = "http://drupal.org/files/2007164-filter.patch"

projects[token][version] = "1.5"
projects[token][subdir] = "contrib"

projects[token_field][version] = "1.x-dev"
projects[token_field][subdir] = "contrib"

projects[token_formatters][version] = "1.2"
projects[token_formatters][subdir] = "contrib"

projects[views][version] = "3.7"
projects[views][subdir] = "contrib"

projects[views_bulk_operations][version] = "3.1"
projects[views_bulk_operations][subdir] = "contrib"

projects[views_content_cache][version] = "3.0-alpha2"
projects[views_content_cache][subdir] = "contrib"

projects[webform][version] = "3.19"
projects[webform][subdir] = "contrib"

projects[workbench][version] = "1.2"
projects[workbench][subdir] = "contrib"

projects[workbench_moderation][version] = "1.3"
projects[workbench_moderation][subdir] = "contrib"
; Show revision log message in the workbench message menu_block
projects[workbench_moderation][patch][1972888] = "http://drupal.org/files/1972888-workbench-show-revision-log-message.patch"
; Add features support
projects[workbench_moderation][patch][1314508] = "http://drupal.org/files/1314508-workbench-moderation-features.patch"

projects[workbench_access][version] = "1.2"
projects[workbench_access][subdir] = "contrib"

projects[workbench_email][version] = "2.2"
projects[workbench_email][subdir] = "contrib"

projects[wysiwyg][version] = "2.x-dev"
projects[wysiwyg][subdir] = "contrib"

; -----------------------------------------------------------------------------
; Contributed themes
; -----------------------------------------------------------------------------

projects[adaptivetheme][version] = "3.x-dev"
projects[adaptivetheme][subdir] = "contrib"

projects[pixture_reloaded][version] = "3.x-dev"
projects[pixture_reloaded][subdir] = "contrib"

projects[shiny][version] = "1.2"
projects[shiny][subdir] = "contrib"

; -----------------------------------------------------------------------------
; Libraries
; -----------------------------------------------------------------------------

libraries[ckeditor][download][type]= "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.6.1/ckeditor_3.6.6.1.zip"
libraries[ckeditor][directory_name] = "ckeditor"

libraries[flexslider][download][type] = "get"
libraries[flexslider][download][url] = "https://github.com/woothemes/FlexSlider/archive/master.zip"
libraries[flexslider][download][subtree] = "FlexSlider-master"
libraries[flexslider][directory_name] = "flexslider"

; Currently using a fork of the Chosen module that includes the Chosen library.
;libraries[chosen][download][type] = "get"
;libraries[chosen][download][url] = "https://github.com/koenpunt/chosen/archive/option_adding.zip"
;libraries[chosen][download][subtree] = "chosen-option_adding"
;libraries[chosen][directory_name] = "chosen"

libraries[superfish][download][type] = "get"
libraries[superfish][download][url] = "https://github.com/mehrpadin/Superfish-for-Drupal/archive/1.x.zip"
libraries[superfish][download][subtree] = "Superfish-for-Drupal-1.x"
libraries[superfish][directory_name] = "superfish"

libraries[datatables][download][type]= "get"
libraries[datatables][download][url] = "http://www.datatables.net/releases/DataTables-1.9.4.zip"
libraries[datatables][directory_name] = "datatables"
