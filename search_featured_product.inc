<?php

//Featured Product query
function get_featured_product(){
  global $user;
  if($user->uid){
     $client_specific_table = getCompanyTableName($user);
     $client_specific_table = $client_specific_table[product_table];    
  }
  else{
     global $_domain;
    $domainId=$_domain['domain_id'];               //To get the domain id
    $boutique_id=variable_get('domain'.$domainId); 
    // print_r($boutique_id);die();
    $company_reference_id=getCompanyReferenceID(null,$boutique_id);
    $companies_name=getCompanyTableNameByTargetId($company_reference_id);
    $client_specific_table=$companies_name[product_table];
  }

   // print_r($client_specific_table);   die();
   // $client_specific_table= 'new_company_101_product';                     //For temp uses
    $query = db_select($client_specific_table,'c');
    $query->fields('c',array('id','title','image','price','product_id','description'));
    $query ->orderBy('id', 'DESC');
    $query->condition('featured',1);
  $result = $query->execute()->fetchAll();
  $rows = array();
  foreach ($result as $key => $row) { 
    $rows[] = array('id' => $row->id,
      'title' => l($row->title,'featured/product/detail/'.$row->id),
      'img' => $row->image,
      'price' => $row->price,
      'description' => $row->description, 
      'product_id' => $row->product_id,
    );
  }
  $output = theme('client_featured_product', array('rows' => $rows)); 
  return $output;
}


function featured_product_display($id){
  session_start();
  if($user->uid){
     $client_specific_table = getCompanyTableName($user);
     $client_specific_table = $client_specific_table[product_table];    
  }
  else{
     global $_domain;
    $domainId=$_domain['domain_id'];               //To get the domain id
    $boutique_id=variable_get('domain'.$domainId); 
    $company_reference_id=getCompanyReferenceID(null,$boutique_id);
    $companies_name=getCompanyTableNameByTargetId($company_reference_id);
    $client_specific_table=$companies_name[product_table];
   }
   // $client_specific_table= 'new_company_101_product';                 //For temporary uses
    $error_string = t("Product not found!!");
    $data = db_select($client_specific_table,'n');
    $data->fields('n');
    $data->condition('id',$id,'=');
    $result = $data->execute()->fetchAll();
    foreach ($result as $key => $row) { 
      $rows[] = array(
        'id' => $row->id,
        'product_id' => $row->id,
        'price' => $row->price,
        'description' => $row->description,
        'image' => $row->image,
        'image_1' => $row->image_1,
        'image_2' => $row->image_2,
        'image_3' => $row->image_3,
        'image_4' => $row->image_4,
        'image_5' => $row->image_5,
        'size' => $row->size,
        'category' => $row->category,
        'add'=>t('Add to wishlist'),
        'share'=>t('Share on social media'),
      );
    }
    //To start the session and set the product id of selected featured product for wishlist
    // $_SESSION['featured_product_id']=$rows[0]['id'];
        if($data){
          return theme('client_featured_product_details',$product = array('product' => $rows ));
        }else{
          return theme('client_featured_product_details',$error = array('error'=> $error_string));
        }   
  }