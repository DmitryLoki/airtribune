(function ($) {

Drupal.behaviors.hybridauthWidget = {};
Drupal.behaviors.hybridauthWidget.attach = function (context, settings) {
  $('.hybridauth-widget-provider', context).once('hybridauth', function() {
    $(this).click(function(event) {
      event.preventDefault();
      var url = $(this).attr('href');
      popup_window = window.open(url, 'hybridauth', 'location=no,menubar=no,resizable=yes,scrollbars=yes,status=no,titlebar=yes,toolbar=no,channelmode=yes,fullscreen=yes,width=800,height=500');
      popup_window.focus();
      return false;
    });
  });
};

/**
 * Provide the HTML to create the modal dialog.
 * Clone of function Drupal.theme.prototype.CToolsModalDialog.
 */
Drupal.theme.prototype.HybridAuthModalDialog = function () {
  var html = '';
  html += '  <div id="ctools-modal">';
  html += '    <div id="hybridauth-modal">';
  html += '      <div class="ctools-modal-content">'; // panels-modal-content
  html += '        <div class="modal-header">';
  html += '          <a class="close" href="#">';
  html +=              Drupal.CTools.Modal.currentSettings.closeText + Drupal.CTools.Modal.currentSettings.closeImage;
  html += '          </a>';
  html += '          <span id="modal-title" class="modal-title"></span>';
  html += '        </div>';
  html += '        <div id="modal-content" class="modal-content">';
  html += '        </div>';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';
  
  return html;
};

})(jQuery);
