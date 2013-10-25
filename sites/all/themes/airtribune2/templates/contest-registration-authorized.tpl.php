<?php

// Hide OG registration Cancel link
drupal_render($form['multiform'][0]['actions']['cancel']);

drupal_render($form['multiform'][1]['actions']);

$form['multiform'][2]['register']['#prefix'] = '<div class="form-actions">';
$form['multiform'][2]['register']['#suffix'] = '</div>';

print drupal_render_children($form);
