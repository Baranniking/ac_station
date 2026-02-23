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

void logicalUpdateDataBMS();
const SystemState* logical_get();

//передача обьекта


//инициализация зарядника
void charger_init(void);

//управление 
void logical_charger_enable(void);
void logical_charger_disable(void);
void logical_toggle_auto_mode(void);
void charger_fault(void);

//логика
void charger_logical(void);

//сеттер
void logical_set_state(charger_state newState);

void activSetChargAU(bool state);

//геттер
charger_state logical_get_state(void);






#endif // CHARGER_H