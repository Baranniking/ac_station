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

void drawChargeValue(uint16_t colorBack, uint16_t colorText, uint16_t colorBar, float voltageValue, float currentValue, float powerValue){
tft.fillScreen(colorBack);
tft.drawRect(5, 5, 315, 230, TFT_WHITE);
tft.drawLine(157, 5, 157, 95, TFT_WHITE);
tft.drawLine(5, 35, 320, 35, TFT_WHITE);
tft.drawLine(5, 65, 320, 65, TFT_WHITE);
tft.drawLine(5, 95, 320, 95, TFT_WHITE);
tft.drawLine(5, 200, 320, 200, TFT_WHITE);

tft.setTextSize(2);
tft.setTextColor(colorText, colorBack);
tft.setCursor(15, 15);
tft.print("Valtage: V");
tft.setCursor(200, 15);
tft.print(voltageValue, 1);

tft.setCursor(15, 45);
tft.print("Current: A");
tft.setCursor(200, 45);
tft.print(currentValue, 1);

tft.setCursor(15, 75);
tft.print("Power: W");
tft.setCursor(200, 75);
tft.print(powerValue, 1);

tft.setCursor(140, 210);
tft.print("Main");




}