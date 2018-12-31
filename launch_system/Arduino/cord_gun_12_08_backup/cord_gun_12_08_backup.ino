// Change x(on), y(off), Ver (1,2), then remember to sace: cmd+s
int intervalOn=37; //20 is a good number          
int intervalOff=0;           // interval at which to blink (milliseconds)
int ver=1;

int mode = 1; //can override with intervalOff
int test = 0;
String base="_data_st_mg_";
String filename=base+intervalOn+"_" + intervalOff+"_v" + ver +".txt";
const int ledPin3 =  2;// the number of the LED pin
const int ledPin2 =  3;// the number of the LED pin
//const int ledPin0 =  1;// the number of the LED pin
// Variables will change:  
int ledState = LOW;             // ledState used to set the LED
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillisRelay = 0;        // will store last time LED was updated
unsigned long previousMillisMeasure = 0;        // will store last time LED was updated
// constants won't change:
int dir = 0;
///////////////////////
const int analogIn = 1;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;
int iter = 1;
////////////////////
int sizeOfSample = 1000;
int ts[1000];
double current[1000];
int index=0;
float value;
int printed = 0;
int start = 0;
///////////////////
void setup() {
  // set the digital pin as output:
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin2, ledState);
  digitalWrite(ledPin3, ledState);
  Serial.begin(9600);  
  if (intervalOff ==0)
  {
    mode = 0;
  }
  
  delay(3000);
  if (test==0)
  {
    Serial.println(filename);
  }
  Serial.println("                    ");
  Serial.println("#Turn on switch now within 3 seconds...."); // shows pre-scaled value 
  delay(3000);
  Serial.println("#Shooting..."); // shows pre-scaled value 
}

void loop() {

  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  
  unsigned long currentMillis = millis();
  
  if (ledState == LOW)
  {
    if (currentMillis - previousMillisRelay >= intervalOff) 
    {
      // save the last time you blinked the LED
      previousMillisRelay = currentMillis;
      ledState=HIGH;
      if (mode ==0)
      {
        if (dir == 0)
        {
          digitalWrite(ledPin3, ledState);
          dir++;
        }
      } else
      {
      if (dir == 0)
      {
        digitalWrite(ledPin3, ledState);
        dir++;
      } else if (dir == 2)
      {
        digitalWrite(ledPin2, ledState);
        dir++;
      }
      }
    }
  } else 
  {
    if (currentMillis - previousMillisRelay >= intervalOn) 
    {
      // save the last time you blinked the LED
      previousMillisRelay = currentMillis;
      ledState=LOW;      
      dir++;
      digitalWrite(ledPin3, ledState);
      digitalWrite(ledPin2, ledState);
      


      
      if ((mode == 1&& dir == 4) || (mode==0 && dir==2)) {

      Serial.println("#Done shooting, turn the switch off"); // shows pre-scaled value 
  

if (start == 1 && index > 0)
{
  while (value < 500 || value > 530)        
{
value = analogRead(analogIn);  

  
  ts[index] = micros();
  current[index] = value;
  index = index + 1;
}
   Serial.println("iter,index,micro,raw,voltage,amps");


  for (int i =0; i < index; i ++)
  {
    Voltage = (current[i] / 1024.0) * 5000; // Gets you mV
    Amps = ((Voltage - ACSoffset) / mVperAmp);
    
    
    Serial.print(iter ); // shows pre-scaled value 
    Serial.print("," ); // shows pre-scaled value 
    Serial.print(i ); // shows pre-scaled value 
    Serial.print("," ); // shows pre-scaled value 
    Serial.print(ts[i]); // shows pre-scaled value 
    Serial.print(","); // shows pre-scaled value 
    Serial.print(current[i]); // shows pre-scaled value 
    Serial.print(","); // shows pre-scaled value 
    Serial.print(Voltage); // shows pre-scaled value 
    Serial.print(","); // shows pre-scaled value 
    Serial.println(Amps); // shows pre-scaled value 

  }
  iter = iter + 1;
    index = 0;
  start = 0;
  memset(ts, 0, sizeof(ts));
  memset(current, 0, sizeof(current));


}       
        delay (86400000);
        dir = 0;
      }       
    }
  }


//////////////////////
//////////////////////
value = analogRead(analogIn);  
if (start ==0 && value >= 500 && value <= 530 && index <= 5)
{
  ts[index] = micros();
  current[index] = value;
  index = index + 1;
}

if ((value < 500 || value > 530 ) && start == 0)
{
  start = 1;
}

if (index < 10 || (currentMillis - previousMillisMeasure >= 1)) 
{
previousMillisMeasure = currentMillis;       

//if (index < sizeOfSample && (value < 510 || value > 515 ))
if (start == 1 && index < sizeOfSample)
{
  ts[index] = micros();
  current[index] = value;
  index = index + 1;
}
}
//////////////////////

//////////////////////
// RawValue = analogRead(analogIn);
// Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
// Amps = ((Voltage - ACSoffset) / mVperAmp);
// 
// if (Amps > 1 || Amps < -1) {
// Serial.print("Raw Value = " ); // shows pre-scaled value 
// Serial.print(RawValue); 
// Serial.print("\t mV = "); // shows the voltage measured 
// Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
// Serial.print("\t Amps = "); // shows the voltage measured 
// Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 //delay(2); 
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
