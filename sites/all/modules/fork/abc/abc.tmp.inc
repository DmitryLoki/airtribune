<?php

function abc_test() {
  if (!empty($_POST)) {
    dsm($_POST);
    //$_POST = $_POST['multiform']['abc_test_form1'];
    //dsm($_POST);
  }
  
  $settings = array(
    '#subforms' => array(
      0 => array(
        'form_id' => 'abc_test_form1',
      ),
      1 => array(
        'form_id' => 'abc_test_form2',
      ),
    ),
  );
  
  //return drupal_get_form('abc_test_form1');
  return abc_get_form($settings);
}

function abc_test_form1() {
  $form['text1'] = array(
    '#type' => 'textfield',
    '#title' => 'Text 1',
    '#required' => TRUE,
  );
  $form['submit1'] = array(
    '#type' => 'submit',
    '#value' => 'Submit 1',
    '#submit' => array('abc_test_submit1'),
  );
  $form['submit11'] = array(
    '#type' => 'submit',
    '#value' => 'Submit 11',
    '#submit' => array('abc_test_submit11'),
  );
  return $form;
}

function abc_test_form2() {
  $form['text2'] = array(
    '#type' => 'textfield',
    '#title' => 'Text 2',
    '#required' => TRUE,
  );
  $form['submit2'] = array(
    '#type' => 'submit',
    '#value' => 'Submit 2',
    '#submit' => array('abc_test_submit2'),
  );
  return $form;
}

function abc_test_submit1($form, $form_state) {
  drupal_set_message('Submit 1');
}

function abc_test_submit11($form, $form_state) {
  drupal_set_message('Submit 11');
}

function abc_test_submit2($form, $form_state) {
  drupal_set_message('Submit 2');
}

