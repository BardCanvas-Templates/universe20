<?php

global $settings;

$title = $settings->get("templates:universe20.staff_title");
if( empty($title) ) return;

$persons = array();
for($c = 1; $c <= 4; $c++)
{
    $name = $settings->get("templates:universe20.staff_{$c}_name");
    $link = $settings->get("templates:universe20.staff_{$c}_link");
    $pic  = $settings->get("templates:universe20.staff_{$c}_picture");
    
    if( empty($name) || empty($pic) ) continue;
    
    $persons[] = (object) array(
        "name" => explode("\n", $name),
        "link" => $link,
        "pic"  => $pic
    );
}
if( count($persons) == 0 ) return;

$td_width = round(70 / count($persons), 3);
?>

<div id="u20_template_staff">
    
    <div class="title" style="width: 30%">
        <div class="text">
            <?= $title ?>
        </div>
    </div>
    
    <? foreach($persons as $person): ?>
        <a class="item" <? if( ! empty($person->link) ) echo "href='$person->link'"; ?> target="_blank"
           style="width: <?= $td_width ?>%" >
            <img src="<?= $person->pic ?>">
            <span class="info">
                <span class="name ellipsified"><?= $person->name[0] ?></span><br>
                <span class="pos ellipsified"><?= $person->name[1] ?></span>
            </span>
        </a>
    <? endforeach ?>
    
</div>
