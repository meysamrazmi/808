<?php
function check_808_options($mlid){

}
function render_menu_items($menu, &$level = 0, $sub = false){
	$output = '';
	foreach($menu as $link){
        if($level == 0)
	        $output .= '<ul class="sub">';

		$level++;

		$a = l($link['link']['link_title'], $link['link']['link_path'], $link['link']['localized_options']);
		$output .= '<li class="'. (!$sub?'main':'') .'">' . $a ."</li>\n";

		if($level >= 13){
			$output .= '</ul>';
			$level = 0;
		}
		if ($link['below']) {
			$output .= render_menu_items($link['below'], $level, true) ;
		}
//		$output .= (!$sub?'</ul>':'');
	}
	if((!$sub && $level < 13 && $level != 0) || ($sub && $level == 13)){
		$output .= '</ul>';
    }
	return $output;
}
$menu = menu_build_tree('main-menu');
?>
<div id="main-nav">
    <span class="menu-icon"></span>
    <ul class="main">
        <span class="active-item"></span>
        <a href="/" class="logo" target="_blank"><img src="/sites/all/themes/sara/logo.png" style="height: 50px;padding: 3px;"></a>
        <li class="">
            <a href="/" class="has-sub">808</a>
            <div class="sub">
                <?php print render_menu_items(menu_build_tree('menu-civil-column1')); ?>
            </div>
        </li>
        <li class="">
            <a href="/saze/808" title="">عمران</a>
        </li>
        <li class="">
            <a href="/arch" title="">معماری</a>
        </li>
        <li class="">
            <a href="/pedia" title="">دانشنامه</a>
        </li>
        <li class="">
            <a href="#" class="has-sub">لبه دانش</a>
            <div class="sub no-mega">
		        <?php print render_menu_items(menu_build_tree('menu-pedia')); ?>
            </div>
        </li>
        <li class="">
            <a href="/pedia" class="has-sub">محتوای تخصصی</a>
            <div class="sub">
			    <?php print render_menu_items(menu_build_tree('menu-contents')); ?>
            </div>
        </li>
        <li class="">
            <a href="/college" class="has-sub">آموزشگاه</a>
            <div class="sub">
			    <?php print render_menu_items(menu_build_tree('menu-college-links')); ?>
            </div>
        </li>
        <li class="">
            <a href="/shop" class="has-sub">فروشگاه</a>
            <div class="sub">
			    <?php print render_menu_items(menu_build_tree('menu-shop')); ?>
            </div>
        </li>
        <li class="">
            <a href="/gallery" class="has-sub">گالری</a>
            <div class="sub">
			    <?php print render_menu_items(menu_build_tree('menu-gallery')); ?>
            </div>
        </li>
        <li class="">
            <a href="/question/list">پرسش و پاسخ</a>
        </li>
        <li class="">
            <a href="/app">اپلیکیشن</a>
        </li>
        <li class="search">
            <a href="/search/google" class="has-sub">جستجو</a>
            <div class="sub">
                <form class="google-cse" action="/search/google" method="post" id="search-form" accept-charset="UTF-8">
                    <div>
                        <div class="container-inline">
                            <div class="form-item form-type-textfield form-item-search-block-form">
                                <input title="عبارتی را که می‌خواهید جستجو گردد را وارد نمایید." type="text" id="search-block-form" name="keys" value="" size="15" maxlength="128" class="form-text">
                            </div>
                            <div class="form-actions form-wrapper">
                                <input type="submit" id="search-submit" name="op" value="جستجو" class="form-submit has-wave">
                            </div>
                        </div>
                    </div>
                </form>
            </div>
        </li>
    </ul>
</div>

<style>
div#main-nav {
    float: right;
    width: 100%;
}
#main-nav ul {
    margin: 0;
    padding: 0;
}
#main-nav ul.main {
    display: flex;
    position: relative;
    height: 50px;
    max-width: calc(100% - 130px);
}
#main-nav ul.main > li > a {
    padding: 0 20px;
    line-height: 50px;
    height: 50px;
    white-space: nowrap;
}
#main-nav ul.main > li > a:hover,
#main-nav ul.main > li.active > a {
    color: #000;
}
#main-nav a {
    line-height: 2.2em;
    display: inline-block;
    color: #444;
    transition: all 0.2s ease;
}
#main-nav .sub a {
    color: #666;
    padding: 0 10px;
    width: 100%;
    /* overflow: hidden; */
}
#main-nav .sub a:hover {
    background: #f5f5f5;
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
#main-nav div.sub.no-mega {
    width: 300px;
    right: unset;
    margin-right: -80px;
}
#main-nav div.sub.no-mega ul.sub {
    width: 100%;
    margin: 0;
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
    min-width: calc(20% - 15px);
    margin-left: 15px;
}
#main-nav li.main a {
    color: #5a3ab7;
    font-weight: 500;
    position: relative;
}
#main-nav li.main a:before,
span.nolink:before {
    content: "\f141";
    font-family: mat;
    font-size: 16px;
    position: absolute;
    right: -6px;
}
#main-nav .sub li:not(.main) a {
    padding-right: 20px;
}
#main-nav a.has-sub:after {
    content: "\f140";
    font-family: mat;
    position: absolute;
    color: #ccc;
    margin-right: 3px;
}
.menu-icon {
    position: absolute;
    right: 0;
    width: 50px;
    height: 50px;
    top: 0;
    display: none;
    justify-content: center;
    align-items: center;
    cursor: pointer;
    transition: all 0.4s ease;
}
.menu-icon:before {
    content: "\f35c";
    font-family: mat;
    font-size: 29px;
    color: #9C27B0;
}
#main-nav form {
    width: 100%;
    max-width: 700px;
    margin: auto;
}
#main-nav form .container-inline {
    display: flex;
}
#main-nav form .form-item {
    width: 100%;
    display: inline-block;
    margin: auto;
}
#main-nav form .form-item input {
    width: 100%;
    margin: auto;
    box-shadow: 0 1px 6px rgba(0,0,0,0.12), 0 1px 4px rgba(0,0,0,0.12);
    height: 37px;
    line-height: 36px;
    font-size: 17px;
    padding: 0 15px;
}
#main-nav form .form-actions {
    padding-right: 0;
    margin-right: -1px;
}
.search .sub {
    border-top: 1px solid #eee;
    background: linear-gradient(to bottom left, #fff ,#eee) !important;
}
.search a {
    font-size: 0;
}
.search a:before {
    content: "\f349";
    font-family: mat;
    font-size: 24px;
    vertical-align: middle;
    padding-left: 5px;
    color: #666;
}
.search a:after {
    font-size: 14px;
    margin: 0 !important;
}
span.nolink {
    padding: 5px 10px 3px !important;
    display: block;
    position: relative;
}


@media all and (max-width: 1023px){
    #main-nav ul.main {
        width: 300px;
        height: 100vh;
        position: fixed;
        right: -300px;
        top: 0;
        background: #fff;
        flex-direction: column;
        z-index: 2;
        box-shadow: 0 1px 6px rgba(0,0,0,0.12), 0 1px 4px rgba(0,0,0,0.12);
        transition: right 0.4s;
        overflow: scroll;
        overflow: auto;
        margin-right: -6px;
    }
    .admin-menu #main-nav ul.main {
        top: inherit;
        margin-top: -15px;
    }
    #main-nav.open ul.main {
        right: 0px;
    }
    .menu-icon {
        display: flex;
    }
    #main-nav a {
        width: 100%;
        padding: 0;
    }
    #main-nav a:hover {
        background: #eee;
    }
    #main-nav a.has-sub:after {
        left: 15px;
        font-size: 18px;
        color: #888;
    }
    #main-nav .open a.has-sub:after {
        transform: rotate(180deg);
    }
    .active-item {
        display: none;
    }
    #main-nav li.active > div.sub {
        flex-direction: column;
        padding: 0;
        box-shadow: inset 0px 3px 4px rgba(0, 0, 0, .175);
        border: none;
        background: #f5f5f5;
    }
    #main-nav ul.sub {
        width: 100%;
        margin: 0;
    }
    #main-nav .sub a {
        padding: 0 25px;
        height: 40px;
        white-space: nowrap;
        line-height: 40px;
    }
    #main-nav .sub a:hover {
        background: #ddd;
    }
    #main-nav ul.main > li > a {
        padding: 0 16px;
    }
    #main-nav .sub li:not(.main) {
        height: 0;
        overflow: hidden;
    }
    #main-nav li.main a {
        color: #666;
        font-weight: normal;
    }
    #main-nav div.sub {
        position: unset;
        transition: height 0.2s;
    }
    #main-nav li.active > div.sub {
        display: none;
    }
    #main-nav li.open > div.sub {
        display: flex;
        flex-direction: column;
        padding: 0;
        box-shadow: none;
        border: none;
        background: #f5f5f5;
    }
    a.logo {
        text-align: center;
        padding: 10px 5px 0;
        border-bottom: 1px solid #eee;
        background: linear-gradient(to bottom left, #673AB7 ,#9C27B0) !important;
    }
    a.logo img {
        filter: brightness(0) invert(1);
        height: 70px !important;
    }
    div#main-nav.open .menu-icon {
        right: 294px;
        background: #420240;
        z-index: 4;
    }
    div#main-nav.open .menu-icon:before {
        color: #fff;
        content: "\f156";
    }
    #main-nav div.sub.no-mega {
        width: 100%;
        margin: 0;
    }
    #main-nav form .form-actions {
        padding: 5px 0px 0;
    }
    form#search-block-form--2 .container-inline {
        flex-direction: column;
        padding: 5px;
    }
    .search a {
        font-size: inherit;
    }
    span.nolink {
        display: none;
    }
    #main-nav form .form-submit {
        border-radius: 40px;
        position: absolute;
        z-index: 1;
        left: 7px;
        height: 33px;
        padding: 0px 15px 2px !important;
        min-width: auto;
        font-size: 12px;
        margin: 7px 0 0 0;
        line-height: 28px;
        background: #f5f5f5;
        color: #666 !important;
    }
    #main-nav form .form-item input {
        padding-left: 70px;
        border-radius: 30px;
        margin: 10px;
        width: 285px;
    }
    #main-nav li.main a:before, span.nolink:before{
        display: none;
    }
}

@media all and (min-width: 1024px) and (max-width: 1200px){
    #main-nav li.active > div.sub {
        width: 100vw;
    }
    #main-nav ul.main > li > a {
        padding-right: 10px;
        padding-left: 18px;
    }
}
</style>

<script>
$(document).ready(function () {
	//handling sub menu in desktop
	$('#main-nav ul.main > li').mouseenter(function(){
		var el = $(this)
		$('.active-item').css({'width': el.width(), 'left': el.position().left})
		el.addClass('hover')
		setTimeout(function(){
			el.parent().find('.active').removeClass('active')
			if(el.hasClass('hover'))
				el.addClass('active')
		}, 500)
	}).mouseleave(function(){
		var el = $(this)
		$('.active-item').css({'width': 0, 'left': (el.position().left + el.width()/2)})
		el.removeClass('active')
		el.removeClass('hover')
	})

    //handling search in menu
	$('#main-nav form .form-item input').keyup(function(e){
		$(this).parents('form').attr('action', ('/search/google/'+ $(this).val()) )
	}).keypress(function(e) {
		if(e.which == 13){
			e.preventDefault()
			window.location.replace('/search/google/'+ $(this).val())
		}
	})
	$('#main-nav form .form-submit').click(function(e){
		e.preventDefault()
		window.location.replace('/search/google/'+ $('#main-nav form .form-item input').val())
	})

    //handling submenu in mobile
    $('a.has-sub').click(function(e){
    	e.preventDefault()
        $(this).parent().toggleClass('open')
    })
    $('.menu-icon').click(function(){
    	$(this).parent().toggleClass('open')
    })
})
</script>
