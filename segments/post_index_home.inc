<?php
/**
 * Posts index for the home layout
 * 
 * @var template   $template
 * @var posts_data $posts_data
 */

use hng2_base\template;
use hng2_modules\posts\posts_data;

$has_featured_posts = count($posts_data->featured_posts) > 0 ? "true" : "false";
?>

<div id="home_index_wrapper" data-with-featured-posts="<?= $has_featured_posts ?>" class="clearfix">
    
    <div id="featured_posts_column">
        
        <? foreach($posts_data->featured_posts as $post): ?>
            
            <a class="featured_post" href="<?= $post->get_permalink() ?>">
                <? if( ! empty($post->featured_image_thumbnail) ): ?>
                    <span class="thumbnail">
                        <img src="<?= $post->featured_image_thumbnail ?>">
                    </span>
                <? endif; ?>
                <h3><?= $post->get_processed_title() ?></h3>
            </a>
            
        <? endforeach; ?>
        
    </div>
    
    <div id="posts_index_wrapper">
        
        <div id="posts_slider">
            <div align="center" style="margin: 10px; color: maroon;">
                This is the posts slider and should be shown only at the home.
            </div>
        </div>
        
        <?
        $template->set("show_quick_post_form", true);
        $template->set("pagination_url_prefix", "$config->full_root_url/");
        include __DIR__ . "/post_index_renderer.inc";
        ?>
        
    </div>
    
</div>
