<?php
/**
 * Featured posts
 *
 * @var template   $template
 * @var posts_data $posts_data
 */

use hng2_base\template;
use hng2_modules\posts\posts_data;
?>

<div id="featured_posts_column">
    <? foreach($posts_data->featured_posts as $post):
        $src = "";
        if( ! empty($post->featured_image_thumbnail) )
            $src = $post->featured_image_thumbnail;
        else
            $src = $settings->get("modules:posts.default_featured_image");
        
        $pinned = $post->pin_to_home == 1 ? "pinned" : "";
        ?>
        <a class="featured_post <?= $pinned ?>" href="<?= $post->get_permalink() ?>">
            <? if( ! empty($src) ): ?><span class="thumbnail"><img src="<?= $src ?>"></span><? endif; ?>
            <h3><?= $post->get_processed_title() ?></h3>
        </a>
    <? endforeach; ?>
</div>
