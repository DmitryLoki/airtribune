                       == N o d e S y m l i n k s ==

                     Installation & Usage instructions

                           Author: Vojtěch Kusý
                     wojtha@gmail.com, http://kusy.info


I.) FEATURES
==============
This module allows that nodes can appear on different places at the website and
each path is unique, so it means:
 - Each duplicate path has own unique breadcrumb.
 - Each duplicate path has own unique active menu trail.
 - All duplicate content path is sanitized with marking duplicate node pages
   with "<robots noindex>" metatag.

EXPERIMENTAL
------------
Support in SubmenuTree which allows you to list duplicated content in
SubmenuTree pages and blocks. (A patch to Submenutree must be applied).

________________________________________________________________________________

II.) WHY?
===========
Example: I worked on a website for an university. There were some branches of
study (= nodes) and categories with N:N relation (some branches appear in three
different categories). How Drupal solve this by design? You always have only one
path = one alias = one breadcrumb to the content. If there is multiple
paths/trails/breadcrumbs to content (i.e. in taxonomy), the one with the
lightest weight wins and it is used, all time.

Imagine this situation on the introduced university website:

You are looking for some branches on this website, you like science, so you
click on category "Making science", website is using content_taxonomy module, so
you see now "Making science" in the breadcrumb and the list of branches inside, so
you choose one branch of study... click on it... but what happend?

You see the right branch, but the breadcrumb navigation shows, that you are in
the category "Making money" (it has lower weight than "Making Money") and also
the same happen with the menu, active menu trail shows, that you are in totally
different category than you came from! You are confused ...

Additionaly, if you have this branch-node in menu multiple times, all menus
which contain it is expanded and marked as active. (I know in some usecases it
is wanted behaviour, but sometimes not - you have no choice. Only way is doing
some workarounds like custom menu handling or making several similar menu and
showing/hiding them by conditions).

Imaginary discusssion about duplicate paths
-------------------------------------------
* Why is duplicate menu paths not supported with Menu API "by design"?
> The main reason is, that if you don't sanitize duplicate content it will lower
your SEO pagerank. Many cheater pages tried and still trying to get more
pagerank with creating many paths to same content, so on the "first sight" it
appears that the site has many content, but actually it hasn't. The search
engines companies like Google begun to defend against that cheating
and started to penalize duplicate content...

* Ok, it seems reasonable, duplicate paths is bad ... but wait - many legal
websites and e-shops has categorized content which appears on many pages and has
huge pagerank, how it is possible?
> Well, there is a one or two methods how to say some informations about your
site to search engine robots and affect the way how they will index your site
and finally count your impetrated pagerank. First method is using robots.txt
file in root dir, the second method is <robots meta tag> placed in the head of
HTML page ---> And this the way which is this module using to be nice to SEO
robots :-)

________________________________________________________________________________

III.) INSTALLATION
====================

1) Unpack and upload module to the module directory
2) Enable Node Symlinks module on the Administer >> Modules page
3) Add support to Submenutree Module
   3.1 Apply patch
   3.2 Add these two lines at the end of your template node preprocess function
       in template.php:
         $vars['node_original_url'] = $vars['node_url'];
         $vars['node_url'] = url($vars['node']->path);

       EXAMPLE:

       function phptemplate_preprocess_node(&$vars, $hook) {

         ...

         // MenuDuplicateLinks support, preserve path to original node
         $vars['node_original_url'] = $vars['node_url'];
         $vars['node_url'] = url($vars['node']->path);
       }

________________________________________________________________________________

IV.) USAGE INSTRUCTIONS
=========================

Users who has "Administer menu" rights will now see Node Symlinks fieldset where
it can add or delete existing menu link.

Remember that all these duplicates will not be indexed by search robots, using
this meta tag:
<META NAME="ROBOTS" CONTENT="NOINDEX, FOLLOW">
So, if you want to be sure that content will be indexed properly, create first
menu item by "standard" menu fieldset on the node form.

________________________________________________________________________________

V.)RESOURCES
==============
* Read Google answer about duplicate content
http://www.google.com/support/webmasters/bin/answer.py?hl=en&answer=66359
* Robots meta tag
http://www.robotstxt.org/meta.html
________________________________________________________________________________