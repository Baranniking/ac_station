#ifndef CHARGER_H          // если CHARGER_H ещё не определён
#define CHARGER_H          // определить CHARGER_H (защита от повторного include)
#include <Arduino.h>
#include <daly-bms-uart.h>  // <- обязательно здесь
// стандартные типы с фиксированным размером
#include <stdint.h>       // uint8_t, uint16_t, uint32_t

// логический тип bool, true, false
#include <stdbool.h>





// состояние зарядника

typedef enum {
    CHARGER_OFF,
    CHARGER_ON,
    CHARGER_DONE,
    CHARGER_CHECK,
    CHARGER_AUTO,
    CHARGER_FAULT
} charger_state;


typedef struct {
    float soc;
    float voltage;
    float current;
    float temp;
    bool dischargeEnabled;
    bool chargeEnabled;
} SystemState;

void UpdateDataBMS();
const SystemState* bms_get_state();

//передача обьекта
void chargeBegin(Daly_BMS_UART* bms);


//инициализация зарядника
void charger_init(void);

//управление 
void charger_enable(void);
void charger_disable(void);
void charger_au(void);
void charger_fault(void);

//логика
void charger_logical(void);

//сеттер
void logical_set_state(charger_state newState);

void activSetChargAU(bool state);

//геттер
charger_state logical_get_state(void);






#endif // CHARGER_H