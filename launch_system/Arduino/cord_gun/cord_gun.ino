// Change x(on), y(off), Ver (1,2), then remember to sace: cmd+s
int intervalXOn=37; //20 is a good number          
int intervalTOff=9;           // interval at which to blink (milliseconds)
int intervalYOn=9;           // interval at which to blink (milliseconds)
int ver=1;

int mode = 1; //can override with intervalOff
int test = 0; //test run 

String base="_data_st_mg_";
String filename=base+intervalXOn+"_" + intervalTOff+"_" + intervalYOn+"_v" + ver +".txt";
const int ledPin3 =  2;// the number of the LED pin
const int ledPin2 =  3;// the number of the LED pin

// Variables will change:  
int ledState = LOW;             // ledState used to set the LED
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillisRelay = 0;        // will store last time LED was updated
unsigned long previousMillisMeasure = 0;        // will store last time LED was updated
// constants won't change:
String state = "START";

///////MEASUREMENT//////////////
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
  //set the digital pin as output:
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

  if (state.equals("START"))
  {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);  
    previousMillisRelay = currentMillis;
    state = "X_ON";
  } 
  
  if (state =="X_ON" && if (currentMillis - previousMillisRelay >= intervalXOn) )
  {
    digitalWrite(ledPin2, LOW); 
    digitalWrite(ledPin3, LOW); 
    previousMillisRelay = currentMillis;
    state = "T_OFF";
  } 

  if (state =="T_OFF" && if (currentMillis - previousMillisRelay >= intervalTOff) )
  {
    digitalWrite(ledPin2, LOW); 
    digitalWrite(ledPin3, HIGH); 
    previousMillisRelay = currentMillis;
    state = "Y_ON";
  } 

  if (state =="Y_ON" && if (currentMillis - previousMillisRelay >= intervalYOn) )
  {
    digitalWrite(ledPin2, LOW); 
    digitalWrite(ledPin3, LOW); 
    previousMillisRelay = currentMillis;
    state = "END";
    Serial.println("#Done shooting, turn the switch off"); // shows pre-scaled value 

    //Measure all tail current at the end
    if (measureState.equals("ON") && index > 0)
    {
      while (value < 500 || value > 530)        
      {
        value = analogRead(analogIn);  
        ts[index] = micros();
        current[index] = value;
        index = index + 1;
      }
      
      // Print to Processing/File
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
  } 

 // MEASURE CURRENT
 
  value = analogRead(analogIn);  

  //Record 5 "OFF" current at the begining
  if (measureState.equals("START") && value >= 500 && value <= 530 && index <= 5)
  {
    ts[index] = micros();
    current[index] = value;
    index = index + 1;
  }

  //Record "ON" current
  if ((value < 500 || value > 530 ) && measureState.equals("START"))
  {
    measureState = "ON";
  }

  if (index < 10 || (currentMillis - previousMillisMeasure >= 1)) 
  {
    previousMillisMeasure = currentMillis;       

    //if (index < sizeOfSample && (value < 510 || value > 515 ))
    if (measureState.equals("ON") && index < sizeOfSample)
    {
      ts[index] = micros();
      current[index] = value;
      index = index + 1;
    }
  }
}
