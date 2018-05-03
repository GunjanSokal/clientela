<?php

//Featured Product query
function get_wishlisted_product(){
  // session_start();
  // $id=$_SESSION['featured_product_id'];
  global $user;
   $client_specific_table = getCompanyTableName($user);
   $client_specific_table = $client_specific_table[product_table];
   
   $nid = db_select('node', 'n')
        ->fields('n',array('nid'))
        ->condition('uid',$user->uid)
        ->condition('type','client_wishlist')
        ->execute()
        ->fetchField();
        // print_r('nid :- ' .$nid . '    end ');
        // print_r($user);
        // die();
        // print_r($user);die();
  $node=node_load($nid);
    $wishlisted_product_id=$node->field_product_id[und];
    // $client_specific_table='new_company_101_product'; //For temp
    $query = db_select($client_specific_table,'c');
    $query->fields('c',array('id','title','image','price','product_id','description'));
    $query ->orderBy('id', 'DESC');
    $query->condition('id',$wishlisted_product_id);
    $result = $query->execute()->fetchAll();
    
  $rows = array();
  foreach ($result as $key => $row) { 
    $rows[] = array(
      'id' => $row->id,
      'title' => $row->title,
      'img' => $row->image,
      'price' => $row->price,
      'description' => $row->description, 
      'product_id' => $row->product_id,
    );
  }
  $output = theme('client_featured_product', array('rows' => $rows)); 
  return $output;
}