<?php
/**
 * Posts index for the home layout
 * 
 * @var post_record[] $posts
 * @var post_record[] $featured_posts
 * @var array         $pagination
 */

use hng2_modules\posts\post_record;

$has_featured_posts = count($featured_posts) > 0 ? "true" : "false";
?>

<div id="home_index_wrapper" data-with-featured-posts="<?= $has_featured_posts ?>" class="clearfix">
    
    <div id="featured_posts_column">
        
        <? foreach($featured_posts as $post): ?>
            
            <div class="featured_post">
                <div class="thumbnail">
                    <img src="http://www.foro-elite.com/wp-content/uploads/2016/07/Katherine-Jackman-255339.13-201927-e1468460131434-375x210.png?8f7ba1">
                </div>
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
