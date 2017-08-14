

#include "./TiltSensor.h"


/* Bluetooth */
int const outBluetoothLED = 13;
char bleServiceUUID[40] = "025A7775-49AA-42BD-BBDB-E2AE77782966";
char positionCharUUID[40] = "F38A2C23-BC54-40FC-BED0-60EDDA139F47";

/* Sensors */
int const qtyOfSensors = 4;
TiltSensor sensors[qtyOfSensors] = 
{
  //TiltSensor(Port, Value, LockTime) *Value 0->(-1 Live, >0 Points)
  TiltSensor(5, 0, 1000),
  TiltSensor(6, 1000, 1000),
  TiltSensor(7, 2000, 1000),
  TiltSensor(8, 3000, 1000)
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

