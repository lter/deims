<?php

/**
 * @file
 * Theme callbacks for the DEIMS Data Explorer module.
 */

/**
 * Clone of theme_file_link() for downloading, with optional filesize display.
 */
function theme_deims_data_explorer_file_download_link($variables) {
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $uri = file_entity_download_uri($file);
  $icon = theme('file_icon', array('file' => $file, 'icon_directory' => $icon_directory));

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  //$uri['options']['attributes']['type'] = $file->filemime . '; length=' . $file->filesize;

  // Use the description as the link text if available.
  if (empty($file->description)) {
    $link_text = $file->filename;
  }
  else {
    $link_text = $file->description;
    $uri['options']['title'] = check_plain($file->filename);
  }

  $output = '<span class="file">' . $icon . ' ' . l($link_text, $uri['path'], $uri['options']);

  if ($variables['filesize']) {
    $output .= ' ' . '<span class="file-size">(' . format_size($file->filesize) . ')</span>';
  }
  $output .= '</span>';

  return $output;
}
