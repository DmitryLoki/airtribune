(function ($) {

  Drupal.behaviors.day_feature = {
    attach: function (context) {
      $('.race-links:not(".processed")').each(function (i, raceBlock) {
        var $raceBlock = $(raceBlock).removeClass('race-awaiting').addClass('processed');
        var timeHelperText = $raceBlock.closest('.view-content').find('.time').hide(),
          helperText = $raceBlock.closest('.view-content').find('.help-text'),
          $raceButton,
          raceTime;

        var setOnlineTime = function () {
          raceTime = Math.floor((raceData.raceStartTime - new Date().getTime()) / 1000);
          var absD = Math.abs(raceTime);
          timeHelperText.html((raceTime > 0 ? "-" : "") + getTimeStr(Math.floor(absD / 3600), Math.floor(absD % 3600 / 60), absD % 60));

          if (raceTime < 0) {
            var isRaceStateReady = timeHelperText.parents('.race-links').hasClass('race-block-activated');
            setOnlineTimeView(isRaceStateReady, raceTime, timeHelperText, helperText);
          }
          setTimeout(setOnlineTime, 1000);
        };

        var setReplayTime = function() {
          raceTime = (Math.floor(raceData.raceDeadlineTime - raceData.raceStartTime) / 1000);
          timeHelperText.html(getTimeStr(Math.floor(raceTime / 3600), Math.floor(raceTime % 3600 / 60), raceTime % 60));
        };

        var raceData = getRaceDataFromRaceBlock($raceBlock);

        if (!raceData.isOnline) {
          setReplayTime();
          $raceButton = $raceBlock.parents('.views-field-day-pg-race-play-link');
          if($raceBlock.parents('.front_live_events').length == 0) {
            $raceButton.hide();
          }
        } else {
          if(Drupal.settings.Day && Drupal.settings.Day.button_soon_text) {
            helperText.text(Drupal.settings.Day.button_soon_text)
          } else {
            helperText.text('');
          }
          setOnlineTime();
          $raceButton = $raceBlock.find('a.race-link');
        }

        var closestViewsRow = $raceBlock.closest('.views-row'),
          hasDayblogText = isDayblogTextExists(closestViewsRow);

        if(closestViewsRow.length) {
          if (!hasDayblogText) {
            closestViewsRow.addClass('no-dayblog-text');
          } else {
            closestViewsRow.addClass('day-blog');
            closestViewsRow.find('.views-field-title-1').removeClass('views-field-title-1').addClass('title');
          }
        }


        if (!raceData.raceId || !raceData.contestId) {
          return;
        }

        timeHelperText.show();
        requestRaceState(raceData, function response(raceInfo) {
          //raceInfo=[{a:1}]
          if (raceInfo && raceInfo.length > 0 && !$.isEmptyObject(raceInfo)) {
            //make links clickable
            setHrefAttr($raceBlock.find('a.race-link.2d').show(), raceData.raceEid, '2d');
            setHrefAttr($raceBlock.find('a.race-link.ge').show(), raceData.raceEid, 'ge');

            $raceButton.show();
            $raceBlock.addClass('race-block-activated');
            if(raceData.isOnline) {
              setOnlineTimeView(true, raceTime, timeHelperText, helperText);
            }
            if(closestViewsRow.length) {
              closestViewsRow.removeClass('no-dayblog-text day-blog').addClass('race-activated');
              if(hasDayblogText) {
                closestViewsRow.find('.views-field.title').removeClass('title').addClass('views-field-title-1');
              }
            }
          } else {
            if(raceData.isOnline) {
              setOnlineTimeView(false, raceTime, timeHelperText, helperText);
            } else {
              raceData.requestType = 'online';
            }
            setTimeout(function () {
              requestRaceState(raceData, response);
            }, 10000);
          }
        });
      });

      function setOnlineTimeView(isRaceStateReady, raceTime, timeHelperText, helperText) {
        var raceBlock = timeHelperText.closest('.view-content');
        if (raceTime <= 0) {
          raceBlock.removeClass('race-awaiting').addClass('race-started');
          helperText.text(Drupal.settings.Day.race_on_text);
          if (isRaceStateReady) {
            raceBlock.addClass('race-online');
          } else {
            raceBlock.removeClass('race-online');
          }
        } else {
          raceBlock.addClass('race-awaiting').removeClass('race-started');
          helperText.text(Drupal.settings.Day && Drupal.settings.Day.race_in_text);
        }

      }

      function getTimeStr(h, m, s) {
        h = Math.abs(h);
        m = Math.abs(m);
        s = Math.abs(s);
        return (h < 10 ? "0" : "") + h + ":" + (m < 10 ? "0" : "") + m + ":" + (s < 10 ? "0" : "") + s;
      }

      function requestRaceState(raceData, responseCallback) {
        /*'http://api.airtribune.com/v0.1.4/contest/cnts-130607-2736547863/race/r-23be3210-f0f7-49c3-b071-63da6cd56e61/tracks'*/
        $.ajax({
          url: Drupal.settings.pgRace.coreApiAddress + '/contest/' + raceData.contestId + '/race/' + raceData.raceId + '/tracks?type=' + raceData.requestType,
          dataType:"json",
          success: responseCallback,
          error: function () {
            responseCallback(null);
          }});
      }

      function getRaceDataFromRaceBlock($raceBlock) {
        var raceData = {
          contestId: $raceBlock.data('contest-cid'),
          raceId: $raceBlock.data('race-cid'),
          raceEid: $raceBlock.data('race-eid'),
          raceStartTime: parseInt($raceBlock.data('start-time')),
          raceDeadlineTime: parseInt($raceBlock.data('deadline-time')),
          isOnline: $raceBlock.data('view-type') != undefined
        };

        raceData.requestType = raceData.isOnline || !hasTracksLoaded($raceBlock) ? 'online' : 'competition_aftertask';
        return raceData;
      }

      function hasTracksLoaded($raceBlock) {
        return $raceBlock.parents('div.event-day,div.views-row').find('.views-field-field-pg-race-tracks').length>0
          || $raceBlock.find('.views-field-field-pg-race-tracks').length>0;
      }

      function setHrefAttr(link, raceEid, mode) {
        link.attr('href', 'http://'+location.host+'/play/' + raceEid + '/' + mode)
      }

      function isDayblogTextExists(viewsRow) {
        if(viewsRow.length){
          return viewsRow.find('.day-blog').length > 0;
        }
        return false;
      }
    }
  }

})(jQuery);
