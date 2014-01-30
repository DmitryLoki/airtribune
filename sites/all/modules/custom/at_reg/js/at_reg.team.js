(function($){
  Drupal.behaviors.at_reg_team = {
    attach: function(){
      $(".authorized-team-registration a.pilot").click(function(){
        $(".authorized-team-registration-form").show();
        $(".authorized-team-registration").hide();
        return false;
      });
      
      $("a.at-reg-team-leader-add-error").one("click", function(){
        at_reg_set_error_message(Drupal.settings.at_reg.team_leader_add_error);
        return false;
      });

      function at_reg_set_error_message(message) {
        $('.pane-pane-messages #tasks').append(
          '<div class="messages error"><h2 class="element-invisible">Error message</h2><span>'+message+'</span><span class="valign"></span></div>'
        );
      }
    }
  }
})(jQuery);
