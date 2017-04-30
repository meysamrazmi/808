Description
===========
Ubercart Product Actions provides a set of Drupal Actions for usage by Ubercart
shop administrators for conducting site-wide changes to product data, using
custom code or the excellent Views Bulk Operations (VBO) module.

It does so by providing a few new actions:

- Modify product weight
- Modify product sell price
- Modify product list price
- Modify product cost price
- Modify default quantity to add to cart
- Modify product stock level
- Modify product stock threshold
- Enable/disable stock tracking

These actions can be used to manipulate these values on multiple products, using
three methods:

1. Percentage - alter values up or down by a percentage.
   (for example: increase the cost of selected products by 10%.)
2. Difference - alter values up or down by a fixed amount.
   (for example: decrease the price of all products by $5.)
3. Absolute - set values to a specified number.
   (for example: set the price on selected items to $15.)

* For prices, the result will be rounded according to your store settings.
* For stock, values will be rounded to the nearest integer.
* For weight, when modifying by a percentage and the old value contains a
  decimal, the new value will be rounded to the same precision.

Usage
=====
The module does nothing on its own. Here's how to quickly get it up and running:
 1) Download and install the Views and VBO modules:
    * http://drupal.org/project/views
    * http://drupal.org/project/vbo
 2) Create a new node view, using a "Page" display and "Bulk Operations" as the
    display style.
 3) Filter the view to display products only, and optionally expose some filters
    so that you can filter the list of products as you wish.
 4) In the VBO settings of that view, check the boxes next to the actions you
    wish to enable.
 5) Save the view, and visit the page.
 6) Select some products and choose the desired action from the Bulk Operations
    select box, and click "Execute".
 7) On this screen enter your desired change, and click "Next".
 8) Make sure you've selected the right products, and click "Confirm".

 You're done! ;)

If you have any problems/questions/ideas - please visit the Issue Queue and let
us know: http://drupal.org/project/issues/uc_product_actions

Authors
=======
Asaph (www.drupal.org/u/asak) - asaph at cpo.co.il
Sean (www.drupal.org/u/seana) - sean at tuxbox-computers.com
