<?php

/**
 * @file
 * This file is the default customer invoice template for Ubercart.
 *
 * Available variables:
 * - $products: An array of product objects in the order, with the following
 *   members:
 *   - title: The product title.
 *   - model: The product SKU.
 *   - qty: The quantity ordered.
 *   - total_price: The formatted total price for the quantity ordered.
 *   - individual_price: If quantity is more than 1, the formatted product
 *     price of a single item.
 *   - details: Any extra details about the product, such as attributes.
 * - $line_items: An array of line item arrays attached to the order, each with
 *   the following keys:
 *   - line_item_id: The type of line item (subtotal, shipping, etc.).
 *   - title: The line item display title.
 *   - formatted_amount: The formatted amount of the line item.
 * - $shippable: TRUE if the order is shippable.
 *
 * Tokens: All site, store and order tokens are also available as
 * variables, such as $site_logo, $store_name and $order_first_name.
 *
 * Display options:
 * - $op: 'view', 'print', 'checkout-mail' or 'admin-mail', depending on
 *   which variant of the invoice is being rendered.
 * - $business_header: TRUE if the invoice header should be displayed.
 * - $shipping_method: TRUE if shipping information should be displayed.
 * - $help_text: TRUE if the store help message should be displayed.
 * - $email_text: TRUE if the "do not reply to this email" message should
 *   be displayed.
 * - $store_footer: TRUE if the store URL should be displayed.
 * - $thank_you_message: TRUE if the 'thank you for your order' message
 *   should be displayed.
 *
 * @see template_preprocess_uc_order()
 */
?>
<style type="text/css">
      #center{
	margin: 0 auto;
    padding: 0;
    border: 0;
    font-size: 14px;
    font: inherit;
    direction: rtl;
    vertical-align: baseline;
    line-height: 1;
    background: #f7f7f7;
    color: #444;
    width: 100%;
    border-radius: 2px;
    font-family: tahoma !important;
}
#header-mail{
	margin: 2px auto;
    padding: 15px 0;
    border: 0;
    font-size: 100%;
    font: inherit;
    direction: rtl;
    vertical-align: baseline;
    text-align: center;
    display: block;
    overflow: hidden;
    width: 85%;
}
#header-mail img{
	max-width: 100%;
    width: 127.2px;
    min-height: auto!important;
}
#main{
	margin: 0 auto 0px;
    padding: 30px 30px;
    border: 1px solid #e2e2e2;
    font-size: 100%;
    font: inherit;
    direction: rtl;
    vertical-align: baseline;
    background: #fff;
    overflow: hidden;
    border-radius: 2px;
    line-height: 30px;
    box-sizing: border-box;
    text-align: justify;
	width: 77%;
}
#footer-mail{
	direction: rtl;
    font-family: tahoma!important;
    font-size: 100%;
	margin: -5px auto 0 auto;
    font: inherit;
    vertical-align: baseline;
    text-align: center;
    display: block;
    overflow: hidden;
    width: 100%;
    padding-bottom: 20px;
    padding: 0;
    border: 0;
    background-color: #f7f7f7;
    padding: 20px 0;
}
.first-row a{
	font-size: 20px;
    color: black;
    text-decoration: blink;
    padding-bottom: 20px;
    display: block;
    font-family: yekan;
}
.socialss a{
	margin:0px 10px;
}

   </style>
<style type="text/css">
					.sender {
						word-spacing: 4px;
					}
					.sender br{
					display: none;
					}
					.sender br:nth-child(4) {
						display: block;
					}
					.logo img {
						width: 150px;
						padding: 10px 40px;
					}
					*{
							direction: rtl;
							font-family: tahoma !important;
							font-size: small;
					}
</style>




<div id="center">
		<div id="header-mail">
			<a href="http://civil808.com"  target="_blank">
			<img src="http://civil808.com/sites/all/themes/sara/logo.png" alt="">
			</a>
		</div>
		<div id="main">
        
		
		
		
		
		<table width="95%" border="0" cellspacing="0" align="center"  style="">
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0"  align="center" style="">
        <?php/* if ($business_header): ?>
        <tr valign="top">
          <td>
            <table width="100%" style="">
               <tr>
                <td class="logo">
                  <?php print $site_logo; ?>
                </td>
				
               <td width="98%">
                  <div style="padding-left: 1em;">
                  <a style="font-size: 25px;color: #444;text-decoration: none;" href="http://civil808.com" target="blank">موسسه آموزشی 808</a><br />
                  <span><?php print $site_slogan; ?></span>
                  </div>
                </td>
                <td nowrap="nowrap">
					<div nowrap="nowrap" class="sender" style="  word-spacing: 4px;  border: 1px solid #eee;  padding: 15px;  text-indent: 10px;  line-height: 25px;  border-radius: 5px;  background: #fdfdfd;">
						<div>
							<b>آدرس موسسه: </b>
							<span><?php print $store_address; ?><br /></span>
						</div>
						<div>
							<b>شماره تماس موسسه: </b>
							<span style="padding-right:5px;"><?php print $store_phone;?></span>
						</div>
					</div>
				</td>
				
              </tr>
            </table>
          </td>
        </tr>
				
        endif; */?>

        <tr valign="top">
          <td>

            <?php if ($thank_you_message): ?>
            <p><b><?php print t('Thanks for your order, !order_first_name!', array('!order_first_name' => $order_first_name)); ?></b></p>

            <?php if (isset($order->data['new_user'])): ?>
            <p><b><?php print t('An account has been created for you with the following details:'); ?></b></p>
            <p><b><?php print t('Username:'); ?></b> <?php print $order_new_username; ?><br />
            <b><?php print t('Password:'); ?></b> <?php print $order_new_password; ?></p>
            <?php endif; ?>

            <p><b><?php print t('Want to manage your order online?'); ?></b><br />
            <?php print 'اگر نیاز به بررسی وضعیت سفارش خود را دارید، لطفا در صفحه ی اصلی civil808.com بر روی منو کاربری خود (بالای صفحه سمت چپ) کلیک کرده و پس از باز شدن منو ، با انتخاب گزینه ی "پیگیری سفارش ها" وارد صفحه ی مورد نظر شوید یا با استفاده از لینک زیر وارد شوید : ' ; ?>
            <br /><?php print $site_login_link; ?></p>
            <?php endif; ?>

            <table cellpadding="4" cellspacing="0" border="0" width="100%" style="font-family: verdana, arial, helvetica; font-size: small;">

			  <tr><td nowrap="nowrap" style="border-bottom: 3px solid #a5a;"></td><td nowrap="nowrap" style="border-bottom: 3px solid #a5a;"></td></tr>
              <tr>
                <td colspan="2">
					<?php /*
					<p style="text-align:right; font-size: 23px;   margin-bottom: 5px;">
						<b><?php print t('Products on order:'); ?>&nbsp;</b>
					</p>
					*/?>
                  <table border="0" cellpadding="1" cellspacing="0" width="100%" style="font-size: small;">
                    <tr>
						<td>
							<table width="100%" cellspacing="0" cellpadding="0" style="background-color: #fdfdfd;border: 1px solid #eee;border-radius: 5px;margin-left: 1%;box-sizing: border-box;width: 99%;margin-bottom: 5px;padding: 5px 15px;">
								<tr>
								<?php /*
								<td valign="top" width="50%">
									<b><?php print t('Billing Address:'); ?></b><br />
									<?php print $order_billing_address; ?><br />
									<b><?php print t('Billing Phone:'); ?></b>
									<?php print $order_billing_phone; ?><br />
								</td>
								*/ ?>
								<?php if ($shippable): ?>
								<td valign="top" width="50%">
									<?php print $order_shipping_address; ?><br />
									<?php/*<b><?php print t('Shipping Phone:'); ?></b>
									<?php print $order_shipping_phone; ?><br />*/ ?>
								</td>
								<?php endif; ?>
								</tr>
							</table>
						</td>
						<td valign="top">
							<table style="  border: 1px solid #eee;  border-radius: 5px;  margin-left: 1%;  box-sizing: border-box;  width: 99%;background-color: #fdfdfd;  margin-bottom: 5px;  padding: 5px 15px;display: inline-block;">
								<tbody style="  width: 100%;  display: block;">
									<tr>
										<td nowrap="nowrap" style="  width: 100%;  display: block;">
											<b><?php print t('Order #:'); ?></b>
											<span style="padding-right: 5px;"><?php print $order_link; ?></span>
										</td>
									</tr>
									<tr>
										<td nowrap="nowrap" style="  width: 100%;  display: block;">
											<b><?php print t('Order Date: '); ?></b>
											<span style="padding-right: 5px;"><?php print $order_created; ?></span>
										</td>
									</tr>
									<tr>
										<td width="98%" style="  width: 100%;  display: block;">
											<b><?php print t('Payment Method:'); ?></b>
											<span style="padding-right: 5px;"><?php print $order_payment_method; ?></span>
										</td>
									</tr>
									<tr>
										<td nowrap="nowrap" style="  width: 100%;  display: block;">
											<b><?php print t('E-mail:'); ?></b>
											<span style="padding-right: 5px;"><?php print $order_email; ?></span>
										</td>
									</tr>
								</tbody>
							</table>
						</td>
					</tr>
					
                    <tr>
                      <td colspan="2">
						<table width="100%" style="  text-align: center;border-collapse: collapse;">
							<thead style="background: #f5f9f9;  line-height: 34px;  font-size: 15px;">
								<tr>
									<th style="border: 1px solid #eee;">
										<span>ردیف</span>
									</th>
									<th style="border: 1px solid #eee;">
										<span>کد محصول</span>
									</th>
									<th style="border: 1px solid #eee;">
										<span>شرح محصول یا خدمات</span>
									</th>
									<th style="border: 1px solid #eee;">
										<span>توضیحات</span>
									</th>
									<th style="border: 1px solid #eee;">
										<span>تعداد</span>
									</th>
									<th style="border: 1px solid #eee;">
										<span>مبلغ واحد(تومان)</span>
									</th>
									<th style="border: 1px solid #eee;">
										<span>مبلغ کل(تومان)</span>
									</th>
								</tr>
							</thead>
							<tbody style="line-height: 35px;">
								<?php $index = 1;?>
								<?php foreach ($products as $product): ?>
									<tr>
										<td style="border: 1px solid #eee;">
											<span><?php print $index; $index++;?></span>
										</td>
										<td style="border: 1px solid #eee;">
											<span><?php print $product->model; ?></span>
										</td>
										<td style="border: 1px solid #eee;">
											<span><?php print $product->title; ?></span>
										</td>
										<td style="border: 1px solid #eee;">
											<span><?php print $product->details; ?></span>
										</td>
										<td style="border: 1px solid #eee;">
											<span><?php print $product->qty; ?></span>
										</td>
										<td style="border: 1px solid #eee;">
											<span><?php print $product->individual_price; ?></span>
										</td>
										<td style="border: 1px solid #eee;">
											<span><?php print $product->total_price; ?></span>
										</td>
									</tr>
								<?php endforeach; ?>
							</tbody>
						</table>

                      </td>
                    </tr>

                    <tr style="font-weight: bold;   height: 40px;">
                      <td nowrap="nowrap" width="84%" style="text-align: left;">
                        <span style="  font-size: 15px;  padding: 4px 10px;  width: 140px;  text-align: right;  box-sizing: border-box;  display: inline-block;"><?php print t('Products Subtotal:'); ?>&nbsp;</span>
                      </td>
                      <td style="min-width: 215px;  text-indent: 15px;">
                        <span><?php print $order_subtotal; ?></span>
                      </td>
                    </tr>

					<tr>
                      <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                      <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                    </tr>
					
                    <?php if ($shipping_method && $shippable): ?>
                    <tr>
                      <td nowrap="nowrap" style="text-align:right;">
                        <span style="  font-size: 15px;  padding: 10px;  display: inline-block;  border-right: 4px solid #eee;  width: 140px;  text-align: right;  box-sizing: border-box;"><b><?php print t('Shipping Method:'); ?></b><span>
                      </td>
                      <td width="98%" style="  display: none;">
                        <span><?php print $order_shipping_method; ?><span>
                      </td>
                    </tr>
                    <?php endif; ?>

                    <?php foreach ($line_items as $item): ?>
                    <?php if ($item['type'] == 'subtotal' || $item['type'] == 'total')  continue; ?>

                    <tr>
                      <td nowrap="nowrap" style="text-align: left;">
                        <span style="  font-size: 15px;  padding: 4px 10px;  width: 140px;  text-align: right;  box-sizing: border-box;  display: inline-block;"><?php print $item['title']; ?>:<span>
                      </td>
                      <td style="min-width: 215px;  text-indent: 15px;">
                        <span><?php print $item['formatted_amount']; ?><span>
                      </td>
                    </tr>

                    <?php endforeach; ?>

                    <tr>
                      <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                      <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                    </tr>

                    <tr>
                      <td nowrap="nowrap" style="text-align: left;">
                        <span style="  font-size: 15px;  padding: 4px 10px;  width: 140px;  text-align: right;  box-sizing: border-box;  display: inline-block;"><b><?php print t('Total for this Order:'); ?>&nbsp;</b></span>
                      </td>
                      <td style="min-width: 215px;  text-indent: 15px;">
                        <b><?php print $order_total; ?></b>
                      </td>
                    </tr>

                  
				  </table>

                </td>
              </tr>
			  <?php /*
			  <tr><td nowrap="nowrap" style="border-bottom: 7px solid #a5a;height: 30px;"></td><td nowrap="nowrap" style="border-bottom: 7px solid #a5a;height: 30px;"></td></tr>
			  <tr><td nowrap="nowrap" style="height: 10px;"></td><td nowrap="nowrap" style="height: 10px;"></td></tr>
			  */ ?>

              <?php /*if ($help_text || $email_text || $store_footer): ?>
              <tr>
                <td colspan="2">
                  <hr noshade="noshade" size="1" /><br />

                  <?php if ($help_text): ?>
                  <p><b><?php print t('Where can I get help with reviewing my order?'); ?></b><br />
                  <?php print t('To learn more about managing your orders on !store_link, please visit our <a href="!store_help_url">help page</a>.', array('!store_link' => $store_link, '!store_help_url' => $store_help_url)); ?>
                  <br /></p>
                  <?php endif; ?>

                  <?php if ($email_text): ?>
                  <p><?php print t('Please note: This e-mail message is an automated notification. Please do not reply to this message.'); ?></p>

                  <p><?php print t('Thanks again for shopping with us.'); ?></p>
                  <?php endif; ?>

                  <?php if ($store_footer): ?>
                  <p><b><?php print $store_link; ?></b><br /><b><?php print $site_slogan; ?></b></p>
                  <?php endif; ?>
                </td>
              </tr>
              <?php endif; */ ?>

            </table>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
		
		
		

		</div>
		
	</div>


			


