<?php
global $base_url;
global $users;
?>
<div class="client-landing-wrapper company-registration">
<div class = 'user-login-banner'>
  <h2>Register</h2>
</div>
  <div class="client-landing-form-wrapper">
    <div class="client-landing pdb-0">
 
      <div class="client-landing-form">

        <div class="client-landing-heading col-md-12 text-center">
        	<!-- <h2 class="client_landing-ps">PERSONAL SHOPPING</h2> -->
        	<!-- <p><h4>Connect with a Fashion Advisor</h4></p> -->
        	<p><h6><?php print t('Welcome to Clientela. Please fill all the fields to get started.'); ?> </h6></p>
        </div>

        <div class="client-landing-mail col-md-12"><?php print drupal_render($form['client_email']); ?> </div>

        <div class="client-landing-fname col-md-12"><?php print drupal_render($form['client_fname']); ?> </div>

        <div class="client-landing-lname col-md-12"><?php print drupal_render($form['client_lname']); ?> </div>

        <div class="client-landing-lname col-md-12"><?php print drupal_render($form['password']); ?> </div>

        <div class="client-landing-lname col-md-12"><?php print drupal_render($form['confirm_password']); ?> </div>
     
      <div class="client-landing-user-save-submit col-md-12">


        <?php
       print drupal_render($form['form_build_id']); 
       print drupal_render($form['form_token']);
       print drupal_render($form['form_id']);   
       // print drupal_render($form['#submit']); 
       print drupal_render($form['submit']);  
        ?>
      </div>
      <!-- This div is for render boutique image using JS -->
<!--       <div class="client-landing-boutique-image col-md-12">
      </div> -->

      <!-- This div is for render boutique address using JS -->
      <div class="client-landing-boutique-address col-md-12">
      </div>
      
      <!-- This div is for render boutique phone number using JS -->
      <div class="client-landing-boutique-phone-number col-md-12">
      </div>
      
      <!-- This div is for render boutique timing using JS -->
      <!-- <div class="client-landing-boutique-timing col-md-12">
      </div> -->


   
  </div>
 </div>
</div>
<div class="register-link col-md-12 text-center">
    <?php 
      session_start();
      $_SESSION['redirect_user_to_wishlist_page']='1';
    ?>
  <p class="register-login"> <?php echo "If you already have an account. Try to  " . l(t("Login"),"user"); ?></p>
</div>      
