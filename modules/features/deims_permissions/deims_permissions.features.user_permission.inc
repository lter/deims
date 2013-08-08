<?php
/**
 * @file
 * deims_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function deims_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration menu.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: access administration pages.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access all views.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: access biblio content.
  $permissions['access biblio content'] = array(
    'name' => 'access biblio content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: access contextual links.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'contextual',
  );

  // Exported permission: access print.
  $permissions['access print'] = array(
    'name' => 'access print',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'print',
  );

  // Exported permission: access private fields.
  $permissions['access private fields'] = array(
    'name' => 'access private fields',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: access site in maintenance mode.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access site reports.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access site-wide contact form.
  $permissions['access site-wide contact form'] = array(
    'name' => 'access site-wide contact form',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: access toolbar.
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'toolbar',
  );

  // Exported permission: access user contact forms.
  $permissions['access user contact forms'] = array(
    'name' => 'access user contact forms',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: access user profiles.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: access workbench.
  $permissions['access workbench'] = array(
    'name' => 'access workbench',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench',
  );

  // Exported permission: access workbench access by role.
  $permissions['access workbench access by role'] = array(
    'name' => 'access workbench access by role',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_access',
  );

  // Exported permission: admin_classes.
  $permissions['admin_classes'] = array(
    'name' => 'admin_classes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'ds_ui',
  );

  // Exported permission: admin_display_suite.
  $permissions['admin_display_suite'] = array(
    'name' => 'admin_display_suite',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'ds',
  );

  // Exported permission: admin_fields.
  $permissions['admin_fields'] = array(
    'name' => 'admin_fields',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'ds_ui',
  );

  // Exported permission: admin_view_modes.
  $permissions['admin_view_modes'] = array(
    'name' => 'admin_view_modes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'ds_ui',
  );

  // Exported permission: administer actions.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer administration menu select.
  $permissions['administer administration menu select'] = array(
    'name' => 'administer administration menu select',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'admin_select',
  );

  // Exported permission: administer biblio.
  $permissions['administer biblio'] = array(
    'name' => 'administer biblio',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: administer blocks.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'block',
  );

  // Exported permission: administer contact forms.
  $permissions['administer contact forms'] = array(
    'name' => 'administer contact forms',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: administer content types.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: administer custom breadcrumbs.
  $permissions['administer custom breadcrumbs'] = array(
    'name' => 'administer custom breadcrumbs',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'custom_breadcrumbs',
  );

  // Exported permission: administer entity view modes.
  $permissions['administer entity view modes'] = array(
    'name' => 'administer entity view modes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'entity_view_mode',
  );

  // Exported permission: administer facets.
  $permissions['administer facets'] = array(
    'name' => 'administer facets',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'facetapi',
  );

  // Exported permission: administer features.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: administer field permissions.
  $permissions['administer field permissions'] = array(
    'name' => 'administer field permissions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: administer file types.
  $permissions['administer file types'] = array(
    'name' => 'administer file types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: administer files.
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: administer filters.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: administer image styles.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'image',
  );

  // Exported permission: administer menu.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'menu',
  );

  // Exported permission: administer module filter.
  $permissions['administer module filter'] = array(
    'name' => 'administer module filter',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'module_filter',
  );

  // Exported permission: administer modules.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer nodes.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: administer pathauto.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: administer permissions.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: administer print.
  $permissions['administer print'] = array(
    'name' => 'administer print',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'print',
  );

  // Exported permission: administer schema.
  $permissions['administer schema'] = array(
    'name' => 'administer schema',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'schema',
  );

  // Exported permission: administer search.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: administer search_api.
  $permissions['administer search_api'] = array(
    'name' => 'administer search_api',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'search_api',
  );

  // Exported permission: administer shortcuts.
  $permissions['administer shortcuts'] = array(
    'name' => 'administer shortcuts',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: administer site configuration.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer software updates.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer superfish.
  $permissions['administer superfish'] = array(
    'name' => 'administer superfish',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'superfish',
  );

  // Exported permission: administer taxonomy.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: administer themes.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer url aliases.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: administer users.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: administer views.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: administer workbench.
  $permissions['administer workbench'] = array(
    'name' => 'administer workbench',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench',
  );

  // Exported permission: administer workbench access.
  $permissions['administer workbench access'] = array(
    'name' => 'administer workbench access',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_access',
  );

  // Exported permission: administer workbench moderation.
  $permissions['administer workbench moderation'] = array(
    'name' => 'administer workbench moderation',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: assign workbench access.
  $permissions['assign workbench access'] = array(
    'name' => 'assign workbench access',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_access',
  );

  // Exported permission: batch update workbench access.
  $permissions['batch update workbench access'] = array(
    'name' => 'batch update workbench access',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_access',
  );

  // Exported permission: block IP addresses.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: bypass file access.
  $permissions['bypass file access'] = array(
    'name' => 'bypass file access',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: bypass node access.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: bypass workbench moderation.
  $permissions['bypass workbench moderation'] = array(
    'name' => 'bypass workbench moderation',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: cancel account.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: change own username.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: create article content.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create biblio content.
  $permissions['create biblio content'] = array(
    'name' => 'create biblio content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create data_set content.
  $permissions['create data_set content'] = array(
    'name' => 'create data_set content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create data_source content.
  $permissions['create data_source content'] = array(
    'name' => 'create data_source content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create field_doi.
  $permissions['create field_doi'] = array(
    'name' => 'create field_doi',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: create field_eml_hash.
  $permissions['create field_eml_hash'] = array(
    'name' => 'create field_eml_hash',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: create field_eml_revision_id.
  $permissions['create field_eml_revision_id'] = array(
    'name' => 'create field_eml_revision_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: create field_eml_valid.
  $permissions['create field_eml_valid'] = array(
    'name' => 'create field_eml_valid',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: create files.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: create image_gallery content.
  $permissions['create image_gallery content'] = array(
    'name' => 'create image_gallery content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create page content.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create person content.
  $permissions['create person content'] = array(
    'name' => 'create person content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create project content.
  $permissions['create project content'] = array(
    'name' => 'create project content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create research_site content.
  $permissions['create research_site content'] = array(
    'name' => 'create research_site content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create url aliases.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: customize shortcut links.
  $permissions['customize shortcut links'] = array(
    'name' => 'customize shortcut links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: delete any article content.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any audio files.
  $permissions['delete any audio files'] = array(
    'name' => 'delete any audio files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete any biblio content.
  $permissions['delete any biblio content'] = array(
    'name' => 'delete any biblio content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any data_set content.
  $permissions['delete any data_set content'] = array(
    'name' => 'delete any data_set content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any data_source content.
  $permissions['delete any data_source content'] = array(
    'name' => 'delete any data_source content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any document files.
  $permissions['delete any document files'] = array(
    'name' => 'delete any document files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete any image files.
  $permissions['delete any image files'] = array(
    'name' => 'delete any image files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete any image_gallery content.
  $permissions['delete any image_gallery content'] = array(
    'name' => 'delete any image_gallery content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any page content.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any person content.
  $permissions['delete any person content'] = array(
    'name' => 'delete any person content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any project content.
  $permissions['delete any project content'] = array(
    'name' => 'delete any project content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any research_site content.
  $permissions['delete any research_site content'] = array(
    'name' => 'delete any research_site content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any video files.
  $permissions['delete any video files'] = array(
    'name' => 'delete any video files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own article content.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own audio files.
  $permissions['delete own audio files'] = array(
    'name' => 'delete own audio files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own biblio content.
  $permissions['delete own biblio content'] = array(
    'name' => 'delete own biblio content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own data_set content.
  $permissions['delete own data_set content'] = array(
    'name' => 'delete own data_set content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own data_source content.
  $permissions['delete own data_source content'] = array(
    'name' => 'delete own data_source content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own document files.
  $permissions['delete own document files'] = array(
    'name' => 'delete own document files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own image files.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own image_gallery content.
  $permissions['delete own image_gallery content'] = array(
    'name' => 'delete own image_gallery content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own page content.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own person content.
  $permissions['delete own person content'] = array(
    'name' => 'delete own person content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own project content.
  $permissions['delete own project content'] = array(
    'name' => 'delete own project content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own research_site content.
  $permissions['delete own research_site content'] = array(
    'name' => 'delete own research_site content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own video files.
  $permissions['delete own video files'] = array(
    'name' => 'delete own video files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete revisions.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete terms in 1.
  $permissions['delete terms in 1'] = array(
    'name' => 'delete terms in 1',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 2.
  $permissions['delete terms in 2'] = array(
    'name' => 'delete terms in 2',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 3.
  $permissions['delete terms in 3'] = array(
    'name' => 'delete terms in 3',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 4.
  $permissions['delete terms in 4'] = array(
    'name' => 'delete terms in 4',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 5.
  $permissions['delete terms in 5'] = array(
    'name' => 'delete terms in 5',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: display drupal links.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: download any audio files.
  $permissions['download any audio files'] = array(
    'name' => 'download any audio files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download any document files.
  $permissions['download any document files'] = array(
    'name' => 'download any document files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download any image files.
  $permissions['download any image files'] = array(
    'name' => 'download any image files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download any video files.
  $permissions['download any video files'] = array(
    'name' => 'download any video files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own audio files.
  $permissions['download own audio files'] = array(
    'name' => 'download own audio files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own document files.
  $permissions['download own document files'] = array(
    'name' => 'download own document files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own image files.
  $permissions['download own image files'] = array(
    'name' => 'download own image files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own video files.
  $permissions['download own video files'] = array(
    'name' => 'download own video files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: eck add bundles.
  $permissions['eck add bundles'] = array(
    'name' => 'eck add bundles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck add entities.
  $permissions['eck add entities'] = array(
    'name' => 'eck add entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck add entity types.
  $permissions['eck add entity types'] = array(
    'name' => 'eck add entity types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck add project_role bundles.
  $permissions['eck add project_role bundles'] = array(
    'name' => 'eck add project_role bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add project_role project_role entities.
  $permissions['eck add project_role project_role entities'] = array(
    'name' => 'eck add project_role project_role entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add site_details bundles.
  $permissions['eck add site_details bundles'] = array(
    'name' => 'eck add site_details bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add site_details site_details entities.
  $permissions['eck add site_details site_details entities'] = array(
    'name' => 'eck add site_details site_details entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer bundles.
  $permissions['eck administer bundles'] = array(
    'name' => 'eck administer bundles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck administer entities.
  $permissions['eck administer entities'] = array(
    'name' => 'eck administer entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck administer entity types.
  $permissions['eck administer entity types'] = array(
    'name' => 'eck administer entity types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck administer project_role bundles.
  $permissions['eck administer project_role bundles'] = array(
    'name' => 'eck administer project_role bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer project_role project_role entities.
  $permissions['eck administer project_role project_role entities'] = array(
    'name' => 'eck administer project_role project_role entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer site_details bundles.
  $permissions['eck administer site_details bundles'] = array(
    'name' => 'eck administer site_details bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer site_details site_details entities.
  $permissions['eck administer site_details site_details entities'] = array(
    'name' => 'eck administer site_details site_details entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete bundles.
  $permissions['eck delete bundles'] = array(
    'name' => 'eck delete bundles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck delete entities.
  $permissions['eck delete entities'] = array(
    'name' => 'eck delete entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck delete entity types.
  $permissions['eck delete entity types'] = array(
    'name' => 'eck delete entity types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck delete project_role bundles.
  $permissions['eck delete project_role bundles'] = array(
    'name' => 'eck delete project_role bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete project_role project_role entities.
  $permissions['eck delete project_role project_role entities'] = array(
    'name' => 'eck delete project_role project_role entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete site_details bundles.
  $permissions['eck delete site_details bundles'] = array(
    'name' => 'eck delete site_details bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete site_details site_details entities.
  $permissions['eck delete site_details site_details entities'] = array(
    'name' => 'eck delete site_details site_details entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit bundles.
  $permissions['eck edit bundles'] = array(
    'name' => 'eck edit bundles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck edit entities.
  $permissions['eck edit entities'] = array(
    'name' => 'eck edit entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck edit entity types.
  $permissions['eck edit entity types'] = array(
    'name' => 'eck edit entity types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck edit project_role bundles.
  $permissions['eck edit project_role bundles'] = array(
    'name' => 'eck edit project_role bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit project_role project_role entities.
  $permissions['eck edit project_role project_role entities'] = array(
    'name' => 'eck edit project_role project_role entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit site_details bundles.
  $permissions['eck edit site_details bundles'] = array(
    'name' => 'eck edit site_details bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit site_details site_details entities.
  $permissions['eck edit site_details site_details entities'] = array(
    'name' => 'eck edit site_details site_details entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list bundles.
  $permissions['eck list bundles'] = array(
    'name' => 'eck list bundles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck list entities.
  $permissions['eck list entities'] = array(
    'name' => 'eck list entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck list entity types.
  $permissions['eck list entity types'] = array(
    'name' => 'eck list entity types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck list project_role bundles.
  $permissions['eck list project_role bundles'] = array(
    'name' => 'eck list project_role bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list project_role project_role entities.
  $permissions['eck list project_role project_role entities'] = array(
    'name' => 'eck list project_role project_role entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list site_details bundles.
  $permissions['eck list site_details bundles'] = array(
    'name' => 'eck list site_details bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list site_details site_details entities.
  $permissions['eck list site_details site_details entities'] = array(
    'name' => 'eck list site_details site_details entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view entities.
  $permissions['eck view entities'] = array(
    'name' => 'eck view entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'eck',
  );

  // Exported permission: eck view project_role project_role entities.
  $permissions['eck view project_role project_role entities'] = array(
    'name' => 'eck view project_role project_role entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view site_details site_details entities.
  $permissions['eck view site_details site_details entities'] = array(
    'name' => 'eck view site_details site_details entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: edit any article content.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any audio files.
  $permissions['edit any audio files'] = array(
    'name' => 'edit any audio files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit any biblio content.
  $permissions['edit any biblio content'] = array(
    'name' => 'edit any biblio content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any data_set content.
  $permissions['edit any data_set content'] = array(
    'name' => 'edit any data_set content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any data_source content.
  $permissions['edit any data_source content'] = array(
    'name' => 'edit any data_source content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any document files.
  $permissions['edit any document files'] = array(
    'name' => 'edit any document files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit any image files.
  $permissions['edit any image files'] = array(
    'name' => 'edit any image files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit any image_gallery content.
  $permissions['edit any image_gallery content'] = array(
    'name' => 'edit any image_gallery content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any page content.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any person content.
  $permissions['edit any person content'] = array(
    'name' => 'edit any person content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any project content.
  $permissions['edit any project content'] = array(
    'name' => 'edit any project content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any research_site content.
  $permissions['edit any research_site content'] = array(
    'name' => 'edit any research_site content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any video files.
  $permissions['edit any video files'] = array(
    'name' => 'edit any video files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit biblio authors.
  $permissions['edit biblio authors'] = array(
    'name' => 'edit biblio authors',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: edit by all biblio authors.
  $permissions['edit by all biblio authors'] = array(
    'name' => 'edit by all biblio authors',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: edit field_doi.
  $permissions['edit field_doi'] = array(
    'name' => 'edit field_doi',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit field_eml_hash.
  $permissions['edit field_eml_hash'] = array(
    'name' => 'edit field_eml_hash',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit field_eml_revision_id.
  $permissions['edit field_eml_revision_id'] = array(
    'name' => 'edit field_eml_revision_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit field_eml_valid.
  $permissions['edit field_eml_valid'] = array(
    'name' => 'edit field_eml_valid',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit own article content.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own audio files.
  $permissions['edit own audio files'] = array(
    'name' => 'edit own audio files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit own biblio content.
  $permissions['edit own biblio content'] = array(
    'name' => 'edit own biblio content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own data_set content.
  $permissions['edit own data_set content'] = array(
    'name' => 'edit own data_set content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own data_source content.
  $permissions['edit own data_source content'] = array(
    'name' => 'edit own data_source content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own document files.
  $permissions['edit own document files'] = array(
    'name' => 'edit own document files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit own field_doi.
  $permissions['edit own field_doi'] = array(
    'name' => 'edit own field_doi',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit own field_eml_hash.
  $permissions['edit own field_eml_hash'] = array(
    'name' => 'edit own field_eml_hash',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit own field_eml_revision_id.
  $permissions['edit own field_eml_revision_id'] = array(
    'name' => 'edit own field_eml_revision_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit own field_eml_valid.
  $permissions['edit own field_eml_valid'] = array(
    'name' => 'edit own field_eml_valid',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: edit own image files.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit own image_gallery content.
  $permissions['edit own image_gallery content'] = array(
    'name' => 'edit own image_gallery content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own page content.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own person content.
  $permissions['edit own person content'] = array(
    'name' => 'edit own person content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own project content.
  $permissions['edit own project content'] = array(
    'name' => 'edit own project content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own research_site content.
  $permissions['edit own research_site content'] = array(
    'name' => 'edit own research_site content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own video files.
  $permissions['edit own video files'] = array(
    'name' => 'edit own video files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit terms in 1.
  $permissions['edit terms in 1'] = array(
    'name' => 'edit terms in 1',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 2.
  $permissions['edit terms in 2'] = array(
    'name' => 'edit terms in 2',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 3.
  $permissions['edit terms in 3'] = array(
    'name' => 'edit terms in 3',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 4.
  $permissions['edit terms in 4'] = array(
    'name' => 'edit terms in 4',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 5.
  $permissions['edit terms in 5'] = array(
    'name' => 'edit terms in 5',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: flush caches.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: import from file.
  $permissions['import from file'] = array(
    'name' => 'import from file',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: manage features.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: manage project_role properties.
  $permissions['manage project_role properties'] = array(
    'name' => 'manage project_role properties',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: manage site_details properties.
  $permissions['manage site_details properties'] = array(
    'name' => 'manage site_details properties',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: moderate content from draft to needs_review.
  $permissions['moderate content from draft to needs_review'] = array(
    'name' => 'moderate content from draft to needs_review',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from needs_review to draft.
  $permissions['moderate content from needs_review to draft'] = array(
    'name' => 'moderate content from needs_review to draft',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from needs_review to published.
  $permissions['moderate content from needs_review to published'] = array(
    'name' => 'moderate content from needs_review to published',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: node-specific print configuration.
  $permissions['node-specific print configuration'] = array(
    'name' => 'node-specific print configuration',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'print_ui',
  );

  // Exported permission: notify of path changes.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: search content.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: select account cancellation method.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: select administration menu.
  $permissions['select administration menu'] = array(
    'name' => 'select administration menu',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'admin_select',
  );

  // Exported permission: show download links.
  $permissions['show download links'] = array(
    'name' => 'show download links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show export links.
  $permissions['show export links'] = array(
    'name' => 'show export links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show filter tab.
  $permissions['show filter tab'] = array(
    'name' => 'show filter tab',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show own download links.
  $permissions['show own download links'] = array(
    'name' => 'show own download links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show sort links.
  $permissions['show sort links'] = array(
    'name' => 'show sort links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: switch shortcut sets.
  $permissions['switch shortcut sets'] = array(
    'name' => 'switch shortcut sets',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: use PHP for label patterns.
  $permissions['use PHP for label patterns'] = array(
    'name' => 'use PHP for label patterns',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'auto_entitylabel',
  );

  // Exported permission: use advanced search.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: use php in custom breadcrumbs.
  $permissions['use php in custom breadcrumbs'] = array(
    'name' => 'use php in custom breadcrumbs',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'custom_breadcrumbs',
  );

  // Exported permission: use text format filtered_html.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: use text format full_html.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'filter',
  );

  // Exported permission: use workbench_moderation my drafts tab.
  $permissions['use workbench_moderation my drafts tab'] = array(
    'name' => 'use workbench_moderation my drafts tab',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: use workbench_moderation needs review tab.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view all unpublished content.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view field_doi.
  $permissions['view field_doi'] = array(
    'name' => 'view field_doi',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view field_eml_hash.
  $permissions['view field_eml_hash'] = array(
    'name' => 'view field_eml_hash',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view field_eml_revision_id.
  $permissions['view field_eml_revision_id'] = array(
    'name' => 'view field_eml_revision_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view field_eml_valid.
  $permissions['view field_eml_valid'] = array(
    'name' => 'view field_eml_valid',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view files.
  $permissions['view files'] = array(
    'name' => 'view files',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view full text.
  $permissions['view full text'] = array(
    'name' => 'view full text',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: view moderation history.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view moderation messages.
  $permissions['view moderation messages'] = array(
    'name' => 'view moderation messages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view own field_doi.
  $permissions['view own field_doi'] = array(
    'name' => 'view own field_doi',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view own field_eml_hash.
  $permissions['view own field_eml_hash'] = array(
    'name' => 'view own field_eml_hash',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view own field_eml_revision_id.
  $permissions['view own field_eml_revision_id'] = array(
    'name' => 'view own field_eml_revision_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view own field_eml_valid.
  $permissions['view own field_eml_valid'] = array(
    'name' => 'view own field_eml_valid',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: view own files.
  $permissions['view own files'] = array(
    'name' => 'view own files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view own private files.
  $permissions['view own private files'] = array(
    'name' => 'view own private files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: view private files.
  $permissions['view private files'] = array(
    'name' => 'view private files',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: view the administration theme.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: view workbench access information.
  $permissions['view workbench access information'] = array(
    'name' => 'view workbench access information',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_access',
  );

  // Exported permission: view workbench taxonomy pages.
  $permissions['view workbench taxonomy pages'] = array(
    'name' => 'view workbench taxonomy pages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_access',
  );

  return $permissions;
}
