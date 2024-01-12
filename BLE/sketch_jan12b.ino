//voltmeter define variable names
float input_voltage = 0.0;

float temp=0.0;

float r1=100000.0;    //r1 value

float r2=10000.0;      //r2 value

//add ble library
#include <ArduinoBLE.h>

#define BLE_UUID_TEST_SERVICE               "9A48ECBA-2E92-082F-C079-9E75AAE428B1"
#define BLE_UUID_FLOAT_VALUE                "C8F88594-2217-0CA6-8F06-A4270B675D69"
    
BLEService testService( BLE_UUID_TEST_SERVICE );
BLEFloatCharacteristic floatValueCharacteristic( BLE_UUID_FLOAT_VALUE, BLERead | BLENotify );
//BLEFloatCharacteristic amplitudeCharacteristic( BLE_UUID_AMPLITUDE, BLERead | BLEWrite );



float oldBatteryLevel = 0;  // last battery level reading from analog input
long previousMillis = 0;  // last time the battery level was checked, in ms


void setup()
{
  BLE.begin();

  // set advertised local name and service
  BLE.setDeviceName( "Arduino Nano 33 BLE" );
  BLE.setLocalName( "Arduino Nano 33 BLE" );
  BLE.setAdvertisedService( testService );

  // BLE add characteristics
  testService.addCharacteristic( floatValueCharacteristic );
  //testService.addCharacteristic( amplitudeCharacteristic );
  

  // add service
  BLE.addService( testService );

  // set the initial value for characeristics
  floatValueCharacteristic.writeValue( oldBatteryLevel );
  //amplitudeCharacteristic.writeValue( amplitude );
  

  BLE.advertise();
}


void loop() {
  // wait for a Bluetooth® Low Energy central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral:
  if (central) {
    
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    // check the battery level every 200ms
    // while the central is connected:
    while (central.connected()) {
      long currentMillis = millis();
      // if 60s have passed, check the battery level:
      if (currentMillis - previousMillis >= 60000) {
        previousMillis = currentMillis;
        updateBatteryLevel();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void updateBatteryLevel() 
{ 
//Reading analog input from A0 pin 
int digitalValue = (analogRead(0)); 
//Converting digital value to voltage 
//int voltage = ((digitalValue*5)/1023); 
temp = (digitalValue * 3.3) / 1024.0;   
input_voltage = temp / (r2/(r1+r2));        
if (input_voltage < 0.1)   
{     
 input_voltage=0.0;    
}     
floatValueCharacteristic.writeValue( input_voltage );
}