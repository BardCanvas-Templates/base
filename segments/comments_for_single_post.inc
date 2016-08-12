<?php
/**
 * Comments listing for single post.
 * Note: this is included directly, so no globals are imported.
 *
 * @package    BardCanvas
 * @subpackage comments
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *
 * @var config   $config
 * @var settings $settings
 * @var template $template
 * @var module   $this_module    self (comments)
 * @var module   $current_module posts
 *             
 * Trailing vars:
 * @var post_record      $post
 * @var comment_record[] $comments
 */

use hng2_base\config;
use hng2_base\module;
use hng2_base\settings;
use hng2_base\template;
use hng2_modules\comments\comment_record;
use hng2_modules\comments\comments_repository;
use hng2_modules\posts\post_record;
use hng2_tools\record_browser;

$browser    = new record_browser("");
$repository = new comments_repository();

list($find_params, $comments_count, $comments, $pagination) = $repository->get_for_single_post($post->id_post);
?>

<div id="post_comments" class="content_frame" data-post-id="<?= $post->id_post ?>">
    
    <h1>
        <!--suppress HtmlUnknownAnchorTarget -->
        <a href="#post_new_comment_form" class="pull-right"><?= $this_module->language->list->post_comment ?></a>
        <?= replace_escaped_vars($this_module->language->list->title, '{$amount}', $comments_count) ?>
    </h1>
    
    <? foreach($comments as $comment): ?>
        <?
        $author     = $comment->get_author();
        $avatar_url = $author->get_avatar_url();
        $max_level  = $settings->get("modules:comments.max_indent_level"); if( empty($max_level) ) $max_level = 5;
        $level      = $comment->indent_level <= $max_level ? $comment->indent_level : $max_level;
        ?>
        <div class="comment_entry" id="comment_<?= $comment->id_comment ?>" data-id-comment="<?= $comment->id_comment ?>"
             data-parent-comment="<?= $comment->parent_comment ?>" data-indent-level="<?= $level ?>">
            
            <div class="comment_wrapper">
                <div class="meta_box clearfix">
                    <img class="user_avatar" src="<?= $avatar_url ?>">
                    
                    <div class="meta_section upper">
                        <? if($author->_exists): ?>
                            <a class="meta_field" href="<?= $config->full_root_url ?>/user/<?= $author->user_name ?>/">
                                <span class="fa fa-user fa-fw"></span>
                                <?= $author->get_processed_display_name() ?>
                            </a>
                        <? else: ?>
                            <span class="meta_field">
                                <span class="fa fa-user fa-fw"></span>
                                <?= $comment->author_display_name ?>
                            </span>
                        <? endif; ?>
                    </div>
                    <div class="meta_section">
                        <span class="meta_field dimmed">
                            <span class="fa fa-calendar fa-fw"></span>
                            <?= time_elapsed_string($comment->creation_date) ?>
                        </span>
                    </div>
                </div>
                
                <div class="content">
                    <?= $comment->get_processed_content() ?>
                </div>
            </div>
            
            <div class="comment_reply">
                <div class="trigger">
                    <span class="pseudo_link" onclick="prepare_comment_reply(this)">
                        <span class="fa fa-reply"></span>
                        <?= $this_module->language->list->reply_comment ?>
                    </span>
                </div>
                <div class="target"></div>
            </div>
        </div>
    <? endforeach; ?>
    
    <? if( $comments_count > $find_params->limit )
        $browser->render_pagination_links($template->get("pagination_url_prefix"), $pagination); ?>
    
</div>
