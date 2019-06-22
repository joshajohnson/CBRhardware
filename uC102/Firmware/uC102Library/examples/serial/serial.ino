//////////////////////////////////////////////////////////////
//                      UART TX                             //
//////////////////////////////////////////////////////////////
#include "uC101.h"
#include "uart.h"

void setup()
{
  uartInit();
  dirIn(BUTTON_1_PORT,BUTTON_1);
}

void loop()
{
  if (readPin(BUTTON_1_PORT,BUTTON_1))
  {
    uartPutStr("Hello World! \r\n");
    _delay_ms(500);    
  }
}

//////////////////////////////////////////////////////////////
//                      UART Echo                           //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include "uart.h"
//
//uint8_t strIn[128];
//
//void setup()
//{
//  uartInit();
//}
//
//void loop()
//{
//  uartPutStr("Enter a Word: \r\n");
//  uartGetStr(strIn);
//  uartPutStr("You entered: ");
//  uartPutStr(strIn);
//  uartPutStr("\r\n");
//}

//////////////////////////////////////////////////////////////
//                      ISR TX                              //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include "uart.h"
//
//extern circ_buf_t uartTxBuffer;
//
//uint8_t strIn[128];
//
//void setup()
//{
//  uartInit();
//  dirIn(BUTTON_1_PORT,BUTTON_1);
//  dirIn(BUTTON_2_PORT,BUTTON_2);
//}
//
//void loop()
//{
//  if (readPin(BUTTON_1_PORT,BUTTON_1))
//  {
//    uartPutStrBuf("This is using an Interrupt!\r\n", &uartTxBuffer);
//    _delay_ms(500);
//  }
//
//  if (readPin(BUTTON_2_PORT,BUTTON_2))
//  {
//    uartPutStrBuf("Time to send it!\r\n", &uartTxBuffer);
//    uartTransmit();
//    _delay_ms(500);
//  }
//}

/////////////////////////////////////////////////////////////////////////
//                      ISR RX and TX                                  //
// MAKE SURE TO COMMENT IN LAST uartInit() line and ISR(USART_RX_vect) //
/////////////////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include "uart.h"
//
//uint8_t str[128];
//
//extern circ_buf_t uartRxBuffer;
//
//void setup() 
//{
//  uartInit();  
//}
//
//void loop() 
//{
// 
//  if (uartRxBuffer.dataReady)
//  {
//    uartRxBuffer.dataReady = 0;
//    copyBuffer(&uartRxBuffer, str);    
//    uartPutStr(str);
//    uartPutStr("\r\n");
//  }
//
//  _delay_ms(5000);
//  
//}
