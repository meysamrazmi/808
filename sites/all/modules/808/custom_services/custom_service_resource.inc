<?php

function custom_service_resource_index($hash , $version){
    if(!(hash_true($hash , "preRequests"))) return "failed to access";
    if($version == 0){
        return ["forced_update" => false , "ebook_key" => "V7Tb7veIyyFjUAaG5tO4Tk2DqqeZqJqI"];
    }
    return "This version not supported";
}