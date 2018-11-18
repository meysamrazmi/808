
<div id="taxonomy-term-<?php print $term->tid; ?>" class="<?php print $classes; ?>">
    <h1>marjantest<h1>
        <?php if (!$page): ?>
            <h2><a href="<?php print $term_url; ?>"><?php print $term_name; ?></a></h2>
        <?php endif; ?>

        <div class="content test">
            <?php print render($content); ?>
        </div>
</div>