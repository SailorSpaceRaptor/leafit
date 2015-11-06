/*
 * created by Jonathan Eskow 11/5/2015
 * this is a class for use with the LeafIt garden system that dictates behavior of the dht temp/humidity sensor
 */
#include "DHT.h" //include DHT library

#define DHTTYPE DHT22
 class tempHumid : public DHT //class tempHumid inherits DHT
{
  
 public:
 
 //member variables
 float temp;
 float humid;

 //default constructor, DHT takes in the pin number the sensor is attached to 
 tempHumid(int pin, uint8_t type = DHT22): DHT(pin, type)
 {
  float temp = 0.0;
  float humid = 0.0;
 }

/*
 * public get methods
 */
 float getFtemp()
 {
  float fTemp = convert(temp);
  return fTemp;
 }


float getTemp()
{
  float temp = takeMeasure();
  return temp;
}

 float getHumid()
 {
  float humid = humidMeasure();
  return humid;
 }
 
 String tempRead()
 {
  //initialize 
  float tempRead = getFtemp();
  float celRead = getTemp();
  String message;

  if(celRead < 15.00)
  {
    String warning1 = " Continued exposure at this temperature may be harmful warmer weather plants"; 
    String space = " : ";
    message = tempRead + space + warning1;
  }
  else if (celRead > 32.0)
  {
    String warning2 = " Continued exposure at this temperature may be harmful for cool weather plants.";
    String space = " : ";
    message = tempRead + space + warning2;
  }
  else
  {
    String warning0 = "The current temperature is ";
    message = warning0 + tempRead;
  }

  return message;
 }

 
 
 /*
  * private methods
  */
 
 private:

//this method converts Celsius to Faharenheit
 float convert(int temp)
 {
  float fTemp = convertCtoF(temp);
  return fTemp;
 }

//this method returns the Celsius temperature reading
float takeMeasure()
{
  float temp = readTemperature();
  return temp;
}
 
float humidMeasure()
{
  float humid = readHumidity();
  return humid;
}

}
;
