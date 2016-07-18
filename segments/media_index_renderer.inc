<?php
/**
 * Media index renderer
 *
 * @var media_record[] $items
 * @var media_record[] $featured_posts
 * @var array          $pagination
 * @var record_browser $media_browser
 */

use hng2_base\repository\media_record;
use hng2_tools\record_browser;
?>

<div id="posts_index" class="posts_index clearfix">
    
    <? foreach( $items as $item): ?>
        <? $author = $item->get_author(); ?>
        
        <article class="post clearfix" data-post-id="<?= $item->id_post ?>"
                 data-main-category="<?= $item->main_category_slug ?>"
                 data-author-role="<?= $author->get_role() ?>">
            
            <div class="post_meta clearfix">
                
                <img class="user_avatar" src="<?= $config->full_root_url ?>/media/default_avatar.jpg">
                
                <div class="meta_section upper">
                    <a class="meta_field" href="<?= $config->full_root_url ?>/user/<?= $author->user_name ?>/">
                        <span class="fa fa-user fa-fw"></span>
                        <?= $author->get_processed_display_name() ?>
                    </a>
                    <a class="meta_field" href="<?= $config->full_root_url ?>/category/<?= $item->main_category_slug ?>/">
                        <span class="fa fa-folder fa-fw"></span>
                        <?= $item->main_category_title ?>
                    </a>
                </div>
                <div class="meta_section">
                    <a class="meta_field dimmed" href="<?= $config->full_root_url ?>/date/<?= date("Y/m/d", strtotime($item->publishing_date)) ?>/">
                        <span class="fa fa-calendar fa-fw"></span>
                        <?= time_elapsed_string($item->publishing_date) ?>
                    </a>
                </div>
            
            </div>
            
            <h1><?= $item->get_processed_title() ?></h1>
            
            <div class="post_featured_image">
                <img src="http://www.foro-elite.com/wp-content/uploads/2016/07/Katherine-Jackman-255339.13-201927-e1468460131434-375x210.png?8f7ba1">
            </div>
            
            <div class="post_contents post_excerpt">
                <?= make_excerpt_of($item->description, $settings->get("modules:gallery.excerpt_length", 30)) ?>
            </div>
            
        </article>
    
    <? endforeach; ?>
    
</div>

<div id="posts_pagination">
    
    <? $media_browser->render_pagination_links($template->get("pagination_url_prefix"), $pagination); ?>

</div>
