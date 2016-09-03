<?php
/**
 * Media index renderer
 *
 * @var config         $config
 * @var template       $template
 * @var settings       $settings
 * @var items_data     $items_data
 */

use hng2_base\config;
use hng2_base\settings;
use hng2_base\template;
use hng2_modules\gallery\items_data;

$this_module = $modules["gallery"];
?>

<div id="posts_index" class="posts_index clearfix">
    
    <? foreach( $items_data->items as $item): ?>
        <? $author = $item->get_author(); ?>
        
        <article class="post clearfix" data-post-id="<?= $item->id_post ?>"
                 data-main-category="<?= $item->main_category_slug ?>"
                 data-author-role="<?= $author->get_role(true) ?>" data-author-level="<?= $author->level ?>">
            
            <div class="meta_box clearfix">
                
                <img class="user_avatar" src="<?= $author->get_avatar_url() ?>">
                
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
            
            <h1><a href="<?= $item->get_page_url() ?>"><?= $item->get_processed_title(false) ?></a></h1>
            
            <div class="post_featured_image thumbnail">
                <img src="<?= $item->get_thumbnail_url() ?>">
            </div>
            
            <div class="post_contents post_excerpt">
                <?= $item->get_description_excerpt() ?>
            </div>
            
        </article>
    
    <? endforeach; ?>
    
</div>

<div id="posts_pagination">
    
    <? $items_data->browser->render_pagination_links($template->get("pagination_url_prefix"), $items_data->pagination); ?>

</div>
