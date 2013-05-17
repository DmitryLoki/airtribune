jQuery(function ($) {
  $('ul.race-links').each(function (i, raceBlock) {
    var $raceBlock = $(raceBlock);
    var raceData = getRaceDataFromRaceBlock($raceBlock);

    requestRaceState($raceBlock, function response(answer) {
      console.log('response is', answer);

      if (answer == 'OK') {

        console.log('enable links in ', $raceBlock);
        //make links clickable
        setHrefAttr($raceBlock.find('a.race-link.2d'), raceData.raceEid, '2d', raceData.isOnline);
        setHrefAttr($raceBlock.find('a.race-link.3d'), raceData.raceEid, '3d', raceData.isOnline)
      } else {

        console.log('timeout for new request');
        setTimeout(function () {
          requestRaceState($raceBlock, response);
        }, 10000)
      }
    });
  });


  function requestRaceState($raceBlock, responseCallback) {
    console.log('send request for link block', $raceBlock);
    generateAnswer(responseCallback);
  }

  function getRaceDataFromRaceBlock($raceBlock) {
    return {
      contestId: $raceBlock.data('contest-id'),
      raceId: $raceBlock.data('race-id'),
      raceEid: $raceBlock.data('race-eid'),
      isOnline: $raceBlock.attr('date-view-type') != undefined
    }
  }

  function setHrefAttr(link, raceEid, mode, isOnline) {
    link.attr('href', '/play/' + raceEid + '/' + mode + (isOnline ? '/online' : ''))
  }

})
;

function generateAnswer(responseCallback) {
  var result = Math.random() <= .3 ? 'OK' : 'NOPE';
  responseCallback(result);
}