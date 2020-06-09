/*!
 * @file Adafruit_BMP085_U.h
 */

#ifndef __BMP085_H__
#define __BMP085_H__

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_Sensor.h>

#ifdef __AVR_ATtiny85__
#include "TinyWireM.h"
#define Wire TinyWireM
#else
#include <Wire.h>
#endif

/*!
 * @brief BMP085 I2C address/bits
 */
#define BMP085_ADDRESS (0x77)

/*!
 * @brief BMP085 I2C registers
 */
enum {
  BMP085_REGISTER_CAL_AC1 = 0xAA,   //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_AC2 = 0xAC,   //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_AC3 = 0xAE,   //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_AC4 = 0xB0,   //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_AC5 = 0xB2,   //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_AC6 = 0xB4,   //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_B1 = 0xB6,    //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_B2 = 0xB8,    //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_MB = 0xBA,    //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_MC = 0xBC,    //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CAL_MD = 0xBE,    //!< R   Calibration data (16 bits)
  BMP085_REGISTER_CHIPID = 0xD0,    //!< Register that contains the chip ID
  BMP085_REGISTER_VERSION = 0xD1,   //!< Register that contains the chip version
  BMP085_REGISTER_SOFTRESET = 0xE0, //!< Register for doing a soft reset
  BMP085_REGISTER_CONTROL = 0xF4,   //!< Control register
  BMP085_REGISTER_TEMPDATA = 0xF6,  //!< Temperature data register
  BMP085_REGISTER_PRESSUREDATA = 0xF6, //!< Pressure data register
  BMP085_REGISTER_READTEMPCMD =
      0x2E, //!< Read temperature control register value
  BMP085_REGISTER_READPRESSURECMD =
      0x34 //!< Read pressure control register value
};

/*!
 * @brief BMP085 mode settings
 */
typedef enum {
  BMP085_MODE_ULTRALOWPOWER = 0,
  BMP085_MODE_STANDARD = 1,
  BMP085_MODE_HIGHRES = 2,
  BMP085_MODE_ULTRAHIGHRES = 3
} bmp085_mode_t;
/*=========================================================================*/

/*!
 * @brief Calibration data
 */
typedef struct {
  int16_t ac1;  //!< R calibration coefficient (16-bits)
  int16_t ac2;  //!< R calibration coefficient (16-bits)
  int16_t ac3;  //!< R calibration coefficient (16-bits)
  uint16_t ac4; //!< R calibration coefficient (16-bits)
  uint16_t ac5; //!< R calibration coefficient (16-bits)
  uint16_t ac6; //!< R calibration coefficient (16-bits)
  int16_t b1;   //!< R calibration coefficient (16-bits)
  int16_t b2;   //!< R calibration coefficient (16-bits)
  int16_t mb;   //!< R calibration coefficient (16-bits)
  int16_t mc;   //!< R calibration coefficient (16-bits)
  int16_t md;   //!< R calibration coefficient (16-bits)
} bmp085_calib_data;

/*!
 * @brief Class that stores state and functions for interacting with BMP183
 */
class Adafruit_BMP085_Unified : public Adafruit_Sensor {
public:
  Adafruit_BMP085_Unified(
      int32_t sensorID = -1); //!< @param sensorID ID of the BMP085 sensor

  /*!
   * @brief Starts I2C connection
   * @param mode Mode to set, ultra high-res by default
   * @return Returns true if successful
   */
  bool begin(bmp085_mode_t mode = BMP085_MODE_ULTRAHIGHRES);
  /*!
   * @brief Gets the temperature over I2C from the BMP085
   * @param temp Temperature
   * @return Returns the temperature
   */
  void getTemperature(float *temp);
  /*!
   * @brief Gets the pressure over I2C from the BMP085
   * @param pressure Pressure
   * @return Returns the pressure
   */
  void getPressure(float *pressure);
  /*!
   * @brief Calculates absolute pressure
   * @param seaLevel Pressure at sea level
   * @param atmospheric measured pressure
   * @return Absolute altitude
   */
  float pressureToAltitude(float seaLevel, float atmospheric);
  /*!
   * @brief Calculates pressure at sea level
   * @param altitude Altitude
   * @param atmospheric measured pressure
   * @return Pressure at sea level
   */
  float seaLevelForAltitude(float altitude, float atmospheric);
  // Note that the next two functions are just for compatibility with old
  // code that passed the temperature as a third parameter.  A newer
  // calculation is used which does not need temperature.
  /*!
   * @brief Calculates absolute pressure
   * @param seaLevel Pressure at sea level
   * @param atmospheric Measured pressure
   * @param temp Temperature
   * @return Absolute altitude
   */
  float pressureToAltitude(float seaLevel, float atmospheric, float temp);
  /*!
   * @brief Calculates pressure at sea level
   * @param altitude Altitude
   * @param atmospheric measured pressure
   * @param temp Temperature
   * @return Pressure at sea level
   */
  float seaLevelForAltitude(float altitude, float atmospheric, float temp);
  /*!
   * @brief Used to read the sensor
   * @return Returns an event
   */
  bool getEvent(sensors_event_t *);
  void getSensor(sensor_t *);

private:
  int32_t computeB5(int32_t ut);
  int32_t _sensorID;
};

#endif
