<?php

// Hide OG registration Cancel link
drupal_render($form['multiform'][1]['actions']['cancel']);

print drupal_render_children($form);
