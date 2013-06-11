<?php
/**
 * @file
 * deims_workbench.features.workbench_moderation_states.inc
 */

/**
 * Implements hook_workbench_moderation_export_states().
 */
function deims_workbench_workbench_moderation_export_states() {
  $items = array(
    'draft' => array(
      'name' => 'draft',
      'label' => 'Draft',
      'description' => 'Work in progress',
      'weight' => '-10',
    ),
    'needs_contributor_work' => array(
      'name' => 'needs_contributor_work',
      'label' => 'Needs Contributor Work',
      'description' => 'Draft needs more work from a contributor before published.',
      'weight' => '-9',
    ),
    'needs_review' => array(
      'name' => 'needs_review',
      'label' => 'Needs IM Review',
      'description' => 'Ready Information Manager moderation',
      'weight' => '-8',
    ),
    'published' => array(
      'name' => 'published',
      'label' => 'Published',
      'description' => 'Make this version live',
      'weight' => '-6',
    ),
    'ready_for_publication' => array(
      'name' => 'ready_for_publication',
      'label' => 'Ready for Publication',
      'description' => 'Ready to make this version live, but hold for now.',
      'weight' => '-7',
    ),
  );
  return $items;
}
