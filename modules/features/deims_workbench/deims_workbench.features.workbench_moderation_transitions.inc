<?php
/**
 * @file
 * deims_workbench.features.workbench_moderation_transitions.inc
 */

/**
 * Implements hook_workbench_moderation_export_transitions().
 */
function deims_workbench_workbench_moderation_export_transitions() {
  $items = array(
    'draft:needs_review' => array(
      'from_name' => 'draft',
      'to_name' => 'needs_review',
    ),
    'needs_contributor_work:needs_review' => array(
      'from_name' => 'needs_contributor_work',
      'to_name' => 'needs_review',
    ),
    'needs_review:draft' => array(
      'from_name' => 'needs_review',
      'to_name' => 'draft',
    ),
    'needs_review:needs_contributor_work' => array(
      'from_name' => 'needs_review',
      'to_name' => 'needs_contributor_work',
    ),
    'needs_review:published' => array(
      'from_name' => 'needs_review',
      'to_name' => 'published',
    ),
    'needs_review:ready_for_publication' => array(
      'from_name' => 'needs_review',
      'to_name' => 'ready_for_publication',
    ),
    'ready_for_publication:published' => array(
      'from_name' => 'ready_for_publication',
      'to_name' => 'published',
    ),
  );
  return $items;
}
