
Welcome to HybridAuth for Drupal

Installation:
-------------
Install as any other module - http://drupal.org/documentation/install/modules-themes

This module needs third-party library to work with authentication providers - HybridAuth.
Download it at http://hybridauth.sourceforge.net/download.html and unpack into 
'sites/all/libraries/hybridauth' directory.
HybridAuth library requires php-curl extension.

If you need additional providers support like Mail.ru - then you need to download 
additional providers package and then copy needed additional providers to the library.
For instance, to get Mail.ru provider working you need to copy 'hybridauth-mailru/Providers/Mailru.php' 
to 'hybridauth/Hybrid/Providers/Mailru.php' and you are good to go.
After that you just need to configure your application ID, private and secret keys at module configuration pages.

After installation please go through the configuration settings and grant your users permission to use
HybridAuth:
- anonymous users - to login using HybridAuth widget
- authenticated users - to add more HybridAuth identities to the account

Dependencies:
-------------
- Ctools module (http://drupal.org/project/ctools) - it is used fo an overlay and to manage icon pack plugins.
Yes, you can now easily have your own icon packs as Ctools plugins.

To make it happen you need to implement hook_ctools_plugin_directory():
/**
 * Implements hook_ctools_plugin_directory().
 */
function mymodule_ctools_plugin_directory($module, $type) {
  if ($module == 'hybridauth' && $type == 'icon_pack') {
    return 'plugins/icon_pack';
  }
}

And then place your icon pack plugins into 'plugins/icon_pack/iconpackname".
This directory should contain 2 or 3 files - plugin definition and css/js files:
plugins/icon_pack/iconpackname/iconpackname.inc
***********************************************
<?php

/**
 * Plugin declaration.
 */
$plugin = array(
  'title' => t('Mymodule icon pack'),
  //specify css file name to include
  'css' => 'iconpackname.css',
  //specify 'js' key if js file needs to be included
  'js' => 'iconpackname.js',
);
***********************************************

Take a look at these modules icon packs in "plugins/icon_pack" and you will figure it out.
Themes can also define their icon packs - turn to Ctools module documentation on how themes should declare their plugins.

Recommended additions:
----------------------
It is recommended to have the following modules:
- Token (http://drupal.org/project/token) - to get a browsable list of available tokens on administration pages.
- Rules (http://drupal.org/project/rules) - to map HybridAuth data to user profile fields and other great stuff.
See this issue for a working example - http://drupal.org/node/1808456
- Real name (http://drupal.org/project/realname) - as it caches display names and improves performance of your site.
