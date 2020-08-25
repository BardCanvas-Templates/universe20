<?
/**
 * Alternate menu
 *
 * @package    Universe20 template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

$markup = get_items_for_alt_menu($template->build_menu_items("priority"));
if( empty($markup) ) return;
?>

<style type="text/css">
    #alt_menu                         { text-align: center; background: rgba(0, 0, 0, 0.25);
                                        margin: 0; border: 1px solid black;
                                        font-family: Arial, Arial, Helvetica, sans-serif; font-size: 10pt; }
    #header #alt_menu .main_menu_item { line-height: 20px !important; display: inline-block !important;
                                        padding: 5px 10px !important; }
    body.main  #alt_menu              ,
    body.admin #alt_menu              { border-radius: 0; margin: 0;
                                        border-left: none; border-right: 0; border-bottom: 0; }
</style>

<div id="alt_menu">
    <?= $markup ?>
</div>
