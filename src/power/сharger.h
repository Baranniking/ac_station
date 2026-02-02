#ifndef CHARGER_H          // если CHARGER_H ещё не определён
#define CHARGER_H          // определить CHARGER_H (защита от повторного include)

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

//инициализация зарядника
void charger_init(void);

//управление 
void charger_enable(void);
void charger_disable(void);
void charger_au(void);

//логика
void charger_logical(void);

// статус
charger_state charger_get_state(void);




























#endif // CHARGER_H