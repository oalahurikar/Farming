// First we include the libraries
#include <DallasTemperature.h>
#include <OneWire.h> 

int temp_sensor1 = 5;
int temp_sensor2 = 4;
float temperature = 0;

OneWire oneWire(temp_sensor1);
OneWire oneWire(temp_sensor2);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void) 
{ 
 // start serial port 
 Serial.begin(9600); 
 Serial.println("Temperature"); 
 // Start up the library 
 sensors.begin(); 
} 

void loop(void) 
{ 
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
 Serial.print("Temperature1 is: "); 
 Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
 Serial.print(sensors.getTempCByIndex(1));
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   delay(1000); 
} 
