<?php
/**
 * Base template - Common header
 *
 * @package    HNG2
 * @subpackage core
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *             
 * @var template $template
 * @var settings $settings
 * @var config   $config
 * @var account  $account
 */

use hng2_base\account;
use hng2_base\config;
use hng2_base\settings;
use hng2_base\template;
?>

<!-- Base metas -->
<meta name="viewport"              content="width=device-width, initial-scale=1">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta http-equiv="Content-Type"    content="text/html; charset=utf-8">
<meta charset="UTF-8">

<title><?= $template->get_page_title() ?></title>

<link rel="icon"          type="image/x-icon" href="<?= $template->url ?>/media/favicon.ico">
<link rel="shortcut icon" type="image/x-icon" href="<?= $template->url ?>/media/favicon.ico">

<!-- Defaults -->
<script type="text/javascript">
    var $_FULL_ROOT_PATH          = '<?= $config->full_root_path ?>';
    var $_PHP_SELF                = '<?= $_SERVER["PHP_SELF"] ?>';
    var $_CURRENT_USER_ID_ACCOUNT = '<?= $account->id_account ?>';
    var $_CURRENT_USER_LANGUAGE   = '<?= $_COOKIE["{$config->website_key}_UL"] ?>';
    var $_CURRENT_USER_LEVEL      = parseInt('<?= $account->level ?>');
    var $_CURRENT_USER_IS_ADMIN   = <?= $account->_is_admin ? "true" : "false" ?>;
    var $_TEMPLATE_URL            = '<?= $template->url ?>';
    var $_SCRIPTS_VERSION         = '<?= $config->scripts_version ?>';
    
    var $_MAIN_MENU_AUTO_COLLAPSE_WIDTH = parseInt('<?= (int) $settings->get("engine.main_menu_auto_collapse_width", 700) ?>');

    var tinymce_full_toolbar     = 'bold italic underline strikethrough forecolor backcolor fontsizeselect removeformat | blockquote hr alignleft aligncenter alignright | outdent indent bullist numlist | link unlink';
    var tinymce_standard_toolbar = 'bold italic underline strikethrough forecolor backcolor removeformat | blockquote hr | outdent indent | link unlink';
    var tinymce_minimal_toolbar  = 'bold italic underline strikethrough forecolor backcolor removeformat | hr | link unlink';
    var tinymce_default_css_files = [
        $_FULL_ROOT_PATH  + '/media/styles~v' + $_SCRIPTS_VERSION + '.css',
        $_TEMPLATE_URL    + '/media/styles~v' + $_SCRIPTS_VERSION + '.css',
        $_TEMPLATE_URL    + '/media/post_styles~v' + $_SCRIPTS_VERSION + '.css'
    ];
    var tinymce_custom_plugins = [];
    var tinymce_custom_toolbar_buttons = [];
</script>
<script type="text/javascript" src="<?= $config->full_root_path ?>/media/defaults~v<?=$config->scripts_version?>.js"></script>

<!-- jQuery -->
<script type="text/javascript" src="<?= $config->full_root_path ?>/lib/jquery-1.11.0.min.js"></script>
<script type="text/javascript" src="<?= $config->full_root_path ?>/lib/jquery-migrate-1.2.1.js"></script>
<script type="text/javascript" src="<?= $config->full_root_path ?>/lib/jquery.cookie.js"></script>

<!-- jQuery UI -->
<script type="text/javascript"          src="<?= $config->full_root_path ?>/lib/jquery-ui-1.10.4.custom.min.js"></script>
<link rel="stylesheet" type="text/css" href="<?= $config->full_root_path ?>/lib/jquery-ui-themes-1.10.4/blitzer/jquery-ui.css">
<script type="text/javascript"          src="<?= $config->full_root_path ?>/lib/jquery.ui.touch-punch.min.js"></script>

<!-- UI Additions -->
<link rel="stylesheet" type="text/css" href="<?= $config->full_root_path ?>/lib/font-awesome-4.6.3/css/font-awesome.css">
<link rel="stylesheet" type="text/css" href="<?= $config->full_root_path ?>/lib/prettyPhoto_compressed_3.1.6/css/prettyPhoto.css">
<script type="text/javascript"          src="<?= $config->full_root_path ?>/lib/prettyPhoto_compressed_3.1.6/js/jquery.prettyPhoto.js"></script>
<script type="text/javascript" charset="utf-8"> $(document).ready(function(){ $(".prettyPhoto").prettyPhoto({social_tools: false}); }); </script>
<script type="text/javascript"          src="<?= $config->full_root_path ?>/lib/sprintf.js"></script>
