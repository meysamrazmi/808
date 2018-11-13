<div class="question">
    <div class="reply">
        <a href="/node/<?php print $node->nid; ?>#answer-question" target="_blank"><span>پاسخ به سوال</span></a>
    </div>

    <div class="right">
        <a href="/user/<?php print $node->uid; ?>" target="_blank" class="pic" title="<?php print $node->name; ?>"><img src="<?php if(!empty($node->picture)) print image_style_url("200x200" , $node->picture->uri); else print '/sites/all/themes/sara/images/profile2front.jpg'; ?>" alt="عکس کاربر"></a>
        <div class="comment-count"><?php (!empty($node->comment_count)) ? print $node->comment_count : print 0 ?> پاسخ </div>
    </div>

    <div class="left">
        <a href="/node/<?php print $node->nid; ?>" target="_blank" class="title"> <?php print $node->title; ?>  </a>
        <? if(!empty($node->body)): ?> <div class="body"> <?php print $node->body["und"][0]["value"];?>  </div> <?php endif; ?>
    </div>
</div>

