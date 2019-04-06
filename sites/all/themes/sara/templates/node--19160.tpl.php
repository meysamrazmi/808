<!--<img src="/sites/default/files/importviaftp/423.jpg" width="100%" height="auto" style="box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 5px;">-->
<?php
    $node_content = node_load(19160);
    $url = substr($node_content->field_image['und'][0]['uri'] , 8);
    $url = "https://civil808.com/sites/default/files" . $url;
?>
<img src="<?php print $url;?>" width="100%" height="auto" style="box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 5px;" alt="<?php print $node_content->title;?>" title="دوره های آنلاین <?php print $node_content->title;?>">

<section style="margin: 87px 0 30px 0;">
    <div class="kargah-vip" style="margin-bottom: 15px;">
        <a target="_blank" href="/node/21193">
            <div>
                دوره حضوری مدل سازی اطلاعات ساختمان "Steps Towards Implementing BIM"
                <ul>
                    <li style="font-size: 13px;color: #909090 !important; padding: 18px 5px 5px 5px;">
                        Case study example: UAE Expolink Project
                    </li>
                    <li style="font-size: 13px;color: #909090 !important; padding: 5px 5px;">
                        lecturer: Omare Muhammad Azam
                    </li>
                    <li style="font-size: 13px;color: #909090 !important; padding: 5px 5px;">
                        will be held on 25-26th April 2019, IRAN, Tehran
                    </li>

                </ul>
                <button class="btn btn-primary has-wave"><span class="click-wave"></span>ثبت نام</button>
            </div>
            <div class="date-fan">
                <div class="day">5</div>
                <div class="month">اردیبهشت</div>
                <div class="year">1398</div>
            </div>
        </a>
    </div>
</section>

<section style="margin: 87px 0 30px 0;">
    <div class="kargah-vip" style="margin-bottom: 15px;">
        <a target="_blank" href="/node/21270">
            <div>
                تور تخصصی آزمون Autodesk Revit در شهر استانبول ترکیه به همراه آموزش قبولی در آزمون
                <ul>
                    <li style="font-size: 13px;color: #909090 !important; padding: 18px 5px 5px 5px;">
                        محل برگزاری آزمون: شهر استانبول ترکیه
                    </li>
                    <li style="font-size: 13px;color: #909090 !important; padding: 5px 5px;">
                        رشته های مورد استفاده:  عمران-معماری-مکانیک-برق
                    </li>
                    <li style="font-size: 13px;color: #909090 !important; padding: 5px 5px;">
                        مدت زمان تور:  3 روز (1 روز شرکت در آزمون- 1 روز بازدید از پروژه های در حال اجرای بیم در شهر استانبول - 1 روز آموزش رایگان نرم افزار های مرتبط در بیم در محل برگزاری آزمون در شهر استانبول) - کلاس آموزشی قبل از آزمون به مدت 8 ساعت در یکروز در محل موسسه 808 یک هفته قبل آزمون با تدریس مهندس قاسم آریانی برگزار میگردد
                    </li>

                </ul>
                <button class="btn btn-primary has-wave"><span class="click-wave"></span>ثبت نام</button>
            </div>
            <!--<div class="date-fan">
                <div class="day"></div>
                <div class="month">خرداد</div>
                <div class="year">1398</div>
            </div>-->
        </a>
    </div>
</section>

<section class="kargah-sec">
    <h2><?php print $node_content->title;?></h2>
<!--    <p style="text-align: center;margin-top: 30px;font-size: 15px;color: #888;">دوره فقط به صورت حضوری برگزار می شود.</p>-->
    <!--<p style="text-align: center;margin-top: 30px;font-size: 15px;color: #888;">برای مشاهده مجموعه تصاویر اولین همایش انقلاب بیم در صنعت ساخت و سازه به <a href="/node/19756" target="_blank"> این صفحه </a> مراجعه کنید</p>-->
    <div class="first-row" style="margin-top: 40px;">
        <div>
            <?php
            print($node_content->body['und'][0]['value']);
            ?>
        </div>
        <div class="lecturer">
            <img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-4445-1529945699.jpg?itok=WHa8HWzj" width="150px" height="auto">
            <p style="margin: 10px 0 0 0"><strong> مدرس </strong></p>
            <h3 style="margin:5px"> قاسم آریانی </h3>
            <p> مدرس تخصصی نرم افزارهای BIM </p>
            <a href="/user/4445/iran-bim" target="_blank" class="btn btn-primary">رزومه</a>
        </div>
    </div>
</section>

<!--<section class="timing six-box">
    <h2 class="text"> برنامه زمان بندی </h2>
    <div class="timing-wh">
        <div class="timebox time1 little-one">
            <div class="moddat"> 2 ساعت </div>
            <div class="circle"></div>
            <div class="line"></div>
            <div class="description">
                <a href="/user/4445/iran-bim" style="color: black" target="_blank">
                    <div class="des-top">
                        <img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-4445-1529945699.jpg?itok=WHa8HWzj" alt="قاسم آریانی" width="100px" height="100px">
                        <div class="des-left">
                            <b> قاسم آریانی </b>
                            <div> متخصص BIM و نرم افزارهای مربوطه </div>
                        </div>
                    </div>
                    <div class="des-down">
                        بررسی، شناخت و کاربرد درست نرم افزارهای BIM
                    </div>
                </a>
            </div>
        </div>
        <div class="timebox time2 little-one">
            <div class="moddat"> 15 دقیقه </div>
            <div class="circle"></div>
            <div class="line"></div>
            <div class="description">
                <a href="#" style="color: black">
                    <div class="des-top">
                        <img src="https://civil808.com/sites/default/files/pictures/default.png" alt="علیرضا ادیب فر" width="100px" height="100px">
                        <div class="des-left">
                            <b> علیرضا ادیب فر </b>
                            <div>  </div>
                        </div>
                    </div>
                    <div class="des-down">
                        بررسی کاربرد BIM در زیرساخت های حمل و نقلی
                    </div>
                </a>
            </div>
        </div>
        <div class="timebox time3 little-one">
            <div class="moddat"> 15 دقیقه </div>
            <div class="circle"></div>
            <div class="line"></div>
            <div class="description">
                <a href="/user/18104/mehdirasouli" style="color: black" target="_blank">
                    <div class="des-top">
                        <img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-18104-1533349689.jpg?itok=dOQvW5rF" alt="مهدی رسولی" width="100px" height="100px">
                        <div class="des-left">
                            <b> مهدی رسولی </b>
                            <div> کارشناس معماری و مشاور در زمینه BIM </div>
                        </div>
                    </div>
                    <div class="des-down">
                        پروسه طراحی بر اساس BIM، دغدغه معماری امروز
                    </div>
                </a>
            </div>
        </div>
        <div class="timebox time4">
            <div class="moddat"> 15 دقیقه </div>
            <div class="circle"></div>
            <div class="line"></div>
            <div class="description">
                <a href="/user/18106/saharzamansoltani" style="color: black" target="_blank">
                    <div class="des-top">
                        <img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-18106-1533345874.jpg?itok=YsTatyCO" alt="سحر زمان سلطانی" width="100px" height="100px">
                        <div class="des-left">
                            <b> سحر زمان سلطانی </b>
                            <div> کارشناس ارشد ارشد معماری و مشاور در زمینه BIM </div>
                        </div>
                    </div>
                    <div class="des-down">
                        نگاهی پسا معمارانه بر روش آموزش معماری در آتلیه های معماری (نقد به روایت تصویر)
                    </div>
                </a>
            </div>
        </div>
        <div class="timebox time5">
            <div class="moddat"> 15 دقیقه </div>
            <div class="circle"></div>
            <div class="line"></div>
            <div class="description">
                <a href="/user/10721/larijanimojtaba" style="color: black" target="_blank">
                    <div class="des-top">
                        <img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-10721-1502030043.jpg?itok=1hcyz0F9" alt="مجتبی اردشیر لاریجانی" width="100px" height="100px">
                        <div class="des-left">
                            <b> مجتبی اردشیر لاریجانی </b>
                            <div> متخصص BIM با نرم افزار Tekla Structures</div>
                        </div>
                    </div>
                    <div class="des-down">
                        بررسي عملكرد سازه اي بيم (مدل واقع گرايانه-مديريت پروژه-مديريت ريسك-مديريت حمل و نقل-توالي نصب و حمل قطعات-نمايش پيشرفت پروژه در بازه هاي زماني خاص-مديريت استراتژيك پروژه)
                    </div>
                </a>
            </div>
        </div>
        <div class="timebox time6">
            <div class="moddat"> 15 دقیقه </div>
            <div class="circle"></div>
            <div class="line"></div>
            <div class="description">
                <a href="/user/1546/khsaeid" style="color: black" target="_blank">
                    <div class="des-top">
                        <img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-1546-1496071500.jpg?itok=1KRQ1LSz" alt="سعید خلیلی قمی" width="100px" height="100px">
                        <div class="des-left">
                            <b> سعید خلیلی قمی </b>
                            <div> متخصص BIM و مدیریت و کنترل پروژه</div>
                        </div>
                    </div>
                    <div class="des-down">
                        لزوم تغییر رویکرد طراحی، ساخت و ... از روش های متداول به BIM مبنا و تفاوت های عمده بین آنها
                    </div>
                </a>
            </div>
        </div>
    </div>
</section>-->
<!--<section class="second">
    <h2 class="text" style="width:820px;"> ثبت نام در ورکشاپ حضوری تخصصی معرفی (BIM (Revit, Dynamo, Naviswork </h2>
    <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">علاوه بر این دوره شما می توانید در
        <a href="#edu-form" class="title"> دوره های حضوری و آنلاین BIM </a>
        ثبت نام کنید.
    </p>
    <div class="tickets">
        <div>
            <a target="_blank">
                <div class="city-name"><span>ثبت نام در دوره به صورت حضوری</span></div>
                <div class="inner-text">
                    <p class="text"> برنامه زمان بندی و نام اساتید را می توانید در بخش بالا مشاهده کنید </p>
                    <p style="padding: 9px 12px 0px 0px;">به همراه پذیرایی</p>
                    <div class="tarikh">چهارشنبه ۲۴ مرداد ماه</div>
                    <div class="makan"> سالن انجمن فارغ التحصیلان دانشگاه صنعتی شریف </div>
                    <div class="zaman"> ساعت ۱۶ تا ۲۰ </div>
                    <div class="mablagh"> 20,000 تومان </div>
                </div>
                <span class="sabtenam"> ثبت نام </span>
            </a>
            <a href="/cart/add/p20476?destination=cart" target="_blank">
                <div class="city-name"><span>ثبت نام در دوره به صورت حضوری</span></div>
                <div class="inner-text">
                    <p style="padding: 9px 12px 0px 0px;">به همراه ارسال فیلم وبینار به ایمیل ثبت نام کنندگاه بعد از برگزاری همایش</p>
                    <div class="tarikh">جمعه ۲۳ آذر ماه ۱۳۹۷</div>
                    <div class="makan">گیشا، فروزانفر، جنب بانک صادرات، پلاک ۱، واحد ۷، موسسه ۸۰۸ </div>
                    <div class="zaman"> ساعت ۱۷ تا ۲۰ </div>
                    <div class="mablagh"> ۲۵,۰۰۰ تومان </div>
                </div>
                <span class="sabtenam"> ثبت نام </span>
            </a>
        </div>
        <div class="bought-tickets">سوال های خود را می توانید از طریق شماره تماس موسسه و سیستم پیغام خصوصی با ما در میان بگذارید.</div>
	</div>

</section>-->

<div style="width: 70%; background-color: #ffffff; padding: 10px; margin: 45px auto 25px auto; border: solid #b39dd9; border-width: 0px 3px; box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px; text-align: center;">
    <a href="/node/20487" target="_blank" style="color: #909090 !important; font-size: 16px; margin: 5px; display: block;">
        مجموعه تصاویر و فیلم از اولین همایش انقلاب در صنعت ساخت و ساز با BIM برگزار شده در مرداد 97
    </a>
</div>

<div class="node">
    <div class="content">
        <!--<div class="field field-name-field-image field-type-image field-label-hidden">
            <div class="field-items">
                <div class="field-item even">
                    <img src="/sites/default/files/attachfromftp/bim-timing.jpg" width="500" alt=" برنامه زمانبندی همایش " title="برنامه زمانبندی همایش" style="width:500px !important;/*box-shadow: none!important;*/">
                </div>
            </div>
        </div>-->

        <div class="field field-name-body field-type-text-with-summary field-label-hidden">
            <!--
            <div class="main-text">
                <p>کلمه BIM که مخفف Building Information Modeling است، به مدل اطلاعاتی ساختمان می‌پردازد. همانطور که از کلمه Information پیداست، اطلاعات موجود در مدل اهمیت بسیاری دارند. نرم‌افزارهای BIM که تاکنون در عرصه جهانی معرفی شده‌اند به نام­‌های Revit ،Bently ،ArchiCAD ،MagiCAD ،DigitalProject ،Tekla Structure ،Navis work ،Vico و … است.</p>
                <p>مهم‌ترین کاربردها و توانمندی‌­های ویژه مدل‌سازی اطلاعات ساختمان در چرخه حیات پروژه عبارت است از:</p>
                <ul>
                    <li>کمک در برنامه­‌ریزی اولیه پروژه طراحی حجمی و کانسپت‌های معمارانه تهیه جزئیات اجرایی آنالیز و محاسبات سازه</li><li>انرژی و تأسیسات مستندسازی استاد و مدارک به‌صورت یکپارچه تدارکات شامل ارائه دقیق مقادیر</li><li>زنجیره‌ی تأمین مصالح و تجهیزات پروژه مدیریت ساخت و شبیه ‌سازی مدل زمان</li><li>هزینه ساخت تجهیز کارگاه مدیریت بهره‌­برداری و نگهداری ساختمان</li><li>بازسازی­‌ها و تغییر کاربری کاربرد در تخریب پروژه</li></ul>
                <p>از همین رو بر آن شدیم که دوره‌های آنلاینی برای آموزش نرم‌افزارهای بیم توسط مدرسین باتجربه در این زمینه ترتیب ببینیم. جهت ثبت نام در هر یک از دوره‌های تدارک دیده شده در این ترم می‌توانید از انتهای صفحه اقدام کنید.</p>
                <blockquote>
                    <p>این دوره ها مختص همه رشته های مرتبط با صنعت ساختمان یعنی عمران معماری برق و مکانیک برگزار میگردد.</p>
                </blockquote>
            </div>
            -->
            <a href="/node/19162" target="_blank" style="margin: 31px auto 0;display: block;text-align: center;">
                <img src="https://civil808.com/sites/default/files/field/image/node_19162.jpg" width="700" height="auto" alt="یادداشت تحلیلی: چگونه BIM صنعت ساختمان و شهرسازی را متحول کرد؟" title="یادداشت تحلیلی: چگونه BIM صنعت ساختمان و شهرسازی را متحول کرد؟">
            </a>

            <section id="relatives">
                <h2> اخبار و رویدادهای مرتبط </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/news" target="_blank">کلیک کنید</a>
                </p>
                <?php
                $args1 = 3753;
                $args2 = 'article';
                print views_embed_view('tags_content', 'block_4', $args1 , $args2 ); ?>
            </section>

            <section id="relatives">
                <h2> مقالات تحلیلی و ایبوک های مرتبط </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/publication" target="_blank">کلیک کنید</a>
                </p>
                <?php
                $args1 = 3753;
                $args2 = 'designteam+publication';
                print views_embed_view('tags_content', 'block_4', $args1 , $args2 ); ?>
            </section>

            <!--<section id="relatives">
                <h2> یادداشت ها و پادکست های مرتبط </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/podcast" target="_blank">کلیک کنید</a>
                </p>
                <?php
                //$args1 = 3753;
                //$args2 = 'podcast+blog';
                //print views_embed_view('tags_content', 'block_4', $args1 , $args2 ); ?>
            </section>-->

            <section id="relatives" class="films-section">
                <h2> مجموعه فیلم وبینار های برگزار شده </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/education" target="_blank">کلیک کنید</a>
                </p>
                <?php
                $args1 = 3753;
                $args2 = 'education';
                print views_embed_view('tags_content', 'block_4', $args1 , $args2 ); ?>
            </section>

            <section style="text-align: center;" class="diff film-relatives" id="relatives">
                <h2> فیلم های آموزشی رایگان در گالری 808 </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/gallery/videos" target="_blank">کلیک کنید</a>
                </p>
                <a style="margin: 25px auto 15px auto;" class="btn btn-primary" href="https://civil808.com/gallery/videos/playlist/4089/19930" > مجموعه فیلم همایش انقلاب در صنعت ساخت و ساز با BIM </a>
                <?php
                $args1 = 3753;
                $args2 = 'film';
                print views_embed_view('tags_content', 'block_1', $args1 , $args2 ); ?>
            </section>

            <section class="diff" id="relatives">
                <h2> مطالب بخش های مختلف سایت در تگ های مرتبط </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/pedia?title=bim" target="_blank">کلیک کنید</a>
                </p>
                <?php
                $args1 = 3753;
                print views_embed_view('tag_content', 'block', $args1 ); ?>
            </section>

            <section id="relatives" >
                <h2> دوره های آموزشی مرتبط </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/college" target="_blank">کلیک کنید</a>
                </p>
                <?php
                $args1 = 3753;
                $args2 = 'college';
                print views_embed_view('tags_content', 'block_4', $args1 , $args2 ); ?>
            </section>

            <section class="shop-relatives diff" id="relatives" >
                <h2> محصولات فروشگاه و پکیج های آموزشی 808 </h2>
                <p style="text-align: center;margin-top: 30px;font-size: 15px;color: #888;">
                    برای مشاهده مطالب بیشتر
                    <a href="https://civil808.com/shop/product" target="_blank">کلیک کنید</a>
                </p>
                <?php
                $args1 = 3753;
                $args2 = 'product+product_kit';
                print views_embed_view('tags_content', 'block_1', $args1 , $args2 ); ?>
            </section>

            <section class="diff last-sec" id="relatives" style="font-size: 13px;">
                <h2> برای انجام پروژه های BIM خود به مدرسین و مشاورین ما پیغام دهید </h2>
                <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">
                    برای مشاهده لیست مشاوران سایت
                    <a href="https://civil808.com/landing/advisor" target="_blank">کلیک کنید</a>
                </p>
                <div class="stickies all-members">
                    <div class="view-content" style="display: flex;justify-content: center;margin-top: 35px;">
                        <div class="views-row views-row-3 views-row-odd">

                            <div class="views-field views-field-counter">    <span class="views-label views-label-counter">#</span>    <span class="field-content">1</span>  </div>
                            <div class="views-field views-field-picture">        <div class="field-content"><a href="/user/1546/khsaeid"><img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-1546-1496071500.jpg?itok=1KRQ1LSz" width="220" height="220" alt=""></a></div>  </div>
                            <div class="views-field views-field-field-full-name">        <div class="field-content"><a href="/user/1546" target="_blank">سعید خلیلی قمی</a></div>  </div>
                            <span class="vip_icon" title="کاربر vip"></span>
                            <div class="views-field views-field-rid">    <span class="views-label views-label-rid">نقش‌ها: </span>    <span class="field-content">editor, Vip, مشاور, نمایندگی, همکاران</span>  </div>
                            <div class="views-field views-field-created">    <span class="views-label views-label-created">عضو به مدت: </span>    <span class="field-content">3 سال 8 ماه</span>  </div>
                            <div class="views-field views-field-field-experts">        <div class="field-content"><a href="">مدیریت پروژه</a><a href="">BIM</a><a href="">مدیریت ساخت</a></div>  </div>
                            <div class="views-field views-field-php-1 send-pm">        <span class="field-content"><a href="/messages/new/1546">ارسال پیام</a></span>  </div>
                            <div class="views-field views-field-php">        <span class="field-content views-field-status-link"><span class="add"><a href="/relationship/1546/request/1?destination=node/19160" class="user_relationships_popup_link">ایجاد ارتباط</a></span>
    </span>  </div>  </div>
                        <div class="views-row views-row-4 views-row-even">

                            <div class="views-field views-field-counter">    <span class="views-label views-label-counter">#</span>    <span class="field-content">2</span>  </div>
                            <div class="views-field views-field-picture">        <div class="field-content"><a href="/user/4445/iran-bim"><img src="https://civil808.com/sites/default/files/styles/200x200/public/pictures/picture-4445-1529945699.jpg?itok=WHa8HWzj" width="220" height="220" alt=""></a></div>  </div>
                            <div class="views-field views-field-field-full-name">        <div class="field-content"><a href="/user/4445" target="_blank">قاسم آریانی</a></div>  </div>
                            <span class="vip_icon" title="کاربر vip"></span>
                            <div class="views-field views-field-rid">    <span class="views-label views-label-rid">نقش‌ها: </span>    <span class="field-content">Vip, مشاور, همکاران</span>  </div>
                            <div class="views-field views-field-created">    <span class="views-label views-label-created">عضو به مدت: </span>    <span class="field-content">2 سال 7 ماه</span>  </div>
                            <div class="views-field views-field-field-experts">        <div class="field-content"><a href="">BIM</a><a href="">Autodesk Revit Structure</a><a href="">Revit Architecture</a></div>  </div>
                            <div class="views-field views-field-php-1 send-pm">        <span class="field-content"><a href="/messages/new/4445">ارسال پیام</a></span>  </div>
                            <div class="views-field views-field-php">        <span class="field-content views-field-status-link"><span class="add"><a href="/relationship/4445/request/1?destination=node/19160" class="user_relationships_popup_link">ایجاد ارتباط</a></span>
    </span>  </div>  </div>
                    </div>
                </div>
                <?php
                $args1 = 2680;
                print views_embed_view('represation', 'block_4', $args1 ); ?>
            </section>

        </div>
    <div class="flag-outer flag-outer-bookmarks" style="top: -38px;">
    <span class="flag-wrapper flag-bookmarks flag-bookmarks-19160">
      <a href="/flag/flag/bookmarks/19160?destination=node/19160&amp;token=nKQ22QkR9OyGSOJa0wd9GaKNxORrmdaBhrM38dwldGo" title="نشان کردن" class="flag flag-action flag-link-toggle flag-processed" rel="nofollow">Bookmark this</a>
        <span class="flag-throbber">&nbsp;</span>
    </span>
    <div class="flag-hint"><span>این مطلب را به لیست نشان شده ها اضافه کنید</span>
    </div>
</div>
<?php
    print(drupal_render($edu_form));
?>
    </div>
    <?php
        global $user;
        if (!$user->uid) {
            if ( isset($content['links']['comment']['#links']['comment_forbidden']) ){
                $comment_forbidden = $content['links']['comment']['#links']['comment_forbidden'];
                unset($content['links']['comment']['#links']['comment_forbidden']);
            }
        }
        print render($content['links']);
        if (!$user->uid) {
            if( isset($comment_forbidden) ){
                print '<li class="comment_forbidden first last"><span>';
                print render($comment_forbidden['title']);
                print '</span></li>';
            }
        }
        print render($content['comments']);
    ?>
</div>

<style>
    .kargah-vip{
        position: relative;
        width: 70%;
        background-color: #ffffff;
        padding: 19px 23px;
        margin: 30px auto 93px auto;
        border: solid #b39dd9;
        border-width: 0px 3px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        text-align: right;
    }
    .kargah-vip button{
        float:right;
        margin-right:10px;
    }
    .date-fan {
        font-family: fanum;
        position: relative;
        min-width: 98px;
        min-height: 129px;
        margin-bottom: 10px;
    }
    .date-fan .day {
        font-size: 64px;
        color: #bbb;
        position: absolute;
        right: 25px;
        top: 0;
    }
    .date-fan .month {
        font-size: 23px;
        color: #dadada;
        position: absolute;
        left: 2px;
        top: 69px;
    }
    .date-fan .year {
        color: #b5b5b5;
        position: absolute;
        top: 103px;
        left: 30px;
    }
    @media (max-width: 1100px){
        .kargah-vip{
            width: 96%;
            padding: 2% 2.5%;
        }
    }
    @media (max-width: 768px){
        .kargah-vip a{
            flex-direction: column-reverse;
        }
        .kargah-vip .vip-icon{
            margin: 0 0 18px 0;
        }
        .kargah-vip button{
            float: none;
            margin-right:auto;
        }
    }
    .kargah-vip a{
        color: black !important;
        font-size: 16px;
        margin: 5px;
        display: flex;
        justify-content: space-between;
        align-items: center;
    }
    .kargah-vip .vip-icon{
        width: 95px;
        margin-left: 2%;
    }
    .node section > h2{
        font-size: 24px;
        text-align: center;
        position: relative;
        font-weight:500;
        line-height: 40px;
    }
    .node section > h2:before {
        content: "";
        position: absolute;
        width: 130px;
        height: 3px;
        background: #883ab7;
        bottom: -10px;
        right: calc(50% - 65px);
        box-shadow: rgba(136,58,183,0.15) 0px 1px 6px, rgba(136,58,183,0.157) 0px 1px 4px;
    }
    .page-landing.page-bim .content .field-name-body * {
        /*line-height: normal !important;*/
    }

    #relatives{
        position: relative;
        padding: 80px 0px 0px;
    }
    .owl-theme .owl-dots,.owl-theme .owl-nav{text-align:center;-webkit-tap-highlight-color:transparent}.owl-theme .owl-nav{margin-top:10px}.owl-theme .owl-nav [class*=owl-]    {color:#FFF;font-size:14px;margin:5px;padding:4px 7px;background:#D6D6D6;display:inline-block;cursor:pointer;border-radius:3px}.owl-theme .owl-nav [class*=owl-]:hover  {background:#869791;color:#FFF;text-decoration:none}.owl-theme .owl-nav .disabled{opacity:.5;cursor:default}.owl-theme .owl-nav.disabled+.owl-dots{margin-top:10px}   .owl-theme .owl-dots .owl-dot{display:inline-block;zoom:1}.owl-theme .owl-dots .owl-dot span{width:10px;height:10px;margin:5px 7px;background:#D6D6D6;display:block;   -webkit-backface-visibility:visible;transition:opacity .2s ease;border-radius:30px}.owl-theme .owl-dots .owl-dot.active span,.owl-theme .owl-dots .owl-dot:hover span  {background:#869791}

    .owl-item .item {
        background: #2196F3;
        padding: 15px;
    }
    .owl-item .item {
        background: #abc;
        padding: 15px;
    }
    .owl-item .row {
        margin: 15px 3px 15px 0;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        background: #fff;
    }
    #relatives:not(.shop-relatives) .owl-carousel .owl-stage-outer{
        margin-bottom: 45px;
    }
    #relatives:not(.diff) .field-type-image img{
        width: 100% !important;
    }
    #relatives:not(.diff) .field-name-title h2{
        margin-top: 0px;
    }
    #relatives.film-relatives .field-name-title{
        margin-top: 0px;
    }
    #relatives.film-relatives .node-film{
        min-height: auto;
    }
    #relatives.film-relatives .field-name-title a {
        max-height: none;
    }
    .owl-item .row .title,
    #block-system-main > .content .field-name-body .owl-item .row .node:not(.node-product-kit):not(.node-product) .field-name-title a,
    #block-system-main > .content .field-name-body .owl-item .row .views-field-name a{
        padding: 10px 10px 2px 10px;
        color: #333 !important;
        line-height: 26px !important;
        display: block !important;
        border-top: 1px solid #eee;
        font-size: 13px;
        font-weight: normal;
    }
    .owl-carousel {
        padding: 15px 5%;
        width: 90% !important;
        margin: auto;
    }
    .owl-carousel .owl-item img {
        height: auto;
        margin: auto;
    }
    .owl-dot span:before {
        content: "";
        background: #aaa;
        display: inline-block;
        width: 15px;
        height: 15px;
        border-radius: 50%;
    }
    .owl-dot.active span:before {
        background: #333;
    }
    .owl-dots {
        display: flex;
        justify-content: center;
    }
    .owl-dot {
        padding: 0 10px;
        margin: 0 5px;
    }
    .owl-nav {
        display: flex;
        justify-content: center;
        display: none !important;
    }
    .owl-nav div {
        background: #eee;
        margin: 10px 20px 20px;
        padding: 5px 25px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        font-size: 15px;
        color: #555;
    }
    #relatives .node-film.view-mode-teaser{
        width: 100%;
        box-shadow: none !important;
        margin: 0;
        padding: 0;
    }
    #relatives.shop-relatives .row{
        box-shadow: none;
    }
    #relatives.shop-relatives .view-mode-teaser{
        width: 100%;
    }
    #relatives .node-architect img {
        border-radius: 0 !important;
        box-shadow: none !important;
        margin: auto;
    }
    #relatives .node-architect.node-teaser {
        margin: 0;
        width: 100%;
    }
    .page-landing.page-bim form#edu-form {
        padding: 15px 25px;
        margin: 40px 80px 50px;
        background: #fff;
        border-radius: 2px;
        box-shadow: rgba(0,0,0,0.117647) 0px -1px 6px, rgba(0,0,0,0.117647) 0 3px 3px;
        overflow: visible;
    }
    .page-landing.page-bim #block-system-main .content .content {
        background-color: transparent;
        box-shadow: none !important;
        border: none !important;
    }
    .page-landing.page-bim .field-name-body .main-text{
        max-width: 1240px;
        margin: auto;
    }
</style>

<style>
    <?php
        echo readfile("https://civil808.com/sites/all/themes/sara/css/less/kargah-land.min.css");
    ?>
</style>

<style>
    section.second {
        margin: 50px auto 0 !important;
    }
    .inner-text:before {
        /*content: "ظرفیت تکمیل شد";
        position: absolute;
        width: 180px;
        height: 35px;
        top: 95px;
        right: calc(50% - 120px);
        color: #F44336;
        font-size: 25px;
        font-weight: bold;
        border: 5px solid #F44336;
        padding: 15px;
        border-radius: 6px;
        background: hsla(0, 0%, 100%, 0.9);*/
    }
    .field-name-body .group-header .field-name-title h2{
        margin-top: 0px!important;
    }
    .last-sec *:not([class*='btn']){
        line-height: normal !important;
    }
</style>