(function ($) {

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
