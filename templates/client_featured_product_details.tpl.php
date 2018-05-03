<?php
	global $base_url;
	if(isset($product)){
   	
   		$file = file_load($product[0]['image']);
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
	<!-- <script type="text/javascript" language="javascript"></script> -->


    <?php if(isset($product)):?>

    	<div class="item_title text-center pw-item-title">
    		 <div class=product-title> <p style="margin:0;"><?php print ucwords($product[0]['title'])?></p></div>
    	</div>


	    <div class="product-info">
	    	<div class="product-left">           


	            <img id="product-banner" src="<?php print get_thumbnail_path($product[0]['image'],"full");?>" class="product-image">

	           	<div>
	           		<img id="thumbnail-1" onclick="clickHandler(event)" class="product-thumbnails" src="<?php print get_thumbnail_path($product[0]['image'],"thumbnail");?>" alt="1" >
	           		<?php
		           		for($i=1;$i<=5;$i++){
		           			if((!($product[0]['image_'.$i]==0))){		           				

		           				 $temp = file_load($product[0]['image_'.$i]);
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
	    			<p><?php print $product[0]['product_id']?></p>
	    		</div>
	    		<?php if($product[0]['description']){  ?>
		    		<div><strong><?php print t('Description').':' ?></strong></div>
		    		<div>
		    			<p><?php print $product[0]['description']?></p>
		    		</div>
		    	<?php }  ?>
	    		<div><strong><?php print t('Price').':' ?></strong></div>
	    		<div>
	    			<p><?php print "$".$product[0]['price'] ?></p>
	    		</div>	  

	    		<div><strong><?php print t('Color').':' ?></strong></div>
	    		<div>
	    			<p><?php print ucwords(taxonomy_term_load($product[0]['color'])->name) ?></p>
	    		</div>

	    		<div><strong><?php print t('Size').':' ?></strong></div>
	    		<div>
	    			<p><?php print ucwords(taxonomy_term_load($product[0]['size'])->name) ?></p>
	    		</div>

	    		<div><strong><?php print t('Category').':' ?></strong></div>
	    		<div>
	    			<p><?php print ucwords(taxonomy_term_load($product[0]['category'])->name) ?></p>
	    		</div>	 
	    		<div>
	    			<?php       
	    				$product_id=$product[0]['product_id'];

	    			?>
	    				<button type="button" onclick="setSession('<?php echo $product_id; ?>','<?php echo $base_url; ?>'); return false;"> <p><?php print $product[0]['add'] ?></p></button> 
	    			
		    	</div>
		    	<div>
		    		<a href="/#" ><button><p><?php print $product[0]['share'] ?></p></button> </a>
		    	</div>
	    	</div>
	    	
	    </div>
<?php endif;?>
<?php if(isset($error)):?>
	
		<div class="error-display"><?php @print $error;?></div>

	<?php endif;?>

		<script>
		function clickHandler(event){
			console.log(event.target.src);
			document.getElementById("product-banner").src = event.target.src;
		}
		function setSession(id,base_url){
			
	            $.ajax({
	            	// method: "POST",
	                url: base_url+"/set/session/"+id ,
	            });
	             // jQuery("#ajax-target").load(base_url+"set/session/"+id);

	       



			// alert(id);
			// sessionStorage.setItem("featured_product_id",id);
			// setSession['featured_product_id']=id;
			// window.location.assign(base_url+"/newuser/registration");
		}

	</script>