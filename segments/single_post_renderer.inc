<?php
/**
 * Single post renderer
 *
 * @var config      $config
 * @var module      $current_module posts
 * @var post_record $post
 */

use hng2_base\config;
use hng2_base\module;
use hng2_modules\posts\post_record;

$author = $post->get_author();
?>

<article class="post single_post clearfix" data-post-id="<?= $post->id_post ?>"
         data-main-category="<?= $post->main_category_slug ?>"
         data-author-role="<?= $author->get_role(true) ?>" data-author-level="<?= $author->level ?>">
    
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
                <span class="meta_field important">
                    <span class="fa fa-clock-o fa-fw"></span>
                    <?= preg_replace('/\d+s/', "", time_remaining_string($post->expiration_date)) ?>
                </span>
            <? endif; ?>
        </div>
    
    </div>
    
    <h1>
        <?= $post->get_processed_title() ?>
        <a class="permalink" href="<?= $post->get_permalink(true) ?>">
            <span class="fa fa-link fa-border"></span>
        </a>
    </h1>
    
    <div class="post_contents">
        <?= $post->get_processed_content() ?>
        <? $current_module->load_extensions("front", "single_post_content_additions"); ?>
    </div>
    
    <? if( ! empty($author->signature) ): ?>
        <div class="author_signature">
            <?= $author->get_processed_signature() ?>
        </div>
    <? endif ?>
    
</article>

<? $current_module->load_extensions("front", "single_post_after_contents"); ?>
