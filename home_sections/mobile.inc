<?php

global $settings;

$markup = $settings->get("templates:universe20.mobile_left");
$shot   = $settings->get("templates:universe20.mobile_shot");
$height = $settings->get("templates:universe20.mobile_height");
if( empty($height) ) $height = 400;

if( empty($markup) || empty($shot) ) return;
?>

<div id="u20_template_mobile">
    <div class="shot" style="height: <?= $height?>px; line-height: <?= $height?>px; background-image: url('<?= $shot ?>');">
        <div class="markup">
            <?= $markup ?>
        </div>
        <div class="image">
            <img src="<?= $shot ?>">
        </div>
    </div>
</div>
