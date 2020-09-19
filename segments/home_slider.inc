<?php
/**
 * Posts index renderer - slider on the home page
 *
 * @var config     $config
 * @var template   $template
 * @var module[]   $modules
 * @var module     $this_module
 */

use hng2_base\config;
use hng2_base\module;
use hng2_base\template;
use hng2_modules\posts\posts_repository;

if( $template->get("exclude_home_slider") ) return;

$cache_ver = (int) $settings->get("templates:universe20.slider_cache_version");
$cache_ttl = (int) $settings->get("templates:universe20.slider_cache_ttl");
$cache_key = "universe20_template.slider/v{$this_module->version}-$cache_ver";

if( $cache_ttl > 0 )
{
    $code = $mem_cache->get($cache_key);
    
    if( $code == "empty" ) return;
    
    if( ! empty($code) )
    {
        echo "
            <!-- @caching: Universe20 slider pre-cached segment v{$this_module->version}-{$cache_ver} start -->
            $code
            <!-- @caching: Universe20 slider pre-cached segment end -->
        ";
        
        return;
    }
}

$this_module   = $modules["posts"];
$repository    = new posts_repository();

$slider_filter     = array("status" => "published", "visibility" => "public");
$slider_categories = trim($settings->get("modules:posts.slider_categories"));

$or    = array();
$lines = explode("\n", $slider_categories);
foreach($lines as $line)
{
    if( substr($line, 0, 1) == "#" ) continue;
    
    list($slug, $ttl) = explode(" - ", $line);
    $slug = trim($slug);
    $ttl  = trim($ttl); if( empty($ttl) ) $ttl = 0;
    
    if( $ttl == 0 )
    {
        $or[] = "main_category in (select id_category from categories where categories.slug = '$slug')";
    }
    else
    {
        $boundary = date("Y-m-d H:i:s", strtotime("now - $ttl hours"));
        $or[] = "(
               main_category in (select id_category from categories where categories.slug = '$slug')
               and posts.publishing_date >= '$boundary'
        )";
    }
}
$slider_filter[] = "\n# Slider posts start\n(\n" . implode("\nOR\n", $or) . "\n# Slider posts end\n)";

$slider_posts = $repository->find($slider_filter, 0, 0, "title asc");
if( empty($slider_posts) )
{
    if( $cache_ttl > 0 )
    {
        $code = "empty";
        
        $cache_ver++;
        $cache_key = "universe20_template.slider/v{$this_module->version}-$cache_ver";
        $mem_cache->set($cache_key, $code, 0, $cache_ttl * 60 * 60);
        $settings->set("templates:universe20.slider_cache_version", $cache_ver);
    }
    
    return;
}

$adaptive_height = "false";
$slider_height   = "max-height: calc(100vh - 40px);";

$input_height = (int) $settings->get("templates:universe20.slider_height");
if( $input_height > 0 )
{
    $adaptive_height = "false";
    $slider_height   = "height: {$input_height}px;";
}

if( $cache_ttl > 0 ) ob_start();
?>

<script type="text/javascript" src="<?= $config->full_root_path ?>/lib/jquery-bxslider/jquery.bxslider.js"></script>
<link rel="stylesheet" type="text/css" href="<?= $config->full_root_path ?>/lib/jquery-bxslider/jquery.bxslider.css">

<script type="text/javascript">
    $(document).ready(function()
    {
        window.__slider = $('#posts_slider').bxSlider({
            mode: 'horizontal',
            startSlide: 0,
            captions: false,
            adaptiveHeight: <?= $adaptive_height ?>,
            responsive: true,
            touchEnabled: true,
            pause: 10000,
            
        });
        
        $(window).resize(function() { window.__slider.redrawSlider(); });
    });
</script>

<link href="https://fonts.googleapis.com/css2?family=Noto+Serif:ital,wght@0,400;0,700;1,400;1,700&display=swap" rel="stylesheet">
<style type="text/css">
    #posts_slider         { font-family: 'Noto Serif', 'Times New Roman', 'Times Roman', serif; font-size: 14pt; }
    #posts_slider         { margin-top: 0; margin-bottom: 20px; padding: 0; background-color: transparent;
                            color: rgba(255, 255, 255, .7); text-shadow: 1px 1px 3px black; }
    #posts_slider li      { padding: 20px 60px 0 60px; }
    .bx-wrapper           { background: transparent; border: none; box-shadow: none; margin-bottom: 0; }
    .bx-viewport          { <?= $slider_height ?> }
    .bx-wrapper .bx-pager { bottom: 5px; padding-top: 0; }
</style>

<ul id="posts_slider">
    
    <?
    $config->globals["modules:posts.working_posts_set"] =& $slider_posts;
    $this_module->load_extensions("front", "index_renderer_before_slider_loop_start");
    
    $index = 1;
    foreach($slider_posts as $post)
    {
        $back_image = "";
        $post_image = "";
        if( ! empty($post->featured_image_path) )
        {
            $back_image = $post_image = "{$config->full_root_path}{$post->featured_image_path}";
        }
        elseif( ! empty($post->featured_image_thumbnail) )
        {
            $back_image = "{$config->full_root_path}{$post->featured_image_thumbnail}";
            $post_image = "{$config->full_root_path}{$post->featured_image_thumbnail}";
        }
        else
        {
            $default = $settings->get("modules:accounts.default_profile_banner");
            if( empty($default) ) $default = "media/default_user_banner.jpg";
            
            $back_image = "{$config->full_root_path}{$default}";
            $post_image = "{$config->full_root_path}/media/spacer.png";
        }
        
        $contents = $post->content;
        $contents = convert_shortcodes($contents);
        $contents = convert_emojis($contents);
        
        $style = $index > 1 ? "display: none" : "";
        $index++;
        
        echo "<li>$contents</li>";
    }
    ?>
    
</ul>
<?
if( $cache_ttl > 0 )
{
    $code = ob_get_clean();
    
    $cache_ver++;
    $cache_key = "universe20_template.slider/v{$this_module->version}-$cache_ver";
    $mem_cache->set($cache_key, $code, 0, $cache_ttl * 60 * 60);
    $settings->set("templates:universe20.slider_cache_version", $cache_ver);
    echo "
        <!-- @caching: Universe20 slider freshly cached segment v{$cache_ver} start -->
        $code
        <!-- @caching: Universe20 slider freshly cached segment end -->
    ";
}
