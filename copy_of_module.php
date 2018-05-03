<?php
/**
* @file
* Play with the Form API.
*/
/**
* Implements hook_menu().
*/
module_load_include('inc','clientela_product','search_product');
module_load_include('inc','clientela_product','display');
drupal_add_css(drupal_get_path('module','clientela_product').'/styles.css');

function clientela_product_menu() {
  $items['product/create'] = array(
    'title' => 'Clientela Product Information Form',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('clientela_product_form'),
    'access arguments' => array('administer product application'),
    'type' => MENU_NORMAL_ITEM
  );
  $items['product/display'] = array(
    'title' => 'Clientela Product Information List',
    'page callback' => 'all_record_from_db',
    'access arguments' => array('administer product application'),
    'type' => MENU_NORMAL_ITEM
  );
  $items['product/search'] = array(
  'title' => 'Search Result',
  'page callback' => 'client_details',
  // 'page arguments' => array(1),
  'access arguments' => array('administer productform applications'),
   
  'type' => MENU_NORMAL_ITEM
  );
  $items['view/clientela_product/%'] = array(
      'title' => 'View clientela product',
      'description' => 'Create a new product.',
      'page callback' => 'product_display',
      'page arguments' => array(2),
      'access arguments' => array('administer productform applications'),
  );
  return $items;
}

/**
*Implement hook_permission
*/
function clientela_product_permission(){
  return array(
    'administer product application' =>array(
      'title' => t('Administer product applicationnn'),
      'description' => t('Permissions for Product module'),
    ),
  );
}

/*
**Function for getting taxonomy vocabulary values.
*/
function clientela_product_get_taxonomy_term_options($machine_name){
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

/**
* Define a form.
*/
function clientela_product_form() {
  $product_a_i_id =" ";
  $product_a_i_id = arg(2);
  //Function to get the data for default values in form.(For edit option).
  $default_values = get_default_values($product_a_i_id);
  // print_r($default_values); die();
  
  $form['title'] = array(
    '#title' => t('Product Title'),
    '#type' => 'textfield',
    '#default_value' => $default_values[0]['title'],
    '#description' => t('Please Enter Product Title')
  );
  $form['price'] = array(
    '#title' => t('Product Price'),
    '#type' => 'textfield',
    '#default_value' => $default_values[0]['price'],
    '#description' => t('Please Enter Product Price')
  );
  $form['description'] = array(
    '#title' => t('Product Description'),
    '#type' => 'textarea',
    '#default_value' => $default_values[0]['description'],
    '#description' => t('Please Enter Product Description')
  ); 

  $form['color'] = array(
    '#title' => t('Product color'),
    '#type' => 'select',
     '#default_value' => $default_values[0]['color'],
    '#description' => 'Please Enter Product Color',
    '#options' => clientela_product_get_taxonomy_term_options('color_taxonomy'),
  );
  $form['size'] = array(
    '#title' => t('Product Size'),
    '#type' => 'select',
    '#description' => t('Please Select Product Size'),
     '#default_value' => $default_values[0]['size'],
     '#options' => clientela_product_get_taxonomy_term_options('size_taxonomy'),
  );
  $form['category'] = array(
    '#title' => t('Product Category'),
    '#type' => 'select',
     '#default_value' => $default_values[0]['category'],
    '#description' =>t('Please Select Product Category'),
    '#options' => clientela_product_get_taxonomy_term_options('category_taxonomy')
  );
  
   $form['image'] = array(
    '#title' => t('Product Image *'),
    '#type' => 'managed_file',
     '#default_value' => $default_values[0]['image'],
    '#upload_location' => 'public://product_image',
    '#description' => t('Please Select Product Image')
  );
  $form['image_1'] = array(
    '#title' => t('Product Image (optional)'),
    '#type' => 'managed_file',
    '#upload_location' => 'public://product_image',
     '#default_value' => $default_values[0]['image_1'],
    '#description' => t('Please Select Product Image')
  );
  $form['image_2'] = array(
    '#title' => t('Product Image (optional)'),
    '#type' => 'managed_file',
     '#default_value' => $default_values[0]['image_2'],
    '#upload_location' => 'public://product_image',
    '#description' => t('Please Select Product Image')
  );
  $form['image_3'] = array(
    '#title' => t('Product Image (optional)'),
    '#type' => 'managed_file',
     '#default_value' => $default_values[0]['image_3'],
    '#upload_location' => 'public://product_image',
    '#description' => t('Please Select Product Image')
  );
  $form['image_4'] = array(
    '#title' => t('Product Image (optional)'),
    '#type' => 'managed_file',
     '#default_value' => $default_values[0]['image_4'],
    '#upload_location' => 'public://product_image',
    '#description' => t('Please Select Product Image')
  );
  $form['image_5'] = array(
    '#title' => t('Product Image (optional)'),
    '#type' => 'managed_file',
     '#default_value' => $default_values[0]['image_5'],
    '#upload_location' => 'public://product_image',
    '#description' => t('Please Select Product Image')
  );
  $form['product_id'] = array(
    '#title' => t('Product Id'),
    '#type' => 'textfield',
     '#default_value' => $default_values[0]['product_id'],
    '#description' => t('Please Enter Product Id')
  );
  $form['active_status'] = array(
    '#title' => t('Product Status'),
    '#type' => 'checkbox',
    '#default_value' => $default_values[0]['active_status'],
    '#description' => t('Please Select Product Status')
  );
  $form['id'] = array(
    '#title' => t('S id'),
    '#type' => 'hidden',
    '#default_value' => $default_values[0]['id'],
  );
  $a=($default_values==""?'submit':'update');
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t($a)
  );  
  return $form;
}

/*
** Validation function
*/

function clientela_product_form_validate($form ,&$form_state){
    $image=$form_state['values']['image'];    
    $image_save = file_save_upload('product_image');  
    if($image_save){
      $form_state['values']['image'] = $image_save;
    }

  $title=$form_state['values']['title'];
  $price=$form_state['values']['price'];
  $description=$form_state['values']['description']; 
  $product_id=$form_state['values']['product_id']; 
  $color=$form_state['values']['color'];
  $size=$form_state['values']['size'];
  $category=$form_state['values']['category'];
  $image=$form_state['values']['image'];
  
    
  $image_save = file_save_upload('product_image');

  if($image_save){
    $form_state['values']['image'] = $image_save;
  }

  if($title == ""){
    form_set_error('p_name',
    t('Please Enter Product title'));
  }
  if($price == ""){
    form_set_error('p_price',
    t('Please Enter Product Price'));
  }
  if(!is_numeric($price)){
    form_set_error('p_price',
    t('Please Enter Valid Price'));
  }
  if($product_id == ""){
    form_set_error('p_price',
    t('Please Enter Product Id'));
  }
  if(!is_numeric($product_id)){
    form_set_error('p_price',
    t('Please Enter Valid Id'));
  }
  /*
  **  Validation for product id 
  **  Unique Product Id
  */
  // global $user;
  // $client_specific_table = getCompanyTableName($user);
  // $client_specific_table = $client_specific_table.'_product';

  // $searchQuery_result=all_record_from_db();
  // $queryOne="";
  // $queryOne = db_select($client_specific_table, 'c')
  //     ->fields('c', array('title'))
  //     ->condition('product_id',$product_id)
  //     ->execute()
  //     ->fetchAll();
  // if($queryOne!=Array()){
  //   form_set_error('p_price',
  //   t('This Product Id is already used'));
  // }

}

/*
** Function for form submission
*/
function clientela_product_form_submit($form, &$form_state)  {
  global $user;
  $client_specific_table = getCompanyTableName($user);
  $client_specific_table = $client_specific_table.'_product';
  $a=$form_state['values']['submit'];
  global $user;
  $id=$form_state['values']['id'];
  $title=$form_state['values']['title'];
  $price=$form_state['values']['price'];
  $description=$form_state['values']['description'];
  $color=$form_state['values']['color'];
  $size=$form_state['values']['size'];
  $category=$form_state['values']['category'];
  $image[0]=$form_state['values']['image'];
  $image[1]=$form_state['values']['image_1'];
  $image[2]=$form_state['values']['image_2'];
  $image[3]=$form_state['values']['image_3'];
  $image[4]=$form_state['values']['image_4'];
  $image[5]=$form_state['values']['image_5'];
  $product_id=$form_state['values']['product_id'];
  $active_status = $form_state['values']['active_status'];
 
  //Condition for empty image field suffling
  for($j=0;$j<=4;$j++){
    if($image[$j]==0){
      for($i=5;$i>$j;$i--){
        if($image[$i]!=0){
          $image[$j]=$image[$i];
          $image[$i]= 0;
          break;
        }
      }
    }
  }

  //Insert data When user submit the form
  if($a=='submit')
  {
    db_insert($client_specific_table)
    ->fields(array(
      'title' => $title,
      'price' => $price,
      'description' => $description,
      'color' => $color,
      'size' => $size,
      'category' => $category,
      'image' => $image[0],
      'image_1' => $image[1],
      'image_2' => $image[2],
      'image_3' => $image[3],
      'image_4' => $image[4],
      'image_5' => $image[5],
      'product_id' => $product_id,
      'active_status' => $active_status,
      ))
    ->execute();
    drupal_set_message("Form Submitted");
    drupal_goto('product/display');
  }
  //Update data when user edit the form
  else
  {
    $num_updated = db_update($client_specific_table)
    ->fields(array(
      'title' => $title,
      'price' => $price,
      'description' => $description,
      'color' => $color,
      'size' => $size,
      'category' => $category,
      'image' => $image[0],
      'image_1' => $image[1],
      'image_2' => $image[2],
      'image_3' => $image[3],
      'image_4' => $image[4],
      'image_5' => $image[5],
      'product_id' => $product_id,
      'active_status' => $active_status,
      ))
    ->condition('id',$id)
    ->execute();
    drupal_set_message("Form Updated");
    drupal_goto('product/display');
  }
  
}

//View API
function clientela_product_views_api(){
  return array('api' => '3.0',
  'path' => drupal_get_path('module','clientela_product'). '/views',
  );
}

/*
** Function to display data in table.
*/
function all_record_from_db(){
  global $user;
  $client_specific_table = getCompanyTableName($user);
  $client_specific_table = $client_specific_table.'_product';  
  $product_a_i_id =" ";
  $product_a_i_id = arg(2);
  delete_default_values($product_a_i_id);

  //For Heading of Table
  $header = array('Id','Title','Price','Description','Color','size','Category','Image','P_Id','Status','Edit','Delete');
  $rows = array();
  
  //query to fetch all content
  $query = db_select($client_specific_table, 'c');
  $query ->fields('c',array('id','title','price','description','color','size','category','image','product_id','active_status'))
    ->execute() 
    ->fetchAll();
  $result = $query->execute()->fetchAll();
  
  foreach ($result as $key => $data) {
    $file = file_load($data->image);
    $url = @file_create_url($file->uri);
    $color_term=clientela_product_get_taxonomy_term_options('color_taxonomy');
    $size_term=clientela_product_get_taxonomy_term_options('size_taxonomy');
    $category_term=clientela_product_get_taxonomy_term_options('category_taxonomy');
    if($data->active_status==1){
      $status = 'active';
    }
    else{
      $status = 'inactive';
    }
    $rows[] = array(
      'id' => $data ->id,
      'title' => l($data ->title,'http://localhost/drupal_d//view/clientela_product/'.$data ->product_id),
      'price' => $data ->price,
      'description' => $data ->description,
      'color' => $color_term[$data->color],
      'size' => $size_term[$data ->size],
      'category' => $category_term[$data ->category],
      'image'=> '<img src="'.$url.'" alt="Not Available" style="width:40px;height:40px;">',
       // 'image_1'=> '<img src="'.$url.'" alt="Not Available" style="width:40px;height:40px;">',
       // 'image_2'=> '<img src="'.$url.'" alt="Not Available" style="width:40px;height:40px;">',
       // 'image_3'=> '<img src="'.$url.'" alt="Not Available" style="width:40px;height:40px;">',
       // 'image_4'=> '<img src="'.$url.'" alt="Not Available" style="width:40px;height:40px;">',
       // 'image_5'=> '<img src="'.$url.'" alt="Not Available" style="width:40px;height:40px;">',
      'product_id'=> $data->product_id,
      'active_status'=> $status,
      'k'=>l('Edit','product/create/'.$data ->id),
      'y'=>l('Delete','product/display/'.$data ->id),
      );   
  }
return theme('table', array('header'=>$header,'rows'=>$rows));
} 

/*
** Function to get the data for default values in form.(For edit option).
*/

function get_default_values($id){
  global $user;
  $client_specific_table = getCompanyTableName($user);
  $client_specific_table = $client_specific_table.'_product';
  $rows = array();
  $query = db_select($client_specific_table, 'c');
  $query ->fields('c',array('id','title','price','description','color','size','category','image','image_1','image_2','image_3','image_4','image_5','product_id','active_status'))
    ->condition('id',$id)
    ->extend('PagerDefault')->limit(5)
    ->execute() 
    ->fetchAll();
  $result = $query->execute()->fetchAll();    
  foreach ($result as $key => $data) {
    $file = file_load($data->image);
    $url = @file_create_url($file->uri);
    $rows[] = array(
      'id' => $data ->id,
      'title' => $data ->title,
      'price' => $data ->price,
      'description' => $data ->description,
      'color' => $data ->color,
      'size' => $data ->size,
      'category' => $data ->category,
      'image' => $data ->image,
      'image_1' => $data ->image_1,
      'image_2' => $data ->image_2,
      'image_3' => $data ->image_3,
      'image_4' => $data ->image_4,
      'image_5' => $data ->image_5,
      'product_id' => $data ->product_id,
      'active_status' => $data ->active_status,
    );

  return $rows;
 }
}

//Function to delete the row from table.
function delete_default_values($id){
  global $user;
  $client_specific_table = getCompanyTableName($user);
  $client_specific_table = $client_specific_table.'_product';
  $query = db_delete($client_specific_table)
    ->condition('id',$id)
    ->execute();
    drupal_set_message("Row Deleted");
}

