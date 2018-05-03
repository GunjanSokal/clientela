
<div class="search-container">
	<?php 
		if(isset($form['page_title']) && !empty($form['page_title'])) : 
	?>
	<div class="global-heading clearfix">
		<span class="global-title"><?php  print render($form['page_title']); ?></span>
	</div>
	<?php endif;?>
	<div class="search-body row tpl">
		<div class="col-md-6"><?php print render($form['product_id']); ?> </div>
		<div class="col-md-6"><?php print render($form['title']); ?>	</div>
		<div class="col-md-6"><?php  print render($form['price']); ?></div>		
		<div class="col-md-6"><?php print render($form['description']); ?></div>
		<div class="col-md-6"><?php print render($form['color']); ?> </div>	
		<div class="col-md-6"><?php print render($form['size']); ?> </div>
		<div class="col-md-6"><?php print render($form['category']); ?></div>
		
	</div>		
		<div class="col-md-12">
		<div class="row">			
		<div class="col-md-6"><?php print render($form['image']); ?> </div>
		<div class="col-md-6"><?php print render($form['image_1']); ?> </div>
		</div>
		</div>

		<div class="col-md-12">
		<div class="row">
		<div class="col-md-6"><?php print render($form['image_2']); ?> </div>
		<div class="col-md-6"><?php print render($form['image_3']); ?> </div>
		</div>
		</div>

		<div class="col-md-12">
		<div class="row">
		<div class="col-md-6"><?php print render($form['image_4']); ?> </div>
		<div class="col-md-6"><?php print render($form['image_5']); ?> </div>
		</div>
		</div>

		<div class="col-md-12">
		<div class="row">
		<div class="col-md-6"><?php print render($form['p_id']); ?> </div>
		<div class="col-md-6"></div>
		</div>
		</div>

		<div class="col-md-12">
		<div class="row">
		<div class="col-md-6"><?php print render($form['active_status']); ?> </div>
		<div class="col-md-6"><?php print render($form['featured']); ?> </div>
		</div>
		</div>
		
		<div class="col-md-6"><?php print render($form['id']); ?></div>
		<div class="col-md-6"><?php print render($form['client_specific_table']); ?> </div>
		<div class="col-md-12"><span class="tpl-btn"><?php print render($form['submit']); ?></span></div>
		
	</div>
</div>
<?php print drupal_render($form['form_build_id']); 
                  print drupal_render($form['form_token']);
                  print drupal_render($form['form_id']);
                  ?> 

