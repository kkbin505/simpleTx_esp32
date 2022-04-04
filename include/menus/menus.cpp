
//menu code based on work from:
//https://www.youtube.com/watch?v=fjsmVzMdqyU
//https://drive.google.com/drive/folders/1w3jhBr031lmTeeE9Du9uZkYuoHx6m21P
//dsnmechanic@gmail.com 
//instagram: dsnmechanics

#include <Arduino.h>
#include "oled.h"
#include "gpio/gpio.cpp"

 

void displayMenu(char * name,crsf_param_t *crsf_p,int num) { 
  display.println(name);

  char * menu_item;
  uint8_t menu_item_id;
  int page_off = num%5;

  int page = (selected/5);
  int offset = num-5;
  int start = page*5;
  int max = (num-offset)*(page+1);
  if (max>num) max = num;
  if (selected>=num) selected = 0;
  display.printf("%i:%i:%i:%i:%i:%i \n",
  selected,offset,page_off,max,page,start);
  
  for (int i = start; i < max; i++) {
    if (i == selected)
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    else if (i != selected)
      display.setTextColor(SSD1306_WHITE);
    
    menu_item = crsf_p[i].name;
    menu_item_id = crsf_p[i].id;
    //TODO options
    display.printf("%s\n",menu_item);
  }
   if (offset>0) {
    display.setTextColor(SSD1306_WHITE);
    display.printf("... \n");
  } 
}
void displaySubmenu(crsf_param_t *cv, int num_items,char *opt_list[20],int count) { 
    display.println("CRSF config");
    display.printf("%s options:\n",cv[selected].name);
    display.println("");
    
  for (int i = 0; i < count; i++)
  {    
    db_out.printf("lines %s\n",opt_list[i]);
    display.printf("%s\n",opt_list[i]);

  }
  
    

}
void updateDisplay(
                    int8_t tx_rssi,
                    uint8_t tx_lq,
                    uint8_t rf_mode,
                    uint8_t tx_pwr,
                    int8_t rx_rssi_1,
                    int8_t rx_rssi_2,
                    uint8_t rx_lq, 
                    uint8_t batteryVoltage,
                    uint8_t bpkts,
                    uint16_t gpkts,
                    char * name,
                    module_type_t typeModule,
                    int num_menu_item,
                    crsf_param_t *cv,
                    char *opt_list[20],
                    int count,
                    int entered  ) {

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
     
  if (entered == -1) {
    displayMenu(name,cv,num_menu_item);
  }
  else if (entered == -2) {
    //display.println(F("main"));
    //updateDisplay();
    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    char * typeModName;
      if (typeModule==1) typeModName =  (char *)"elrs";
    display.printf("%s:%s",name,typeModName);
    display.println("");
    display.printf("Tx %idBm %i:%i%% ",tx_rssi,rf_mode,tx_lq);
    display.println("");
    display.println("");
    display.printf("Rx %idBm %i:%i%% ",rx_rssi_1,rf_mode,rx_lq);
    display.setTextSize(2);
    display.println("");
    display.printf("%imW", tx_pwr);
    float vBat = (float)batteryVoltage/10;
    display.printf("%4.1fv",vBat);
    display.println();             // Start at top-left corner
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.printf("%u:%u",bpkts,gpkts);
  } else {
    displaySubmenu(cv,num_menu_item,opt_list,count);
  }
  display.display();
  //delay(200);
}