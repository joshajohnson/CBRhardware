#ifndef __uart_H__
#define __uart_H__

#include <stdint.h>

#define BAUD_RATE   9600UL
#define UBRR_VALUE  (F_CPU/16/BAUD_RATE)

#define BUF_SIZE  128

typedef struct{
  volatile uint8_t buf[BUF_SIZE];
  volatile uint8_t head;
  volatile uint8_t tail;
  volatile uint16_t dataSize;
  volatile uint8_t dataReady;
} circ_buf_t;

void uartInit(void);
void uartPutBit(uint8_t data);
void uartPutStr(uint8_t *str);
uint8_t uartGetBit(void);
void uartGetStr(uint8_t* str);
void uartPutBitBuf(uint8_t ch, circ_buf_t buffer);
void uartPutStrBuf(uint8_t* str, circ_buf_t *buffer);
void copyBuffer(circ_buf_t *rxBuffer, uint8_t *userBuf);
void uartTransmit(void);

#endif
