<?php
$profile == $variables['profile'];
?>

<div class="linkedin-profile head-info">
    <?php if (!empty($profile['picture'])) : ?>
        <a href="<?php print $profile['picture']; ?>" <?php if (!empty($profile['full_name'])) : ?> title="Public profile of <?php print $profile['full_name']; ?> on www.linkedin.com."<?php endif; ?> >
            <img src="<?php print $profile['picture']; ?>" alt="<?php print $profile['full_name']; ?>" />
        </a>
    <?php endif; ?>


    <?php
    global $user;
    if($user->uid == arg(1)):
    $expire = linkedin_token_expire();
    if($expire !== false):
        ?>
        <div class="linkdin-refresh"><a class="" href="/linkedin/<?php print arg(1) ?>/connect"></a><div class="expire">اعتبار تا<br><?php print $expire ?></div></div>
    <?php
    endif;
    endif;
    ?>

    <div class="linkedin-head">
        <?php if (!empty($profile['full_name'])) : ?>
            <a href="<?php print $profile['profile']; ?>" title="Public profile of <?php print $profile['full_name']; ?> on www.linkedin.com.">
                <h2 class="linkedin-name"><?php print $profile['full_name']; ?></h2>
            </a>
        <?php endif; ?>

        <ul>
            <?php if(!empty($profile["headline"])): ?><li class="linkedin-headline"><span class="label">Headline : </span><span><?php print $profile['headline']?></span></li> <?php endif; ?>
            <?php if(!empty($profile["location"])): ?><li class="linkedin-location"><span class="label">Location : </span><span><?php print $profile['location']?></span></li> <?php endif; ?>
            <?php if(!empty($profile["location"])): ?><li class="linkedin-industry"><span class="label">Industry : </span><span><?php print $profile['location']?></span></li> <?php endif; ?>
            <?php if(!empty($profile["summary"])): ?><li class="linkedin-summary"><span class="label">Summary : </span><span><?php print $profile['summary']?></span></li> <?php endif; ?>
            <?php if(!empty($profile["connections"])): ?><li class="linkedin-num-connections"><span class="label">connections : </span><span><?php print $profile['connections']?></span></li> <?php endif; ?>
            <?php if(!empty($profile["profile"])): ?><li class="linkedin-public-profile-url">View Profile On <a href="<?php print $profile['profile']?>" target="_blank">Linked</a></li> <?php endif; ?>
        </ul>
    </div>
</div>

<div class="linkedin-positions">
    <h2>Experience</h2>
    <?php
    $positions = isset($profile['positions'][0]['id']) && !empty($profile['positions'][0]['id']) ? $profile['positions'] : array();

    foreach ($positions as $position) : ?>
        <div class="linkedin-position<?php ($position['isCurrent'] == TRUE) ? print ' linkedin-position-current' : ''; ?> linkedin-profile">
            <h4><?php
                ($position['isCurrent'] == TRUE) ? print t('Currently') . ' ' : '';
                if (!empty($position['title'])){
                    print $position['title'];
                }
                if (!empty($position['company']['name'])){
                    print ' at '. $position['company']['name'];
                } ?>
            </h4>

            <p><?php
                if (!empty($position['startDate']['year'])){
                    if (!empty($position['endDate']['year']))
                        print t('From') . ' ';
                    else
                        print t('Since') . ' ';
                    if (!empty($position['startDate']['month']))
                        print $position['startDate']['month'] . '/';
                    print $position['startDate']['year'] .' ';
                }
                if (!empty($position['endDate']['year'])){
                    if (!empty($position['startDate']['year']))
                        print ' ' . t('to') . ' ';
                    else
                        t('Until') . ' ';
                    if (!empty($position['endDate']['month']))
                        print $position['endDate']['month'] . '/';
                    print $position['endDate']['year'];
                }else
                    print '- ' . t('Present') ;
                ?>
            </p>
            <ul class="linkedin-company">
                <?php if(!empty($position['company'])){
                    print !empty($position['company']['name'])?'<h5 class="company-name">'. $position['company']['name'] .'</h5>': '';
                    print !empty($position['company']['size'])?'<li class="company-size">size : '. $position['company']['size'] .'</li>': '';
                    print !empty($position['company']['type'])?'<li class="company-type">type : '. $position['company']['type'] .'</li>': '';
                    print !empty($position['company']['industry'])?'<li class="company-industry">industry : '. $position['company']['industry'] .'</li>': '';
                }
                print !empty($position['location'])?'<li class="company-location">location : '. $position['location']['name'] .'</li>': '';
                ?>
            </ul>

            <?php if (!empty($position['summary']))
                print '<div class="linkedin-position-summary">'. $position['summary'] .'</div>';
            ?>
        </div>
    <?php endforeach; ?>
</div>
