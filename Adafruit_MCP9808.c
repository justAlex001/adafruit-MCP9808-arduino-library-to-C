
// .c van de library mcp9808 omgebouwd van c++ naar c door alex jongejans

#define F_CPU 32000000UL
#include <avr/io.h>
#include <math.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "clock.h"
#include "i2c.h"
#include "Adafruit_MCP9808.h"




// de write functies van de .h
 void MCP9808_write16(Adafruit_MCP9808_t *s, uint8_t reg, uint16_t value);
 uint16_t MCP9808_read16(Adafruit_MCP9808_t *s, uint8_t reg);
 uint16_t MCP9808_read16(Adafruit_MCP9808_t *s, uint8_t reg);
 void MCP9808_write8(Adafruit_MCP9808_t *s, uint8_t reg, uint8_t value);
 uint8_t MCP9808_read8(Adafruit_MCP9808_t *s, uint8_t reg);






// begin voor het starten van de sensor
boolean MCP9808_begin(Adafruit_MCP9808_t *s, uint8_t addr, TWI_t *pTWI) {
 s->_i2caddr = addr;
 s->pTWI = pTWI;
  

  return MCP9808_init(s);
}

//initialisatie de sensor anders geeft hij een false terug
boolean MCP9808_init(Adafruit_MCP9808_t *s) {
  i2c_start(s->pTWI, s->_i2caddr, I2C_WRITE);
 

  if (MCP9808_read16(s, MCP9808_REG_MANUF_ID) != 0x0054)

    {
		return false;
	}
  if (MCP9808_read16(s, MCP9808_REG_DEVICE_ID) != 0x0400)
    {
		return false;
	}

  MCP9808_write16(s, MCP9808_REG_CONFIG, 0x0);
  return true;
   i2c_stop(s->pTWI);
  
}

// leest de temp in celius en geeft een float terug
float MCP9808_readTempC(Adafruit_MCP9808_t *s) {
  float temp = NAN;

   uint16_t t = MCP9808_read16(s, MCP9808_REG_AMBIENT_TEMP);


  if (t != 0xFFFF) {
    temp = t & 0x0FFF;
    temp /= 16.0;
    if (t & 0x1000){
      temp -= 256;}
  }

  return temp;
}

// leest de temp in farneit en geeft een float terug
float MCP9808_readTempF(Adafruit_MCP9808_t *s) {
  float temp = NAN;
  uint16_t t = MCP9808_read16(s, MCP9808_REG_AMBIENT_TEMP);


  if (t != 0xFFFF) {
    temp = t & 0x0FFF;
    temp /= 16.0;
    if (t & 0x1000)
      temp -= 256;

    temp = temp * 9.0 / 5.0 + 32;
  }

  return temp;
}

// zet Sensor om uit te schakelen of wakker te worden
//true = shutdown / false = wakeup
void MCP9808_shutdown_wake(Adafruit_MCP9808_t *s, TWI_t *pTWI, boolean sw) {
  uint16_t conf_shutdown;
  uint16_t conf_register = MCP9808_read16(s, MCP9808_REG_CONFIG);
  if (sw == true) {
    conf_shutdown = conf_register | MCP9808_REG_CONFIG_SHUTDOWN;
    MCP9808_write16(s, MCP9808_REG_CONFIG, conf_shutdown);
  }
  if (sw == false) {
    conf_shutdown = conf_register & ~MCP9808_REG_CONFIG_SHUTDOWN;
    MCP9808_write16(s, MCP9808_REG_CONFIG, conf_shutdown);
  }
}

//stopt de sensor
void MCP9808_shutdown(Adafruit_MCP9808_t *s) { MCP9808_shutdown_wake(s, &TWIE, true); }

//start de sensor
void MCP9808_wake(Adafruit_MCP9808_t *s) {

  MCP9808_shutdown_wake(s, &TWIE, false);
  _delay_ms(250);
}

//leest de resolutsie
uint8_t MCP9808_getResolution(Adafruit_MCP9808_t *s) {
    return MCP9808_read8(s, MCP9808_REG_RESOLUTION);
}



 //   Set Resolution Value

void MCP9808_setResolution(Adafruit_MCP9808_t *s, uint8_t value) {
  MCP9808_write8(s, MCP9808_REG_RESOLUTION, value & 0x03);
 
}

// write functie 16bit
void MCP9808_write16(Adafruit_MCP9808_t *s, uint8_t reg, uint16_t value) {

 i2c_start(s->pTWI, s->_i2caddr, I2C_WRITE);
 i2c_write(s->pTWI, reg);
 i2c_write(s->pTWI, value);
 i2c_stop(s->pTWI);
}

// read functie 16bit
uint16_t MCP9808_read16(Adafruit_MCP9808_t *s, uint8_t reg) {
  uint16_t val = 0xFFFF;
  
  i2c_start(s->pTWI, s->_i2caddr, I2C_WRITE);
  i2c_write(s->pTWI, reg);

  i2c_stop(s->pTWI);

  
    i2c_start(s->pTWI, s->_i2caddr, I2C_READ);
    val = i2c_read(s->pTWI, I2C_ACK);
    val <<= 8;
    val |= i2c_read(s->pTWI, I2C_NACK);
	i2c_stop(s->pTWI);
  

  return val;
}

// write functie 8bit
void MCP9808_write8(Adafruit_MCP9808_t *s, uint8_t reg, uint8_t value) {

  i2c_start(s->pTWI, s->_i2caddr, I2C_WRITE);
  i2c_write(s->pTWI, reg);
  i2c_write(s->pTWI, value);
  i2c_stop(s->pTWI);
  
}

// read functie 8bit
uint8_t MCP9808_read8(Adafruit_MCP9808_t *s, uint8_t reg) {
  uint8_t val = 0xFF;

  i2c_start(s->pTWI, s->_i2caddr, I2C_WRITE);
  i2c_write(s->pTWI, reg);
  i2c_stop(s->pTWI);
  


	  i2c_start(s->pTWI, s->_i2caddr, I2C_READ);
      val = i2c_read(s->pTWI, I2C_NACK);
	  i2c_stop(s->pTWI);
  

  return val;
}
