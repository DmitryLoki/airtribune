/**
 * @file
 * JS for approve team leader field.
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see $4339
 * @todo this is only for teams_applications view
 */

(function ($) {

  Drupal.behaviors.pg_nation_team = {
    attach: function (context, settings) {
      $(document.body).once(function () {

        var teamLeadersCheckboxes = $('.form-item-approve-team-leader input[type="checkbox"]').on('change', function () {
          var currentCheckbox = this;
          teamLeadersCheckboxes.filter(function (i, checkbox) {
            //TODO: исправить conutry тут
            return checkbox.dataset.conutry === currentCheckbox.dataset.conutry && checkbox !== currentCheckbox
          }).attr('checked', false).prev().removeClass('check_checkbox');
        })

      })
    }
  }

})(jQuery);
