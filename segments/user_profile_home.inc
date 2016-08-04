<?php
/**
 * Base template - User profile home contents
 *
 * @package    HNG2
 * @subpackage core
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *
 * @var module            $current_module accounts
 * @var account           $account
 * @var config            $config
 * @var template          $template
 * @var \SimpleXMLElement $language
 * @var settings          $settings
 */

use hng2_base\account;
use hng2_base\config;
use hng2_base\module;
use hng2_base\settings;
use hng2_base\template;

/** @var account $author */
$author = $template->get("user_profile_account");
?>

<h1><?= replace_escaped_vars($current_module->language->user_profile_page->title, '{$user}', $author->get_processed_display_name()) ?></h1>

<div id="user_info_sections">
    
    <section>
        <h2><?= $current_module->language->user_profile_page->info->title ?></h2>
        <form class="framed_content">
            <div class="field">
                <div class="caption">
                    <?= $current_module->language->user_profile_page->info->country ?>
                </div>
                <div class="input">
                    <?= $author->country_name ?>
                </div>
            </div>
            <div class="field">
                <div class="caption">
                    <?= $current_module->language->user_profile_page->info->home_page ?>
                </div>
                <div class="input">
                    <a href="<?= $author->homepage_url ?>" target="_blank"><?= $author->homepage_url ?></a>
                </div>
            </div>
            <div class="field">
                <div class="caption">
                    <?= $current_module->language->user_profile_page->info->feed ?>
                </div>
                <div class="input">
                    <a href="<?= $config->full_root_url ?>/user/<?= $author->user_name ?>/feed" target="_blank">
                        <?= $config->full_root_url ?>/user/<?= $author->user_name ?>/feed
                    </a>
                </div>
            </div>
        </form>
    </section>
    
    <section>
        <h2><?= $current_module->language->user_profile_page->signature->title ?></h2>
        <div class="framed_content user_signature">
            <?= $author->signature ?>
        </div>
    </section>
    
    <section>
        <h2><?= $current_module->language->user_profile_page->bio->title ?></h2>
        <div class="framed_content user_bio">
            <?= $author->bio ?>
        </div>
    </section>
    
</div>

<? if( $author->id_account != $account->id_account ): ?>
    <section>
        <h2><?= replace_escaped_vars($language->contact->contact_user, '{$display_name}', $author->get_processed_display_name()) ?></h2>
        <div class="framed_content">
            <ul>
                <li>
                    <span class="pseudo_link disabled">
                        <?= replace_escaped_vars( $language->contact->pm->title, '{$website_name}', $settings->get("engine.website_name") ) ?>
                    </span>
                </li>
                <li>
                    <span class="pseudo_link disabled">
                        <?= $language->contact->email->title ?>
                    </span>
                </li>
            </ul>
        </div>
    </section>
<? endif; ?>

