#include "ui.h"
#include <daly-bms-uart.h>


TFT_eSPI tft;

bool dischargeStatus = false;
static ScreenState currentScreen = SCREEN_MAIN;
static ScreenState lastScreen = SCREEN_CHARGE;

void setCurrentScreen(ScreenState newScreen){
    currentScreen = newScreen;
}




ScreenState getCurrentScreen(){
    return currentScreen;
}

void updateScreen(){
    if(currentScreen != lastScreen){
        lastScreen = currentScreen;

        switch(currentScreen)
        {
            case SCREEN_MAIN:
            drawMainMenu(TFT_RED);
            drawBulb(30, 30, dischargeStatus);
            break;

            case SCREEN_CHARGE:
            drawChargeMenu(TFT_GREEN, TFT_RED, TFT_CYAN);
            break;

            case SCREEN_SETTINGS:
            drawSettingsMenu();
        }
    }
}

void displayBegin(){
tft.init();
tft.setRotation(1);
tft.fillScreen(TFT_BLACK);

}

void gridStatus(bool gridStat){
tft.fillRect(290, 10, 15, 15, gridStat ? TFT_GREEN : TFT_RED);
}

void drawMainMenu(uint16_t colorCircle){
    tft.fillScreen(TFT_BLACK);
    tft.drawCircle(160, 120, 118, colorCircle);
    tft.drawCircle(160, 120, 80, colorCircle);

    
    tft.fillCircle(290, 30, 30, TFT_RED);
    tft.fillCircle(30, 210, 30, TFT_RED);
    tft.fillCircle(290, 210, 30, TFT_RED);
}
void drawMainValue(uint16_t colorText, uint8_t volBat){
    tft.setTextSize(6);
    tft.setTextColor(colorText, TFT_BLACK);
    tft.setCursor(120, 100);
    tft.print(volBat);
    tft.print("%");
}

void drawChargeMenu(uint16_t colorVoltage, uint16_t colorCurrent, uint16_t colorPower){
tft.fillScreen(TFT_BLACK);
tft.drawRect(5, 5, 315, 230, TFT_WHITE);
tft.drawLine(157, 5, 157, 95, TFT_WHITE);
tft.drawLine(5, 35, 320, 35, TFT_WHITE);
tft.drawLine(5, 65, 320, 65, TFT_WHITE);
tft.drawLine(5, 95, 320, 95, TFT_WHITE);
tft.drawLine(5, 200, 320, 200, TFT_WHITE);

tft.setTextSize(2);
tft.setTextColor(colorVoltage, TFT_BLACK);
tft.setCursor(15, 15);
tft.print("Valtage: V");

tft.setTextColor(colorCurrent, TFT_BLACK);
tft.setCursor(15, 45);
tft.print("Current: A");

tft.setTextColor(colorPower, TFT_BLACK);
tft.setCursor(15, 75);
tft.print("Power: W");


tft.setCursor(140, 210);
tft.print("Main");

}

void drawChargeValue(uint16_t colorBack, uint16_t colorText, float voltageValue, float currentValue, float powerValue, float socValue)
{
 tft.setTextSize(2);
 tft.setTextColor(colorText, colorBack);
 tft.setCursor(200, 15);
 tft.print(voltageValue, 1);

 tft.setCursor(200, 45);
 tft.print(currentValue, 1);

 tft.setCursor(200, 75);
 tft.print(powerValue, 1);

}

void drawSettingsMenu(){

}

void drawBulb(uint8_t x, uint8_t y, bool state){
    uint16_t color = state ? TFT_YELLOW : TFT_DARKGREY;
    // Колба лампы
    tft.fillCircle(x, y, 18, color);
    tft.drawCircle(x, y, 18, TFT_WHITE);

    // Нижняя часть колбы
    tft.fillRect(x - 10, y + 12, 20, 12, color);
    tft.drawRect(x - 10, y + 12, 20, 12, TFT_WHITE);

    // Цоколь
    tft.fillRect(x - 8, y + 24, 16, 10, TFT_LIGHTGREY);
    tft.drawRect(x - 8, y + 24, 16, 10, TFT_WHITE);

    // Резьба цоколя
    tft.drawLine(x - 8, y + 27, x + 8, y + 27, TFT_DARKGREY);
    tft.drawLine(x - 8, y + 30, x + 8, y + 30, TFT_DARKGREY);

    // Спираль внутри
    tft.drawLine(x - 6, y, x + 6, y, TFT_ORANGE);
    tft.drawLine(x - 4, y - 5, x + 4, y + 5, TFT_ORANGE);
}


