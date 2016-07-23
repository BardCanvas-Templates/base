<?php
/**
 * Posts index renderer
 *
 * @var post_record[] $posts
 * @var post_record[] $featured_posts
 * @var array         $pagination
 * @var record_browser $posts_browser
 */

use hng2_modules\posts\post_record;
use hng2_tools\record_browser;
?>

<div id="posts_index" class="posts_index clearfix">
    
    <? foreach( $posts as $post ): ?>
        <? $author = $post->get_author(); ?>
        
        <article class="post clearfix" data-post-id="<?= $post->id_post ?>"
                 data-main-category="<?= $post->main_category_slug ?>"
                 data-author-role="<?= $author->get_role() ?>">
            
            <div class="post_meta clearfix">
                
                <img class="user_avatar" src="<?= $config->full_root_url ?>/media/default_avatar.jpg">
                
                <div class="meta_section upper">
                    <a class="meta_field" href="<?= $config->full_root_url ?>/user/<?= $author->user_name ?>/">
                        <span class="fa fa-user fa-fw"></span>
                        <?= $author->get_processed_display_name() ?>
                    </a>
                    <a class="meta_field" href="<?= $config->full_root_url ?>/category/<?= $post->main_category_slug ?>/">
                        <span class="fa fa-folder fa-fw"></span>
                        <?= $post->main_category_title ?>
                    </a>
                </div>
                <div class="meta_section">
                    <a class="meta_field dimmed" href="<?= $config->full_root_url ?>/date/<?= date("Y/m/d", strtotime($post->publishing_date)) ?>/">
                        <span class="fa fa-calendar fa-fw"></span>
                        <?= time_elapsed_string($post->publishing_date) ?>
                    </a>
                    <? if($post->expiration_date != "0000-00-00 00:00:00"): ?>
                        <span class="meta_field dimmed">
                            <span class="fa fa-clock-o fa-fw"></span>
                            <?= preg_replace('/\d+s/', "", time_remaining_string($post->expiration_date)) ?>
                        </span>
                    <? endif; ?>
                </div>
                
            </div>
            
            <h1><a href="<?= $config->full_root_path ?>/<?= $post->id_post ?>"><?= $post->get_processed_title() ?></a></h1>
    
            <? if( ! empty($post->featured_image_thumbnail) ): ?>
                <div class="post_featured_image">
                    <img src="<?= $post->featured_image_thumbnail ?>">
                </div>
            <? endif; ?>
            
            <div class="post_contents post_excerpt">
                <?= $post->get_processed_excerpt() ?>
            </div>
        
        </article>
    
    <? endforeach; ?>
    
</div>

<div id="posts_pagination">
    
    <? $posts_browser->render_pagination_links($template->get("pagination_url_prefix"), $pagination); ?>

</div>
