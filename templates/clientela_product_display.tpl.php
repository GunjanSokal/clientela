<?php

	if(isset($product)){
   	
   		$file = file_load($product['image']);
   		$url = @file_create_url($file->uri);
	}

   function get_thumbnail_path($thumbnail_id,$type){
   		$temp = file_load($thumbnail_id);
   		if($type=="full"){
   			$img_url=image_style_url('product_detail_image', $temp->uri);
   		}
   		else{
   			$img_url=image_style_url('product_detail_image', $temp->uri);
   		}
   	   return $img_url;

   }

?>
<script>

	function clickHandler(event){
console.log(event.target.src);
		document.getElementById("product-banner").src = event.target.src;

	}
	</script>
    <?php if(isset($product)):?>

    	<div class="item_title text-center pw-item-title">
    		 <div class=product-title> <p style="margin:0;"><?php print ucwords($product['title'])?></p></div>
    	</div>


	    <div class="product-info">
	    	<div class="product-left">           


	            <img id="product-banner" src="<?php print get_thumbnail_path($product['image'],"full");?>" class="product-image">

	           	<div>
	           		<img id="thumbnail-1" onclick="clickHandler(event)" class="product-thumbnails" src="<?php print get_thumbnail_path($product['image'],"thumbnail");?>" alt="1" >
	           		<?php
		           		for($i=1;$i<=5;$i++){
		           			if((!($product['image_'.$i]==0))){		           				

		           				 $temp = file_load($product['image_'.$i]);
   	  							 $img_url=image_style_url('product_detail_image', $temp->uri);		           				
		           				?>

								<img id="thumbnail-1" onclick="clickHandler(event)" class="product-thumbnails" src="<?php print $img_url;?>" alt="1" >
						
						<?php								
		           			}
			           	}
		           	?>


	           		
	           	</div>
	    	</div>
	    	<div class="product-right">
	    		<div><strong><?php print t('Product Id').':' ?></strong></div>
	    		<div>
	    			<p><?php print $product['product_id']?></p>
	    		</div>
	    		<?php if($product['description']){  ?>
		    		<div><strong><?php print t('Description').':' ?></strong></div>
		    		<div>
		    			<p><?php print $product['description']?></p>
		    		</div>
		    	<?php }  ?>
	    		<div><strong><?php print t('Price').':' ?></strong></div>
	    		<div>
	    			<p><?php print "$".$product['price'] ?></p>
	    		</div>	  

	    		<div><strong><?php print t('Color').':' ?></strong></div>
	    		<div>
	    			<p><?php print ucwords(taxonomy_term_load($product['color'])->name) ?></p>
	    		</div>

	    		<div><strong><?php print t('Size').':' ?></strong></div>
	    		<div>
	    			<p><?php print ucwords(taxonomy_term_load($product['size'])->name) ?></p>
	    		</div>

	    		<div><strong><?php print t('Category').':' ?></strong></div>
	    		<div>
	    			<p><?php print ucwords(taxonomy_term_load($product['category'])->name) ?></p>
	    		</div>	 
	    		
	    	</div>

	    </div>
<?php endif;?>
<?php if(isset($error)):?>
	
		<div class="error-display"><?php @print $error;?></div>

	<?php endif;?>