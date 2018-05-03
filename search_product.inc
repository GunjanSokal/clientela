<?php

/**
* Define a form.
*/
function clientela_product_nameform() {
  
  $form['product'] = array(
    // '#title' => t('Search Product'),
    '#type' => 'textfield',
    '#attributes' => array(
      'placeholder' => t('Please enter the product Id/Title'),
    ),      
    '#default_value' => isset($_REQUEST['keyword'])?$_REQUEST['keyword']:'',
    '#required' => FALSE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  return $form;
}


function clientela_product_nameform_submit($form, &$form_state) {
	$search_var = $form_state['values']['product'];
  if (isset($_REQUEST['identifier']) && !empty($_REQUEST['identifier'])) {
    drupal_goto('product/search',array('query' => array('keyword' => $search_var, 'identifier' => $_REQUEST['identifier'])));
  }else{
    drupal_goto('product/search',array('query' => array('keyword' => $search_var)));
  }
}

//Define a  search query
function client_details(){
  $check_arg=arg(1);
  global $user;
   $client_specific_table = getCompanyTableName($user);
   $client_specific_table = $client_specific_table[product_table];
   
  $search = isset($_REQUEST['keyword'])?$_REQUEST['keyword']:'';
    $query = db_select($client_specific_table,'c')->extend('PagerDefault')->limit(20);
    $query->fields('c',array('id','title','image','price','product_id','description'));
  $query ->orderBy('id', 'DESC');
  $db_or = db_or();
  $db_or->condition('product_id',$search);
  $db_or->condition('title', '%' . db_like($search) . '%', 'LIKE');
  $query->condition($db_or);
  if($check_arg=='featured'){
    $query->condition('featured',1);
  }
  $result = $query->execute()->fetchAll();
  $rows = array();
  foreach ($result as $key => $row) {	
  	$rows[] = array('id' => $row->id,
      'title' => l($row->title,'product/detail/'.$row->id),
      'img' => $row->image,
      'price' => $row->price,
      'description' => $row->description, 
      'product_id' => $row->product_id);
  }
  $pager = theme('pager', array("quantity" => 5));
    $output = theme('client_custom_product_search', array('rows' => $rows));
    $output = $output . $pager;
  return $output;
}









 









