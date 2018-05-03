<?php
  /**
  * Implement hook_views_data
  *
  */

function clientela_product_views_data() {
  $data = array();
    $data['clientela_product']['table']['group'] = t('Clientela Product Information View');

     $data['clientela_product']['table']['base'] = array(
      'field' => 'id', // This is the identifier field for the view.
      'title' => t('Clientela Product List'),
      'help' => t('This table is for final'),            
    );

    $data['clientela_product']['id'] = array(
          'title' => t('S.Id'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
     $data['clientela_product']['title'] = array(
          'title' => t('Product Title'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['price'] = array(
          'title' => t('Product Price'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['product_description'] = array(
          'title' => t('Product Description'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['color'] = array(
          'title' => t('Product Color'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['size'] = array(
          'title' => t('Product Size'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['category'] = array(
          'title' => t('Product Category'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['image'] = array(
          'title' => t('Product Image'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['image_1'] = array(
          'title' => t('Product Imageee 1'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['image_2'] = array(
          'title' => t('Product Image 2'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['image_3'] = array(
          'title' => t('Product Image 3'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['image_4'] = array(
          'title' => t('Product Image 4'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['image_5'] = array(
          'title' => t('Product Image 5'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['product_id'] = array(
          'title' => t('Product Id'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['active_status'] = array(
          'title' => t('Product Status'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data[''][''] = array(
          'title' => t('Edit'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 
      $data['clientela_product']['active_status'] = array(
          'title' => t('Delete'),
          // 'help' => t('Add group id for view'),
          'filter' => array(
              'handler' => 'views_handler_filter_string',
          ),
          'field' => array(
              'handler' => 'views_handler_field',
              'click sortable' => TRUE,
          ),
          'sort' => array(
              'handler' => 'views_handler_sort',
          ),
          'argument' => array(
              'handler' => 'views_handler_argument',
          ),
      ); 

     return $data;
  }