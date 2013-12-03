jQuery(function ($) {
  $(".view-paragliding-pilots-list table").filterTable();
  var $main_input = $(".filter-table:first input");
  $main_input.keyup(function(){
    $(".filter-table input").not(this).val(jQuery(this).val()).keyup();
  });
  $(".filter-table input").not($main_input).hide();
});
