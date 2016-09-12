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
            <a class="meta_field user_display_name" data-user-level="<?= $author->level ?>"
               href="<?= $config->full_root_url ?>/user/<?= $author->user_name ?>/">
                <span class="fa fa-user fa-fw"></span>
                <?= $author->get_processed_display_name() ?>
            </a>
            <a class="meta_field" href="<?= $config->full_root_url ?>/category/<?= $post->main_category_slug ?>/">
                <span class="fa fa-folder fa-fw"></span>
                <?= $post->main_category_title ?>
            </a>
            <? if( $post->main_category_visibility == "level_based" && ! empty($post->main_category_min_level) ): ?>
                <span class="meta_field important">
                    <span class="fa fa-users"></span>
                    <?= $config->user_levels_by_level[$post->main_category_min_level]; ?>
                </span>
            <? elseif( $post->visibility == "level_based" ): ?>
                <span class="meta_field important">
                    <span class="fa fa-users"></span>
                    <?= $config->user_levels_by_level[$post->author_level]; ?>
                </span>
            <? endif; ?>
            
            <? foreach( $post->get_filtered_tags_list() as $tag): ?>
                <a class="meta_field" href="<?= $config->full_root_path ?>/tag/<?= $tag ?>" target="_blank">
                    <span class="fa fa-hashtag"></span>
                    <?= $tag ?>
                </a>
            <? endforeach; ?>
        </div>
        <div class="meta_section">
            <a class="meta_field dimmed" href="<?= $config->full_root_url ?>/date/<?= date("Y/m/d", strtotime($post->publishing_date)) ?>/">
                <span class="fa fa-calendar fa-fw"></span>
                <?= time_elapsed_string($post->publishing_date) ?>
            </a>
            <span class="meta_field">
                <span class="fa fa-eye fa-fw"></span>
                <?= number_format($post->views); ?>
            </span>
            <? if($post->expiration_date != "0000-00-00 00:00:00"): ?>
                <span class="meta_field important">
                    <span class="fa fa-clock-o fa-fw"></span>
                    <?= preg_replace('/\d+s/', "", time_remaining_string($post->expiration_date)) ?>
                </span>
            <? endif; ?>
            
            <? if( $account->level >= config::MODERATOR_USER_LEVEL ): ?>
                <span class="meta_field critical">
                    <span class="fa fa-cloud"></span>
                    <?= $post->creation_ip ?>
                </span>
                <?
                $parts   = explode("; ", $post->creation_location);
                $isp      = array_pop($parts);
                $location = implode("; ", $parts);
                ?>
                <span class="meta_field critical">
                    <span class="fa fa-map-marker"></span>
                    <?= $location ?>
                </span>
                <span class="meta_field critical">
                    <span class="fa fa-building"></span>
                    <?= $isp ?>
                </span>
            <? endif; ?>
        </div>
        
    </div>
    
    <h1>
        <?= $post->get_processed_title() ?>
    </h1>
    
    <p class="single_item_actions">
        <a class="item action clipboard-copy seamless_right" href="<?= $post->get_permalink(true) ?>">
            <?= $language->permalink ?>
        </a><span class="item action clipboard-copy seamless_left"
                  data-clipboard-text="<?= $post->get_permalink(true) ?>" style="">
            <span class="fa fa-clipboard"></span>
        </span>
        
        <? if( $post->can_be_edited() ): ?>
            <a class="item action" href="<?= $config->full_root_path ?>/posts/?edit_post=<?= $post->id_post ?>&wasuuup=<?= md5(mt_rand(1, 65535)) ?>">
                <span class="fa fa-pencil"></span>
                <?= $language->edit ?>
            </a>
        <? endif; ?>
        
        <? if($account->_exists): ?>
            <? if( $account->id_account != $author->id_account ): ?>
                <span class="item action" onclick="send_pm(this, '<?= $author->user_name ?>', '<?= replace_escaped_vars($language->contact->pm->send_to, '{$recipient}', htmlspecialchars($author->display_name)) ?>')"
                      title="<?= replace_escaped_vars( $language->contact->pm->title, '{$website_name}', $settings->get("engine.website_name") ) ?>">
                    <span class="fa fa-inbox"></span>
                    <?= $language->pm_author ?>
                </span>
            <? endif; ?>
        <? else: ?>
            <? if( $author->get_engine_pref("@contact:allow_emails") != "false"
                   || $account->level >= config::MODERATOR_USER_LEVEL ): ?>
                <a class="item action" href="<?= $config->full_root_path ?>/contact/?target=<?= urlencode($author->user_name) ?>">
                    <span class="fa fa-envelope"></span>
                    <?= $language->email_author ?>
                </a>
            <? endif; ?>
        <? endif; ?>
        
        <? if( $account->level < config::MODERATOR_USER_LEVEL ): ?>
            <a class="item action" href="<?= $config->full_root_path ?>/contact/?action=report&type=post&id=<?= $post->id_post ?>">
                <span class="fa fa-exclamation-circle"></span>
                <?= $language->report_to_webmaster ?>
            </a>
        <? endif; ?>
    </p>
    
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
