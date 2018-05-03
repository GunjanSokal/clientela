​<?php 
    global $base_url;
    $error_string = t("Product not found");

?>   
    <div class="search-body product-clientela">
    <?php
        if (isset($rows) && count($rows) > 0) {
            foreach($rows as $rownumber => $values) :
            $item_id = $values['id'];
            if($values['img']){
            $img = file_load($values['img']);
            $urlv = image_style_url('item_150x150', $img->uri);
            $values['img']=$urlv;  
            }
            $alter = array(
                'max_length' => 12,
                'word_boundary' => 'yes',
                'ellipsis' => 'yes',
                'html' => 'yes' 
            );              
    ?>
   <div class="col-sm-4 col-md-3">
    <div class="prod-wrapper">
    <div class="views-field views-field-field-item-image"><?php 
        if($values['img']){
             ?>
           <a href="detail/<?php echo $item_id; ?>"> <img src = <?php echo $values['img']; ?> > </a>
              <?php  } 
                 else{         
                    ?>
               <a href="detail/<?php echo $item_id; ?>"><img src = <?php print $base_url; ?>/sites/default/files/default_images/default_image.png    alt = t("image") ></a>          

             <?php   } ?>
         </div>
            <div class="prod-content">   
            <div class="views-field views-field-field-list-price-usd">
            <div class="field-content">   
                <p><?php print $values['title']; ?></p>
                <p><?php print t('$').$values['price']; ?></p> 
                <p><b>ID : </b><?php print $values['product_id']; ?></p>

         <?php if (isset($_SESSION['sidepanel']['active']) && count($_SESSION['sidepanel']['active'])): ?>
          <!--output select button-->
          <div class="views-field views-field-select-button" entity_id="<?php print $item_id;?>">
            <img src="<?php print $base_url . '/' . drupal_get_path('theme', 'hlab_store_main');?>/images/wait.gif"  entity_id="<?php print $item_id;?>"/>
            </div>
          <?php elseif (isset($_REQUEST['identifier'])): 
          $holded = already_wished_item($_REQUEST['identifier'], $item_id);
          ?>
           <div class="views-field views-field-select-button view-client-hold" entity_id="<?php print $item_id;?>" recommended_by="<?php print $user->uid;?>" client_id="<?php print $_REQUEST['identifier'];?>">
           <?php if (!empty($holded)) {?>
             <button class = "btn btn-sm disable btn-primary wishlisted" disabled>Wishlisted</button>
             <span holded_id="<?php echo $holded[0]->nid?>" class="wishlisted_button"> <a href="javascript:void(0)" class="btn anc-remove btn-primary active" data-mini="false" data-theme="a">X</a></span>
             <span class="wishlist_button" style="display:none;">
             <a href="javascript:void(0)" class="btn anc-item-single-admin btn-primary active" data-mini="false" data-theme="a">Add to Wish-List</a> </span>
              <?php } else {?>   
             <a href="javascript:void(0)" class="btn anc-item-single-admin btn-primary active" data-mini="false" data-theme="a">Add to Wish-List</a>
              <span holded_id="<?php echo $holded[0]->nid?>" class="wishlisted_button add_wishlist" style="display:none;"> 
               <button class = "btn btn-sm disable btn-primary wishlisted" disabled >Wishlisted</button>
              <a href="javascript:void(0)" class="btn anc-remove btn-primary active" data-mini="false" data-theme="a">X</a></span>
            
             <?php }
            ?>
   </div>
        <?php endif; ?>        
            </div>  
          </div>
            </div>   
            </div>
            </div>
        
        <?php
        endforeach;
        }
        else{
            echo $error_string;
        }
        ?>
    </div>
</div>