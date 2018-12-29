/*
Use to detect a touch down - measure the change in resistance..
Operation :

A OHM tester is build with a Voltage divider and testing for the unknown resistance value.
On startup the Sketch check if the probe is connected and a resistance is detected. If not a 
error state (RED LED / YELLO LED) is shown. a 4.7k resistor is used for R 1 on a Open circuit R 2 will 
show 13000.00 and a open  circuit  is detected.
If there is a resistance the state will be waiting for the set of the check value (Green LED Blink)
Once the Check resistance is activated the Green LED is solid and touch down can begin.
The moment the probe touches the work piece the resistance will drop and the Yello LED and buzzer will 
go off indicating touch down. 

3 LED's is used to show the States of the system
Red Led / Yellow Led  -   Blink   - shows error state - no probes are connected
Red Led / Green Led   -   Blink   - the resistance is too low to measure attamtp to turn the spindle to increase the resistance 
Green Led             -   Blink   - Compared value not set , need to push button
                      -   Solid   - Value is set and are waiting to state change
                      -   Off     - State has changed and you have touch down
Yello Led and Buz     -   Solid   - state has changed and touch down is achieved.
Yello Led / Green Led -   Blink   - Time out ( 100 sec) this is to preserve battery unit needs to be switched of and on to reset
*/


int LEDR = 11;
int LEDY = 9;
int LEDG = 10;
int buttonPin = 12; 
int buttonState = 0;

int analogPin= 2;
int raw= 0;
int Vin= 5;
float Vout= 0;
float R1= 4700;
float R2= 0;
float buffer= 0;
int a2d_data=0;
float open_ct=13000.00;
float oper_ct=10.00;
float setval = 0;

// -------- Set timing module ----
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 100000;  //the value is a number of milliseconds
unsigned long time_changed = 0;

void setup()
{
Serial.begin(115200);
// ------ set timer ------
startMillis = millis();  //initial start time
// ------ end ------------

pinMode(buttonPin,HIGH);
pinMode(LEDG, OUTPUT);
digitalWrite(LEDG,LOW);
pinMode(LEDY, OUTPUT);
digitalWrite(LEDY,LOW);
// ------------------------ Run Startup event --------------- 

digitalWrite(LEDR,HIGH);
digitalWrite(LEDG,LOW);
digitalWrite(LEDY,LOW);
delay(500);
digitalWrite(LEDR,LOW);
digitalWrite(LEDG,HIGH);
digitalWrite(LEDY,LOW);
delay(500);
digitalWrite(LEDR,LOW);
digitalWrite(LEDG,LOW);
digitalWrite(LEDY,HIGH);
delay(500);
digitalWrite(LEDR,HIGH);
digitalWrite(LEDG,HIGH);
digitalWrite(LEDY,HIGH);
delay(500);
digitalWrite(LEDR,LOW);
digitalWrite(LEDG,LOW);
digitalWrite(LEDY,LOW);



  
}

void loop()
{
// -------------------- Read Button State ---------------------
buttonState = digitalRead(buttonPin);

// -------------------- Get Average Value of R2  --------------
 unsigned int x;
    unsigned int samples = 1024;
    unsigned long int accumulator = 0; // initialize accumulator
    for (x = 0; x < samples; x++) {
        accumulator += analogRead(A2);
    }
a2d_data=accumulator / samples;

buffer=a2d_data*Vin;
Vout=(buffer)/1024.0;
buffer=Vout/(Vin-Vout); 
raw= analogRead(analogPin);
R2=R1*buffer;
Serial.print("R2: ");
Serial.println(R2);
//delay(10);
// ---------- Check if Probes Connected -------
if(R2 >= open_ct)
{ digitalWrite(LEDR, LOW);
  digitalWrite(LEDY,HIGH);
  Serial.println(R2);
  Serial.println("Please Connect Probes");
  delay(500);                  
  digitalWrite(LEDR, HIGH); 
  digitalWrite(LEDY,LOW);     
  Serial.println("Please Connect Probes");
  Serial.println(R2);
  delay(500);  
}else {
  
// ------------- Check id Resisatnce is big enough ----------
if(R2 <= oper_ct && setval == 0 )
{ startMillis = currentMillis;
  digitalWrite(LEDY,LOW); 
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG,LOW);
  Serial.println(R2);
  Serial.println("Please Turn Spindle");
  delay(100); 
  digitalWrite(LEDY,LOW);  // to ensure that buzzer is not on.                 
  digitalWrite(LEDR, LOW); 
  digitalWrite(LEDG,HIGH);     
  Serial.println(R2);
  delay(100);  
}else {
  
// ------------- Check the Sate of the Button ---------------
int sensorValue = R2;

// Check if the value has been the same for 10 sec and if so sound the alarm
 //currentMillis = millis();
 time_changed = currentMillis - startMillis ;
 Serial.println(time_changed);
 if(time_changed > period && time_changed!= 0 )  //test whether the period has elapsed
  { //setval == 0 ; 
    digitalWrite(LEDG,LOW);  //if so, change the state of the LED.  Uses a neat trick to change the state
    digitalWrite(LEDY,HIGH);
    Serial.println(time_changed);
    delay(200);
    digitalWrite(LEDY,LOW);
    digitalWrite(LEDG,LOW);
    Serial.println(time_changed);
    
  }else {
 
if (buttonState == HIGH) { //pressing the button will produce a LOW state 0V 
digitalWrite(LEDG,HIGH); //the led with turn on 
Serial.println("Button Trigger");
setval = R2;
startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
Serial.println(R2); 
}else {
 digitalWrite(LEDG,LOW); 
 digitalWrite(LEDY,LOW);
 Serial.println(R2);
}
  }

// -------------- Compare Set Val with Current Val
if (setval > 0 ){
  float checkval = R2 ;
  if (checkval < (setval ) ){
    Serial.println("State Changed");
    digitalWrite(LEDY,HIGH); //the led with turn on
    digitalWrite(LEDG,LOW);
    //digitalWrite(buzzer,HIGH);
    Serial.println(setval); 
    Serial.println(checkval);
  }else{
  currentMillis = millis();  
  Serial.println("Waiting for Sate");
  digitalWrite(LEDG,HIGH);
  //digitalWrite(buzzer,LOW);
  Serial.print("Time:");
  Serial.println(time_changed);
  Serial.println(setval);
  Serial.println(checkval);
  }
}else{
 currentMillis = millis();  
 Serial.println("State Not Set"); 
   Serial.print("Time:");
  Serial.println(time_changed);
 Serial.println(R2);
 digitalWrite(LEDG,HIGH);
 digitalWrite(LEDR, LOW);
 digitalWrite(LEDY,LOW);
 delay(100); 
 digitalWrite(LEDG,LOW);
 digitalWrite(LEDR, LOW);
 digitalWrite(LEDY,LOW);
 delay(100);
}

}
}
}

