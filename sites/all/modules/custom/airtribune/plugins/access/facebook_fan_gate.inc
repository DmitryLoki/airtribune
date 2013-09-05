<?php

/**
 * @file
 * Plugin to provide access control based upon facebook user 'like' for page.
 */

// Plugin defenition.
$plugin = array(
  'title' => t('Facebook user fan (clicked LIKE button)'),
  'description' => t('Check whether the user is a fan of our page (already click "like" button).'),
  'callback' => 'airtribune_facebook_fan_gate_access_check',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Check for access.
 */
function airtribune_facebook_fan_gate_access_check($conf, $context) {

  // There should always be a context at this point, but this is safe.
  if (empty($context) || empty($context->data) || !($context->data->type == AIRTRIBUNE_PG_CONTEST_TYPE)) {
    return;
  }

  // Parse facebook request data.
  if ($signed_request = parsePageSignedRequest()) {
    if ($signed_request->page->liked) {
      // User already click "like" button.
      return TRUE;
    }
    else {
      // User not yet our fan (not yet click "like" button)
      return FALSE;
    }
  }
  else {
    // No data from facebook, so probably this page loaded directly, not from facebook iframe.
    return FALSE;
  }

  /*
    // Based on Facebook-API https://github.com/facebook/facebook-php-sdk
    require 'facebook-php-sdk/src/facebook.php';
    $facebook = new Facebook(array(
      'appId'  => '220193031439173',
      'secret' => '32504968a9407ff077a4d7a62b83ef6e',
      'cookie' => true
    ));
    $signed_request = $facebook->getSignedRequest();
    $like_status = $signed_request["page"]["liked"];

    if ($like_status) {
      return TRUE;
    } else {
      return FALSE;
    }
  */
}

/**
 * Help function, to parse facebook request data.
 */
function parsePageSignedRequest() {
  if (isset($_REQUEST['signed_request'])) {
    $encoded_sig = NULL;
    $payload = NULL;
    list($encoded_sig, $payload) = explode('.', $_REQUEST['signed_request'], 2);
    $sig = base64_decode(strtr($encoded_sig, '-_', '+/'));
    $data = json_decode(base64_decode(strtr($payload, '-_', '+/'), TRUE));
    return $data;
  }
  return FALSE;
}
