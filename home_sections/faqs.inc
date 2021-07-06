<?php
use hng2_modules\posts\posts_repository;

global $settings;

$cache_ver = (int) $settings->get("templates:universe20.faqs_cache_version");
$cache_ttl = (int) $settings->get("templates:universe20.faqs_cache_ttl");
$cache_key = "universe20_template.faqs/v{$this_module->version}-$cache_ver";

if( $cache_ttl > 0 )
{
    $code = $mem_cache->get($cache_key);
    
    if( $code == "empty" ) return;
    
    if( ! empty($code) )
    {
        echo "
            <!-- @caching: Universe20 FAQs pre-cached segment v{$this_module->version}-{$cache_ver} start -->
            $code
            <!-- @caching: Universe20 FAQs pre-cached segment end -->
        ";
        
        return;
    }
}

$category = $settings->get("templates:universe20.faqs_category");
if( empty($category) ) return;

$repository = new posts_repository();

$filter = array("main_category" => $category, "visibility" => "public", "status" => "published");
$limit  = $settings->get("templates:universe20.faqs_limit");
$order  = $settings->get("templates:universe20.faqs_order");

if( empty($limit) ) $limit = 5;

switch($order)
{
    case "":        $order = "publishing_date asc";              break;
    case "newer":   $order = "publishing_date desc";             break;
    case "popular": $order = "views desc, publishing_date desc"; break;
}


$faqs = $repository->find($filter, $limit, 0, $order);
if( count($faqs) == 0 )
{
    if( $cache_ttl > 0 )
    {
        $code = "empty";
        
        $cache_ver++;
        $cache_key = "universe20_template.faqs/v{$this_module->version}-$cache_ver";
        $mem_cache->set($cache_key, $code, 0, $cache_ttl * 60 * 60);
        $settings->set("templates:universe20.faqs_cache_version", $cache_ver);
    }
    
    return;
}

if( $cache_ttl > 0 ) ob_start();
?>

<script type="text/javascript">
    function toggle_faq_item(e)
    {
        var $item  = $(e).closest('.faq_item');
        var index  = $item.attr('data-index');
        var others = sprintf('.faq_item:not([data-index="%s"])', index);
        
        $item.toggleClass('expanded');
        $item.closest('.faqs_container').find(others).removeClass('expanded');
    }
</script>

<div id="u20_template_faqs">
    
    <h1 class="line-below"><?= $template->language->faqs ?></h1>
    
    <div class="faqs_container">
        
        <?
        $index = 1;
        foreach($faqs as $faq):
            ?>
            <div class="faq_item" data-index="<?= $index ?>">
                <div class="trigger clearfix" onclick="toggle_faq_item(this)">
                    <span class="icon">
                        <i class="expand   fa fa-chevron-down fa-fw"></i>
                        <i class="collapse fa fa-chevron-up   fa-fw"></i>
                    </span>
                    <span class="number"><?= $index ?>.</span>
                    <span class="title"><?= $faq->title ?></span>
                </div>
                <div class="excerpt">
                    <div>
                        <?= $faq->excerpt ?>
                    </div>
                    <div align="right" style="margin-top: 10px;">
                        <a href="<?= $faq->get_permalink() ?>">
                            <?= $template->language->read_more ?> <i class="fa fa-chevron-right"></i>
                        </a>
                    </div>
                </div>
            </div>
            <?
            $index++;
        endforeach; ?>
        
    </div>
    
</div>

<?
if( $cache_ttl > 0 )
{
    $code = ob_get_clean();
    
    $cache_ver++;
    $cache_key = "universe20_template.faqs/v{$this_module->version}-$cache_ver";
    $mem_cache->set($cache_key, $code, 0, $cache_ttl * 60 * 60);
    $settings->set("templates:universe20.faqs_cache_version", $cache_ver);
    echo "
        <!-- @caching: Universe20 FAQs freshly cached segment v{$cache_ver} start -->
        $code
        <!-- @caching: Universe20 FAQs freshly cached segment end -->
    ";
}
