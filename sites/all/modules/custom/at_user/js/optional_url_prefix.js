/**
 * Created by vk on 3/26/14.
 */
jQuery(function($){
  $.mask.definitions['a'] = '';
  $.mask.definitions['Z'] = '[a-zA-Z]';
  $.mask.placeholder = ' ';
  var urlMask = new Array(15).join('Z');
  $('#edit-optional-url').mask('airtribune.com/'+urlMask)
});