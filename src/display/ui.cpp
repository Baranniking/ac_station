#include "ui.h"
#include "config.h"
#include "iconChargeAv.h"
#include "iconInvertor.h"
#include "iconSettings.h"
#include "iconChargeManual.h"
#include "iconBattIcon.h"
TFT_eSPI tft;


bool stateChargeAu = false;
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
            drawMainMenu();
            break;

            case SCREEN_CHARGE:
            drawChargeMenu();
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

void drawMainMenu(){
     tft.fillScreen(TFT_BLACK);
     drawBulb(dischargeStatus);
     drawChargeAuIcon(stateChargeAu);
     drawSettingsIcon();
     drawChargeManualIcon();
     drawBattIcon();
    tft.drawLine(64, 64, 256, 64, TFT_DARKGREEN);
    tft.drawLine(74, 35, 246, 35, TFT_DARKGREEN);

}
void drawMainValue(uint16_t colorText, uint8_t volBat){
    tft.setTextSize(6);
    tft.setTextColor(colorText, TFT_BLACK);
    tft.setCursor(120, 100);
    tft.print(volBat);
    tft.print("%");
}

void drawChargeMenu()
{
    // фон
    tft.fillScreen(FALL_OUT_BG);

    // рамка и линии
    tft.drawRect(5, 5, 315, 230, FALL_OUT_COLOR);   // рамка
    tft.drawLine(157, 5, 157, 95, FALL_OUT_COLOR);  // вертикальная
    tft.drawLine(5, 35, 320, 35, FALL_OUT_COLOR);   // горизонтальные
    tft.drawLine(5, 65, 320, 65, FALL_OUT_COLOR);
    tft.drawLine(5, 95, 320, 95, FALL_OUT_COLOR);
    tft.drawLine(5, 200, 320, 200, FALL_OUT_COLOR);

    tft.setTextSize(2);

    // текст
    tft.setTextColor(FALL_OUT_COLOR, FALL_OUT_BG);
    tft.setCursor(15, 15);
    tft.print("Voltage: V");

    tft.setCursor(15, 45);
    tft.print("Current: A");

    tft.setCursor(15, 75);
    tft.print("Power: W");

    tft.setCursor(140, 210);
    tft.print("Main");
}


void drawChargeValue(float voltageValue, float currentValue, float powerValue, float socValue)
{

    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN, FALL_OUT_BG);

    tft.setCursor(200, 15);
    tft.print(voltageValue, 1);

    tft.setCursor(200, 45);
    tft.print(currentValue, 1);

    tft.setCursor(200, 75);
    tft.print(powerValue, 1);
}

void drawSettingsMenu(){

}

void drawBulb(bool state){
    tft.drawBitmap(0, 0, invertorIcon, 64, 64, state ? TFT_GREEN : TFT_DARKGREEN);
   
}

void drawChargeAuIcon(bool stateChargeAu){
    tft.drawBitmap(258, 0, charge_av, 64, 64, stateChargeAu ? TFT_GREEN : TFT_DARKGREEN);
}

void drawSettingsIcon(){
    tft.drawBitmap(0, 175, settingsIcon, 64, 64, TFT_DARKGREEN);
}

void drawChargeManualIcon(){
    tft.drawBitmap(258, 175, chargeManualIcon, 64, 64, TFT_DARKGREEN);
}

void drawBattIcon(){
    tft.drawBitmap(70, 63, batteryIcon, 192, 112, TFT_GREEN);
}

void getStatMoc(bool ChargState){
    
    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(100, 45);
    tft.print("Charge: ");
    ChargState ? tft.print("Yes") : tft.print("No ");
    
}

void getStatDisMoc(bool DisStat){
    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(80, 15);
    tft.print("Discharg: ");
    DisStat ? tft.print("Yes") : tft.print("No ");
}
