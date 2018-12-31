/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.

  The circuit:
  - Use the onboard LED.
  - Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA
    and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN
    is set to the correct LED pin independent of which board is used.
    If you want to know what pin the on-board LED is connected to on your
    Arduino model, check the Technical Specs of your board at:
    https://www.arduino.cc/en/Main/Products

  created 2005
  by David A. Mellis
  modified 8 Feb 2010
  by Paul Stoffregen
  modified 11 Nov 2013
  by Scott Fitzgerald
  modified 9 Jan 2017
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

// constants won't change. Used here to set a pin number:
const int ledPin3 =  2;// the number of the LED pin
const int ledPin2 =  3;// the number of the LED pin
const int ledPin0 =  1;// the number of the LED pin
// Variables will change:
int ledState = LOW;             // ledState used to set the LED
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillis2 = 0;        // will store last time LED was updated
// constants won't change:
const long interval1 = 5000;           // interval at which to blink (milliseconds)
const long interval2 = 100; //20 is a good number           // interval at which to blink (milliseconds)
const long interval3 = 1000;//currency

int ts[100];
float current[100];
int index=0;
float value;
int printed = 0;

///////////////////////
const int analogIn = 1;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;
//////////////////////

void setup() {
  // set the digital pin as output:
//  pinMode(ledPin2, OUTPUT);
//  pinMode(ledPin3, OUTPUT);
//  pinMode(ledPin0, INPUT);
//  digitalWrite(ledPin2, ledState);
//  digitalWrite(ledPin3, ledState);
  Serial.begin(9600);  
}

void loop() {


  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.

  unsigned long currentMillis = millis();

  //measure currency
//  if (currentMillis - previousMillis2 >= interval3) 
//  {
//    int current = analogRead(ledPin0);    
//    Serial.println((float)(current*5)/1024);
//    Serial.println(current);
//    previousMillis2 = currentMillis;
//  }
  
//  if (ledState == LOW)
//  {
//    if (currentMillis - previousMillis >= interval1) 
//    {
//      // save the last time you blinked the LED
//      previousMillis = currentMillis;
//      ledState=HIGH;
//    }
//  } else 
//  {
//    if (currentMillis - previousMillis >= interval2) 
//    {
//      // save the last time you blinked the LED
//      previousMillis = currentMillis;
//      ledState=LOW;      
//    }
//  }
//  digitalWrite(ledPin3, ledState);


//////////////////////
value = analogRead(analogIn);  
Serial.println(value);
if (value <=300)
{ 

if (index < 100)
{ 
  ts[index] = millis();
  current[index] = value;
  index = index + 1;
}
}
else if (printed ==0 && (index == 100 || value >300))
{
  for (int i =0; i < index; i ++)
  {
    Serial.print(i ); // shows pre-scaled value 
    Serial.print(" " ); // shows pre-scaled value 
    Serial.print(ts[i]); // shows pre-scaled value 
    Serial.print(" "); // shows pre-scaled value 
    Serial.println(current[i]); // shows pre-scaled value 
  }
  printed = 1;
}


 //Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 //Amps = ((Voltage - ACSoffset) / mVperAmp);
 
 //if (Amps > 0.5 || Amps < -0.5) {
 
    
// Serial.println("Raw Value = " ); // shows pre-scaled value 
// Serial.print(RawValue); 
// Serial.print("\t mV = "); // shows the voltage measured 
// Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
// Serial.print("\t Amps = "); // shows the voltage measured 
// Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 //delay(2); 
 //}
}
/////////////////////  
///////////////////////////////////////////
//  unsigned long currentMillis = millis();
//  ledState = HIGH;
//  if (currentMillis - previousMillis >= interval) {
//    // save the last time you blinked the LED
//    previousMillis = currentMillis;
//
//    // if the LED is off turn it on and vice-versa:
//    if (ledState == LOW) {
//      ledState = HIGH;
//    } else {
//      ledState = LOW;
//    }
//
//    set the LED with the ledState of the variable:
//    //digitalWrite(ledPin3, ledState2);
//    digitalWrite(ledPin2, ledState);
//}
