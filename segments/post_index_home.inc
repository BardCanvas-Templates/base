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
            
            <div class="featured_post">
                <? if( ! empty($post->featured_image_thumbnail) ): ?>
                    <div class="thumbnail">
                        <img src="<?= $post->featured_image_thumbnail ?>">
                    </div>
                <? endif; ?>
                <h3><?= $post->get_processed_title() ?></h3>
            </div>
            
        <? endforeach; ?>
        
    </div>
    
    <div id="posts_index_wrapper">
        
        <?
        $template->set("pagination_url_prefix", "$config->full_root_url/");
        include __DIR__ . "/post_index_renderer.inc";
        ?>
        
    </div>
    
</div>
