<?php

?>
<div id="college-nav">
    <ul class="mains">
        <span class="active-item"></span>
        <li class="">
            <a href="/college" class="college">آموزشگاه</a>
        </li>
        <li class="">
            <a href="/college/herfe" class="herfe">ورود به حرفه</a>
        </li>
        <li class="">
            <a href="/college/ejra" class="ejra">اجرا</a>
        </li>
        <li class="">
            <a href="/college/arshad" class="arshad">ارشد</a>
        </li>
        <li class="">
            <a href="/college/phd" class="phd">دکتری</a>
        </li>
        <li class="">
            <a href="/college/architect" class="architect">معماری</a>
        </li>
        <li class="">
            <a href="/college/software" class="soft">نرم افزار</a>
        </li>
        <li class="">
            <a href="/college/Dadgostari" class="dadgostari">دادگستری</a>
        </li>
        <li class="">
            <a href="/college/search" class="sear">جستجو</a>
        </li>
    </ul>
</div>

<style>
div#college-nav ul {
    margin: 0;
    display: flex;
    justify-content: space-around;
}
div#college-nav ul a {
    padding: 25px 0;
    display: block;
    text-align: center;
    font-weight: 500;
    position: relative;
    border-left: 1px dashed #aaa;
    overflow: hidden;
    transition: all 0.3s;
    white-space: nowrap;
}
div#college-nav ul a:hover {
    background: #fff;
    color: #000;
}
div#college-nav ul li {
    list-style: none;
    width: 20%;
}
div#college-nav ul a:before {
    content: "";
    background: url(/sites/all/themes/sara/images/college/college.png);
    width: 35px;
    display: inline-block;
    height: 35px;
    background-size: contain;
    margin-left: 15px;
    top: 15px;
    background-repeat: no-repeat;
    vertical-align: middle;
}
div#college-nav ul a.herfe:before {
    background-image: url(/sites/all/themes/sara/images/college/herfe.png);
}
div#college-nav ul a.herfe:before {
    background-image: url(/sites/all/themes/sara/images/college/herfe.png);
}
div#college-nav ul a.ejra:before {
    background-image: url(/sites/all/themes/sara/images/college/ejra.png);
}
div#college-nav ul a.phd:before {
    background-image: url(/sites/all/themes/sara/images/college/phd.png);
}
div#college-nav ul a.architect:before {
    background-image: url(/sites/all/themes/sara/images/college/memari.png);
}
div#college-nav ul a.arshad:before {
    background-image: url(/sites/all/themes/sara/images/college/arshad.png);
}
div#college-nav ul a.soft:before {
    background-image: url(/sites/all/themes/sara/images/college/software.png);
}
div#college-nav ul a.dadgostari:before {
    background-image: url(/sites/all/themes/sara/images/college/hammer.png);
}
div#college-nav ul a.sear:before {
    background-image: none;
    content: "\f349";
    font-family: mat;
    font-size: 35px;
    color: #000;
    line-height: 35px;
}
@media all and (max-width: 1023px){
    div#college-nav ul a:before {
        width: 25px;
        height: 25px;
        font-size: 25px !important;
        line-height: 25px !important;
    }
}
@media (max-width: 840px){
    div#college-nav ul a:before{
        display: none;
    }
}

</style>

<script>
$(document).ready(function () {
})
</script>
