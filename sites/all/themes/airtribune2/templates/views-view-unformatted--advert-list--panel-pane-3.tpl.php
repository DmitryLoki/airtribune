<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

$output = '';

if (!empty($title)) {
  $output .= '<h3>' . $title . '</h3>';
}
foreach ($rows as $id => $row) {
  $output .= $prefixes[$id] . '<div' . (($classes_array[$id]) ? ' class="' . $classes_array[$id] .'"' : '') . '>';
    $output .= $row;
  $output .= '</div>' . $suffixes[$id];
} 

print $output;

?>
