#include "Arduino.h"
#include "uC101.h"
#include "uart.h"

circ_buf_t uartTxBuffer;
circ_buf_t uartRxBuffer;

void uartInit(void)
{
  UBRR0H = (uint8_t)(UBRR_VALUE>>8);            // Baud Rate High
  UBRR0L = (uint8_t) UBRR_VALUE;                // Baud Rate Low
  UCSR0C = (0<<USBS0)|(3<<UCSZ00);              // 1 stop bit, 8 data, No parity (default)
  // UCSR0B |= (1<<RXEN0)|(1<<TXEN0);              // Enable receiver and transmitter
  UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);  // Enable receiver and transmitter and RX ISR

  sei();
}

void uartPutBit(uint8_t data)
{
  while (!(UCSR0A & (1<<UDRE0)));   // Wait for transmit buffer empty
  UDR0 = data;                      // Put data into buffer, sends the data
}

void uartPutStr(uint8_t *str)
{
  while(*str)               // While there is data to be sent
  {
    uartPutBit(*str++);     // Send next bit to uart TX   
  }
}

uint8_t uartGetBit(void)
{
  while (!(UCSR0A & (1<<RXC0)));  // Wait for a bit to arrive
  return UDR0;                    
}

void uartGetStr(uint8_t* str)
{
  uint8_t ch;
  while ((ch = uartGetBit()) != '\r')   // While var is not a carriage return
  {
    *str++ = ch;                        // Append to array 
  }
  *str = '\0';                          // Close with null character
}

ISR(USART_UDRE_vect)
{
  if (uartTxBuffer.dataSize == 0)           // If data size == 0, nothing else to send, so disable interrupt
  {
    clearBit(UCSR0B,UDRIE0);              // Clear data register empty flag (leave this ISR)
  }
  else if (uartTxBuffer.tail == BUF_SIZE)   // If we reach the end of the buffer, overflow to 0
  {
    uartTxBuffer.tail = 0;
  }
  else                           
  {                 
    uartPutBit(uartTxBuffer.buf[uartTxBuffer.tail++]);  // Send the tail value over USART
    uartTxBuffer.dataSize--;                          // Decrease the data size to keep count of how many chars are left
  }
}

void uartPutBitBuf(uint8_t ch, circ_buf_t *buffer)
{
  if (buffer->head == BUF_SIZE)        // If we reach the end of the buffer, overflow to 0
  {    
    buffer->head = 0;
  }
      
  buffer->buf[buffer->head++] = ch; // Add ch to the buffer
  buffer->dataSize++;      
}

void uartPutStrBuf(uint8_t* str, circ_buf_t *buffer)
{
  for (int i=0; i < strlen(str); i++)
  {
    uartPutBitBuf(str[i], buffer);
  }
  
}

void uartTransmit(void)
{
  // We've put data in the buffer so turn on the TX-UDRE interrupt (triggers TX ISR)
  setBit(UCSR0B,UDRIE0);  
}

// RX ISR
ISR(USART_RX_vect)
{
  uint8_t ch = UDR0;  
  
  uartPutBitBuf(ch, &uartRxBuffer);  

  uartRxBuffer.dataReady = 1;    

}

void copyBuffer(circ_buf_t *rxBuffer, uint8_t *userBuf)
{
  if (rxBuffer->tail != rxBuffer->head)    // If there is data in the buffer
  {
    uint16_t count = 0;
    while (rxBuffer->tail != rxBuffer->head)  // While there is data in the buffer
    {
      userBuf[count] = rxBuffer->buf[rxBuffer->tail]; // Move data from circ buffer to user buffer
      (rxBuffer->tail == BUF_SIZE) ? rxBuffer->tail = 0 : rxBuffer->tail = rxBuffer->tail + 1;
      count++;
    }
    
    while (count < BUF_SIZE)  // Null terminator pad rest of buffer
    {
      userBuf[count] = '\0';
      count++;
    }
  } 
}