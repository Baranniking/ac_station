#include "ui.h"

TFT_eSPI tft;

void displayBegin(){
tft.init();
tft.setRotation(1);
tft.fillScreen(TFT_BLACK);
}

void gridStatus(bool gridStat){
tft.fillRect(290, 10, 15, 15, gridStat ? TFT_GREEN : TFT_RED);
}

void drawVoltageValue(uint16_t colorBack, uint16_t colorText, uint16_t colorBar, float voltageValue, float currentValue, float powerValue){
tft.fillScreen(colorBack);
tft.setTextSize(3);
tft.setTextColor(colorText, colorBack);
tft.setCursor(20, 32);
tft.print("Valtage: ");
tft.print(voltageValue, 1);
tft.setCursor(20, 64);
tft.print("Currtent: ");
tft.print(currentValue, 1);
tft.setCursor(20, 96);
tft.print("Power: ");
tft.print(powerValue, 1);



}