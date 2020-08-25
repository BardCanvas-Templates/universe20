<?php

include_once ROOTPATH . "/lib/phpQuery-onefile.php";

function add_admin_menu_items_to_header_menu()
{
    global $modules, $current_module, $config, $template, $account;
    
    foreach($modules as $module_name => $this_module)
    {
        if( ! $account->has_admin_rights_to_module($module_name) ) continue;
        
        if(is_array($this_module->menu_items) || is_object($this_module->menu_items))
        {
            foreach($this_module->menu_items->item as $this_menu_item)
            {
                $strict_item_level = trim($this_menu_item["strict_admin_level"]);
                if( ! empty($strict_item_level) &&  $account->level < $strict_item_level ) continue;
                
                $item_url    = trim($this_menu_item->url);
                $added_class = ($module_name == $current_module->name && stristr($_SERVER["PHP_SELF"], "/$module_name/$item_url") !== false) ? "current" : "";
                $url         = "{$config->full_root_path}/$module_name/$item_url";
                $caption     = $this_module->language->admin->menu_items->{$this_menu_item->caption_language_var};
                $icon        = empty($this_module->language->icon) ? "fa-circle-o" : trim($this_module->language->icon);
                
                $html = "
                    <a class='main_menu_item highlighted $added_class' href='$url'>
                        <span class='fa {$icon}'></span> $caption
                    </a>
                ";
                
                $template->add_menu_item(
                    $caption,
                    $html,
                    0
                );
            }
        }
    }
    
}


function remove_items_for_alt_menu($markup)
{
    global $settings;
    
    if( empty($markup) ) return "";
    
    $raw_selectors = $settings->get("templates:universe20.alt_menu_selectors");
    if( empty($raw_selectors) ) return $markup;
    
    $selectors = explode("\n", $raw_selectors);
    
    $pq = phpQuery::newDocumentHTML($markup);
    foreach($selectors as $selector)
        $pq->find($selector)->remove();
    
    return $pq->html();
}

function get_items_for_alt_menu($markup)
{
    global $settings;
    
    if( empty($markup) ) return "";
    
    $raw_selectors = $settings->get("templates:universe20.alt_menu_selectors");
    if( empty($raw_selectors) ) return "";
    
    $selectors = explode("\n", $raw_selectors);
    $output    = "";
    
    $pq = phpQuery::newDocumentHTML($markup);
    foreach($selectors as $selector)
        $output .= $pq->find($selector)->htmlOuter();
    
    # echo "<pre>" . htmlspecialchars($markup) . "</pre>";
    # echo "<pre>" . htmlspecialchars($output) . "</pre>";
    return trim($output);
}
