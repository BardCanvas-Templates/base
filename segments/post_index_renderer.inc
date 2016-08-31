<?php
/**
 * Posts index renderer - called by the home layout and archives
 *
 * @var config     $config
 * @var posts_data $posts_data
 * @var template   $template
 * @var module[]   $modules
 * @var module     $this_module
 */

use hng2_base\config;
use hng2_base\module;
use hng2_base\template;
use hng2_modules\posts\posts_data;

$this_module = $modules["posts"];
?>

<? if( $template->get("page_tag") == "home" 
       && $posts_data->pagination["this_page_number"] == 1 ): ?>
    <div id="posts_slider">
        <div align="center" style="margin: 10px; color: maroon;">
            This is the posts slider and should be shown only at the page 1 of the home.
        </div>
    </div>
<? endif; ?>

<? if( in_array($template->get("page_tag"), array("post_category_index", "home"))
       && $account->level >= config::NEWCOMER_USER_LEVEL ): ?>
    <div id="quick_post_form_container">
        <? include "{$this_module->abspath}/contents/quick_post_form.inc"; ?>
    </div>
<? endif; ?>

<? if( $posts_data->count == 0 ) return; ?>

<div id="posts_index" class="posts_index clearfix">
    
    <?
    $config->globals["modules:posts.working_posts_set"] =& $posts_data->posts;
    $this_module->load_extensions("front", "index_renderer_before_loop_start");
    
    foreach( $posts_data->posts as $post ):
        $author = $post->get_author();
        if( $template->get("page_tag") == "home" && $post->pin_to_home == 1 )
            $pinned = "pinned";
        elseif( $template->get("page_tag") == "post_category_index" && $post->pin_to_main_category_index == 1 )
            $pinned = "pinned";
        else $pinned = ""; ?>
        
        <article class="post clearfix <?= $pinned ?>" data-post-id="<?= $post->id_post ?>"
                 data-main-category="<?= $post->main_category_slug ?>"
                 data-author-role="<?= $author->get_role() ?>">
            
            <div class="meta_box clearfix">
                
                <img class="user_avatar" src="<?= $author->get_avatar_url() ?>">
                
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
            
            <h1><a href="<?= $post->get_permalink() ?>"><?= $post->get_processed_title(false) ?></a></h1>
            
            <? if( ! empty($post->featured_image_thumbnail) ): ?>
                <div class="post_featured_image thumbnail">
                    <img src="<?= $post->featured_image_thumbnail ?>">
                </div>
            <? endif; ?>
            
            <div class="post_contents post_excerpt">
                <?= $post->get_processed_excerpt() ?>
                <? $this_module->load_extensions("front", "indexes_after_excerpt"); ?>
            </div>
            
        </article>
    
    <? endforeach; ?>
    
</div>

<div id="posts_pagination">
    
    <? $posts_data->browser->render_pagination_links($template->get("pagination_url_prefix"), $posts_data->pagination); ?>
    
</div>
