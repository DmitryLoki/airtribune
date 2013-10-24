<?php

// Hide OG registration Cancel link
drupal_render($form['multiform'][1]['actions']['cancel']);
$form['multiform'][3]['#attributes']['class'][] = 'form-actions';

print drupal_render_children($form);
