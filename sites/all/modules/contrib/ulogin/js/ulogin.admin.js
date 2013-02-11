(function ($) {

Drupal.behaviors.ulogin_vtabs_SettingsSummary = {};
Drupal.behaviors.ulogin_vtabs_SettingsSummary.attach = function(context, settings) {
  // Make sure this behavior is processed only if drupalSetSummary is defined.
  if (typeof jQuery.fn.drupalSetSummary == 'undefined') {
    return;
  }
  
  $('fieldset', context).not('#edit-fset-ulogin-other').each(function(index, Element) {
    $(this).drupalSetSummary(function (context) {
      var vals = [];
      
      $('label', context).each(function (index, Element) {
        var label_for = $(this).attr('for');
        if ($('#' + label_for).is(':checked')) {
          vals.push($.trim($(this).text()));
        }
      });
      
      return vals.join(', ');
    });
  });
  
  $('fieldset#edit-fset-ulogin-other', context).drupalSetSummary(function(context) {
    var vals = [];
    
    var redirect = $('input#edit-ulogin-destination', context).attr('value');
    var label = '<span style="font-weight:bold;">' + $.trim($('label[for="edit-ulogin-destination"]', context).text()) + '</span>';
    if (redirect) {
      vals.push(label + ': ' + redirect);
    }
    else {
      vals.push(label + ': ' + 'return to the same page');
    }
    
    label = '<span style="font-weight:bold;">' + $.trim($('label[for="edit-ulogin-forms"]', context).text()) + '</span>';
    var list = [];
    $('div#edit-ulogin-forms', context).find('label').each(function(index, Element) {
      var label_for = $(this).attr('for');
      if ($('#' + label_for).is(':checked')) {
        list.push($.trim($(this).text()));
      }
    });
    vals.push(label + ': ' + list.join(', '));
    
    label = '<span style="font-weight:bold;">' + $.trim($('label[for="edit-ulogin-duplicate-emails"]', context).text()) + '</span>';
    list = [];
    $('div#edit-ulogin-duplicate-emails', context).find('label').each(function(index, Element) {
      var label_for = $(this).attr('for');
      if ($('#' + label_for).is(':checked')) {
        list.push($.trim($(this).text()));
      }
    });
    vals.push(label + ': ' + list.join(', '));
    
    return vals.join('<br />');
  });
  
  $providers_fset = $('fieldset#edit-fset-ulogin-providers', context);
  $providers_fset.find('input').each(function(index, Element) {
    var id = $(this).attr('id');
    var corr_id = id.replace('providers', 'hidden');
    if (id == corr_id) {
      corr_id = id.replace('hidden', 'providers');
    }
    
    var $corr_el = $providers_fset.find('#' + corr_id);
    if ($(this).is(':checked') && !$corr_el.is(':checked')) {
      $corr_el.parent().hide();
    }
    $(this).click(function(event) {
      if (!$(this).is(':checked')) {
        $corr_el.parent().show();
      }
      else if ($(this).is(':checked') && !$corr_el.is(':checked')) {
        $corr_el.parent().hide();
      }
    });
  });
};

})(jQuery);
