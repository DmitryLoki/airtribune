The User Import Framework (UIF) module provides simple, extensible user import via CSV (comma-separated value) files. The guiding philosophy is to make the import process as simple as possible for the end-user (the user doing the import). Hooks allow the developer to add the bells and whistles they need while providing a strong base of support. 

User import is a two-step process. 1) The user chooses a csv file, along with specifying the number of records they'd like to preview (this preview can be skipped by power users). The user can also choose whether new users get a welcome email. 2) If happy with the preview, user submits the form again and users are created (or modified, if the user already exists).


Installation
------------
1) Copy the uif directory to the modules folder in your installation.

2) Enable the module.

3) Enable 'import users' permission for any role(s) you want to be able to do imports.

4) Go to People > Import (/admin/people/uif) and import some users.


Basic Setup
-----------
The only field required for user import is an email address (mail). Beyond that, out of the box UIF provides support for user name (name), password (pass), and many other core {user} table fields (for a full list expand the help on the import page). If no username is provided, the module creates a unique one based on the email. If no password is provided, a random one is generated.

Only CSV file format is supported. The import file must have a header row, and it must contain a column labeled "mail" (no quotes). If username and/or password is provided in any of the user data rows, there must be header columns labeled "name" or "pass" respectively. Header case in input files is ignored.  Programmers should use lower case when referring to column data.

The "roles" column, if provided, contains a pipe-delimited (by default; this is configurable) list of role names, e.g. "admin|editor" (quotes are mine).

Support is also provided for many Field module fields in core including Text, Float, Integer, Decimal, etc.  The list types are also supported.  The header for each column should contain the machine name of the field you wish to import.

For additional field and module support check out the companion uif_plus module, which provides support for profile2, organic groups, file and image fields, and entityreference fields.


Extensibility
-------------
Several hooks are provided so that you can execute code at various stages of the import process. 

hook_uif_help()
This hook allows you to insert help text on the import page. The text appears beneath the basic help provided by the module.

hook_uif_validate_header($header, $form_state)
Your module can implement this hook to validate the array of header values. You may require certain fields for a profile. This is the place to check if the column exists in the import file. Return an array of error strings, all of which will be displayed, and the user will not be allowed to do the import. An empty array (or NULL) is success.

hook_uif_validate_user($user_data, $uid, $form_state)
This hook is called for every row of user data in the file. Like hook_uif_validate_header(), you can return any number of error strings, which are displayed to the user and which cause the import to fail. $user_data is an array of key => value pairs, where the key is the header column and the value is the data from the user row. All values are trimmed. $uid is either 0 for a new user or a positive integer for an existing user.

hook_uif_validate_all_users($user_list, $form_state)
Once all users have been individually validated via calls to hook_uif_validate_user(), if there are no errors this hook is called with the full array of users. This can be useful if, for example, your requirements limit the total number of users to be imported. As with hook_uif_validate_header() and hook_uif_validate_user(), the hook upon error should return any number of error strings, which are displayed to the user and which cause the import to fail.

hook_uif_pre_create($account, $user_data, $form_state)
This hook is called before a new user is created (before user_save() is called). $account contains basic account data (mail, name, pass). $user_data contains key => value pairs for the user about to be created.

hook_uif_post_create($account, $user_data, $form_state)
This hook is called after a new user is created (after user_save() is called). Same arguments as hook_uif_pre_create(). Good place to do work, like creation of a profile node.

hook_uif_pre_update($account, $user_data, $form_state)
Same idea as hook_uif_pre_create(), but used for existing (updated) users. In this case, $account->uid will be a positive integer.

hook_uif_post_update($account, $user_data, $form_state)
Same idea as hook_uif_post_create(), but used for existing (updated) users. In this case, $account->uid will be a positive integer.

hook_uif_supported_fields()
Return an array of fields that your module supports for import. Alternative to using hook_uif_pre_create() and hook_uif_pre_update().

Of course, since user_save() is called, core's hook_user() is available to you as well.

