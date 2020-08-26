<?
/**
 * Embeddable stand-alone multi purpose
 *
 * @package    Universe20 template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

use hng2_tools\internals;

$template->init(__FILE__);
$account->ping();

header("Content-Type: text/html; charset=utf-8"); ?>

<div id="embedded_content">
    <? include "{$current_module->abspath}/{$template->page_contents_include}"; ?>
</div>

<? internals::render(__FILE__); ?>
