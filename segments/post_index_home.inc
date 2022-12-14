<?php
/**
 * Posts index for the home layout
 * 
 * @var template   $template
 * @var posts_data $posts_data
 */

use hng2_base\template;
use hng2_modules\posts\posts_data;

$has_featured_posts = count($posts_data->featured_posts) > 0 ? "true" : "false";
?>

<div id="home_index_wrapper" data-with-featured-posts="<?= $has_featured_posts ?>" class="clearfix">
    
    <? if( empty($_GET["offset"]) ): ?>
        <h1><?= $template->language->latest_news ?></h1>
    <? endif; ?>
    
    <? if( $has_featured_posts == "true" ) include __DIR__ . "/home_featured_posts.inc"; ?>
    
    <div id="posts_index_wrapper">
        <?
        $template->set("pagination_url_prefix", "$config->full_root_url/");
        
        include __DIR__ . "/post_index_renderer.inc";
        ?>
    </div>
    
</div>
