#ifndef EVENTS_H
#define EVENTS_H

#define EVENT_TIME_BIT  (1 << 0)
#define EVENT_LED_BIT   (1 << 1)
#define EVENT_LCD_BIT   (1 << 2)
#define EVENT_UART_BIT  (1 << 3)
#define EVENT_ETH_BIT   (1 << 4)
#define EVENT_ADC_BIT   (1 << 5)
#define EVENT_BTN_BIT   (1 << 6)

extern osEventFlagsId_t eventFlagsHandle;

#endif
