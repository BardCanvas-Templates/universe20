<?php

global $settings;

$title   = $settings->get("templates:universe20.features_title");
$icons   = array();
$markups = array();

$segments = array("top", "right", "bottom", "left");
foreach($segments as $segment)
{
    $icon   = $settings->get("templates:universe20.features_{$segment}_icon");
    $markup = $settings->get("templates:universe20.features_{$segment}_markup");
    
    if( empty($icon) || empty($markup) ) continue;
    
    $icons[$segment]   = $icon;
    $markups[$segment] = $markup;
}

if( empty($title) ) return;
if( count($icons) == 0 ) return;

$index = 0;
?>

<div id="u20_template_features">
    <h2 class="line-below"><?= $title ?></h2>
    <div class="workarea">
        <div class="border"></div>
        <? foreach($segments as $segment): ?>
            <div class="markup <?= $segment ?>" style="<? if($segment == "top") echo "display: block;"; ?>"
                 data-segment="<?= $segment ?>">
                <div class="caption">
                    <?= $markups[$segment] ?>
                </div>
            </div>
        <? endforeach; ?>
        
        <? foreach($segments as $segment): ?>
            <div class="icon <?= $segment ?> <? if($segment == "top") echo "active"; ?>"
                 data-segment="<?= $segment ?>" data-index="<?= $index++ ?>"
                 onmouseover="stop_service_rotator(); u20tpl_show_feature(this);"
                 onclick="stop_service_rotator(); u20tpl_show_feature(this);"
                 onmouseout="start_service_rotator()">
                <i class="fa fa-<?= $icons[$segment] ?> fa-fw"></i>
            </div>
        <? endforeach; ?>
    </div>
</div>

<script type="text/javascript">
    function u20tpl_show_feature(e)
    {
        var $container = $('#u20_template_features');
        var $trigger   = $(e);
        var segment    = $trigger.attr('data-segment');
        
        $container.find(sprintf('.workarea .icon:not([data-segment="%s"])', segment)).toggleClass('active', false);
        $container.find(sprintf('.workarea .markup:not([data-segment="%s"])', segment)).fadeOut('fast');
        
        $trigger.toggleClass('active', true);
        $container.find(sprintf('.workarea .markup[data-segment="%s"]', segment)).fadeIn('fast');
        
        current_service_checked = parseInt( $trigger.attr('data-index') );
    }
    
    var current_service_checked  = 0;
    var service_rotator_interval = null;
    function select_next_service() {
        var $items = $('#u20_template_features').find('.workarea .icon');
        
        current_service_checked++;
        if( current_service_checked > 3 ) current_service_checked = 0;
    
        u20tpl_show_feature( $items[current_service_checked] );
    }
    
    function stop_service_rotator()
    {
        clearInterval( service_rotator_interval );
    }
    
    function start_service_rotator()
    {
        service_rotator_interval = setInterval(select_next_service, 8000);
    }
    
    $(document).ready(function() { start_service_rotator(); });
</script>

<div id="u20_template_features_alt">
    <h2 class="line-below"><?= $title ?></h2>
    <table cellpadding="10" cellspacing="0" border="0">
        <? foreach($segments as $segment): ?>
        <tr valign="middle">
            <td class="icon">
                <i class="fa fa-<?= $icons[$segment] ?> fa-fw"></i>
            </td>
            <td class="caption">
                <?= $markups[$segment] ?>
            </td>
        </tr>
        <? endforeach; ?>
    </table>
    
</div>
