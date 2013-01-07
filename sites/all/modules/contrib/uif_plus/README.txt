User Import Framework Plus extends the brilliant work of the original User Import Framework module. It allows you to import more than the 3 fields (email, username, and password) supported by the original uif module.

1. Core user picture field - Add file name under a header column named "picture". The default location for images is sites/default/files/uif_plus. If you have them elsewhere, enter the full path in the textfield provided on the first user import screen.

2. Organic groups - If you are using the Organic groups module, and would like to import users into groups, add a header column called "groups" (without the quotes). Enter data for either the group node "nid" or "title"

3. Profile2 fields - If you are using the Profile2 module, add header columns for each field you would like to import. Use the exact field names e.g. "field_user_picture", "field_firstname", "field_postcode" etc. For entityreference fields enter the node "nid" or "title". For taxonomy reference enter the term "tid" or "name".

Note:

a) Multiple values -  If the field supports multiple values, delimit data in each row with any of the supported delimiters you will find at the bottom of the User import page: "|" (default), ":", "_:_", "_*_"') (without the quotes)

b) Images - For image fields e.g. user picture, enter the file name in the column. The default location for images is sites/default/files/uif_plus. If you have them elsewhere, enter the full path in the textfield provided on the first user import screen.


Installation
------------

1) Copy the uif_plus directory to your sites/all/modules directory. If you haven't installed the uif module copy that too.

2) Enable the module. If you haven't installed the uif module, you must enable it also.

3) Enable 'import users' permission for any role(s) you'd like to import users. (from uif module).

4) Go to People > Import (/admin/people/uif) and follow the instructions in the help section at the top of the page.

