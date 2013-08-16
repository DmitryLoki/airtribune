-- SUMMARY --

This module implements jQuery tristate checkbox plugin 
(http://jlbruno.github.io/jQuery-Tristate-Checkbox-plugin/) as form element.
In your form definitions you can use $element['#type'] = 'nested_checkboxes'. 

-- REQUIREMENTS --

jQuery Update (jQuery v1.6 or later)
Libraries API

-- INSTALLATION --

To make this module work, you should download jQuery tristate checkbox plugin 
(http://jlbruno.github.io/jQuery-Tristate-Checkbox-plugin/) and extract it in 
the "libraries" folder of your site (renaming if necessary) so that the path 
is libraries/tristate/jquery.tristate.min.js
In jQuery Update settings, select jQuery v1.7 or 1.8 
Then install module as usual.

-- CONFIGURATION --

This module provides a new form element, 'nested_checkboxes'. Its most important
property is '#options'. It should come as a nested array, and for each level you 
should also indicate '#title' element. For example, to get following structure:

* Set 1
  * Option 1
  * Option 2
* Set 2
  * Choice 1
  * Choice 2

you should define
 
'#options' => array(
  'set1' => array(
    '#title' => t('Set 1'),
    'option1' => t('Option 1'),
    'option2' => t('Option 2')
  ),
  'set2' => array(
    '#title' => t('Set 2'),
    'option1' => t('Choice 1'),
    'option2' => t('Choice 2')
  )
)
The resulting value of the element will be also a nested array.

-- CUSTOMIZATION --

The list of checkboxes is implemented as HTML unordered list. 
Its element have classes "nested-checkboxes" and "level-n", where n is the depth
of current level. Custom theming may be implemented by 
theme('nested_checkboxes', ..), but it should be compliant with jQuery tristate 
checkbox plugin. Meanwhile, this module expects that checkboxes are rendered as 
divs, so custom theming of checkboxes may break this module. 
