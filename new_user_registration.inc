<?php
session_start();
function new_user_registration()
{ 
  $form['client_email'] = array(
    '#title'=>'Email',
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => 'Email *'), 
    '#required' => TRUE    
  );

  $form['client_fname'] = array(
    '#title' => 'First Name',
    '#type' => 'textfield', 
    '#attributes' => array('placeholder' => 'First *'),
    '#required' => TRUE
  );  

  $form['client_lname'] = array(
    '#title' => 'Last Name',
    '#type' => 'textfield', 
    '#attributes' => array('placeholder' => 'Last *'),
    '#required' => TRUE
  );

  $form['password'] = array(
    '#title'=>'Password',
    '#type' => 'password',
    '#attributes' => array('placeholder' => 'Password *'), 
    '#required' => TRUE    
  );

  $form['confirm_password'] = array(
    '#title' => 'Confirm Password',
    '#type' => 'password', 
    '#attributes' => array('placeholder' => 'Confirm Password *'),
    '#required' => TRUE
  ); 
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('submit')
  );  
  $form['#theme'] = 'new_user_registration';
  return $form;
}

function new_user_registration_validate($form, &$form_state){
  $client_email=$form_state['values']['client_email'];
  $client_fname=$form_state['values']['client_fname'];
  $client_lname=$form_state['values']['client_lname'];
  $password=$form_state['values']['password'];
  $confirm_password=$form_state['values']['confirm_password'];

  if(strlen($password)<3 ){
      form_set_error('password','Password must contain at least 4 characters');
  }
  if(strlen($password)>10 ){
      form_set_error('password','Password must be less than 10 characters');
  }
  if($password!=$confirm_password){
      form_set_error('password','Password and Confirm password do not match');
  }

  if (!filter_var($client_email, FILTER_VALIDATE_EMAIL)) {
        form_set_error('client_email','Email Address not valid');
  }
  else{
        $client_email = trim($client_email);
        $user_uid =  db_query("SELECT uid FROM {users} WHERE mail = :mail;", array(':mail' => $client_email))->fetchField();
        if ($user_uid){
            form_set_error('client_email','Client already present in system. Please try to log in instead!');
        }
  }   
}

function new_user_registration_submit($form, &$form_state){
  global $_domain;
  $domainId=$_domain['domain_id'];               //To get the domain id
  $boutique_id=variable_get('domain'.$domainId); 
  $company_reference_id=getCompanyReferenceID(null,$boutique_id);
  $companies_name=getCompanyTableNameByTargetId($company_reference_id);
  $company_name=$companies_name['profile_table'];
  $client_email=trim($form_state['values']['client_email']);
  $client_fname=$form_state['values']['client_fname'];
  $client_lname=$form_state['values']['client_lname'];
  $fullname = $client_fname .' '. $client_lname;
  $password=$form_state['values']['password'];
  
  if($company_reference_id){
        $new_user = array(
          'name' => $client_email , 
          'pass' => $password, 
          'mail' => $client_email,
          'status' => 1,
          'init' => $client_email,
          'field_account_full_name' => array(LANGUAGE_NONE => array(array('value' => $fullname))),
          'field_company_reference' => array(LANGUAGE_NONE => array(array('target_id' => $company_reference_id))),
          'roles' => array(
            DRUPAL_AUTHENTICATED_RID => 'authenticated user',
            7 => 'ER',
          ),
          'domain_user' => array($domainId => $domainId)
        );
      }
      user_save('',$new_user);
      $client_uid = db_select('users', 'u')
        ->fields('u', array('uid'))
        ->condition('u.mail',$client_email)
        ->execute()
        ->fetchField();

        db_insert($company_name)
          ->fields(array(
        'client_first_name' => $client_fname,
        'client_last_name' => $client_lname,
        'client_uid' => $client_uid,
        'client_reference_company' => $company_reference_id,
        'client_registered_boutique' => $boutique_id,
      )
    )
    ->execute();
  // global $user;
  $user = user_load($client_uid);  
  // $result=wishlist_node_create_update($user);    //For creating new node
  drupal_set_message(t('Registered'));
  
  // drupal_goto('product/wishlist');
  
  $_SESSION['redirect_user_to_wishlist_page']='1';
  drupal_goto('user');
}

function wishlist_node_create_update($user){
  $nid = db_select('node', 'n')
        ->fields('n', array('nid'))
        ->condition('n.uid',$user->uid)
        ->condition('n.type','client_wishlist')
        ->execute()
        ->fetchField();
  if($nid){
    // print_r('in if');
    // die();
    $node_detail = node_load($nid);
    $node_detail->field_product_id['und'][]['value'] = $_SESSION['featured_product_id']; 
    node_save($node_detail);
  }
  else{
    // print_r('in else');
    // die();
    if(!empty($_SESSION['featured_product_id'])){
      $node= new stdClass();                  // We create a new node object
      $node->type = 'client_wishlist';        //Type :- content type

      $node->title ='node_created_by_'.$user->field_account_full_name[und][0][value];
      $node->uid = $user->uid;
      $node->field_client_uid['und'][0]['value'] =$user->uid;
      $node->field_product_id['und'][]['value']=$_SESSION['featured_product_id'];

      
      $node = node_submit($node); // Prepare node for saving
      node_save($node);
        // print_r($node);die();
        // die();
    }
  }

  
  return $node;
}