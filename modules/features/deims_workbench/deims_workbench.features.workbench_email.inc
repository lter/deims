<?php
/**
 * @file
 * deims_workbench.features.workbench_email.inc
 */

/**
 * Implements hook_workbench_email_export().
 */
function deims_workbench_workbench_email_export() {
  $items = array(
    'draft:needs_review:information manager' => array(
      'from_name' => 'draft',
      'to_name' => 'needs_review',
      'role' => 'information manager',
    ),
    'needs_contributor_work:needs_review:information manager' => array(
      'from_name' => 'needs_contributor_work',
      'to_name' => 'needs_review',
      'role' => 'information manager',
    ),
    'needs_review:draft:data contributor' => array(
      'from_name' => 'needs_review',
      'to_name' => 'draft',
      'role' => 'data contributor',
    ),
    'needs_review:draft:information manager' => array(
      'from_name' => 'needs_review',
      'to_name' => 'draft',
      'role' => 'information manager',
    ),
    'needs_review:needs_contributor_work:data contributor' => array(
      'from_name' => 'needs_review',
      'to_name' => 'needs_contributor_work',
      'role' => 'data contributor',
    ),
  );
  return $items;
}
