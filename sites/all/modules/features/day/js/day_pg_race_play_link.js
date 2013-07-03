(function ($) {
  
  Drupal.behaviors.day_feature = {
    attach: function (context) {

      var timeHelperText = $("#time-counter"),
        helperText = $('.help-text'),
        d = '';
      if (typeof Drupal.settings.Day != 'undefined' && typeof Drupal.settings.Day.start_time != 'undefined') {
        var getTimeStr = function(h,m,s) {
          h = Math.abs(h);
          m = Math.abs(m);
          s = Math.abs(s);
          return (h<10?"0":"") + h + ":" + (m<10?"0":"") + m + ":" + (s<10?"0":"") + s;
        }
        
        var setTime = function() {
          // var d = Math.floor((self.raceKey()-new Date().getTime())/1000);
          
          d = Math.floor((Drupal.settings.Day.start_time-new Date().getTime())/1000);
          timeHelperText.html((d>0?"-":"") + getTimeStr(Math.floor(d/3600),Math.floor(d%3600/60),d%60));
          if(d > 0){
            setTimeout(setTime,1000);
          }

        }
        setTime();
      }

      $('.race-links').each(function (i, raceBlock) {
        var $raceBlock = $(raceBlock);
        var raceData = getRaceDataFromRaceBlock($raceBlock);

        requestRaceState(raceData, function response(raceInfo) {

          if (raceInfo && raceInfo.length > 0 && !$.isEmptyObject(raceInfo)) {
            console.log('enable links in ', $raceBlock);
            //make links clickable
            setHrefAttr($raceBlock.find('a.race-link.2d'), raceData.raceEid, '2d', raceData.isOnline);
            setHrefAttr($raceBlock.find('a.race-link.3d'), raceData.raceEid, '3d', raceData.isOnline);
            if(typeof d == 'number' && d<=0) {
              timeHelperText.show();
              helperText.text('Race starts on');
            }
            $raceBlock.addClass('race-block-activated');
          } else {
            if(typeof d == 'number' && d<=0) {
              timeHelperText.hide();
              helperText.text('Button will be here as soon as task is set.');
            }
            setTimeout(function () {
              requestRaceState(raceData, response);
            }, 10000)
          }
        });
      });


      function requestRaceState(raceData, responseCallback) {
        /*'http://api.airtribune.com/v0.1.4/contest/cnts-130607-2736547863/race/r-23be3210-f0f7-49c3-b071-63da6cd56e61/tracks'*/
        $.ajax({
          url: Drupal.settings.pgRace.coreApiAddress + '/contest/' + raceData.contestId + '/race/' + raceData.raceId + '/tracks',
          success: responseCallback,
          error: function () {
            responseCallback(null);
          }});
      }

      function getRaceDataFromRaceBlock($raceBlock) {
        return {
          contestId: $raceBlock.data('contest-cid'),
          raceId: $raceBlock.data('race-cid'),
          raceEid: $raceBlock.data('race-eid'),
          isOnline: $raceBlock.data('view-type') != undefined
        }
      }

      function setHrefAttr(link, raceEid, mode, isOnline) {
        link.attr('href', '/play/' + raceEid + '/' + mode + (isOnline ? '/online' : ''))
      }
      
    }
  }

})(jQuery);