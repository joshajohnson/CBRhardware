////////////////////////////////////////
//           I2C Example              //
////////////////////////////////////////
#include "uC101.h"
#include "uart.h"
#include <util/twi.h>

#define MPU6050_ADDR                  0x68
#define MPU6050_REGISTER_PWR_MGMT_1   0x6B 
#define MPU6050_REGISTER_GYRO_ZOUT_H  0x47
#define MPU6050_REGISTER_WHO_AM_I     0x75

void twiInit();
int twiWrite(uint8_t addr, uint8_t sub_addr, uint8_t ch);
int twiRead(uint8_t addr, uint8_t sub_addr, uint8_t *data, uint8_t size);

uint8_t data[6] = {};   // Store data from I2C read
uint8_t str1[64];        // For serial comms
uint8_t txStr[64];
void setup() {
  uartInit();
  twiInit();

  // Wake sensor up
  twiWrite(MPU6050_ADDR,MPU6050_REGISTER_PWR_MGMT_1,0); 

  // Confirm we are talking to correct sensor
  twiRead(MPU6050_ADDR,MPU6050_REGISTER_WHO_AM_I,data,1);

  // Tell user if comms were established
  if (data[0] == 0x68)
  {
    uartPutStr("Talking to MPU6050\r\n");
  }
  else
  {
    uartPutStr("Not talking to MPU6050, check wiring\r\n"); 
  }
}

void loop() {

  int16_t gz;
  float gz_RPM;

  // Read two bytes
  twiRead(MPU6050_ADDR, MPU6050_REGISTER_GYRO_ZOUT_H, data, 2);       
  
  // Assemble into 16 bit value
  gz = data[0] << 8 | data[1];

  // Convert to RPM
  gz_RPM = (float) gz / 131.0 / 360.0; // RPM = LSB/degree/sec / degree/min

  // Send to computer
  dtostrf(gz_RPM,1,2,str1);
  sprintf(txStr,"RPM: %s \r\n",str1);
  uartPutStr(txStr);  

  // Take a break
  _delay_ms(50);   
}


void twiInit()
{

  // Set TWI clock to 100 kHz
  //TWBR = 0x5C;  //92 = 0x5C
  TWBR = ((F_CPU / 100000) - 16) / 2;
  TWDR = 0xFF;                        // Default content = SDA released.
  TWCR = (1<<TWEN)|                   // Enable TWI-interface and release TWI pins.
  (0<<TWIE)|(0<<TWINT)|               // Disable Interupt.
  (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|  // No Signal requests.
  (0<<TWWC);
}

int twiWrite(uint8_t addr, uint8_t sub_addr, uint8_t ch)
{
  // 1. Start
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWEA);
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_START)
  return -1;
  
  // 2. Send SLA+W (Write Mode)
  TWDR = (addr << 1) | (TW_WRITE);  // SLA+W
  TWCR = (1<<TWINT)|(1<<TWEN);    // Start transmission
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
  return -2;
  
  //  3. Send Data #1 (sub-address)
  TWDR = sub_addr;          // Data (Sub-address)
  TWCR = (1<<TWINT)|(1<<TWEN);    // Start transmission
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
  return -3;

  //  4. Send Data #2 (actual data)
  TWDR = ch;              // Data (at the sub-address register)
  TWCR = (1<<TWINT)|(1<<TWEN);    // Start transmission
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
  return -4;

  // 5. Stop condition
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  _delay_ms(1);           // Allow time for stop to send
  
  return 0;
}

int twiRead(uint8_t addr, uint8_t sub_addr, uint8_t *data, uint8_t size)
{
  // 1. Start
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_START)
  return -1;
  
  // 2. Send SLA+W (Write Mode)
  TWDR = (addr << 1) | TW_WRITE;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
  return -2;
  
  // 3. Send Data #1 (sub-address)
  if (size>1)
  sub_addr |= 0x80;

  TWDR = sub_addr;        // Sub address + Auto Increment
  TWCR = (1<<TWINT)|(1<<TWEN);  // Start transmission
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
  return -3;
  
  // 4. We need to change to Read mode so Re-start (repeated)
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
  while (!(TWCR & 1<<TWINT));
  if ((TWSR & 0xF8) != TW_REP_START)
  return -4;
  
  // 5. Send SLA+R (Read mode)
  TWDR = (addr << 1) | TW_READ;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_MR_SLA_ACK)
  return -5;

  if (size > 1) // multiple read
  {
    for (int i=0; i<size-1; i++)
    {
      // 6. Data up to #(N-1) (Read a byte). Need to ACK to the slave
      TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWEA); // ACK enabled
      while (!(TWCR & (1<<TWINT)));
      if ((TWSR & 0xF8) != TW_MR_DATA_ACK)
      return -6;
      
      *data++ = TWDR;
    }
  }
  
  // 6. Data #2 or #N (Read a byte). Last byte needs a NACK
  TWCR = (1<<TWINT)|(1<<TWEN); // No TWEA (send NACK to the slave)
  while (!(TWCR & (1<<TWINT)));
  if ((TWSR & 0xF8) != TW_MR_DATA_NACK)
  return -7;

  *data = TWDR; // last byte
  
  //  7. Stop
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  
  _delay_ms(1);
  
  return 0;
}
