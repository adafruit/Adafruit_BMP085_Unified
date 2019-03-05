#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

static sensors_event_t sensors_event;
static float temperature;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(30304);

void setup()
{
	Serial.begin(250000);
	Serial.println("Starting up...");

	if (!bmp.begin())
	{
		Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
	}
}

void loop()
{
	int8_t bmpDataReady = bmp.isDataReady();
	if (bmpDataReady > 0)
	{
		if (bmpDataReady == DATA_READY_TEMPERATURE)
		{
			if (bmp.getTemperature(&temperature))
			{
				Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" C");
			}
			else
			{
				Serial.println("### Temp Error ###");
			}
		}
		else if (bmpDataReady == DATA_READY_PRESSURE)
		{
			if (bmp.getEvent(&sensors_event))
			{
				Serial.print("Pressure: "); Serial.print(sensors_event.pressure); Serial.print(" hPa; ");
				Serial.print("Altitude: "); Serial.print(bmp.pressureToAltitude(SENSORS_PRESSURE_SEALEVELHPA, sensors_event.pressure)); Serial.println(" m");
			}
			else
			{
				Serial.println("### Alt Error ###");
			}
		}
	}
	else if (bmpDataReady < 0)
	{
		Serial.println("### BMP Error ###");
	}
}



