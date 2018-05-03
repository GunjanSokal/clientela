
<div class="search-container">
	<?php 
		if(isset($form['page_title']) && !empty($form['page_title'])) : 
	?>
	<div class="global-heading clearfix">
		<span class="global-title"><?php  print render($form['page_title']); ?></span>
	</div>
	<?php endif;?>
	<div class="search-body row tpl">
		<div class="col-md-3 col-sm-3"><?php print render($form['product']); ?> </div>
		<div class="col-md-3 col-sm-3"><?php print render($form['status']); ?>	</div>
		<div class="col-md-3 col-sm-3"><?php  print render($form['category']); ?></div>
		<div class="col-md-3 col-sm-3"><?php  print render($form['submit']); ?></div>	
	</div>	
</div>
<?php print drupal_render($form['form_build_id']); 
                  print drupal_render($form['form_token']);
                  print drupal_render($form['form_id']);
                  ?> 

