#include "ui.h"
#include "config.h"
#include "logical.h"
#include "iconChargeAv.h"
#include "iconInvertor.h"
#include "iconSettings.h"
#include "iconChargeManual.h"
#include "iconBattIcon.h"
TFT_eSPI tft;

uint16_t scaleX = 40;
uint16_t scaleY = 140;
uint16_t scaleWidth = 240;
uint16_t scaleHeight = 8;
uint16_t oldX = 0;

float currentPercent = 0;
float targetPercent = 0;

uint32_t timeUpdateDataBms = 0;
const uint32_t IntervalUpdate = 1*3000; // 3sec

int bottomY = scaleY + scaleHeight; // низ шкалы
int tipY = bottomY;                 // вершина у шкалы
int baseY = bottomY + 14;           // основание ниже
int halfWidth = 7;                  // половина ширины

bool stateChargeAu = false;
bool dischargeStatus = false;
static ScreenState currentScreen = SCREEN_MAIN;
static ScreenState lastScreen = SCREEN_CHARGE;

const SystemState* state = logic_get_state();

const int numButtons = sizeof(UIBtn)/sizeof(UIBtn[0]); //sizeof определяет общий размер массива и делит его на одну ячейку, тем самым определяем размер в одной ячейке

void displayBegin(){
tft.init();
tft.setRotation(1);
tft.fillScreen(TFT_BLACK);
}



static UIButton UIBtn[]{
    {140, 120, 180, 160, SCREEN_MAIN, enterToChargeMenu, //Кнопка перехода в меню значений.
    {150, 220, 170, 250, SCREEN_CHARGE, enterToMainMenu}, //Кнопка перехода в главное меню с меню значений.
    {0, 0, 50, 50, SCREEN_MAIN, toggleDischargeMode}, //Кнопка запуская разряда.
    {280, 0, 320, 50, SCREEN_MAIN, toggleAuChargeMode} //Кнопка запуска АвтоЗаряда.
    
};

void uiProcessTouch(const tP point){
    Serial.print(" X: "); Serial.println(point.x);
    Serial.print(" Y: "); Serial.println(point.y);
    Serial.print(" Z: "); Serial.println(point.z);

    for(int i = 0; i < numButtons; i++){
        UIButton &btn = UIBtn[i];
        if(getCurrentScreen() == btn.screen &&
             point.x >= btn.x1 && point.x < btn.x2 &&
             point.y >= btn.y1 && point.y < btn.y2){
                btn.action();
                break;
             }
    }
}

    void enterToChargeMenu(){
        setCurrentScreen(SCREEN_CHARGE);
    }

    void enterToMainMenu(){
        setCurrentScreen(SCREEN_MAIN);
    }

    void toggleDischargeMode(){
        dischargeStatus = !dischargeStatus;
        bms_set_discharge(dischargeStatus); 
        drawBulb(dischargeStatus);
    }

    void toggleAuChargeMode(){
        stateChargeAu = !stateChargeAu;

        if(stateChargeAu){
            charger_set_state(CHARGER_AUTO);
            drawChargeAuIcon(stateChargeAu);
        }else{
            charger_set_state(CHARGER_OFF);
           drawChargeAuIcon(stateChargeAu);
        }
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
   








void setCurrentScreen(ScreenState newScreen){
    currentScreen = newScreen;
}

ScreenState getCurrentScreen(){
    return currentScreen;
}

void updateScreen(){
    updateValue();

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

void updateValue(){
    if (millis() - timeUpdateDataBms >= IntervalUpdate){
         timeUpdateDataBms = millis();
         switch(currentScreen)
         {

           case SCREEN_MAIN:
        logicalUpdate();
        targetPercent = 
        currentPercent += (targetPercent - currentPercent) * 0.1;
        int x = procentToX(currentPercent);
        updateMarker(x);
        drawProcentBat(state->soc);
        drawTempReactor(state->temp;
        getStatMoc(state->chargeEnabled);
        getStatDisMoc(state->dischargeEnabled);
        drawChargeAuIcon(stateChargeAu);
        Serial.println(state->chargeEnabled));
        Serial.println(state->dischargeEnabled);
            break;

            case SCREEN_CHARGE:
        drawChargeValue(
        state->voltage,
        state->current,
        state->voltage * state->current,
        state->soc);
            break; 
         }
    }

}

void drawMainMenu(){
     tft.fillScreen(TFT_BLACK);
     drawBulb(dischargeStatus);
     drawChargeAuIcon(stateChargeAu);
     drawSettingsIcon();
     drawChargeManualIcon();
     drawScale();
    tft.drawLine(64, 64, 256, 64, TFT_DARKGREEN);
    tft.drawLine(74, 35, 246, 35, TFT_DARKGREEN);
    tft.drawLine(64, 95, 256, 95, TFT_DARKGREEN);
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

void drawProcentBat(uint8_t procent){
    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(115, 75);
    tft.print("SOC: ");
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    char buffer[5];  // 3 цифры + % + \0
    sprintf(buffer, "%03d", procent);
    tft.print(buffer);
}

void drawTempReactor(int tempReactor){
     tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(115, 105);
    tft.print("TEMP REACTOR: ");
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(tempReactor);
}
 
void drawScale() {
  // основная линия
  tft.fillRect(scaleX, scaleY, scaleWidth, scaleHeight, TFT_DARKGREEN);

  tft.setTextDatum(MC_DATUM); // текст по центру

  for (int i = 0; i <= 100; i += 10) {

    int x = scaleX + (i / 100.0) * scaleWidth;

    // деления
    tft.drawLine(x, scaleY - 6, x, scaleY + scaleHeight + 6, TFT_GREEN);
 
    // числа сверху
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.drawString(String(i), x, scaleY - 15);
  }
}

int procentToX(float procent){
    if (procent < 0) procent = 0;
    if (procent > 100) procent = 100;

    return scaleX + (procent / 100.0) * scaleWidth;
}

void drawMarker(int x, uint16_t color) {

  int bottomY = scaleY + scaleHeight + 8;
  int tipY = bottomY;         
  int baseY = bottomY + 14;
  int halfWidth = 7;

  tft.fillTriangle(
      x, tipY,                    // вершина
      x - halfWidth, baseY,       // левый угол основания
      x + halfWidth, baseY,       // правый угол основания
      color
  );

}

void updateMarker(int newX){
    drawMarker(oldX, TFT_BLACK);
    drawMarker(newX, TFT_WHITE);
    oldX = newX;
}