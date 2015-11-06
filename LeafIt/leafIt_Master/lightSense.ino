enum type {UV, LIGHT};
//#include <LEEPROM.h>

 class lightSense
 {
  /*
  * public methods
  */
   public:
   
   //member variables
  int sensorRead;
  long currentMillis = millis();
  long lastMillis;
  long duration;
  
  //default constructor, takes in pin attached and sensor type
  lightSense(int pin)
  {
    sensorRead = 0;
    duration = 7200000;
  }

//This method takes a reading every 2 hours. After 12 hours it gives an average of how much light the plant received.
 String lightRemind(int pin)
 {
  
 }
 
 int getReading(int pin)
 {
  int reading = takeMeasure(pin);
  return reading;
 }
 ;

/*
 * private methods
 */
 
private:

  // method takes raw voltage reading and gives english read out
   int takeMeasure(int sensePin)
  {
   
   int lightRead = analogRead(sensePin);
   map(lightRead,0,1023,0,255); //map light sensor readings to 8 bits
  
   return lightRead;
 }//end takeMeasure
  

 }
;
