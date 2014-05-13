<?php

// Uncomment the following strings if required.
/*
$form['field_header_image']['und'][0]['select']['#title'] = t('Add image');
$form['field_header_image']['und'][0]['remove']['#title'] = t('Delete');
$form['personalisation']['basic_url'] = $form['basic_url'];
$form['personalisation']['optional_url'] = $form['optional_url'];
$form['personalisation']['field_header_image'] = $form['field_header_image'];
$form['personalisation']['field_social_links'] = $form['field_social_links'];
unset($form['basic_url']);
unset($form['field_header_image']);
*/

print drupal_render_children($form);
