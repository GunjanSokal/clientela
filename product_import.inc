<?php
function product_importer_form() {
    $form['#attributes'] = array(
      'enctype' => 'multipart/form-data'
    );  
    $form['csvfile'] = array( 
      '#title' => t('Attach CSV File'),
      '#type'  => 'file',    
      '#preview' => TRUE,
      '#description' => '<a href="sample">'.t('Download sample product CSV file') .'</a>',      
    ) ;
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
    ) ;
    $form['#validate'] = array(
      'product_importer_validate_fileupload',
     ) ;
    return $form ;
}

// Validation and upload function for file uplaod 

function product_importer_validate_fileupload(&$form, &$form_state) {
    
    $validators = array(
      'file_validate_size' => array(2 *1024 * 1024),
      'file_validate_extensions' => array( 'csv' ),      
    );
    
    if ( $file = file_save_upload('csvfile', $validators, "public://product_csv/", FILE_EXISTS_REPLACE) ) {   
      $form_state['values']['csvupload'] = $file->destination; 
      $GLOBALS['getfilename'] = $file; 
     }
    else {
      if(!$file){
        form_set_error('product_importer', t('No file is selected'));
      }
      form_set_error('product_importer', t('Unable to copy upload file to destination', array('!dest' => $destination)));
    }    
}

// Product import form submit  

function product_importer_form_submit(&$form, &$form_state) {     
    $getfilename = $GLOBALS['getfilename'];
    $batch = array(
      'title' => t('Importing CSV ...'),
      'operations' => array(),
      'init_message' => t('Commencing'),
      'progress_message' => t('Processed @current out of @total.'),
      'error_message' => t('An error occurred during processing'),
      'finished' => 'product_import_finished',
    ) ;
    if ( isset( $form_state['values']['csvupload'] ) ) {
      if ( $handle = fopen($form_state['values']['csvupload'], 'r') ) {
       $GLOBALS['gethandle'] = $handle;
        $key = fgetcsv($handle,4096,"\t");
        $row_count = 0;       
        while(!feof($handle)) {
          $row = fgetcsv($handle, 4096,"\t");
          $row = array_combine($key, $row);
          $validate=0;
          $validate=validate_product_import($row);
          if($validate==1){
           $batch['operations'][] = array('_product_import', array($row));       
          }
        }
        fclose($handle);
      } 
    } 
    batch_set($batch);
  }
//Validation Function
function validate_product_import($row){
    $flag=1;
    $title= $row['title'];
    $price = $row['price'];
    $product_id = $row['product_id'];
    $active_status= $row['active_status'];
    $flag=(empty($title) || empty($price) || empty($product_id) || empty($active_status))?0:1;
    $flag=(!is_numeric($price))?0:1;
  return $flag;
}
   

//Function to invoke when the importing is finished 
function product_import_finished($success, $results, $operations) {
  if ($success) {   
    $message = t('@count product successfully processed', array('@count' => $results['total']));    
    drupal_set_message($message);
  }
  else {   
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }  
}
  //  insertion or updation in database according to the product_id

function _product_import($row,&$context) {
  if (!isset($context['results']['total'])) {
    $context['results']['total'] = 0;
  }   
  global $user;
  $client_specific_table = getCompanyTableName($user);
  $client_specific_table = $client_specific_table['product_table'];  
  $color = $row['color'];
  $size = $row['size'];
  $category = $row['category'];

  $img[] = empty($row['image']) ? '0' : fetch_file_from_url($row['image']);  
  $img[] = empty($row['image_1']) ? '0' : fetch_file_from_url($row['image_1']); 
  $img[] = empty($row['image_2']) ? '0' : fetch_file_from_url($row['image_2']);
  $img[] = empty($row['image_3']) ? '0': fetch_file_from_url($row['image_3']);
  $img[] = empty($row['image_4']) ? '0' : fetch_file_from_url($row['image_4']);
  $img[] = empty($row['image_5']) ? '0' : fetch_file_from_url($row['image_5']);
 //To swap the image 
  for($j=0;$j<=4;$j++){
    if($img[$j]==0){
      for($i=5;$i>$j;$i--){
        if($img[$i]!=0){
          $img[$j]=$img[$i];
          $img[$i]='0';
          break;
        }
      }
    }
  }

  $color_tid = import_get_term_id_by_name($color,'color_taxonomy'); 
  $category_tid = import_get_term_id_by_name($category,'category_taxonomy'); 
  $size_tid = import_get_term_id_by_name($size,'size_taxonomy'); 

       
    $query = db_merge($client_specific_table)
      ->key(array('product_id' => $row['product_id']))
      ->fields(array(
      'title' => $row['title'],
      'price' => $row['price'],
      'description' => $row['description'],
      'color' => $color_tid,
      'size' => $size_tid,
      'category' => $category_tid,
      'image' => $img[0],
      'image_1' => $img[1],
      'image_2' => $img[2],
      'image_3'  => $img[3],
      'image_4' => $img[4],
      'image_5' => $img[5],
      'product_id' => $row['product_id'],
      'active_status' => $row['active_status'],
      ))
    ->execute();

    $context['results']['total']++;
    }

//Function to fetch image from  url

function fetch_file_from_url($url) {
    if (empty($url) || !filter_var($url, FILTER_VALIDATE_URL)) 
    {return '0';}
    $image = system_retrieve_file($url, 'public://product_image', true, FILE_EXISTS_REPLACE);
    return $image->fid;
}

// //Function to fetch delimiter from cvs file 

// function getFileDelimiter($file, $checkLines = 2){
    
//   $gethandle = $GLOBALS['gethandle'];        
//         $delimiters = array(
//           ',',
//           "\t",
//           ';',
//           '|',
//           ':'
//         );
//         $results = array();
//         $i = 0;
//          while($i <= $checkLines){
//             $row = fgets($gethandle);
//             foreach ($delimiters as $delimiter){
//                 $regExp = '/['.$delimiter.']/';
//                 $fields = preg_split($regExp, $row);
//                 if(count($fields) > 1){
//                     if(!empty($results[$delimiter])){
//                         $results[$delimiter]++;
//                     } else {
//                         $results[$delimiter] = 1;
//                     }   
//                 }
//             }
//            $i++;
//         }
//         $results = array_keys($results, max($results));
        
//         return $results[0];

// }

function sample_pdf_open(){
    $sample = 'public://product.csv';
    $file=file_create_url($sample);
    header('Content-type: application/csv');
    header('Content-Transfer-Encoding: UTF-8');
    header('Content-Disposition: attachment; filename="sample.csv"');
    ob_end_clean();
    @readfile($file);
}


