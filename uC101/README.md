# uC101
Project files for an intro to microcontrollers workshop.  

### To get up and running:
Install Arduino IDE  
Copy the uC101Library folder to `/Arduino/libraries`  
In Arduino IDE:  
`File->Examples->uC101->blink`  
`Tools->Board->Arduino Nano`  
`Tools->Processor->ATmega328p` or `Tools->Processor->ATmega328p (Old Bootloader)`  
`Tools->Port->$comPort`

Run `blink.ino` and confirm that the onboard LED is blinking

### Resources:   

[Embedded FM Podcast](embeddedfm.com) Look through old episodes for fundamentals  
[Making Embedded Systems](http://shop.oreilly.com/product/0636920017776.do) Josh has a copy you can borrow  
[Google 'problem' + avr](http://lmgtfy.com/?q=problem+avr)  
[Adafruit](https://www.adafruit.com/) [Sparkfun](https://www.sparkfun.com/) HW and SW resources  

#### Alternative Platforms
[PlatformIO](https://platformio.org/) Highly recomended replacement for Arduino IDE  
[STM32 System Workbench](http://www.openstm32.org/System%2BWorkbench%2Bfor%2BSTM32) Open source STM32 IDE / toolchain  

### Troubleshooting:

#### Windows
If after installing the Arduino software, you are missing a virtual COM port to communicate with your board, and the Device Manager is missing the usb2.0-serial driver, install the below driver:

http://www.wch.cn/download/CH341SER_ZIP.html

This is due to a CH340G USB to serial chip being used on the Arduino Nano.

(Thanks Wayne for the above fix!)
