<?php
/**
 * Posts index renderer - slider on the home page
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
if( empty($posts_data->slider_posts) ) return;
if( $template->get("exclude_home_slider") ) return;
?>

<link rel="stylesheet" type="text/css" href="<?= $config->full_root_path ?>/lib/jquery-bxslider/jquery.bxslider.css">
<script type="text/javascript"          src="<?= $config->full_root_path ?>/lib/jquery-bxslider/jquery.bxslider.js"></script>
<script type="text/javascript">
    $(document).ready(function()
    {
        $('#posts_slider').bxSlider({
            auto:                true,
            pause:               15000,
            autoHover:           true,
            autoControls:        true,
            autoControlsCombine: true,
            adaptiveHeight:      false,
            touchEnabled:        true,
            randomStart:         true
        });
    });
</script>
<style type="text/css">
    #posts_slider { display: block; margin: 0; padding: 0; width: auto; position: relative;
                    overflow: hidden; background-color: white; height: 300px;
                    border: 1px solid #757575; box-shadow: 1px 1px 2px #808080; }
    
    #posts_slider li              ,
    #posts_slider li a            { width: 100%; display: block; margin: 0; padding: 0; height: 100%;
                                    text-align: center; overflow: hidden; background: none center center no-repeat; }
    
    #posts_slider li              { background-color: white; background-size: cover; }
    #posts_slider li a            { background-color: rgba(0, 0, 0, .75); background-size: contain; background-repeat: no-repeat; }
    
    #posts_slider li .title       { line-height: 30px; height: 30px; overflow: hidden; padding-bottom: 5px; display: block; font-size: 24px; font-weight: bold; background-color: rgba(0, 0, 0, .25); }
    #posts_slider li .image       { height: calc(100% - 86px); display: block; }
    #posts_slider li .description { font-size: 20px; line-height: 30px; height: 30px; padding-bottom: 5px; display: block; font-style: italic; overflow: hidden; background-color: rgba(0, 0, 0, .25); }
    #posts_slider li .details     { line-height: 20px; padding-bottom: 5px; display: block; background-color: rgba(0, 0, 0, .25); }
    #posts_slider li .expires     { color: yellow; }
    
    #posts_slider li   ,
    #posts_slider li a { color: white; font-weight: bold; text-shadow: 1px 1px 10px rgba(0, 0, 0, 1); text-decoration: none; }
    
    .bx-wrapper img.emojione { display: inline; }
</style>

<div id="posts_slider">
    
    <?
    $config->globals["modules:posts.working_posts_set"] =& $posts_data->slider_posts;
    $this_module->load_extensions("front", "index_renderer_before_slider_loop_start");
    
    foreach($posts_data->slider_posts as $post):
        
        $back_image = "";
        $post_image = "";
        if( ! empty($post->featured_image_path) )
        {
            $back_image = $post_image = "{$config->full_root_path}{$post->featured_image_path}";
        }
        elseif( ! empty($post->featured_image_thumbnail) )
        {
            $back_image = "{$config->full_root_path}{$post->featured_image_thumbnail}";
            $post_image = "{$config->full_root_path}{$post->featured_image_thumbnail}";
        }
        else
        {
            $default = $settings->get("modules:accounts.default_profile_banner");
            if( empty($default) ) $default = "media/default_user_banner.jpg";
            
            $back_image = "{$config->full_root_path}{$default}";
            $post_image = "{$config->full_root_path}/media/default_avatar.jpg";
        }
        ?>
        <li style="background-image: url('<?= $back_image ?>');">
            <a href="<?= $post->get_permalink() ?>" style="background-image: url('<?= $post_image ?>');">
                <span class="title"><?= $post->get_processed_title() ?></span>
                <span class="image"></span>
                <span class="description"><?= convert_emojis($post->excerpt) ?></span>
                <span class="details">
                    <span class="author"><?= $post->get_processed_author_display_name() ?></span>
                    •
                    <span class="published"><?= get_minimized_date($post->publishing_date) ?></span>
                    <? if($post->expiration_date != "0000-00-00 00:00:00"): ?>
                        <span class="expires">
                            <span class="fa fa-clock-o fa-fw"></span>
                            <?= preg_replace('/\d+s/', "", time_remaining_string($post->expiration_date)) ?>
                        </span>
                    <? endif; ?>
                </span>
            </a>
        </li>
    <? endforeach; ?>
    
</div>
