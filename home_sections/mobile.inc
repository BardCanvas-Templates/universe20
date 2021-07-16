<?php
global $settings;

if( $settings->get("templates:universe20.hide_all_home_sections_for_logged_in_users") == "true"
    && $account->_exists ) return;

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
