<?php

// Hide OG registration Cancel link
drupal_render($form['multiform'][0]['actions']['cancel']);
$form['multiform'][2]['#attributes']['class'][] = 'form-actions';

print drupal_render_children($form);
