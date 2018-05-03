<?php

  function product_display($id){

  global $user;
   $client_specific_table = getCompanyTableName($user);
   $client_specific_table = $client_specific_table[product_table];

    $error_string = t("Product not found!!");
    $data = db_select($client_specific_table,'n')
    
        ->fields('n')
        ->condition('id',$id,'=')
        ->execute() 
        ->fetchAssoc();

        if($data){

          return theme('clientela_product_display',$product = array('product' => $data ));
        }else{

          return theme('clientela_product_display',$error = array('error'=> $error_string));
        }

    
  }