//https://www.arduino.cc/en/Tutorial/Genuino101CurieBLEHeartRateMonitor
#include <CurieBLE.h>


boolean isBluetoothOnline = false;
int const maxSendValue = 255;
int const bluetoothSendDelay = 10;

BLEPeripheral blePeripheral;
BLEService bleService(bleServiceUUID); // BLE LED Service
BLEIntCharacteristic switchCharacteristic(positionCharUUID, BLERead | BLEWrite | BLENotify);

void setup_bluetooth() {
  pinMode(outBluetoothLED, OUTPUT);   // initialize the LED on pin 13 to indicate when a central is connected

  // set advertised local name and service UUID:
  blePeripheral.setAdvertisedServiceUuid(bleService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(bleService);
  blePeripheral.addAttribute(switchCharacteristic);

  // add name:
  blePeripheral.setDeviceName(bleName);
  blePeripheral.setLocalName(bleName);



  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
}


void loop_bluetooth() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      isBluetoothOnline = true;
      digitalWrite(outBluetoothLED, isBluetoothOnline);
      
      second_loop();
      
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    isBluetoothOnline = false;
    digitalWrite(outBluetoothLED, isBluetoothOnline);
  }
}

void sendSensorValue(int value) {

  Serial.print("write value: ");
  Serial.println(value, DEC);

  // Über die Bluetooth-Schnittstelle können nur (INT) Werte zwischen 0-255 übermittelt werden.
  // Ist der Value grösser als 255, so wird dies über x-Loops aufgeteilt und der Rest (Modulo)
  // später versandt.
  
  if (value <= maxSendValue) {
    switchCharacteristic.setValue(value);
  } else {
    int loops = (int) floor(value / maxSendValue);
    int modulo = (int) value % maxSendValue;

    for (int i = 0; i < loops; i++) {
      switchCharacteristic.setValue(maxSendValue);
      delay(bluetoothSendDelay);
    }
    if (modulo != 0) {
      switchCharacteristic.setValue(modulo);
    }
  }
}


