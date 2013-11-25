<?php

function multiform_test() {
  if (!empty($_POST)) {
    dsm($_POST);
    //$_POST = $_POST['multiform']['multiform_test_form1'];
    //dsm($_POST);
  }
  
  $settings = array(
    '#subforms' => array(
      0 => array(
        'form_id' => 'multiform_test_form1',
      ),
      1 => array(
        'form_id' => 'multiform_test_form2',
      ),
    ),
  );
  
  //return drupal_get_form('multiform_test_form1');
  return multiform_get_form($settings);
}

function multiform_test_form1() {
  $form['text1'] = array(
    '#type' => 'textfield',
    '#title' => 'Text 1',
    '#required' => TRUE,
  );
  $form['submit1'] = array(
    '#type' => 'submit',
    '#value' => 'Submit 1',
    '#submit' => array('multiform_test_submit1'),
  );
  $form['submit11'] = array(
    '#type' => 'submit',
    '#value' => 'Submit 11',
    '#submit' => array('multiform_test_submit11'),
  );
  return $form;
}

function multiform_test_form2() {
  $form['text2'] = array(
    '#type' => 'textfield',
    '#title' => 'Text 2',
    '#required' => TRUE,
  );
  $form['submit2'] = array(
    '#type' => 'submit',
    '#value' => 'Submit 2',
    '#submit' => array('multiform_test_submit2'),
  );
  return $form;
}

function multiform_test_submit1($form, $form_state) {
  drupal_set_message('Submit 1');
}

function multiform_test_submit11($form, $form_state) {
  drupal_set_message('Submit 11');
}

function multiform_test_submit2($form, $form_state) {
  drupal_set_message('Submit 2');
}

