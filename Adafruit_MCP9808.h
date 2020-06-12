



/*!
 *  @file Adafruit_MCP9808.h
 *
 * 	I2C Driver for Microchip's MCP9808 I2C Temp sensor
 *
 * 	This is a library for the Adafruit MCP9808 breakout:
 * 	http://www.adafruit.com/products/1782
 *
 * 	Adafruit invests time and resources providing this open source code,
 *please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 * omgebouwd naar c door alex jongejans
 * student nummer 500820547
 * hva
 */

#ifndef _ADAFRUIT_MCP9808_H
#define _ADAFRUIT_MCP9808_H
#include "i2c.h"
#include <avr/io.h>
#include <math.h>
#include <stdbool.h>
#define boolean bool


#define MCP9808_I2CADDR_DEFAULT 0x18 ///< I2C address
#define MCP9808_REG_CONFIG 0x01      ///< MCP9808 config register
#define MCP9808_REG_CONFIG_SHUTDOWN 0x0100   ///< shutdown config
#define MCP9808_REG_CONFIG_CRITLOCKED 0x0080 ///< critical trip lock
#define MCP9808_REG_CONFIG_WINLOCKED 0x0040  ///< alarm window lock
#define MCP9808_REG_CONFIG_INTCLR 0x0020     ///< interrupt clear
#define MCP9808_REG_CONFIG_ALERTSTAT 0x0010  ///< alert output status
#define MCP9808_REG_CONFIG_ALERTCTRL 0x0008  ///< alert output control
#define MCP9808_REG_CONFIG_ALERTSEL 0x0004   ///< alert output select
#define MCP9808_REG_CONFIG_ALERTPOL 0x0002   ///< alert output polarity
#define MCP9808_REG_CONFIG_ALERTMODE 0x0001  ///< alert output mode

#define MCP9808_REG_UPPER_TEMP 0x02   ///< upper alert boundary
#define MCP9808_REG_LOWER_TEMP 0x03   ///< lower alert boundery
#define MCP9808_REG_CRIT_TEMP 0x04    ///< critical temperature
#define MCP9808_REG_AMBIENT_TEMP 0x05 ///< ambient temperature
#define MCP9808_REG_MANUF_ID 0x06     ///< manufacture ID
#define MCP9808_REG_DEVICE_ID 0x07    ///< device ID
#define MCP9808_REG_RESOLUTION 0x08   ///< resolutin

// de struct om verschildende fucties te laten werken
 typedef struct MCP9808_struct{
	 uint8_t _i2caddr;
	 TWI_t *pTWI;
		 
 } Adafruit_MCP9808_t;

// de functies
boolean MCP9808_begin(Adafruit_MCP9808_t *s, uint8_t addr, TWI_t *pTWI);

  
  boolean MCP9808_init(Adafruit_MCP9808_t *s);
  float MCP9808_readTempC(Adafruit_MCP9808_t *s);
  float MCP9808_readTempF(Adafruit_MCP9808_t *s);
  uint8_t MCP9808_getResolution(Adafruit_MCP9808_t *s);
  void MCP9808_setResolution(Adafruit_MCP9808_t *s, uint8_t value);

  void MCP9808_shutdown_wake(Adafruit_MCP9808_t *s, TWI_t *pTWI,  boolean sw);
  void MCP9808_wake(Adafruit_MCP9808_t *s);

//   write functies naar .c gegaan


#endif
