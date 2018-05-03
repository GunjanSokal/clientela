<?php
/**
* Define a form.
*/
function clientela_product_list_nameform() {
  $form['product'] = array(
    '#title' => t('Title/Id'),
    '#type' => 'textfield',
    '#attributes' => array(
      'placeholder' => t('Please enter the product Id/Title'),
    ), 
    '#default_value' => isset($_REQUEST['product'])?$_REQUEST['product']:'',
    '#required' => FALSE,
  );
  $form['category'] = array(
    '#title' => t('Category'),
    '#type' => 'select',
    '#options' => clientela_product_get_taxonomy_term_options('category_taxonomy'),
    '#default_value' => isset($_REQUEST['category'])?$_REQUEST['category']:'',
  );
  $form['status'] = array(
    '#title' => t('Status'),
    '#type' => 'select',
    '#options' => array(t('All'), t('Active'), t('Inactive')),
    '#default_value' => isset($_REQUEST['status'])?$_REQUEST['status']:'',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('submit')
  );
  $form['#theme'] = 'client_product_list';
  return $form;
}
//Form Submit for Listing
function clientela_product_list_nameform_submit($form, &$form_state) {
  $product = $form_state['values']['product'];
  $category = $form_state['values']['category'];
  $status = $form_state['values']['status'];
  drupal_goto('product/list',array('query' => array('product' => $product , 'category' => $category ,'status' => $status)));
}
//Function to get the Taxonomy Name
function get_taxonomy_term_options_for_listing($machine_name){
  Global $user;
    $options = array(); 
    $vid = taxonomy_vocabulary_machine_name_load($machine_name)->vid;
    $options_source = taxonomy_get_tree($vid); 
    foreach($options_source as $item ) {
        $key = $item->tid;
        $value = $item->name;
        $options[$key] = $value;
    }
    return $options;
}


/*
** Function to display data in table.
*/
function all_record_from_db(){
  global $user;
  $client_specific_table = getCompanyTableName($user);
  $client_specific_table = $client_specific_table[product_table];
  $product = isset($_REQUEST['product'])?$_REQUEST['product']:'';
  $category = isset($_REQUEST['category'])?$_REQUEST['category']:'';
  $status=$_REQUEST['status'];
  $status = ($status==0) ? '' :(($status==1)?1:0);
  $statusForCount=$status;
  $rows = array(); 
  $query = db_select($client_specific_table, 'c')->extend('PagerDefault')->extend('TableSort');
  $query ->fields('c',array('product_id','title','price','description','color','size','category','image','product_id','active_status','id'));
  $query ->orderBy('id', 'DESC');
  $db_or = db_or();
  $db_or->condition('product_id',$product);
  $db_or->condition('title', '%' . db_like($product) . '%', 'LIKE');
  $query->condition($db_or);
  $query ->condition('category', '%' . db_like($category) . '%', 'LIKE');
  $query ->condition('active_status', '%' . db_like($status) . '%', 'LIKE');
  $query ->addTag('translatable');
  $query ->limit(20);
  $result = $query->execute()->fetchAll();

  if(!empty($result)){
  //For Heading of Table 
    $header = array(t('Image'),t('Product Id'),t('Title'),t('Price'),t('Category'),t('Status'),t('Edit'),t('Delete'));
    foreach ($result as $key => $data) {
      $file = file_load($data->image);
      $url = image_style_url('thumbnail_50', $file->uri);
      $img='<img src="'.$url.'">';
      $color_term=get_taxonomy_term_options_for_listing('color_taxonomy');
      $size_term=get_taxonomy_term_options_for_listing('size_taxonomy');
      $category_term=get_taxonomy_term_options_for_listing('category_taxonomy');
      $status=($data->active_status==1)?'Active':'Inactive';
      $rows[] = array(   
        'image'=> l($img,'product/detail/'.$data ->id,array('html' => TRUE)),    
        'id' => t($data ->product_id),
        'title' => l(t($data ->title),'product/detail/'.$data ->id),
        'price' => $data ->price,
        'category' => $category_term[$data->category],
        'active_status'=> t($status),
        'k'=>l(t('Edit'),'product/update/'.$data ->id),
        'y'=>l(t('Delete'),'product/delete/'.$data ->id),
        ); 
    }
    $result_count=get_count($client_specific_table,$product,$category,$statusForCount);
    $output = '<p class = "count-product-rows">Total Number of Products :-'.$result_count.'<p>';
    $output .= theme('table', array('header'=>$header,'rows'=>$rows));
    $output .= theme('pager');
  }
  else{
    $output= (t('Product Not Found'));
  }
 
  return $output;
} 

function get_count($client_specific_table,$product,$category,$status){  
  $query = db_select($client_specific_table, 'c');
  $query ->fields('c',array('product_id','id'));
  if(is_numeric($product)){    
     $query ->condition('product_id',$product);
  }
  else{
     $query ->condition('title', '%' . db_like($product) . '%', 'LIKE') ;   
  }    
  $query ->condition('category', '%' . db_like($category) . '%', 'LIKE');
  $query ->condition('active_status', '%' . db_like($status) . '%', 'LIKE');
  $count = $query->execute()->rowCount();
  return $count;
}