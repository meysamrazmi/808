<?php
function check_808_options($mlid){

}
function render_menu_items($menu){
	$output = '';
	foreach($menu as $link){
	    if($link['link']['hidden'] || $link['link']['mlid'] == 8832)
	        continue;
		$sub_menu = '';
		if ($link['below']) {
			$sub_menu = '<div class="sub"><ul class="sub">'. render_menu_items($link['below']) . '</ul></div>';
		}
		$a = l($link['link']['link_title'], '/'. $link['link']['link_path'], $link['link']['localized_options']);
		$output .= '<li>' . $a . $sub_menu . "</li>\n";
	}
	return $output;
}
$menu = menu_build_tree('main-menu');
?>
<div id="main-nav">
    <ul class="main">
        <span class="active-item"></span>
        <?php
            print render_menu_items($menu);
        ?>
        <li>
            <a href="">جستجو</a>
            <div class="sub">
                <form class="google-cse" action="/" method="post" id="search-block-form--2" accept-charset="UTF-8"><div><div class="container-inline">
                            <h2 class="element-invisible">فرم جستجو</h2>
                            <div class="form-item form-type-textfield form-item-search-block-form">
                                <label class="element-invisible" for="edit-search-block-form--4">جستجو </label>
                                <input title="عبارتی را که می‌خواهید جستجو گردد را وارد نمایید." type="text" id="edit-search-block-form--4" name="search_block_form" value="" size="15" maxlength="128" class="form-text">
                            </div>
                            <div class="form-actions form-wrapper" id="edit-actions--2"><input type="submit" id="edit-submit--3" name="op" value="جستجو" class="form-submit has-wave"></div><input type="hidden" name="form_build_id" value="form-tG0rRhEJinsIf5y-j67nJhWKHXUDuAGXBc9SA99Zhz8">
                            <input type="hidden" name="form_token" value="UPRMB0YFiJRgzT2D5ibImg0F5_f33Mk95seJhrxCRVM">
                            <input type="hidden" name="form_id" value="search_block_form">
                        </div>
                    </div>
                </form>
            </div>
        </li>
    </ul>
</div>

<style>
body:not(.uid-3300) #main-nav {
    display: none;
}
#main-nav ul {
    margin: 0;
    padding: 0;
}
#main-nav a {
    line-height: 2.2em;
    display: inline-block;
    color: #444;
    transition: all 0.2s ease;
}
#main-nav ul.main {
    display: flex;
    position: relative;
}
#main-nav ul.main > li > a {
    padding: 0 20px;
    line-height: 50px;
    height: 50px;
}
#main-nav ul.main > li > a:hover,
#main-nav ul.main > li.active > a {
    color: #000;
}
#main-nav div.sub {
    display: none;
    width: 100%;
    position: absolute;
    background: #fff;
    box-shadow: rgba(0, 0, 0, 0.117647) 0px 2px 4px, rgba(0, 0, 0, 0.117647) 0px 2px 4px;
    border-bottom: 2px solid #9C27B0;
    padding: 15px;
    z-index: 10;
    border-radius: 0 0 2px 2px;
    right: 0;
}
span.active-item {
    position: absolute;
    height: 50px;
    background: #f5f5f5;
    width: 0;
    z-index: -1;
    border-bottom: 1px solid #673AB7;
    transition: all 0.3s ease;
}
#main-nav li.active > div.sub {
    display: flex;
}
#main-nav ul.sub {
    width: 20%;
}
</style>

<script>
$(document).ready(function () {
	$('#main-nav ul.main > li').mouseenter(function(){
		var el = $(this)
		$('.active-item').css({'width': el.width(), 'left': el.position().left})
		setTimeout(function(){
			el.parent().find('.active').removeClass('active')
			el.addClass('active')
		}, 500)
	}).mouseleave(function(){
		var el = $(this)
		$('.active-item').css({'width': 0, 'left': (el.position().left + el.width()/2)})
		el.removeClass('active')
		setTimeout(function(){
			el.removeClass('active')
		}, 505)
	})
})
</script>


<style type="text/css" media="all">
    @import url("https://civil808.com/sites/all/modules/tb_megamenu/css/bootstrap.css?pj73mr");
    @import url("https://civil808.com/sites/all/modules/tb_megamenu/css/base.css?pj73mr");
    @import url("https://civil808.com/sites/all/modules/tb_megamenu/css/default.css?pj73mr");
    @import url("https://civil808.com/sites/all/modules/tb_megamenu/css/compatibility.css?pj73mr");
    @import url("https://civil808.com/sites/all/modules/tb_megamenu/css/styles/blue.css?pj73mr");
    .region-ads3, .tb-megamenu .nav>li {
        float: right;
    }
    .tb-megamenu.style-blue .nav li.dropdown.open>.dropdown-toggle, .tb-megamenu .nav>li>a, .tb-megamenu .nav li.dropdown.open>.dropdown-toggle {
        background-color: transparent;
        color: #000;
    }
    .tb-megamenu .row-fluid [class*="span"] {
        float: right;
    }
    .tb-megamenu .row-fluid [class*="span"] {
        margin: 0;
        width: 25%;
    }
</style>
<div id="block-tb-megamenu-main-menu" class="block block-tb-megamenu odd">
    <div class="content">
        <div class="tb-megamenu tb-megamenu-main-menu style-blue">
            <button data-target=".nav-collapse" data-toggle="collapse" class="btn btn-navbar tb-megamenu-button first has-wave" type="button"><span class="click-wave"></span>
                <i class="icon-reorder"></i>
            </button>
            <div class="nav-collapse collapse always-show" style="max-height: 905px;">
                <ul class="tb-megamenu-nav nav level-0 items-15">
                    <li data-id="8533" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify dropdown">
                        <a href="/" class="dropdown-toggle">

                            808          <span class="caret"></span>
                        </a>
                        <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">
                            <div class="mega-dropdown-inner">
                                <div class="tb-megamenu-row row-fluid">
                                    <div data-class="" data-width="3" data-hidewcol="0" id="tb-megamenu-column-1" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8536" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/page/about" class="">

                                                        درباره 808          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-2" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8535" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/blog" class="">

                                                        وبلاگ 808          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-3" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13320" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega mega-align-justify">
                                                    <a href="#" class="">

                                                        فرصت های شغلی          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-4" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13619" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="#" class="">

                                                        دسترسی ها          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>
                                </div>

                                <div class="tb-megamenu-row row-fluid">
                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-5" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-civil-column1" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-civil-column1" class="block block-menu first odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/landing/vip" title="">اشتراک ویژه (vip)</a></li>
                                                                <li class="leaf"><a href="/page/2759/%D9%86%D9%82%D8%B4%D9%87-%D8%B3%D8%A7%DB%8C%D8%AA" title="">نقشه سایت</a></li>
                                                                <li class="leaf"><a href="/landing/help" title="">راهنمای استفاده از سایت</a></li>
                                                                <li class="leaf"><a href="/cooperate" title="">همکاری با ما</a></li>
                                                                <li class="leaf"><a href="/contact-us" title="">تماس با ما</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/contacts" title="">آشنایی با همکاران ما</a></li>
                                                                <li class="last leaf"><a href="/landing/members" title="">کاربران سایت</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-6" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-weblog808" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-weblog808" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%88%D8%A8%D9%84%D8%A7%DA%AF/2180/%D8%A7%D8%B7%D9%84%D8%A7%D8%B9%DB%8C%D9%87-%D9%87%D8%A7" title="">اطلاعیه ها</a></li>
                                                                <li class="leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%88%D8%A8%D9%84%D8%A7%DA%AF/2178/%D8%AA%D8%AE%D9%81%DB%8C%D9%81-%D9%87%D8%A7" title="">تخفیف ها</a></li>
                                                                <li class="leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%88%D8%A8%D9%84%D8%A7%DA%AF/2179/%D8%AF%D9%84-%D9%86%D9%88%D8%B4%D8%AA%D9%87-%D9%87%D8%A7" title="">دل نوشته ها</a></li>
                                                                <li class="leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%88%D8%A8%D9%84%D8%A7%DA%AF/2182/%D8%B3%DB%8C%D9%88%DB%8C%D9%84-808" title="">سیویل 808</a></li>
                                                                <li class="last leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%88%D8%A8%D9%84%D8%A7%DA%AF/2181/%D9%85%D8%B7%D8%A7%D9%84%D8%A8-%D8%AA%D8%AD%D9%84%DB%8C%D9%84%DB%8C" title="">مطالب تحلیلی</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-7" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-project-takhassosi" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-project-takhassosi" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/projects-saze" title="">پروژه های تخصصی</a></li>
                                                                <li class="leaf"><a href="/news/%D8%A2%DA%AF%D9%87%DB%8C-%D9%87%D8%A7%DB%8C-%D8%A7%D8%B3%D8%AA%D8%AE%D8%AF%D8%A7%D9%85%DB%8C" title="">آگهی های استخدام</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/translator" title="">مترجمین 808</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/advisor" title="">مشاوران 808</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/landing/affiliate" title="">نمایندگی های 808</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-8" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu--4---808-" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-4-808-" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/landing/media" title="">808 در رسانه ها</a></li>
                                                                <li class="leaf"><a href="/landing/law" title="">آشنایی با قوانین و مقررات جاری وبسایت</a></li>
                                                                <li class="leaf"><a href="/ads" title="">تبلیغات در سایت</a></li>
                                                                <li class="leaf"><a href="/landing/help" title="">راهنمای ورود، شارژ حساب و معرفی خدمات  سایت</a></li>
                                                                <li class="leaf"><a href="/landing/faq" title="">پاسخ به پرسش های متداول کاربران سایت</a></li>
                                                                <li class="leaf"><a href="http://lock.civil808.com/admin/login.php?admin=808" title="">فعالسازی قفل محصولات</a></li>
                                                                <li class="leaf"><a href="/landing/form/reseller" title="">پرتال جذب نمایندگی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/form/job" title="">پرتال استخدام نیرو </a></li>
                                                                <li class="leaf"><a href="http://civil808.com/pedia" title="">دانشنامه</a></li>
                                                                <li class="leaf"><a href="/question/list" title="">808 پلاس (پرسش و پاسخ)</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/app" title="">اپلیکیشن 808+</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>

                    <li data-id="8539" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify">
                        <a href="/saze/808" class="">

                            عمران          </a>
                    </li>

                    <li data-id="13278" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega">
                        <a href="/arch" class="">

                            معماری          </a>
                    </li>

                    <li data-id="25914" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega dropdown">
                        <a href="#" class="dropdown-toggle">

                            لبه دانش          <span class="caret"></span>
                        </a>
                        <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">
                            <div class="mega-dropdown-inner">
                                <div class="tb-megamenu-row row-fluid">
                                    <div data-class="" data-width="12" data-hidewcol="0" id="tb-megamenu-column-9" class="tb-megamenu-column span12  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-3">
                                                <li data-id="13574" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/eng" class="">

                                                        ورود به حرفه          </a>
                                                </li>

                                                <li data-id="15497" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/pbd/fa" class="">

                                                        طراحی عملکردی          </a>
                                                </li>

                                                <li data-id="25913" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="http://civil808.com/landing/bim" class="">

                                                        مدل سازی اطلاعات ساختمان (BIM)          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>

                    <li data-id="13317" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify dropdown">
                        <a href="/pedia" class="dropdown-toggle">

                            محتوای تخصصی          <span class="caret"></span>
                        </a>
                        <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">
                            <div class="mega-dropdown-inner">
                                <div class="tb-megamenu-row row-fluid">
                                    <div data-class="" data-width="3" data-hidewcol="0" id="tb-megamenu-column-10" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8534" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="1" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/news" class="">

                                                        اخبار          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-11" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8712" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/article" class="">

                                                        مقالات تحلیلی          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-12" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="3598" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega mega-align-justify">
                                                    <a href="/publication" class="">

                                                        کتاب الکترونیکی (ایبوک)          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-13" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13621" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/article/software" class="">

                                                        نرم افزار کاربردی مهندسی          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>
                                </div>

                                <div class="tb-megamenu-row row-fluid">
                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-14" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-akhbaar" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-akhbaar" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/news/%DA%AF%D9%88%D9%86%D8%A7%DA%AF%D9%88%D9%86" title="">گوناگون</a></li>
                                                                <li class="leaf"><a href="/news/%DA%A9%D8%AA%D8%A8%D8%8C-%D9%85%D8%AC%D9%84%D8%A7%D8%AA-%D9%88-%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1%D9%87%D8%A7" title="">کتب، مجلات و نرم افزارها</a></li>
                                                                <li class="leaf"><a href="/news/%D8%B9%D9%84%D9%85%DB%8C-%D8%AA%D8%AD%D9%82%DB%8C%D9%82%D8%A7%D8%AA%DB%8C" title="">علمی تحقیقاتی</a></li>
                                                                <li class="leaf"><a href="/news/%D8%B1%D9%88%DB%8C%D8%AF%D8%A7%D8%AF%D9%87%D8%A7-%D9%88-%DA%A9%D9%86%D9%81%D8%B1%D8%A7%D9%86%D8%B3-%D9%87%D8%A7%DB%8C-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DB%8C" title="">رویدادها و کنفرانس های آموزشی</a></li>
                                                                <li class="leaf"><a href="/news/%D8%AA%DA%A9%D9%86%D9%88%D9%84%D9%88%DA%98%DB%8C-%D9%87%D8%A7%DB%8C-%D9%86%D9%88%DB%8C%D9%86" title="">تکنولوژی های نوین</a></li>
                                                                <li class="leaf"><a href="/news/%D8%A7%D8%AE%D8%A8%D8%A7%D8%B1-%D8%B5%D9%86%D9%81%DB%8C-%D9%86%D8%B8%D8%A7%D9%85-%D9%85%D9%87%D9%86%D8%AF%D8%B3%DB%8C" title="">اخبار صنفی نظام مهندسی</a></li>
                                                                <li class="leaf"><a href="/news/%D8%A7%D8%AE%D8%A8%D8%A7%D8%B1-%D8%B1%D9%88%D8%B2-%D8%AF%D9%86%DB%8C%D8%A7-%D8%AA%D8%B1%D8%AC%D9%85%D9%87-%D8%B4%D8%AF%D9%87" title="">اخبار روز دنیا (ترجمه شده)</a></li>
                                                                <li class="leaf"><a href="/news/%D8%A2%DA%AF%D9%87%DB%8C-%D9%87%D8%A7%DB%8C-%D8%A7%D8%B3%D8%AA%D8%AE%D8%AF%D8%A7%D9%85%DB%8C" title="">آگهی های استخدامی</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/news/%D8%B1%D9%BE%D9%88%D8%B1%D8%AA%D8%A7%DA%98-%D8%A2%DA%AF%D9%87%DB%8C" title="">رپورتاژ آگهی</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-15" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-maghalat-tahlili" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-maghalat-tahlili" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/article/herfe" title="">آزمون ورود به حرفه</a></li>
                                                                <li class="leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%85%D9%82%D8%A7%D9%84%D8%A7%D8%AA-%D8%AA%D8%AD%D9%84%DB%8C%D9%84%DB%8C/2175/%D8%B3%D8%A7%D8%B2%D9%87-%D9%88-%D8%B2%D9%84%D8%B2%D9%84%D9%87-%D9%88-%D8%AE%D8%A7%DA%A9" title="">سازه و زلزله</a></li>
                                                                <li class="leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%85%D9%82%D8%A7%D9%84%D8%A7%D8%AA-%D8%AA%D8%AD%D9%84%DB%8C%D9%84%DB%8C/2177/%D9%81%DB%8C%D9%84%D9%85-%D9%87%D8%A7%DB%8C-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DB%8C-%D8%AA%D8%AE%D8%B5%D8%B5%DB%8C" title="">فیلم های آموزشی تخصصی</a></li>
                                                                <li class="leaf"><a href="/%D8%AF%D8%B3%D8%AA%D9%87-%D8%A8%D9%86%D8%AF%DB%8C-%D9%85%D9%82%D8%A7%D9%84%D8%A7%D8%AA-%D8%AA%D8%AD%D9%84%DB%8C%D9%84%DB%8C/2176/%D9%85%D9%82%D8%B1%D8%B1%D8%A7%D8%AA-%D9%85%D9%84%DB%8C-%D8%B3%D8%A7%D8%AE%D8%AA%D9%85%D8%A7%D9%86" title="">مقررات ملی ساختمان</a></li>
                                                                <li class="leaf"><a href="/article/software" title="">نرم افزار های کاربردی مهندسی عمران (قابلیت خرید به صورت دانلودی)</a></li>
                                                                <li class="last leaf"><a href="/article/store" title=""> تحلیلی آموزشی مهندسی عمران (موارد پیشنهادی)</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-16" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu--3---" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-3-" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="https://civil808.com/publication/20426/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-%DB%B1%DB%B8%DB%B4-%D8%B1%D8%A7%D9%87%D9%86%D9%85%D8%A7%DB%8C-%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1-seismostruct-2018" title="">راهنمای جامع فارسی نرم افزار SeismoStruct</a></li>
                                                                <li class="leaf"><a href="/publication/40/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-43-%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%D9%BE%DB%8C%D8%B4%D8%B1%D9%81%D8%AA%D9%87-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D9%85%D8%AD%D8%A7%D8%B3%D8%A8%D8%A7%D8%AA-%D8%B3%D8%A7%D8%B2%D9%87-%D9%87%D8%A7%DB%8C-%D9%81%D8%B6%D8%A7%DA%A9%D8%A7%D8%B1-%D8%A7%D9%88%D9%84%DB%8C%D9%86-%DA%A9%D8%AA%D8%A7%D8%A8-%D8%B3%D8%A7%D8%B2%D9%87-%D9%87%D8%A7%DB%8C-%D9%81%D8%B6%D8%A7%DA%A9%D8%A7%D8%B1" title="">آموزش پیشرفته طراحی محاسبات سازه های فضاکار</a></li>
                                                                <li class="leaf"><a href="/publication/39/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-42-%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%D9%BE%DB%8C%D8%B4%D8%B1%D9%81%D8%AA%D9%87-opensees-%D8%A7%D9%88%D9%84%DB%8C%D9%86-%DA%A9%D8%AA%D8%A7%D8%A8-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DB%8C-%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1-%D8%A7%D9%BE%D9%86%D8%B3%DB%8C%D8%B3%D9%86-%D8%A8%D9%87-%D8%B2%D8%A8%D8%A7%D9%86-%D9%81%D8%A7%D8%B1%D8%B3%DB%8C" title="">آموزش پیشرفته نرم افزار OpenSees</a></li>
                                                                <li class="leaf"><a href="/publication/819/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-%DB%B5%DB%B5-%D8%B1%D8%A7%D9%87%D9%86%D9%85%D8%A7%DB%8C-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%B3%D8%A7%D8%B2%D9%87-%D9%87%D8%A7%DB%8C-%D8%AE%D8%A7%D8%B5-%D8%AC%D9%84%D8%AF-%D8%AF%D9%88%D9%85" title=""> راهنمای طراحی سازه های خاص (دو جلد)</a></li>
                                                                <li class="leaf"><a href="/publication/307/%D8%A8%D8%B1%D8%B1%D8%B3%DB%8C-%D9%88%D8%A8%D8%B3%D8%A7%DB%8C%D8%AA-%D9%87%D8%A7%DB%8C-%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%D9%85%D8%AC%D8%A7%D8%B2%DB%8C-%D9%85%D9%87%D9%86%D8%AF%D8%B3%DB%8C-%D8%B9%D9%85%D8%B1%D8%A7%D9%86-%D8%AF%D8%B1-%D8%AF%D9%86%DB%8C%D8%A7" title="">بررسی وبسایت های آموزش مجازی عمران در دنیا</a></li>
                                                                <li class="leaf"><a href="/publication/1064/%D9%86%DA%AF%D8%A7%D9%87-%D8%B9%D9%85%D8%B1%D8%A7%D9%86-%D8%B4%D9%85%D8%A7%D8%B1%D9%87-5-%D9%88%DB%8C%DA%98%D9%87-%D8%A8%D9%87%D8%A7%D8%B1-%D9%88-%D8%AA%D8%A7%D8%A8%D8%B3%D8%AA%D8%A7%D9%86-93" title="">مجله = چکیده ای از برترین مصاحبه های رادیو808</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/article/ac/4906" title=""> تحلیل دینامیکی افزایشی IDA در OPENSEES</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/publication/16263/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-173%E2%80%8C-%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%D8%AA%D9%87%DB%8C%D9%87-%D8%B5%D9%88%D8%B1%D8%AA-%D8%AC%D9%84%D8%B3%D8%A7%D8%AA-%D9%88-%D8%AF%D9%81%D8%AA%D8%B1-%D9%81%D9%86%DB%8C-%D8%A8%D8%" title="">آموزش تهیه صورت جلسات و دفتر فنی </a></li>
                                                                <li class="leaf"><a href="http://civil808.com/publication/16092/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-171-%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%DA%AF%D8%A7%D9%85-%D8%A8%D9%87-%DA%AF%D8%A7%D9%85-%D9%88-%D8%AA%D8%B5%D9%88%DB%8C%D8%B1%DB%8C-%D8%A7%D9%86%D8%AC%D8%A7%D9%85-%D9%BE%D8%B1%D9%88%DA%98%" title="">آموزش گام به گام انجام پروژه سازه بتنی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/publication/16188/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-172-%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%D8%AC%D8%A7%D9%85%D8%B9-%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1-etabs2015" title="">ایبوک جامع آموزش نرم افزار ETABS 2015</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/publication/15805/%D8%A7%DB%8C%D8%A8%D9%88%DA%A9-169-%D8%AC%D8%B2%D9%88%D9%87-%D8%B6%D9%88%D8%A7%D8%A8%D8%B7-%D9%88-%D9%85%D9%82%D8%B1%D8%B1%D8%A7%D8%AA-%D8%B4%D9%87%D8%B1%D8%AF%D8%A7%D8%B1%DB%8C-%D9%BE%D8%A7%D8%B1%D8%AA-2" title="">ایبوک ضوابط و مقررات شهرداری</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-17" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-article4" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-article4" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/article/1107/%D8%A8%D8%B1%D9%86%D8%A7%D9%85%D9%87-%D9%87%D8%A7%DB%8C-%D8%B9%D9%85%D8%B1%D8%A7%D9%86%DB%8C-%D9%85%D8%A7%D8%B4%DB%8C%D9%86-%D8%AD%D8%B3%D8%A7%D8%A8-%D9%88%DB%8C%DA%98%D9%87-%D8%A2%D8%B2%D9%85%D9%88%D9%86-%D9%88%D8%B1%D9%88%D8%AF-%D8%A8%D9%87-%D8%AD%D8%B1%D9%81%D9%87-%D9%85%D8%AD%D8%A7%D8%B3%D8%A8%D8%A7%D8%AA-%D9%87%D9%85%D8%B1%D8%A7%D9%87-%D8%A8%D8%A7-2-%D8%B3%D8%A7%D8%B9%D8%AA-%D9%81%DB%8C%D9%84%D9%85" title="">برنامه های عمرانی ماشین حساب</a></li>
                                                                <li class="leaf"><a href="/article/9656/%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%A7%D8%AA%D8%B5%D8%A7%D9%84%D8%A7%D8%AA-%D8%B5%D9%81%D8%AD%D9%87-%D8%B3%D8%AA%D9%88%D9%86-%D8%A8%D9%87-%D8%B1%D9%88%D8%B4-%D8%A7%D8%AC%D8%B2%D8%A7%D8%A1-%D9%85%D8%AD%D8%AF%D9%88%D8%AF-%D8%A2%D9%BE%D8%AF%DB%8C%D8%AA-%D8%B4%D8%AF" title="">طراحی اتصالات صفحه ستون به روش اجزاء محدود</a></li>
                                                                <li class="leaf"><a href="/article/5370/%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1-dcon-%D8%A7%D8%A8%D8%B2%D8%A7%D8%B1-%D9%82%D8%AF%D8%B1%D8%AA%D9%85%D9%86%D8%AF%DB%8C-%D8%AC%D9%87%D8%AA-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%A7%D8%AA%D8%B5%D8%A7%D9%84%D8%A7%D8%AA-%D9%81%D9%88%D9%84%D8%A7%D8%AF%DB%8C-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%A8%DB%8C%D8%B4-%D8%A7%D8%B2-%DB%B7%DB%B0-%D9%86%D9%88%D8%B9-%D8%A7%D8%AA%D8%B5%D8%A7%D9%84-%D8%AA%DB%8C%D8%B1-%D8%A8%D9%87" title="">نرم افزار DCON طراحی اتصالات فولادی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/article/ac/1789" title="">نرم افزار Performance ، مقیاس رکوردهای زلزله برای تحلیل تاریخچه زمانی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/node/16343" title="">نرم افزار سازه پرداز-معرفی حالات و ترکیبات بارگذاری</a></li>
                                                                <li class="leaf"><a href="/article/944/%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%AA%DB%8C%D8%B1%DA%86%D9%87-%D8%A8%D8%A7-%D9%82%D8%A7%D8%A8%D9%84%DB%8C%D8%AA-%DA%A9%D9%86%D8%AA%D8%B1%D9%84-%D8%AE%DB%8C%D8%B2-%D8%AF%D8%B1%D8%A7%D8%B2-%D9%85%D8%AF%D8%AA-%D8%A2%D9%BE%D8%AF%DB%8C%D8%AA-%D8%B4%D8%AF-%D8%8C-%D9%86%D8%B3%D8%AE%D9%87-22" title="">نرم افزار طراحی تیرچه</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/article/16448/%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%B3%D8%A7%D8%B2%D9%87-%D9%87%D8%A7%DB%8C-%D8%AE%D8%A7%D8%B5-%D9%81%D9%88%D9%84%D8%A7%D8%AF%DB%8C-quads" title="">نرم افزار طراحی سازه های خاص فولادی QuadS</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/node/2193" title="">نرم افزار کنترل برش پانچ پی منطبق با SAFE 2014</a></li>
                                                                <li class="last leaf"><a href="/article/3668/%D8%AE%D8%B1%DB%8C%D8%AF-%D8%A2%D9%86%D9%84%D8%A7%DB%8C%D9%86-%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1%D9%87%D8%A7%DB%8C-%D8%B3%D8%A7%D8%B2%D9%87-%D9%88-%D9%BE%DB%8C-checker-vr-815" title="">نرم افزارهاي سازه و پي Checker Vr. 4.7.5</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>

                    <li data-id="8542" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify dropdown">
                        <a href="/college" class="dropdown-toggle">

                            آموزشگاه          <span class="caret"></span>
                        </a>
                        <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">
                            <div class="mega-dropdown-inner">
                                <div class="tb-megamenu-row row-fluid">
                                    <div data-class="" data-width="3" data-hidewcol="0" id="tb-megamenu-column-18" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8547" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="#" class="">

                                                        دپارتمان های آموزشی          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-19" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8548" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="#" class="">

                                                        کارگاه های آموزشی          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-20" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8549" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="#" class="">

                                                        دسترسی ها          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-21" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13604" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/shop/808-movie-packages" class="">

                                                        فیلم دوره های برگزار شده (پکیج های 808)          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>
                                </div>

                                <div class="tb-megamenu-row row-fluid">
                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-22" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-courses-topics" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-courses-topics" class="block block-menu first odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/college" title="">آموزشگاه</a></li>
                                                                <li class="leaf"><a href="/college/herfe" title="">ورود به حرفه</a></li>
                                                                <li class="leaf"><a href="/college/arshad" title="">کارشناسی ارشد</a></li>
                                                                <li class="leaf"><a href="/college/phd" title="">دکتری</a></li>
                                                                <li class="leaf"><a href="/college/Dadgostari" title="">کارشناس دادگستری</a></li>
                                                                <li class="leaf"><a href="/college/software" title="">نرم افزار</a></li>
                                                                <li class="leaf"><a href="/college/ejra" title="">اجرا</a></li>
                                                                <li class="leaf"><a href="/college/architect" title="">معماری</a></li>
                                                                <li class="last leaf"><a href="/college/search" title="">جستجو</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-23" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-amoozeshi-kargah" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-amoozeshi-kargah" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/education" title="">ورکشاپ های تخصصی</a></li>
                                                                <li class="leaf"><a href="/event" title="">فیلم کارگاه های آموزشی برگزار شده</a></li>
                                                                <li class="leaf"><span title="" class="nolink">همایش های 808</span></li>
                                                                <li class="leaf"><a href="http://civil808.com/conference/4" title="">چهارمین همایش ملی طراحی عملکردی سازه</a></li>
                                                                <li class="leaf"><a href="/conference/pt" title="">همایش سقف های بتنی پس کشیده</a></li>
                                                                <li class="leaf"><a href="/conference/3" title="">سومین همایش طراحی عملکردی سازه</a></li>
                                                                <li class="leaf"><a href="/article/1479/%D8%AF%D8%A7%D9%86%D9%84%D9%88%D8%AF-%D9%81%D9%8A%D9%84%D9%85-%D8%AF%D9%88%D9%85%DB%8C%D9%86-%D9%87%D9%85%D8%A7%DB%8C%D8%B4-%D9%85%D9%84%DB%8C-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%B9%D9%85%D9%84%DA%A9%D8%B1%D8%AF%DB%8C-%D8%B3%D8%A7%D8%B2%D9%87-%D9%87%D8%A7-%D8%8C-18-%D8%A7%D8%B3%D9%81%D9%86%D8%AF-93%D8%AF%D8%A7%D9%86%D9%84%D9%88%D8%AF-%D9%81%DB%8C%D9%84%D9%85-%D9%87%D9%85%D8%A7%DB%8C%D8%B4" title="">دومین همایش ملی طراحی عملکردی سازه</a></li>
                                                                <li class="leaf"><a href="/news/732/%D9%85%D8%B4%D8%A7%D9%87%D8%AF%D9%87-%D8%A2%D9%86%D9%84%D8%A7%DB%8C%D9%86-%D8%B1%D8%A7%DB%8C%DA%AF%D8%A7%D9%86-%D9%81%DB%8C%D9%84%D9%85-%D9%87%D9%85%D8%A7%DB%8C%D8%B4-%D8%B7%D8%B1%D8%A7%D8%AD%DB%8C-%D8%B9%D9%85%D9%84%DA%A9%D8%B1%D8%AF%DB%8C-%D8%B3%D8%A7%D8%B2%D9%87-%D9%87%D8%A7-%DA%AF%D8%B2%D8%A7%D8%B1%D8%B4-%D8%AA%D8%B5%D9%88%DB%8C%D8%B1%DB%8C-%D8%AA%D9%87%D8%B1%D8%A7%D9%86-15-%D8%A7%D8%B3%D9%81%D9%86%D8%AF-92" title="">اولین همایش طراحی عملکردی سازه ها</a></li>
                                                                <li class="leaf"><a href="https://civil808.com/node/20486" title="">اولین همایش انقلاب در ساخت و ساز با BIM</a></li>
                                                                <li class="last leaf"><a href="/eventt" title="">سایر همایش های برگزار شده توسط سازه 808</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-24" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-college-links" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-college-links" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/college/course-vip" title="">درخواست کلاس خصوصی</a></li>
                                                                <li class="leaf"><a href="/landing/exam" title="">آزمون آزمایشی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/808calendar?advagg=0" title="">تقویم دوره های آموزشی  سایر مراکز</a></li>
                                                                <li class="leaf"><a href="/calendar" title="">تقویم دوره های آموزشی 808</a></li>
                                                                <li class="leaf"><a href="http://Civil808.com/pedia" title="">دانشنامه تخصصی عمران و معماری</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/moshaver" title="">مشاوره کنکور کارشناسی ارشد</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/moshaver/research" title="">مشاوره مرتبط با مقالات پژوهشی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/advisor" title="">ارتباط با مشاوران اختصاصی 808</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/question/list" title="">سیستم پرسش و پاسخ 808+</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/node/19807" title="">مشاوره آزمون ورود به حرفه عمران و معماری</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/landing/eitexperts" title="">مشاوره ثبت نام و آمادگی آزمون ورود به حرفه بین المللی FE</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-25" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-4column-college" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-4column-college" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/edu95/phd" title="">پکیج آمادگی آزمون دکتری عمران</a></li>
                                                                <li class="leaf"><a href="/edu95/herfe" title="">پکیج آمادگی آزمون ورود به حرفه عمران</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/edu/arshad96" title="">پکیج آمادگی آزمون کارشناسی ارشد عمران</a></li>
                                                                <li class="leaf"><a href="/edu95/rasmi" title="">پکیج آمادگی کارشناسی رسمی دادگستری</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/bim" title="">پکیج دوره های آموزش آنلاین BIM</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/node/15662" title="">..آشنایی با سیستم Dropbox برای اشتراک ویدئوهای دوره های آموزشی 808</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>

                    <li data-id="12336" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify dropdown">
                        <a href="/shop" class="dropdown-toggle">

                            فروشگاه          <span class="caret"></span>
                        </a>
                        <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">
                            <div class="mega-dropdown-inner">
                                <div class="tb-megamenu-row row-fluid">
                                    <div data-class="" data-width="3" data-hidewcol="0" id="tb-megamenu-column-26" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13607" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/shop/main" class="">

                                                        لیست همه ی محصولات           </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-27" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13608" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="#" class="">

                                                        نوع آزمون          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-28" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13609" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="#" class="">

                                                        نوع محصول          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-29" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13610" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="#" class="">

                                                        محصولات دیگر          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>
                                </div>

                                <div class="tb-megamenu-row row-fluid">
                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-30" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-product-noe-kala" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-product-noe-kala" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="http://civil808.com/sites/default/files/civil808-catalog-fall97.pdf" title="">کاتالوگ محصولات آموزشی 808(آپدیت پاییز 97)</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?field=2223" title="">محصولات عمرانی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?field=2253" title="">محصولات معماری</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/landing/members?rid=7" title="">لیست نمایندگی های معتبر فروش محصولات808</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-31" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-product-reshte" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-product-reshte" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="http://civil808.com/shop/main#/?exam=2250" title="">ورود به حرفه (نظام مهندسی)</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?exam=2256" title="">کارشناسی ارشد</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?exam=2267" title="">دکتری</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?exam=2257" title="">کارشناس رسمی</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/shop/main#/?exam=2266" title="">مهندسی حرفه ای</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-32" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-product-azmoon" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-product-azmoon" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="http://civil808.com/shop/main#/?product_kind=2221" title="">کتاب</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?product_kind=2231" title="">نرم افزار</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?product_kind=2241" title="">ابزارهای مهندسی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/shop/main#/?product_kind=2215" title="">فیلم های آموزشی</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/shop/main#/?product_kind=2539" title="">مجلات</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-33" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-product-entesharat" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-product-entesharat" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/shop/808-movie-packages" title="">پکیج های آموزشی 808</a></li>
                                                                <li class="leaf"><a href="/article/software" title="">نرم افزار های کاربردی (دانلودی)</a></li>
                                                                <li class="leaf"><a href="/publication" title="">کتاب های الکترونیکی (دانلودی)</a></li>
                                                                <li class="leaf"><a href="/article/store" title=""> مقالات تحلیلی - آموزشی (دانلودی)</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/node/13647" title="">آموزش های مباحث مقررات ملی ساختمان </a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/software" title="">سفارش آنلاین انواع نرم افزار های داخلی</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/shop/landing/featured" title="">پیشنهادات ویژه 808 (کتاب+فیلم)</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>

                    <li data-id="8540" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify dropdown">
                        <a href="/gallery" class="dropdown-toggle">

                            گالری          <span class="caret"></span>
                        </a>
                        <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">
                            <div class="mega-dropdown-inner">
                                <div class="tb-megamenu-row row-fluid">
                                    <div data-class="" data-width="3" data-hidewcol="0" id="tb-megamenu-column-34" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="6401" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/gallery/picture" class="">

                                                        گالری تصاویر          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-35" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8545" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/gallery/videos" class="">

                                                        گالری فیلم ها          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-36" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="8546" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/podcast" class="">

                                                        رادیو 808          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>

                                    <div data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-37" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <ul class="tb-megamenu-subnav mega-nav level-1 items-1">
                                                <li data-id="13620" data-level="2" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-2 mega">
                                                    <a href="/gallery/video/tag/%D9%85%D8%B5%D8%A7%D8%AD%D8%A8%D9%87-%D9%87%D8%A7" class="">

                                                        گزارش های اختصاصی 808          </a>
                                                </li>
                                            </ul>
                                        </div>
                                    </div>
                                </div>

                                <div class="tb-megamenu-row row-fluid">
                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-38" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="taxonomy_menu_block--3" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-taxonomy-menu-block-3" class="block block-taxonomy-menu-block side-block menu-taxonomy even">


                                                        <div class="content">
                                                            <ul><li class="first"><a href="/gallery/picture/tags/%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%D9%87%D8%A7%DB%8C-%DA%A9%D8%A7%D8%B1%D8%A8%D8%B1%D8%AF%DB%8C">آموزش های کاربردی</a></li><li><a href="/gallery/picture/tags/%D8%A7%D8%B3%D8%A7%D8%AA%DB%8C%D8%AF-%D9%88-%DA%86%D9%87%D8%B1%D9%87-%D9%87%D8%A7%DB%8C-%D8%B4%D8%A7%D8%AE%D8%B5">اساتید و چهره های شاخص</a></li><li><a href="/gallery/picture/tags/%D9%85%D8%B9%D9%85%D8%A7%D8%B1%DB%8C-%D8%B1%D9%88%D8%B2-%D8%AF%D9%86%DB%8C%D8%A7">معماری روز دنیا</a></li><li><a href="/gallery/picture/tags/%D9%87%D9%85%D8%A7%DB%8C%D8%B4-%D9%87%D8%A7-%D9%88-%D8%B3%D9%85%DB%8C%D9%86%D8%A7%D8%B1%D9%87%D8%A7">همایش ها و سمینارها</a></li><li><a href="/gallery/picture/tags/%DA%AF%D9%88%D9%86%D8%A7%DA%AF%D9%88%D9%86">گوناگون</a></li><li class="last"><a href="/gallery/picture/tags/%D8%AA%D8%B5%D8%A7%D9%88%DB%8C%D8%B1-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DB%8C-%D8%B9%D9%85%D8%B1%D8%A7%D9%86">تصاویر آموزشی عمران</a></li></ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-39" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="taxonomy_menu_block--2" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-taxonomy-menu-block-2" class="block block-taxonomy-menu-block odd">


                                                        <div class="content">
                                                            <ul><li class="first"><a href="/gallery/video/tag/bim">BIM</a></li><li><a href="/gallery/video/tag/%D8%A2%D9%85%D8%A7%D8%AF%DA%AF%DB%8C-%D8%A2%D8%B2%D9%85%D9%88%D9%86-%D8%A8%DB%8C%D9%86-%D8%A7%D9%84%D9%85%D9%84%D9%84%DB%8C-fe-%D9%88-pe">آمادگی آزمون بین المللی FE و PE</a></li><li><a href="/gallery/video/tag/%D8%A7%D8%AC%D8%B1%D8%A7%DB%8C%DB%8C-%D8%AE%D8%A7%D8%B1%D8%AC%DB%8C">اجرایی خارجی</a></li><li><a href="/gallery/video/tag/%D8%A7%D8%AC%D8%B1%D8%A7%DB%8C%DB%8C-%D8%AF%D8%A7%D8%AE%D9%84%DB%8C">اجرایی داخلی</a></li><li><a href="/gallery/video/tag/%D8%AA%DA%A9%D9%86%D9%88%D9%84%D9%88%DA%98%DB%8C-%D9%87%D8%A7%DB%8C-%D9%86%D9%88%DB%8C%D9%86-%D8%B3%D8%A7%D8%AE%D8%AA%D9%85%D8%A7%D9%86%DB%8C">تکنولوژی های نوین ساختمانی</a></li><li><a href="/gallery/video/tag/%D9%81%DB%8C%D9%84%D9%85-%D9%87%D8%A7%DB%8C-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DB%8C">فیلم های آموزشی</a></li><li><a href="/gallery/video/tag/%D9%85%D8%B3%D8%AA%D9%86%D8%AF%D9%87%D8%A7%DB%8C-%D8%B9%D9%84%D9%85%DB%8C">مستندهای علمی</a></li><li><a href="/gallery/video/tag/%D9%85%D8%B5%D8%A7%D8%AD%D8%A8%D9%87-%D9%87%D8%A7">مصاحبه ها</a></li><li><a href="/gallery/video/tag/%D9%88%D8%A8%DB%8C%D9%86%D8%A7%D8%B1%D9%87%D8%A7%DB%8C-%D8%B9%D9%84%D9%85%DB%8C">وبینارهای علمی</a></li><li><a href="/gallery/video/tag/%DA%AF%D9%88%D9%86%D8%A7%DA%AF%D9%88%D9%86">گوناگون</a></li><li><a href="/gallery/video/tag/fun">Fun</a></li><li class="last"><a href="/gallery/video/tag/%D9%81%DB%8C%D9%84%D9%85-%D9%BE%DB%8C%D8%B4%D9%86%D9%87%D8%A7%D8%AF%DB%8C">فیلم پیشنهادی</a></li></ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-40" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-radio808" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-radio808" class="block block-menu even">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/podcast/2289/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88-808-%D8%B4%D9%85%D8%A7%D8%B1%D9%87-67-%D8%A2%DB%8C%D8%A7-%D8%B9%D9%85%D8%B1-%D8%B3%D8%AF-%D8%B3%D8%A7%D8%B2%DB%8C-%D8%AF%D8%B1-%D8%A7%DB%8C%D8%B1%D8%A7%D9%86-%D8%A8%D9%87-%D9%BE%D8%A7%DB%8C%D8%A7%D9%86-%D8%B1%D8%B3%DB%8C%D8%AF%D9%87-%D8%A7%D8%B3%D8%AA%D8%9F">آیا عمر سدسازی در ایران به پایان رسیده است؟</a></li>
                                                                <li class="leaf"><a href="/podcast/336/%D9%88%DB%8C%D8%AF%D8%A6%D9%88%DA%A9%D8%B3%D8%AA-%D9%85%D8%B3%D8%AA%D9%86%D8%AF-%D9%85%D8%B5%D8%A7%D8%AD%D8%A8%D9%87-%D8%B1%D8%A7%D8%AF%DB%8C%D9%88-808-%D8%A8%D8%A7-%D9%85%D9%87%D9%86%D8%AF%D8%B3-%D8%B9%D9%84%DB%8C-%D8%A7%DA%A9%D8%A8%D8%B1-%D9%85%D8%B9%DB%8C%D9%86-%D9%81%D8%B1%D8%8C-%D9%BE%D8%AF%D8%B1-%D9%85%D9%87%D9%86%D8%AF%D8%B3%DB%8C-%D8%B2%D9%84%D8%B2%D9%84%D9%87-%D8%A7%DB%8C%D8%B1%D8%A7%D9%86" title="">ویدئوکست مصاحبه با پدر مهندسی زلزله ایران</a></li>
                                                                <li class="leaf"><a href="/podcast/589/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88-808-%D8%B4%D9%85%D8%A7%D8%B1%D9%87-51-%D8%AF%DA%A9%D8%AA%D8%B1-%D9%81%D8%B1%D8%B2%D8%A7%D8%AF-%D9%86%D8%B9%DB%8C%D9%85%D8%8C-%D8%A8%D8%B1%D9%86%D8%AF%D9%87-%D8%AC%D8%A7%DB%8C%D8%B2%D9%87-%DB%8C%DA%A9-%D8%B9%D9%85%D8%B1-%D9%81%D8%B9%D8%A7%D9%84%DB%8C%D8%AA-%D9%85%D9%87%D9%86%D8%AF%D8%B3%DB%8C-%D8%A2%D9%85%D8%B1%DB%8C%DA%A9%D8%A7-2007" title="">پروفسور فرزاد نعیم، برنده یک عمر فعالیت مهندسی آمریکا 2007</a></li>
                                                                <li class="leaf"><a href="/podcast/92/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88-808-%D9%85%D8%B5%D8%A7%D8%AD%D8%A8%D9%87-%D8%A8%D8%A7-%D9%BE%D8%B1%D9%88%D9%81%D8%B3%D9%88%D8%B1-%D8%B4%DB%8C%D8%B1%D9%88-%D8%AA%D8%A7%DA%A9%D8%A7%D8%AF%D8%A7">مصاحبه با پروفسور شیرو تاکادا</a></li>
                                                                <li class="leaf"><a href="/podcast/91/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88-808-%D9%85%D8%B5%D8%A7%D8%AD%D8%A8%D9%87-%D8%A8%D8%A7-%D9%BE%D8%B1%D9%88%D9%81%D8%B3%D9%88%D8%B1-%D8%B1%D9%85%D8%B6%D8%A7%D9%86%DB%8C%D8%A7%D9%86%D9%BE%D9%88%D8%B1">مصاحبه با پروفسور رمضانیانپور</a></li>
                                                                <li class="leaf"><a href="/podcast/159/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88-808-%D8%B4%D9%85%D8%A7%D8%B1%D9%87-22-%D9%88%DB%8C%DA%98%D9%87-%D8%A8%D8%B1%D9%86%D8%A7%D9%85%D9%87-%D8%B1%D9%88%D9%86%D9%85%D8%A7%DB%8C%DB%8C-%D8%A7%D8%B2-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DA%AF%D8%A7%D9%87-%D9%85%D8%AC%D8%A7%D8%B2%DB%8C-808">ویژه برنامه رونمایی از آموزشگاه مجازی 808</a></li>
                                                                <li class="leaf"><a href="/podcast/60/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88-808-%D8%B4%D9%85%D8%A7%D8%B1%D9%87-12-%D9%88%DB%8C%DA%98%D9%87-%D8%A8%D8%B1%D9%86%D8%A7%D9%85%D9%87-%D8%B1%D9%88%D8%B2-%D9%85%D9%87%D9%86%D8%AF%D8%B3%D8%8C-%D9%85%D8%B5%D8%A7%D8%AD%D8%A8%D9%87-%D8%A8%D8%A7-%D8%AF%DA%A9%D8%AA%D8%B1-%D9%86%D8%AC%D9%81%DB%8C-%D9%85%D8%B9%D8%A7%D9%88%D9%86-%D8%B4%D8%B1%DA%A9%D8%AA-%D8%A8%D9%84%D9%86%D8%AF-%D9%BE%D8%A7%DB%8C%D9%87">ویژه برنامه روز مهندس سال 91</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/node/3505" title="">ارتباط دانش با صنعت مصاحبه با دکتر سهیل محمدی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/node/4253" title="">خرافات آب، مصاحبه با کاوه مدنی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/podcast/11591/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88808-%D8%B4%D9%85%D8%A7%D8%B1%D9%87-81-%D8%B3%DB%8C%D8%B3%D8%AA%D9%85-%D9%87%D8%A7%DB%8C-%D8%AA%D8%B9%D9%85%DB%8C%D8%B1-%D9%BE%D8%B0%DB%8C%D8%B1-%D8%B3%D8%A7%D8%B2%D9%87-%D8%A7%DB%8C" title="">سیستم های تعمیر پذیر سازه ای، دکتر حسینی</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/podcast/12103/%D8%B1%D8%A7%D8%AF%DB%8C%D9%88808-%D8%B4%D9%85%D8%A7%D8%B1%D9%87-82-%D9%85%D8%B5%D8%A7%D8%AD%D8%A8%D9%87-%D8%A8%D8%A7-%DA%A9%D8%A7%D9%85%D8%B1%D8%A7%D9%86-%D8%AF%DB%8C%D8%A8%D8%A7" title="">مصاحبه با معمار برجسته، کامران دیبا</a></li>
                                                                <li class="last leaf"><a href="http://civil808.com/node/2668" title="">معماری از منظر زیبایی شهری،دکتر حافظی</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div data-showblocktitle="0" data-class="" data-width="3" data-hidewcol="" id="tb-megamenu-column-41" class="tb-megamenu-column span3  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="menu--menu-gallery4" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-menu-menu-gallery4" class="block block-menu odd">


                                                        <div class="content">
                                                            <ul class="nav navbar-pills"><li class="first leaf"><a href="/blog/3310/%DB%8C%D8%A7%D8%AF%D8%AF%D8%A7%D8%B4%D8%AA-75-%D8%A2%D8%B4%D9%86%D8%A7%DB%8C%DB%8C-%D8%A8%D8%A7-%D8%A7%D8%B4%D8%B1%D9%81-%D8%AD%D8%A8%DB%8C%D8%A8-%D8%A7%D9%84%D9%84%D9%87-%D9%85%D8%AF%DB%8C%D8%B1-%DA%A9%D9%85%D9%BE%D8%A7%D9%86%DB%8C-%D9%86%D8%B1%D9%85-%D8%A7%D9%81%D8%B2%D8%A7%D8%B1%DB%8C-csi-%D8%A8%D8%AE%D8%B4-%D9%87%D8%A7%DB%8C%DB%8C-%D8%A7%D8%B2%D8%AD%D8%A7%D8%B4%DB%8C%D9%87-%D8%B3%D9%85%DB%8C%D9%86%D8%A7%D8%B1" title="">آشنایی با اشرف حبیب الله مدیر کمپانی نرم افزاری CSI (بخش هایی سمینار ستانبول)</a></li>
                                                                <li class="leaf"><a href="/blog/3309/%D8%A8%D8%A7%D8%B2%D8%AF%DB%8C%D8%AF-%D8%B3%D8%A7%D8%B2%D9%87-808-%D8%A7%D8%B2-%D9%BE%D9%84-%D9%85%D8%B9%D9%84%D9%82-%DA%A9%D8%A7%D8%A8%D9%84%DB%8C-%D8%AA%D9%86%DA%AF%D9%87-%D8%A8%D8%B3%D9%81%D8%B1-%D9%88-%D8%AF%D8%A7%D9%86%D8%B4%DA%AF%D8%A7%D9%87-%D8%AA%DA%A9%D9%86%DB%8C%DA%A9%D8%A7%D9%84%D8%8C%D8%A7%D8%B3%D8%AA%D8%A7%D9%86%D8%A8%D9%88%D9%84-%D8%AA%D8%B1%DA%A9%DB%8C%D9%87" title="">بازدید سازه 808 از پل معلق کابلی تنگه بسفر  ترکیه</a></li>
                                                                <li class="leaf"><a href="/education/9102/%D9%81%DB%8C%D9%84%D9%85-%D8%A8%D8%A7%D8%B2%D8%AF%DB%8C%D8%AF-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DB%8C-%D8%B3%D8%A7%D8%B2%D9%87-808-%D8%A7%D8%B2-%D8%B3%D9%82%D9%81-%D8%B3%D8%A7%D8%B2%D9%87-%D9%81%D8%B6%D8%A7-%DA%A9%D8%A7%D8%B1-%D8%A7%D8%B3%D8%AA%D8%AE%D8%B1-%D8%A2%D8%A8%D8%B3%D8%A7%D8%B1-%D8%A7%D8%B5%D9%81%D9%87%D8%A7%D9%86" title="">گزارش از بازدید سازه 808 از پروژه سازه فضاکار اصفهان</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/blog/post/13694" title="">گزارش بازدید سازه 808 از دفتر شرکت SeismoSoft در کشور یونان</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/gallery/videos/playlist/2425/10478" title="">گزارش بازدید808 از نمایشگاه صنعت ساختمان 95</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/landing/sharif" title="">گزارش نشست ارائه دستاوردهای فارغ التحصیلان عمران شریف</a></li>
                                                                <li class="leaf"><a href="http://civil808.com/gallery/videos/playlist/2973/16208" title="">گزارش ویدئویی از هفدهمین نمایشگاه ساختمان96</a></li>
                                                                <li class="last leaf"><a href="/blog/3157/%DB%8C%D8%A7%D8%AF%D8%AF%D8%A7%D8%B4%D8%AA-73-%D9%81%DB%8C%D9%84%D9%85-%D9%87%D8%A7%DB%8C-%D8%A2%D9%85%D9%88%D8%B2%D8%B4%DB%8C-%D8%AA%D8%AE%D8%B5%D8%B5%DB%8C-%D9%85%D8%B9%D8%B1%D9%81%DB%8C-%D8%AA%DA%A9%D9%86%D9%88%D9%84%D9%88%DA%98%DB%8C-%D9%87%D8%A7%DB%8C-%D9%86%D9%88%DB%8C%D9%86-%D8%B3%D8%A7%D8%B2%D9%87-%D8%A7%DB%8C-%D8%8C-%D8%A7%D8%AE%D8%AA%D8%B5%D8%A7%D8%B5%DB%8C-%D8%AA%D9%88%D9%84%DB%8C%D8%AF-%D8%B4%D8%AF%D9%87-808" title="">گزارشی از سومین نمایشگاه صنعتی سازی و تکنولوژی های نوین سازه ای سال 94</a></li>
                                                            </ul>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>

                    <li data-id="23794" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega">
                        <a href="http://civil808.com/app" class="">

                            اپلیکیشن          </a>
                    </li>

                    <li data-id="8832" data-level="1" data-type="menu_item" data-class="" data-xicon="" data-caption="" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify dropdown">
                        <a href="/search/google" class="dropdown-toggle">

                            جستجو          <span class="caret"></span>
                        </a>
                        <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">
                            <div class="mega-dropdown-inner">
                                <div class="tb-megamenu-row row-fluid">
                                    <div data-showblocktitle="0" data-class="" data-width="12" data-hidewcol="" id="tb-megamenu-column-42" class="tb-megamenu-column span12  mega-col-nav">
                                        <div class="tb-megamenu-column-inner mega-inner clearfix">
                                            <div data-type="block" data-block="search--form" class="tb-megamenu-block tb-block tb-megamenu-block">
                                                <div class="block-inner">
                                                    <div id="block-search-form" class="block block-search even">


                                                        <div class="content">
                                                            <form class="google-cse" action="/pedia/tag/3374/zadmin-test" method="post" id="search-block-form--2" accept-charset="UTF-8"><div><div class="container-inline">
                                                                        <h2 class="element-invisible">فرم جستجو</h2>
                                                                        <div class="form-item form-type-textfield form-item-search-block-form">
                                                                            <label class="element-invisible" for="edit-search-block-form--4">جستجو </label>
                                                                            <input title="عبارتی را که می‌خواهید جستجو گردد را وارد نمایید." type="text" id="edit-search-block-form--4" name="search_block_form" value="" size="15" maxlength="128" class="form-text">
                                                                        </div>
                                                                        <div class="form-actions form-wrapper" id="edit-actions--2"><input type="submit" id="edit-submit--2" name="op" value="جستجو" class="form-submit has-wave"></div><input type="hidden" name="form_build_id" value="form-kH10n_K64oqL2prNVPxk1lxWXKcoLciVyihf9GujAjw">
                                                                        <input type="hidden" name="form_token" value="90xdpmYQmHA0B3CJXDc97lEJL9kXqGqbwfJILWSRLvU">
                                                                        <input type="hidden" name="form_id" value="search_block_form">
                                                                    </div>
                                                                </div></form>  </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>
                </ul>
            </div>
        </div>
    </div>
</div>
<script type="text/javascript" src="https://civil808.com/sites/all/modules/tb_megamenu/js/tb-megamenu-frontend.js?pj73mr"></script>