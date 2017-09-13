

#include "./TiltSensor.h"


/* Bluetooth */
const int outBluetoothLED = 13;
char bleServiceUUID[40] = "025A7775-49AA-42BD-BBDB-E2AE77782966";
char positionCharUUID[40] = "F38A2C23-BC54-40FC-BED0-60EDDA139F47";
const char* bleName = "Makerball-5000";

/* Sensors
 *  You can add several sensor. If you have more than 4 sensor 
 *  just add a new instance of an 'TiltSensor' object and increase
 *  the value 'qtyOfSensors'.
 *  The app will multiply the SensorPoint by 25.
 *  
 * TiltSensor(Pin, SensorPoints, SensorBreak)
 */
int const qtyOfSensors = 4;
TiltSensor sensors[qtyOfSensors] = 
{
  TiltSensor(5, 0, 1000),
  TiltSensor(6, 14, 1000),
  TiltSensor(7, 33, 1000),
  TiltSensor(8, 15, 1000)
};

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
  setup_bluetooth();
}

void loop()
{
  loop_bluetooth();
}


void second_loop()
{
  for (int i=0; i < qtyOfSensors; i++)
  {
    int val = sensors[i].check();
    if (val != -1)
    {
      Serial.println(val, DEC);
      sendSensorValue(val);
    }
  }
}

