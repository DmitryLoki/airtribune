<?php

// Hide OG registration Cancel link
drupal_render($form['multiform'][0]['actions']['cancel']);

print drupal_render_children($form);
