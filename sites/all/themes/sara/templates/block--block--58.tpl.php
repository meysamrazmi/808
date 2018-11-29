<div id="main-nav">
    <ul class="main">
        <span class="active-item"></span>
        <li>
            <a href="">808</a>
            <div class="sub">
                <ul class="sub">
                <li><a href="">Bulldog</a></li>
                <li><a href="">Mastiff</a></li>
                <li><a href="">Labrador</a></li>
                <li><a href="">Mutt</a></li>
            </ul>
            </div>
        </li>
        <li>
            <a href="">عمران</a>
        </li>
        <li>
            <a href="">معماری</a>

        </li>
        <li>
            <a href="">لبه دانش</a>
            <div class="sub">
                <ul class="sub">
                <li><a href="">Brown Horse</a></li>
                <li><a href="">Race Horse</a></li>
                <li><a href="">Tall Horse</a></li>
            </ul>
            </div>
        </li>
        <li>
            <a href="">محتوای تخصصی</a>
            <div class="sub">
                <ul class="sub">
                <li><a href="">Cheesy</a></li>
                <li><a href="">More Ketchup</a></li>
                <li><a href="">Some Mustard</a></li>
                <li><a href="">Extra Butter</a></li>
            </ul>
            </div>
        </li>
        <li>
            <a href="">آموزشگاه</a>
            <div class="sub">
                <ul class="sub">
                <li><a href="">Cheesy</a></li>
                <li><a href="">More Ketchup</a></li>
                <li><a href="">Some Mustard</a></li>
                <li><a href="">Extra Butter</a></li>
            </ul>
            </div>
        </li>
        <li>
            <a href="">فروشگاه</a>
            <div class="sub">
                <ul class="sub">
                <li><a href="">Cheesy</a></li>
                <li><a href="">More Ketchup</a></li>
                <li><a href="">Some Mustard</a></li>
                <li><a href="">Extra Butter</a></li>
            </ul>
            </div>
        </li>
        <li>
            <a href="">گالری</a>
            <div class="sub">
                <ul class="sub">
                <li><a href="">Cheesy</a></li>
                <li><a href="">More Ketchup</a></li>
                <li><a href="">Some Mustard</a></li>
                <li><a href="">Extra Butter</a></li>
            </ul>
            </div>
        </li>
        <li>
            <a href="">اپلیکیشن</a>
        </li>
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
            </ul>
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
		$('.active-item').css({'width': $(this).width(), 'left': $(this).position().left})
		setTimeout(function(){
			$(this).addClass('active')
        }, 500)
	}).mouseleave(function(){
		$('.active-item').css({'width': 0, 'left': ($(this).position().left + $(this).width()/2)})
		$(this).removeClass('active')
	})
})
</script>