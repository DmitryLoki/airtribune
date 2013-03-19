(function ($) {

/**
 * Attach handlers to evaluate the strength of any password fields and to check
 * that its confirmation is correct.
 */
Drupal.behaviors.password = {
  attach: function (context, settings) {
    var translate = settings.password;
    $('input.password-field', context).once('password', function () {
      var passwordInput = $(this);
      var innerWrapper = $(this).parent();
      var outerWrapper = $(this).parent().parent();

      // Add identifying class to password element parent.
      innerWrapper.addClass('password-parent');

      // Add the password confirmation layer.
      //$('input.password-confirm', outerWrapper).parent().append('<span class="password-confirm form_booble"><span class="form_booble_inner"></span></span>').addClass('confirm-parent');
      var confirmInput = $('input.password-confirm', outerWrapper);
      var confirmResult = $('span.password-confirm', outerWrapper);
      var confirmChild = $('span', confirmResult);

      // Add the description box.
      //var passwordMeter = '<div class="password-strength"><div class="password-strength-text" aria-live="assertive"></div><div class="password-strength-title">' + translate['strengthTitle'] + '</div><div class="password-indicator"><div class="indicator"></div></div></div>';
	    var passwordMeter = '<span style="display:none" class="password-strength form_booble"><span class="password-strength-text form_booble_inner" aria-live="assertive"></span></span>';
      //$(confirmInput).parent().after('<div class="password-suggestions description"></div>');
      $(innerWrapper).find('input').after(passwordMeter);
      var passwordDescription = $('div.password-suggestions', outerWrapper).hide();

      // Check the password strength.
        Drupal.behaviors.password.passCheck = passwordCheck = function (event) {
        // Evaluate the password strength.
        var result = Drupal.evaluatePasswordStrength(passwordInput.val(), settings.password);
        // Update the suggestions for how to improve the password.
        if (passwordDescription.html() != result.message) {
          //passwordDescription.html(result.message);
        }

        // Only show the description box if there is a weakness in the password.
        if (result.strength == 100) {
          passwordDescription.hide();
        }
        else {
          //passwordDescription.show();
        }

        // Adjust the length of the strength indicator.
        $(innerWrapper).find('.indicator').css('width', result.strength + '%');

        // Update the strength indication text.
        //$(outerWrapper).find('.validate-error').remove();
        $(innerWrapper).removeClass('field_error').removeClass('field_good').removeClass('field_excellent').find('.error').removeClass('error');
		$(innerWrapper).addClass('field_'+result.pass);
		$(innerWrapper).find('.password-strength-text').html(result.indicatorText);
        $(innerWrapper).find('.password-strength').show();
        if(result.pass == 'error'){
          passwordInput.data('error-element', $(innerWrapper).find('.password-strength'));
        } else {
          passwordInput.data('error-element',null);
        }
        return result.pass == 'error';
      };

      // Check that password and confirmation inputs match.
        Drupal.behaviors.password.passCheckMatch = passwordCheckMatch = function () {
        var success = passwordInput.val() && passwordInput.val() === confirmInput.val();
          confirmChild.html(translate['confirm' + (success ? 'Success' : 'Failure')]);

          // Show the confirm result.
          confirmResult.css({ visibility: 'visible'});

          // Remove the previous styling if any exists.
          if (this.confirmClass) {
            confirmChild.removeClass(this.confirmClass);
          }
          $(outerWrapper).find('.validate-error').remove();
          // Fill in the success message and set the class accordingly.
          var confirmClass = '';
		  confirmInput.parent().removeClass('field_error').removeClass('field_good').removeClass('field_excellent').find('.error').removeClass('error');
		  confirmInput.parent().addClass('field_' + (success ? 'excellent' : 'error'));

          this.confirmClass = confirmClass;
        return success;
      };

      // Monitor blur events.
      passwordInput.blur(function(){
          passwordCheck();
          if(confirmInput[0].visited){
              confirmInput.closest('form').validate().element(confirmInput[0]);
          }
      });
      passwordInput.keyup(function(){
        if(confirmInput[0].visited){
            confirmInput.closest('form').validate().element(confirmInput[0]);
        }
      });
      confirmInput.keyup(function(){
          this.visited = true;
          confirmInput.closest('form').validate().element(confirmInput[0]);
      });
    });
  }
};

/**
 * Evaluate the strength of a user's password.
 *
 * Returns the estimated strength and the relevant output message.
 */
Drupal.evaluatePasswordStrength = function (password, translate) {
  var weaknesses = 0, strength = 100, msg = [];

  var alphabet = 'abcdefghijklmnopqrstuvwxyz';
  var qwerty = 'qwertyuiopasdfghklzxcvbnm';
  var lowerPassword = password.toLowerCase();
  var hasLowercase = /[a-z]+/.test(password);
  var hasUppercase = /[A-Z]+/.test(password);
  var hasNumbers = /[0-9]+/.test(password);
  var hasPunctuation = /[^a-zA-Z0-9]+/.test(password);
  var symbolsInRow =
          /(.)\1{5}/.test(password) ||
          alphabet.indexOf(lowerPassword) > -1 ||
          qwerty.indexOf(lowerPassword) > -1;

  // If there is a username edit box on the page, compare password to that, otherwise
  // use value from the database.
  var usernameBox = $('input.username');
  var username = (usernameBox.length > 0) ? usernameBox.val() : translate.username;

  // Lose 5 points for every character less than 6, plus a 30 point penalty.
  if (password.length < 6) {
    msg.push(translate.tooShort);
    strength -= ((6 - password.length) * 5) + 30;
  }


  // Count weaknesses.
  if (!hasLowercase) {
    msg.push(translate.addLowerCase);
    weaknesses++;
  }
  if (!hasUppercase) {
    msg.push(translate.addUpperCase);
    weaknesses++;
  }
  if (!hasNumbers) {
    msg.push(translate.addNumbers);
    weaknesses++;
  }
  if (!hasPunctuation) {
    msg.push(translate.addPunctuation);
    weaknesses++;
  }

    if(symbolsInRow) {
        weaknesses = 5;
    }
  // Apply penalty for each weakness (balanced against length penalty).
  switch (weaknesses) {
    case 1:
      strength -= 12.5;
      break;

    case 2:
      strength -= 25;
      break;

    case 3:
      strength -= 40;
      break;

    case 4:
      strength -= 40;
      break;

    case 5:
      strength = 0;
      break;
  }

  // Check if password is the same as the username.
  if (password !== '' && password.toLowerCase() === username.toLowerCase()) {
    msg.push(translate.sameAsUsername);
    // Passwords the same as username are always very weak.
    strength = 5;
  }
  var indicatorText, pass;
  // Based on the strength, work out what text should be shown by the password strength meter.
  if(password.length == 0){
      indicatorText = Drupal.settings.password.required;
      pass = 'error';
  }
  else if(password.length > 0 && password.length < 6){
    indicatorText = translate.easyToGuess;
    pass = 'error';
  } else if(password.length < 8) {
    indicatorText = translate.weak;
    pass = 'weak';
  } else if( password.length < 10) {
    indicatorText = translate.good;
    pass = 'good';
  } else {
    indicatorText = translate.strong;
    pass = 'excellent';
  }
  /*else if (strength < 60) {
    indicatorText = translate.weak;
	pass = 'error';
  } else if (strength < 70) {
    indicatorText = translate.fair;
	pass = 'good';
  } else if (strength < 80) {
    indicatorText = translate.good;
	pass = 'good';
  } else if (strength <= 100) {
    indicatorText = translate.strong;
	pass = 'excellent';
  }*/

  // Assemble the final message.
  msg = translate.hasWeaknesses + '<ul><li>' + msg.join('</li><li>') + '</li></ul>';
  return { strength: strength, message: msg, indicatorText: indicatorText, 'pass':pass };

};

/**
 * Field instance settings screen: force the 'Display on registration form'
 * checkbox checked whenever 'Required' is checked.
 */
Drupal.behaviors.fieldUserRegistration = {
  attach: function (context, settings) {
    var $checkbox = $('form#field-ui-field-edit-form input#edit-instance-settings-user-register-form');

    if ($checkbox.length) {
      $('input#edit-instance-required', context).once('user-register-form-checkbox', function () {
        $(this).bind('change', function (e) {
          if ($(this).attr('checked')) {
            $checkbox.attr('checked', true);
          }
        });
      });

    }
  }
};

})(jQuery);
