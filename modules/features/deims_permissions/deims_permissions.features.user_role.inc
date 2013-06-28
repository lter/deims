<?php
/**
 * @file
 * deims_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function deims_permissions_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => '5',
  );

  // Exported role: content contributor.
  $roles['content contributor'] = array(
    'name' => 'content contributor',
    'weight' => '2',
  );

  // Exported role: data contributor.
  $roles['data contributor'] = array(
    'name' => 'data contributor',
    'weight' => '3',
  );

  // Exported role: information manager.
  $roles['information manager'] = array(
    'name' => 'information manager',
    'weight' => '4',
  );

  return $roles;
}
