# uC102
Project files for a dive into embedded communication protocols and analog to digital converters.  

### To get up and running:
Install Arduino IDE  
Copy the uC102Library folder to `/Arduino/libraries`  
In Arduino IDE:  
`File->Examples->uC102->blink`  
`Tools->Board->Arduino Nano`  
`Tools->Processor->ATmega328p` or `Tools->Processor->ATmega328p (Old Bootloader)`  
`Tools->Port->$comPort`

Run `blink.ino` and confirm that the onboard LED is blinking

### Resources:   

[Ben Eater](https://www.youtube.com/watch?v=eq5YpKHXJDM)  
[SPI Overview (ADI)](https://www.analog.com/en/analog-dialogue/articles/introduction-to-spi-interface.html)

### Troubleshooting:

#### Windows
If after installing the Arduino software, you are missing a virtual COM port to communicate with your board, and the Device Manager is missing the usb2.0-serial driver, install the below driver:

http://www.wch.cn/download/CH341SER_ZIP.html

This is due to a CH340G USB to serial chip being used on the Arduino Nano.

(Thanks Wayne for the above fix!)
