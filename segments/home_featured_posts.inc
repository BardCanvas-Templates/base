<?php
/**
 * Featured posts
 *
 * @var template   $template
 * @var posts_data $posts_data
 */

use hng2_base\template;
use hng2_modules\posts\posts_data;

$this_module = $modules["posts"];
?>

<div id="featured_posts_column">
    <?
    $config->globals["modules:posts.working_posts_set"] =& $posts_data->featured_posts;
    $this_module->load_extensions("front", "featured_posts_before_loop_start");
    
    foreach($posts_data->featured_posts as $post):
        $author = $post->get_author();
        $src = $post->featured_image_thumbnail;
        if( empty($post->featured_image_thumbnail) ) $src = $settings->get("modules:posts.default_featured_image");
        $pinned = $post->pin_to_home == 1 ? "pinned" : ""; ?>
        <a class="featured_post <?= $pinned ?>" href="<?= $post->get_permalink() ?>">
            <? if( ! empty($src) ): ?><span class="thumbnail"><img src="<?= $src ?>"></span><? endif; ?>
            <h3>
                <?= $post->get_processed_title(false) ?>
                [<?= $author->get_processed_display_name() ?>, <?= $post->main_category_title ?>]
                <? if($post->expiration_date != "0000-00-00 00:00:00"): ?>
                    <span style="display: inline-block">
                        <span class="fa fa-clock-o fa-fw"></span>
                        <?= preg_replace('/\d+s/', "", time_remaining_string($post->expiration_date)) ?>
                    </span>
                <? endif; ?>
            </h3>
        </a>
    <? endforeach; ?>
</div>
