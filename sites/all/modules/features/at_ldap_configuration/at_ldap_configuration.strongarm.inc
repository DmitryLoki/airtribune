<?php
/**
 * @file
 * at_ldap_configuration.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function at_ldap_configuration_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_authentication_conf';
  $strongarm->value = array(
    'sids' => array(
      'codecat' => 'codecat',
    ),
    'authenticationMode' => 1,
    'loginUIUsernameTxt' => NULL,
    'loginUIPasswordTxt' => NULL,
    'ldapUserHelpLinkUrl' => NULL,
    'ldapUserHelpLinkText' => 'Logon Help',
    'emailOption' => 3,
    'emailUpdate' => 1,
    'passwordOption' => 4,
    'allowOnlyIfTextInDn' => array(),
    'excludeIfTextInDn' => array(),
    'allowTestPhp' => '',
    'excludeIfNoAuthorizations' => NULL,
    'ssoRemoteUserStripDomainName' => NULL,
    'ssoExcludedPaths' => array(),
    'ssoExcludedHosts' => array(),
    'seamlessLogin' => NULL,
    'ssoNotifyAuthentication' => NULL,
    'ldapImplementation' => 'mod_auth_sspi',
    'cookieExpire' => NULL,
    'emailTemplate' => '@username@fake-domain.com',
    'emailTemplateHandling' => 3,
    'templateUsagePromptUser' => 0,
    'templateUsageNeverUpdate' => 0,
    'templateUsageResolveConflict' => 0,
    'templateUsagePromptRegex' => '.*@fake-domain\\.com',
    'templateUsageRedirectOnLogin' => 0,
  );
  $export['ldap_authentication_conf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_encryption';
  $strongarm->value = '10';
  $export['ldap_servers_encryption'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_require_ssl_for_credentails';
  $strongarm->value = 0;
  $export['ldap_servers_require_ssl_for_credentails'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_user_conf';
  $strongarm->value = array(
    'drupalAcctProvisionServer' => 'codecat',
    'ldapEntryProvisionServer' => 'codecat',
    'drupalAcctProvisionTriggers' => array(
      2 => '2',
      1 => '1',
    ),
    'ldapEntryProvisionTriggers' => array(
      6 => '6',
      7 => '7',
      8 => '8',
      3 => 0,
    ),
    'orphanedDrupalAcctBehavior' => 'ldap_user_orphan_email',
    'orphanedCheckQty' => '100',
    'userConflictResolve' => 2,
    'manualAccountConflict' => '1',
    'acctCreation' => 4,
    'ldapUserSynchMappings' => array(
      1 => array(
        '[profile2.main.field_full_name.given]' => array(
          'ldap_attr' => '[gn]',
          'user_attr' => '[profile2.main.field_full_name.given]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
          ),
        ),
        '[profile2.main.field_full_name.family]' => array(
          'ldap_attr' => '[sn]',
          'user_attr' => '[profile2.main.field_full_name.family]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
          ),
        ),
        '[profile2.pilot.field_address.locality]' => array(
          'ldap_attr' => '[l]',
          'user_attr' => '[profile2.pilot.field_address.locality]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
          ),
        ),
        '[profile2.pilot.field_address.country]' => array(
          'ldap_attr' => '[c]',
          'user_attr' => '[profile2.pilot.field_address.country]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
          ),
        ),
        '[profile2.pilot.field_phone]' => array(
          'ldap_attr' => '[telephoneNumber]',
          'user_attr' => '[profile2.pilot.field_phone]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
          ),
        ),
        '[field.field_core_id]' => array(
          'ldap_attr' => '[userid]',
          'user_attr' => '[field.field_core_id]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
          ),
        ),
        '[field.field_user_avatar]' => array(
          'ldap_attr' => '[jpegPhoto]',
          'user_attr' => '[field.field_user_avatar]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
        ),
      ),
      2 => array(
        '[dn]' => array(
          'ldap_attr' => '[dn]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'mail=[property.mail],ou=person,dc=airtribune,dc=com',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[sn]' => array(
          'ldap_attr' => '[sn]',
          'user_attr' => '[profile2.main.field_full_name.family]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[cn]' => array(
          'ldap_attr' => '[cn]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '[profile2.main.field_full_name.given] [profile2.main.field_full_name.family]',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[mail]' => array(
          'ldap_attr' => '[mail]',
          'user_attr' => '[property.mail]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[userPassword]' => array(
          'ldap_attr' => '[userPassword]',
          'user_attr' => '[password.user-random]',
          'convert' => 1,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[gn]' => array(
          'ldap_attr' => '[gn]',
          'user_attr' => '[profile2.main.field_full_name.given]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[userid]' => array(
          'ldap_attr' => '[userid]',
          'user_attr' => '[field.field_core_id]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[objectclass:0]' => array(
          'ldap_attr' => '[objectclass:0]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'extensibleObject',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
          ),
        ),
        '[objectclass:1]' => array(
          'ldap_attr' => '[objectclass:1]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'inetOrgPerson',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
          ),
        ),
        '[objectclass:2]' => array(
          'ldap_attr' => '[objectclass:2]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'top',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
          ),
        ),
        '[telephoneNumber]' => array(
          'ldap_attr' => '[telephoneNumber]',
          'user_attr' => '[profile2.pilot.field_phone]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[l]' => array(
          'ldap_attr' => '[l]',
          'user_attr' => '[profile2.pilot.field_address.locality]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[c]' => array(
          'ldap_attr' => '[c]',
          'user_attr' => '[profile2.pilot.field_address.country]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[jpegPhoto]' => array(
          'ldap_attr' => '[jpegPhoto]',
          'user_attr' => '[property.picture]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
      ),
    ),
    'disableAdminPasswordField' => 0,
  );
  $export['ldap_user_conf'] = $strongarm;

  return $export;
}
