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
            <? if( $item->main_category_visibility == "level_based" && ! empty($item->main_category_min_level) ): ?>
                <span class="meta_field important">
                    <span class="fa fa-users"></span>
                    <?= $config->user_levels_by_level[$item->main_category_min_level]; ?>
                </span>
            <? elseif( $item->visibility == "level_based" ): ?>
                <span class="meta_field important">
                    <span class="fa fa-users"></span>
                    <?= $config->user_levels_by_level[$item->author_level]; ?>
                </span>
            <? endif; ?>
            
            <? if( ! empty($item->tags_list) ) foreach($item->tags_list as $tag): ?>
                <a class="meta_field" href="<?= $config->full_root_path ?>/tag/<?= $tag ?>/media" target="_blank">
                    <span class="fa fa-hashtag"></span>
                    <?= $tag ?>
                </a>
            <? endforeach; ?>
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
            
            <? if( $account->level >= config::MODERATOR_USER_LEVEL ): ?>
                <span class="meta_field critical">
                    <span class="fa fa-cloud"></span>
                    <?= $item->creation_ip ?>
                </span>
                <?
                $parts   = explode("; ", $item->creation_location);
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
        <?= $item->get_processed_title() ?>
    </h1>
    
    <p class="single_item_actions">
        <a class="item action clipboard-copy seamless_right" href="<?= $item->get_page_url(true) ?>">
            <?= $language->permalink ?>
        </a><span class="item action clipboard-copy seamless_left"
                  data-clipboard-text="<?= $item->get_page_url(true) ?>" style="">
            <span class="fa fa-clipboard"></span>
        </span>
        
        <? if( $item->can_be_edited() ): ?>
            <a class="item action" href="<?= $config->full_root_path ?>/gallery/?edit_item=<?= $item->id_media ?>&wasuuup=<?= md5(mt_rand(1, 65535)) ?>">
                <span class="fa fa-pencil"></span>
                <?= $language->edit ?>
            </a>
        <? endif; ?>
        
        <? if($account->_exists): ?>
            <span class="item action" onclick="send_pm(this, '<?= $author->user_name ?>', '<?= replace_escaped_vars($language->contact->pm->send_to, '{$recipient}', htmlspecialchars($author->display_name)) ?>')"
                    title="<?= replace_escaped_vars( $language->contact->pm->title, '{$website_name}', $settings->get("engine.website_name") ) ?>">
                <span class="fa fa-inbox"></span>
                <?= $language->pm_author ?>
            </span>
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
            <a class="item action" href="<?= $config->full_root_path ?>/contact/?action=report&type=media&id=<?= $item->id_media ?>">
                <span class="fa fa-exclamation-circle"></span>
                <?= $language->report_to_webmaster ?>
            </a>
        <? endif; ?>
    </p>
    
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
