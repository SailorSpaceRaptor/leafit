enum type {UV, LIGHT};
#include <LEEPROM.h>
#include <Average.h>

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
   String response;
  int addr = 0;
  Average <int> ave(6);
  int average = 0;  
  
  //take reading load into EEPROM
  int val = getReading(pin);

while (currentMillis - lastMillis < 43200000)//while currentMillis - lastMillis is less than 12 hours
  { 
    lastMillis = currentMillis;
    
    while(currentMillis - lastMillis > duration)
    { 
      lastMillis = currentMillis;
      
      EEPROM.write(addr, val);

      addr ++;
      
      if (addr == 512) //roll over if eeprom limit is met
      addr = 0;
      
    }
  }
    
  for(int i = 0; i <= 5; i++) //once 12 hours is met take average
  {
    
    int value = EEPROM.read(i);
    ave.push(value);
    average = ave.mean();
  }
  
    if (average <= 85)//gives proper response then clears eeprom
     {
      String response = "Plants may not be getting enough sunlight.";
     }
    else if (average > 85 && average <= 150)
    {
      String response = "Conditions currently ideal for Partial light plants."  ;
    }
    else
    {
      String response = "Conditions currently ideal for full light plants.";
    }
    
  for (int i = 0; i < 512; i++)// write a 0 to all 512 bytes of the EEPROM to clear
    EEPROM.write(i, 0);
 
  return response;
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
