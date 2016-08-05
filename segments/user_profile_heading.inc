<?php
/**
 * Base template - User profile heading
 *
 * @package    HNG2
 * @subpackage core
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 * 
 * @var account           $account
 * @var config            $config
 * @var template          $template
 * @var account           $author
 * @var \SimpleXMLElement $language
 */

use hng2_base\account;
use hng2_base\config;
use hng2_base\template;

$author = $template->get("user_profile_account");
?>

<div id="user_profile_area">
    
    <div class="avatar"><img src="<?= $author->get_avatar_url() ?>"></div>
    <div id="user_profile_heading" style="background-image: url('<?= $author->get_profile_banner_url() ?>')">
        <div class="details">
            <div class="display_name"><?= $author->get_processed_display_name() ?></div>
            <div class="handler">@<?= $author->user_name ?></div>
            <div class="extras">
                <? if($author->id_account == $account->id_account): ?>
                    <button class="pull-right" onclick="location.href = $_FULL_ROOT_PATH + '/accounts/edit_account.php';">
                        <span class="fa fa-pencil"></span>
                        <?= $language->edit_profile ?>
                    </button>
                <? else: ?>
                    <span class="pull-right">
                        <button disabled title="<?= $language->contact->pm->title ?>">
                            <span class="fa fa-inbox"></span>
                            <?= $language->contact->pm->caption ?>
                        </button>
                        <button disabled title="<?= replace_escaped_vars( $language->contact->pm->title, '{$website_name}', $settings->get("engine.website_name") ) ?>">
                            <span class="fa fa-envelope"></span>
                            <?= $language->contact->email->caption ?>
                        </button>
                    </span>
                <? endif; ?>
                <?= $config->user_levels_by_level[$author->level] ?>
                &bull;
                <?= $language->last_seen . " " . $author->get_last_activity(true) ?>
            </div>
        </div>
    </div>
    
    <div id="user_profile_tabs">
        <?
        $tabs = array();
        foreach($modules as $module)
        {
            if( isset($module->language->user_profile_tabs) )
            {
                foreach($module->language->user_profile_tabs->tab as $tab)
                {
                    $priority = isset($tab["priority"]) ? (int) $tab["priority"] : 100;
                    
                    $tabs[trim($tab["mode"])] = sprintf("%03.0f", $priority) . "\t" . trim($tab);
                }
            }
        }
        asort($tabs);
        
        foreach($tabs as $key => $caption)
        {
            $caption = end(explode("\t", $caption));
            $url = "{$config->full_root_path}/author/{$author->user_name}/" . str_replace("@root", "", $key);
            $current = $template->get("current_user_profile_tab") == $key ? "current" : "";
            echo "<a class='tab {$current}' href='{$url}'>{$caption}</a>";
        }
        ?>
    </div>
    
</div>