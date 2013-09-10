jQuery(function ($) {

  $('.countries_title_suffix_inner').each(function () {
    var countriesInner = $(this),
      countries = countriesInner.find('li a'),
      titleFlag = countriesInner.parents('section').find('.country-flag'),
      titleText = countriesInner.parents('section').find('.country_title');

    var defaultCountry = $("#soon-county-wrapper").data('country');
    if (defaultCountry != "none") {
      $(".change_location_title").click();
      var countryLi = $("#countries-wrapper").find("li." + defaultCountry);
      countryLi.find("a.use-ajax").click();
      updateSoonInCountryTitle.call(countryLi);
    }

    countriesInner.parent().show();
    countriesInner.jScrollPane({scrollbarWidth: 4, showArrows: false});
    //fix jsp wrong height calculation
    countriesInner.css('padding-top', '10px');
    var countriesTitleHeight = $(this).outerHeight(),
      countriesTitleSuffix = $('.countries_title_suffix');

    $('.change_location_title').click(toggleCountriesList);

    function bodyClickHandler(e) {
      if (countriesInner.find(e.target).length == 0) {
        countriesTitleSuffix.height(0);
      }
    }
    function toggleCountriesList(e) {
      e && e.stopImmediatePropagation();
      //toggle height
      if (countriesTitleSuffix.height() > 0) {
        countriesTitleSuffix.height(0);
        $(document.body).unbind('click', bodyClickHandler);
      } else {
        countriesTitleSuffix.height(countriesTitleHeight);
        $(document.body).bind('click', bodyClickHandler);
      }
    }
    countries.click(function(e){
      updateSoonInCountryTitle.call(this);
      toggleCountriesList(e);
    });

    function updateSoonInCountryTitle() {
      var country = $(this),
        countryClass = country.find('div.countryicon-sprite').attr('class'),
        getCountryCodeRegExp = /countrycode-(.*)/g,
        result = getCountryCodeRegExp.exec(countryClass);

      if (result && result.length == 2) {
        var countryCode = result[1];
        //update flag
        titleFlag.css('background-image', 'url(' + Drupal.settings.countryIconsShinyPath + '/images/' + countryCode + '.png' + ')');

        // update title text
        titleText.text(Drupal.t('Soon in ') + country.text());
      }
    }
  });
});