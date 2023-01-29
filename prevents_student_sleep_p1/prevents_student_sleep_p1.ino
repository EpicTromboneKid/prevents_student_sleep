
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks the builtin LED with user's Heartbeat.
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED = LED_BUILTIN;   // The on-board Arduino LED, close to PIN 13.
const int MAX_FAIL_COUNT = 10;
int Threshold = 550;
bool isValid (float BPM){
  if (BPM > 0)
      return (true);
    else
      return (false);
}                  // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
  #include "RunningAverage.h"
  
  RunningAverage myRA(100); //change (100) to set interval of avg measurements
  int trials = 0;
  int failedReading = 0;
   
void setup() {   
  int hrtoavg [100];  
  Serial.begin(9600);          // For Serial Monitor
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("_____________________________________________________________________________________________");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  myRA.clear(); // explicitly start clean
}

void loop() {

 float myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
  
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 // If test is "true", print a message "a heartbeat happened". 
                         // Print the value inside of myBPM. 
}
  
  
          
  if (isValid(myBPM) == true){
    if (myBPM <= 90){
      Serial.println("Are you sleeping?");
    }
    myRA.addValue(myBPM);
    trials++;
    Serial.print("Running Average: ");
    Serial.println(myRA.getAverage()); 
    Serial.println(myBPM);
  failedReading = 0;     
    
  
  }
  else {
    failedReading++;
    if (failedReading == MAX_FAIL_COUNT){
      Serial.print("Still waiting. Did I mention that this sensor sucks? (this message pops up every ");
      Serial.print(MAX_FAIL_COUNT);
      Serial.println(" failed attempts.)");
      failedReading = 0;      
    }
  }
  
  
  


  delay(1500); // considered best practice in a simple sketch.

}

  
