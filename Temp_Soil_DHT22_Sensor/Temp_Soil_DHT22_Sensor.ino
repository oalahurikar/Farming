// First we include the libraries
// Soil Signal to A0; Thermocouple to Digital/PWM 5, DHT to Digital/PWM 8
#include <DallasTemperature.h>
#include <OneWire.h> 
#include <DHT.h>
DHT dht;
// Declare variables for Temp Sensor
int temp_sensor = 5; // assign digital read to pin 5
float temperature = 0; // store temp value
OneWire oneWire(temp_sensor);

// Declare variables for SOil moisture Sensor
int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 3;//Variable for Soil moisture Power PWM pin
//Rather than powering the sensor through the 3.3V or 5V pins, 
//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil. 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup() 
{
  Serial.begin(9600);   // open serial over USB

  pinMode(soilPower, OUTPUT);//Set D3 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
  dht.setup(8); // data pin 8
  //Serial.println("Temperature"); 
  //Serial.println("Humidity (%)\tTemperature (C)\tMoisture\tThermocouple Temp (C)");
}

void loop() 
{
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();   

  //Serial.print(dht.getStatusString());
  //Serial.print("\t");
  Serial.print("A"); 
  Serial.println(humidity, 1);
  Serial.print("B"); 
  Serial.println(temperature, 1);
  //Serial.println(dht.toFahrenheit(temperature), 1);
  Serial.print("C"); 
  Serial.println(readSoil());
  

  //This 1 second timefrme is used so you can test the sensor and see it change in real-time.
  //For in-plant applications, you will want to take readings much less frequently.
   sensors.requestTemperatures(); // Send the command to get temperature readings 
   Serial.print("D"); 
   Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? 
   delay(900000);
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   //delay(5000); 

}
//This is a function used to get the soil moisture content
int readSoil()
{
    digitalWrite(soilPower, HIGH);//turn D3 "On"
    delay(5);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D3 "Off"
    return val;//send current moisture value
}

