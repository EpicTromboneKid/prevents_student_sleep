
#define USE_ARDUINO_INTERRUPTS true  // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>   // Includes the PulseSensorPlayground Library.

//  Variables
int accReadingsx[2];
int accReadingsy[2];
int accReadingsz[2];
int x;                        // x axis variable
int y;                        // y axis variable
int z;                        // z axis variable
const int PulseWire = 3;      // PulseSensor PURPLE WIRE connected to ANALOG PIN 3
const int LED = LED_BUILTIN;  // The on-board Arduino LED, close to PIN 13.
const int MAX_FAIL_COUNT = 10;
int Threshold = 550;
int sleeptimer = 0;
int i = 0;
int ledState = LOW;
const int ledPin = LED_BUILTIN;

bool isMoving(int dx, int dy, int dz) {
  if (dx > 10)
    return (true);
  if (dy > 10)
    return (true);
  if (dz > 10)
    return (true);
  if (dx < 10)
    if (dy < 10)
      if (dz < 10)
        return (false);
}

bool isValid(float BPM) {
  if (BPM > 50)
    return (true);
  else
    return (false);
}  // Determine which Signal to "count as a beat" and which to ignore.
   // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
   // Otherwise leave the default "550" value.

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
#include "RunningAverage.h"

RunningAverage myRA(100);  //change (100) to set interval of avg measurements
int trials = 0;
int failedReading = 0;

void setup() {
  int hrtoavg[100];
  Serial.begin(9600);  // For Serial Monitor
  // Configure the PulseSensor object, by assigning our variables to it.
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  // Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
    Serial.println("_____________________________________________________________________________________________");  //This prints one time at Arduino power-up,  or on Arduino reset.
  }
  myRA.clear();  // explicitly start clean
  pinMode(ledPin, OUTPUT);
}

void loop() {

  float myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                  // "myBPM" hold this BPM value now.

  if (pulseSensor.sawStartOfBeat()) {  // Constantly test to see if "a beat happened".
  }



  if (isValid(myBPM) == true) {
    if (myBPM <= 90) {
      Serial.println("Are you sleeping?");
    }
    myRA.addValue(myBPM);
    trials++;
    Serial.print("Running Average: ");
    Serial.println(myRA.getAverage());
    Serial.println(myBPM);
    failedReading = 0;

  } else {
    failedReading++;
    if (failedReading == MAX_FAIL_COUNT) {
      Serial.print("Still waiting. Did I mention that this sensor sucks? (this message pops up every ");
      Serial.print(MAX_FAIL_COUNT);
      Serial.println(" failed attempts. )");
      Serial.println("---------------------------------------------------------------------------------");
      failedReading = 0;
    }
  }

  for (i = 0; i < 2; i++) {
    accReadingsx[i] = x;
    accReadingsy[i] = y;
    accReadingsz[i] = z;
    x = analogRead(2);  // read the second analog input pin
    y = analogRead(1);  // read the first analog input pin
    z = analogRead(0);  // read the zeroth analog input pin
    Serial.println("--");
    i = i++ % 2;
  }

  int diffx = accReadingsx[1] - accReadingsx[0];
  int diffy = accReadingsy[1] - accReadingsy[0];
  int diffz = accReadingsz[1] - accReadingsz[0];

  if (isMoving(diffx, diffy, diffz) == true)
    sleeptimer = 0;
  else
    sleeptimer++;


  if (sleeptimer >= 10){
    Serial.println("l bozo");
    if (ledState == LOW) {
    ledState = HIGH;
    } else {
    ledState = LOW;
  
  }
    digitalWrite(ledPin, ledState);
  }



  Serial.println(diffx);
  Serial.println(diffy);
  Serial.println(diffz);




  delay(1500);  // considered best practice in a simple sketch.
}
