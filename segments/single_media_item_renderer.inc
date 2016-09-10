<?php
/**
 * Single media item renderer
 *
 * @var config       $config
 * @var module       $current_module posts
 * @var media_record $item
 */

use hng2_base\config;
use hng2_base\module;
use hng2_media\media_record;

$author = $item->get_author();
?>

<article class="post single_post media_item single_media_item clearfix" data-item-id="<?= $item->id_media ?>"
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
            <span class="meta_field">
                <span class="fa fa-eye fa-fw"></span>
                <?= number_format($item->views); ?>
            </span>
        </div>
    
    </div>
    
    <h1>
        <?= $item->get_processed_title() ?>
        <a class="permalink" href="<?= $item->get_page_url(true) ?>">
            <span class="fa fa-link fa-border"></span>
        </a>
    </h1>
    
    <div class="post_contents">
        
        <? if($item->type == "image"): ?>
            <p>
                <a href="<?= $item->get_item_url() ?>" target="_blank">
                    <img src="<?= $item->get_item_url() ?>" style="max-width: 100%; height: auto;">
                </a>
            </p>
        <? elseif($item->type == "video"): ?>
            <p>
                <video width="100%" controls><source src='<?= $item->get_item_url(true) ?>'></video>
            </p>
        <? endif; ?>
        
        <?= $item->get_processed_description() ?>
    </div>
    
    <? if( ! empty($author->signature) ): ?>
        <div class="author_signature">
            <?= $author->get_processed_signature() ?>
        </div>
    <? endif ?>
    
</article>

<? $current_module->load_extensions("front", "single_media_item_after_contents"); ?>
