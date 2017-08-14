

class TiltSensor{

  int _pin;
  unsigned long _sensorDelay;
  int _sensorValue;
  unsigned long _sensorBreak;

  public:
    TiltSensor(int pin, int sensorValue, int sensorDelay)
    {
      _pin = pin;
      _sensorValue = sensorValue,
      _sensorDelay = sensorDelay;
      _sensorBreak = millis();
      
      pinMode(_pin, OUTPUT);
    }

    int check()
    {
      int val = digitalRead(_pin);


      if (_sensorBreak < millis() && val == 1) {
        _sensorBreak = millis() + _sensorDelay;
        return _sensorValue;
      }
      return -1;
    }
};

