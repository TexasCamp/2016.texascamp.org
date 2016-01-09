<?php
//$md_data = array(
//  'fields' => array(),
//  'data_filter' => '',
//  'class_link' => '',
//  'href' => ''
//);
//dsm($md_data);
?>
<li class="cbp-item <?php print $md_data['data_filter'];?> <?php print $md_data['md_level_height'];?>">
    <?php
      if(count($md_data['images']) != 0){
        foreach($md_data['images'] as $field_name => $field_image){
          print '<div class="cbp-caption '.$md_data['class_link'].'" '.$md_data['href'].' >';
          print '    <div class="cbp-caption-defaultWrap ">';
          print '      <img src="'.$field_image['url'].'">';
          print '    </div>';
          print '    <div class="cbp-caption-activeWrap">';
          print '     <div class="cbp-l-caption-alignCenter">';
          print '       <div class="cbp-l-caption-body">';
          if(count($field_image['fields_display']) !=0 ){
            foreach($field_image['fields_display'] as $field_img_display_name => $field_img_display_content){
              print $field_img_display_content;
            }
          }
          print '       </div>';
          print '      </div>';
          print '    </div>';
          print '  </div>';
        }
      }
  //render field default
    if(count($md_data['fields']) != 0){
      foreach($md_data['fields'] as $key => $field){
        if($field['display'] == 1){
          print $field['content'];
        }
      }
    }
  ?>
</li>

