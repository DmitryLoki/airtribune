How to use Ajax links API
--------------------------------------------------------------------------------

METHOD 1 : In module config page, specify the Classes/Ids to trigger Ajax. 
Target DIV will be default CSS selector defined, you can change default CSS 
Selector from module config page.

Example : 
<div class="tabs"><a href="node/add/page">Add page</a></div> . You can ajaxify 
this link by adding .tabs a in module config page.



METHOD 2 : in your tpl , <?php l_ajax($title, $path, $target) ?>

* $title: Title.
* $path : Drupal path.
* $target (optional): ID/CLASS of DIV to be replaced. This will override 
Default CSS Selector defined in module config page.

Example :
<?php l_ajax("add page", "node/add/page", "#content") ?>



METHOD 3 : Add class="ajax-link" to any link. Target div will be default CSS 
selector defined . You can change default CSS Selector from module config page 
or override target by specifying rel="".

Example : 
<a class="ajax-link" href="node/add/page" rel="#content">Add page</a>




Developer Notes
--------------------------------------------------------------------------------
Override tpl : 
Developer can add/remove any variables by copying html--ajax.tpl.php and 
page--ajax.tpl.php to their theme. All variables available to html.tpl.php or 
page.tpl.php can be used. 
In case you want to override page--ajax.tpl.php, for eg: for path /user/, you 
can create page--user--ajax.tpl.php. Same applicable for html--user--ajax.tpl.

Upgrade : 
You can upgrade/degrade module anytime by simply overwriting whole folder.

Ajaxify admin paths :
Overlay module is not compatible with this module. If you want to ajaxify admin
paths.
* You need to disable overlay module,
* Goto admin/appearance, set Administration theme to default.

DEMO
--------------------------------------------------------------------------------
Goto YOUR_SITE/ajax-links-api/test
