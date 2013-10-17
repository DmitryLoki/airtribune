//var ajaxAttach = Drupal.behaviors.AJAX.attach;
//
//(function ($) {
//
//  Drupal.behaviors.AJAX.attach = function (context, settings) {
//    /*
//     Настройки для clientsideValidation, т.е. то, что должно дополнительно быть в
//     Drupal.settings.clientsideValidation
//     */
//    var clientsideValidationSettings = {
//      forms: {
//        'user-register-form': {
//          rules: {
//            'profile_main[field_full_name][und][0][given]': {
//              required: true
//            },
//            'profile_main[field_full_name][und][0][family]': {
//              required: true
//            },
//            'pass[pass1]': {
//              passwordStrength: true,
//              messages: {
//                passwordStrength: Drupal.settings.password.easyToGuess
//              }
//            },
//            'pass[pass2]': {
//              passwordConfirmation: true,
//              messages: {
//                passwordConfirmation: 'A пароли-то не совпадают.'//Какой-то текст:)
//              }
//            },
//            'profile_main[field_birthdate][und][0][value][month]': {
//              required: true
//            },
//            'profile_main[field_birthdate][und][0][value][year]': {
//              required: true
//            },
//            'profile_main[field_birthdate][und][0][value][day]': {
//              required: true
//            }
//          }
//        }
//      }
//    };
//    /*
//     Конец настроек clientsideValidation
//     */
//    ajaxAttach.call(this, context, settings);
//
//    $.extend(true, Drupal.settings.clientsideValidation, clientsideValidationSettings);
//  }
//})(jQuery);


(function ($) {

  $.fn.checkValidationResult = function (errorText) {
    //Костыль!!
    /*if(!this[0] || this.attr('id') == 'edit-profile-main-field-birthdate-und-0-value') {
      $('#user-register-form').validate().checkAllValid();
      return;
    }*/

    var form = this.closest('form'),
      validator = form.validate();
    if (!errorText) {
      validator.checkAllValid();
      return;
    }

    Drupal.settings.clientsideValidation.forms[form.attr('id')].rules[this.attr('name')]['validation-error'] = true;
    this.rules('add', {'validation-error': true, messages: {'validation-error': errorText}});
    if(Drupal.behaviors.DEFClientValidation.myClientsideValidation) {
      Drupal.myClientsideValidation = Drupal.behaviors.DEFClientValidation.myClientsideValidation;
    }
    //show error message
    validator.element(this);

  };

  Drupal.behaviors.DEFClientValidation = {
    myClientsideValidation:undefined,
    beforeSubmit: function (form_values, form, options) {
      //remove previous ajax validation error
      delete Drupal.settings.clientsideValidation.forms[form.attr('id')].rules[this.element.name]['validation-error'];
      $(this.element).rules('remove', 'validation-error');

      var validator = form.validate(),
        validationResult = validator.element(this.element) !== false;

      //ajax validation will not happened
      if (!validationResult) {
        this.ajaxing = false;
      } else {
        Drupal.behaviors.DEFClientValidation.myClientsideValidation = Drupal.myClientsideValidation;
        delete Drupal.myClientsideValidation;
      }

      return validationResult;
    },
    getBooble: function (html) {
      return '<span class="form_booble"><span class="form_booble_inner">' + html + '</span></span>'
    },
    success: function () {
      var successElements = $(this.successList);

      successElements.each(function (i, el) {
        var formItem = $(el).closest('.form-item');
        formItem.removeClass('field_error');
        formItem.find('.error.form_booble').remove();
      });

    },
    prepareErrorElement: function (error) {
      var errorText = error.text(),
        errorElement = $(Drupal.behaviors.DEFClientValidation.getBooble(errorText));
      errorElement.addClass('error');
      return errorElement;
    },
    attach: function (context, settings) {
      $.validator.prototype.checkAllValid = function () {
        var self = this,
          allValid = true;
        var allElements = this.elements();
        allElements.each(function (i, e) {
          allValid = allValid && self.check(e);
        });
        if (allValid) {
          $(self.currentForm).find('.form-submit').removeAttr('disabled');
        }
        return allValid;
      };

      //override beforeSubmit
      for (var ajax_el in Drupal.settings.ajax) {
        var ajax = Drupal.ajax[ajax_el];
        ajax.beforeSubmit = Drupal.behaviors.DEFClientValidation.beforeSubmit.bind(ajax);
      }

      //overrides errorPlacement in validation settings
      Drupal.clientsideValidation.prototype.setErrorElement = function (error, element) {
        if (error.text() == '') {
          return;
        }
        var errorElement = Drupal.behaviors.DEFClientValidation.prepareErrorElement(error);

        var formItem = element.closest('.form-item');
        //remove previous error booble
        formItem.find('.error.form_booble').remove();

        element.after(errorElement);
        formItem.addClass('field_error');

        $(element[0].form).find('.form-submit').attr('disabled', '');
      };

      $(document).bind('clientsideValidationAddCustomRules', function (event) {

        $.validator.addMethod("passwordStrength", function (value, element, param) {
          var passwordStrength = Drupal.evaluatePasswordStrength(value, settings.password),
            passwordField = $(element),
            passwordFieldContainer = passwordField.closest('.form-item-pass-pass1'),
            passStrengthClass = '';
          //remove previous booble
          passwordFieldContainer.find('.form_booble').remove();
          passwordFieldContainer
            .removeClass('field_weak field_good field_excellent');

          //debugger;
          switch (passwordStrength.pass) {
            case 'error':
              return false;
            case 'weak':
              passStrengthClass = 'field_weak';
              break;
            case 'good':
              passStrengthClass = 'field_good';
              break;
            case 'excellent':
              passStrengthClass = 'field_excellent';
              break;
          }

          //set correct password booble
          passwordField
            .after(
              Drupal.behaviors.DEFClientValidation.getBooble(passwordStrength.indicatorText)
            );

          passwordFieldContainer.addClass(passStrengthClass);

          return true;
        });

        $.validator.addMethod("passwordConfirmation", function (value, element, param) {
          var form = $(element.form),
            confirmationField = $(element),
            passwordField = form.find('.password-field'),
            confirmationFieldContainer = $(element).closest('.form-item-pass-pass2'),
            passwordValue = passwordField.val();

          //remove previous booble element
          confirmationFieldContainer.find('.form_booble:not(.error)').remove();
          confirmationFieldContainer.removeClass('field_excellent');

          //validate password confirmation on password field blur
          passwordField.unbind('focusout.validation').bind('focusout.validation', function () {
            form.validate().element(element);
          });

          var result = passwordValue == value;

          if (result) {
            confirmationField
              .after(Drupal.behaviors.DEFClientValidation.getBooble(settings.password.confirmSuccess));
            confirmationFieldContainer.addClass('field_excellent');
          }
          return result;
        });

        $.validator.addMethod("validation-error", function () {
          return false;
        });

      });

      $(document).bind('clientsideValidationInitialized', function () {
        for (var form in settings.clientsideValidation.forms) {
          var validator = Drupal.myClientsideValidation.validators[form];
          validator.settings.success = $.proxy(Drupal.behaviors.DEFClientValidation.success, validator);
          var allElements = validator.elements();

          (function (validator) {
            allElements
              .filter(':not(.ajax-processed)')
              .unbind('keyup.validation')
              .bind('keyup.validation', function () {
                if (!validator.checkAllValid()) {
                  $(this.form).find('.form-submit').attr('disabled', '');
                } else {
                  $(this.form).find('.form-submit').removeAttr('disabled');
                }
              })
              .unbind('focusout.validation')
              .bind('focusout.validation', function(){
                validator.element(this);
              });
            //Disable submit button on ajax field focus
            allElements.filter('.ajax-processed')
              .unbind('focusin.validation')
              .bind('focusin.validation', function () {
                $(this.form).find('.form-submit').attr('disabled', '');
              });
            if (!validator.checkAllValid()) {
              $(allElements[0].form).find('.form-submit').attr('disabled', '');
            }

          })(validator);
        }
      });
    }
  };

  Drupal.behaviors.userRegisterFormSpecials = {
    isAllBirthdateInputsFilled: function (birthdateInputs) {
      return birthdateInputs.filter(function (i, el) {
        return jQuery(el).val() != ''
      }).length == birthdateInputs.length;
    },
    attach: function (context, settings) {
      //Custom error placement for birthdate fields
      var oldSetErrorElement = Drupal.clientsideValidation.prototype.setErrorElement;
      Drupal.clientsideValidation.prototype.setErrorElement = function (error, element) {
        if (element[0].name.indexOf('field_birthdate') > -1 && error.text() != '') {
          var errorElement = Drupal.behaviors.DEFClientValidation.prepareErrorElement(error),
            container = element.parents('.form-item-profile-main-field-birthdate-und-0-value').children();
          container.find('.error.form_booble').remove();
          container.append(errorElement).addClass('field_error');
          return;
        }

        oldSetErrorElement(error, element);
      };

      //override beforeSubmit for birthdate comboboxes
      var birthDateComboboxes = $('#edit-profile-main-field-birthdate-und-0-value-year,#edit-profile-main-field-birthdate-und-0-value-month,#edit-profile-main-field-birthdate-und-0-value-day')
      birthDateComboboxes.each(function (i, birthdateElement) {
        Drupal.ajax[$(birthdateElement).attr('id')].beforeSubmit = function () {
          var isAllFilled = Drupal.behaviors.userRegisterFormSpecials.isAllBirthdateInputsFilled(birthDateComboboxes);
          return isAllFilled;
        }
      });

      birthDateComboboxes.bind('change', function () {
        $(this.form).validate().element(this);
      });

      //override success function
      $(document).bind('clientsideValidationInitialized', function () {
        var validator = Drupal.myClientsideValidation.validators[birthDateComboboxes.get(0).form.getAttribute('id')];
        var oldSuccess = validator.settings.success;
        validator.settings.success = $.proxy(function () {
          if (!Drupal.behaviors.userRegisterFormSpecials.isAllBirthdateInputsFilled(birthDateComboboxes)) {
            oldSuccess.call(this);
            return;
          }

          var successElements = $(this.successList);
          successElements
            .filter(function (i, element) {
              return element.name.indexOf('field_birthdate') > -1;
            })
            .each(function (i, element) {
              var formItem = $(element).parents('.form-item');
              formItem.removeClass('field_error');
              formItem.find('.error.form_booble').remove();
            });

          oldSuccess.call(this);
        }, validator)
      });
    }
  }
})
  (jQuery);
