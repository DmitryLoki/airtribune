jCaption
--------

This is a simple module that uses jQuery to transform the TITLE or ALT attribute of a image to a image caption. There is a settings page with lot's of possible configuration. The module differs in several ways from similar modules.

jCaption changes this:

<img title="Image caption here" src="image.jpg" alt="Image description">

to:

<div class="caption none" style="width: 230px;"> <- the width of the image...
<img title="Image caption here" src="image.jpg" alt="Image description">
<p>Image caprion here!</p>
</div>

Tested in IE6, IE7, Firefox, Safari and Chrome.

Theming captions
----------------
The container have the class caption. It's also possible for the container to inherit classes, styles or alignments from the image.


Similar modules
---------------

Image Caption
You shold check out the more advanced module Image Caption:
http://www.drupal.org/project/image_caption

Image Caption is different from jCaption in several ways:

1. Image Caption works the other way around - you give images the class caption to get captions. jCaption can work like that but can also make captions on all images with TITLES in a id or class.
2. Image Caption only work with TITLE - jCaption can work with TITLE or ALT.
3. Image Caption don't inherit classes or styles from the image
4. Image Caption have options to work without javascript

Caption Filter
Caption Filer is a module that converts WordPress-style [caption] tags into HTML markup.
http://drupal.org/project/caption_filter

Credits
-------

The jQuery is heavily based on Joel Sutherlands excellent jCaption plug-in with some development and small changes for a perfect fit for Drupal. Thanks to Joel Sutherland. Read more about this at http://plugins.jquery.com/project/jcaption


Author's Information
--------------------

The drupal module jCaption is developed by Mattias Axelsson (drupalname: acke) at Happiness Web Agency (http://www.happiness.se) in the beautiful city Stockholm, Sweden.

Follow me at http://twitter.com/mattiasaxelsson

Enjoy!
