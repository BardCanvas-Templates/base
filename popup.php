<?
/**
 * Base template - Embedded layout
 *
 * @package    HNG2
 * @subpackage core
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

use hng2_tools\internals;

$template->init(__FILE__);

foreach($modules as $this_module)
    if( ! empty($this_module->template_includes->pre_rendering) )
        include "{$this_module->abspath}/contents/{$this_module->template_includes->pre_rendering}";

header("Content-Type: text/html; charset=utf-8"); ?>
<!DOCTYPE html>
<html>
<head>
    <? include __DIR__ . "/segments/common_header.inc"; ?>
    
    <!-- Others -->
    <script type="text/javascript" src="<?= $config->full_root_path ?>/lib/jquery.blockUI.js"></script>
    <script type="text/javascript" src="<?= $config->full_root_path ?>/lib/jquery.form.min.js"></script>
    
    <!-- Noty -->
    <script type="text/javascript" src="<?= $config->full_root_path ?>/lib/noty-2.3.7/js/noty/packaged/jquery.noty.packaged.min.js"></script>
    <script type="text/javascript" src="<?= $config->full_root_path ?>/lib/noty-2.3.7/js/noty/themes/default.js"></script>
    <script type="text/javascript" src="<?= $config->full_root_path ?>/media/noty_defaults~v<?=$config->scripts_version?>.js"></script>
    
    <!-- Core functions and styles -->
    <link rel="stylesheet" type="text/css" href="<?= $config->full_root_path ?>/media/styles~v<?=$config->scripts_version?>.css">
    <? if($account->_is_admin): ?><link rel="stylesheet" type="text/css" href="<?= $config->full_root_path ?>/media/admin~v<?=$config->scripts_version?>.css"><? endif; ?>
    <script type="text/javascript"          src="<?= $config->full_root_path ?>/media/functions~v<?=$config->scripts_version?>.js"></script>
    <script type="text/javascript"          src="<?= $config->full_root_path ?>/media/notification_functions~v<?=$config->scripts_version?>.js"></script>
    
    <!-- This template -->
    <link rel="stylesheet" type="text/css" href="<?= $template->url ?>/media/styles~v<?=$config->scripts_version?>.css">
    <link rel="stylesheet" type="text/css" href="<?= $template->url ?>/media/post_styles~v<?=$config->scripts_version?>.css">
    
    <!-- Per module loads -->
    <?
    foreach($modules as $this_module)
        if( ! empty($this_module->template_includes->html_head) )
            include "{$this_module->abspath}/contents/{$this_module->template_includes->html_head}";
    ?>
</head>
<body data-orientation="landscape" data-viewport-class="0" <?=$template->get("additional_body_attributes")?>  class="popup">

<div id="body_wrapper">
    
    <div id="content">
        <? include "{$current_module->abspath}/contents/{$template->page_contents_include}"; ?>
    </div><!-- /#content -->
    
    <?
    foreach($modules as $this_module)
        if( ! empty($this_module->template_includes->post_footer) )
            include "{$this_module->abspath}/contents/{$this_module->template_includes->post_footer}";
    ?>
    
</div><!-- /#body_wrapper -->

<? internals::render(__FILE__); ?>

</body>
</html>
