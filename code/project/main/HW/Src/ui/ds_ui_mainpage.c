
#include <string.h>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "../../Inc/screen/d_screen.h"
#include "../../Inc/spi/d_spi.h"
#include "../../Inc/ui/ds_ui_page_manage.h"
#include "../../Inc/d_system_data.h"
#include "../../Inc/data/ds_data_num.h"
#include "../../Inc/data/ds_data_icon.h"

#include "../../Inc/draw/ds_paint.h"
#include "../../Inc/ui/ds_ui_mainpage.h"
#include "../../Inc/data/ds_data_page.h"
//#include "ds_wifi_ap_sta.h"

void ds_ui_back_main_page(void){
    unsigned int i;
	for(i=0;i<5000;i++){
		spi_send_data(gImage_main_page[i]);  
	} 
}

void ds_screen_display_main(){
	//if(get_wifi_sta_status() == WIFI_STA_MODE_CONNECT_SUCCESS){
		//ds_screen_full_display_bydata(ds_screen_full_display_data,gImage_main_page_wifi);
	//}else
		ds_screen_full_display_bydata(ds_screen_full_display_data,gImage_main_page);
}  

void ds_screen_setting(){
	ds_screen_full_display_bydata(ds_screen_full_display_data,gImage_setting_page);
	
}

void ds_screen_desktop(){
	ds_screen_full_display_bydata(ds_screen_full_display_data,gImage_Desktop_page);
}
