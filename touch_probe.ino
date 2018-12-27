/*
Use to detect a touch down - measure the change in resistance..
Operation :

A OHM tester is build with a Voltage divider and testing for the unknown resistance value.
On startup the Sketch check if the probe is connected and a resistance is detected. If not a 
error state (RED LED) is shown. a 4.7k resistor is used for R 1 on a Open circuit R 2 will 
show 2401700.00 and a open  circuit  is detected.
If there is a resistance the state will be waiting for the set of the check value (Yellow LED Blink)
Once the Check resistance is activated the yellow led is solid and touch down can begin.
The moment the probe touches the work piece the resistance will drop and the Green LED and buzzer will 
go off Indicating touch down. 

3 LED's is used to show the States of the system
Red Led / Yellow Led - Blink   - shows error state - no probes are connected 
GREEN Led           - Blink   - Compared value not set , need to push button
                    - Solid   - Value is set and are waiting to state change
                    - Off     - State has changed and you have touch down
YELLO Led and Buz   - Indicate button press to set state
                    - Solid state has changed and touch down is achieved.
*/
// SETUP LED
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

void setup()
{
Serial.begin(115200);
//pinMode(buttonPin, INPUT_PULLUP); 
pinMode(buttonPin,HIGH);
pinMode(LEDG, OUTPUT);
digitalWrite(LEDG,LOW);
pinMode(LEDY, OUTPUT);
digitalWrite(LEDY,LOW);


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
{ digitalWrite(LEDR, HIGH);
digitalWrite(LEDY,LOW);
  Serial.println(R2);
  Serial.println("Please Connect Probes");
  delay(500);                  
  digitalWrite(LEDR, LOW); 
  digitalWrite(LEDY,HIGH);     
  Serial.println("Please Connect Probes");
  Serial.println(R2);
  delay(500);  
}else {
// ------------- Check id Resisatnce is big enough ----------
if(R2 <= oper_ct && setval == 0 )
{ digitalWrite(LEDR, HIGH);
digitalWrite(LEDG,LOW);
  Serial.println(R2);
  Serial.println("Please Turn Spindle");
  delay(100);                  
  digitalWrite(LEDR, LOW); 
  digitalWrite(LEDG,HIGH);     
  Serial.println("Please Turn Spindle");
  Serial.println(R2);
  delay(100);  
}else {
  
// ------------- Check the Sate of the Button ---------------
int sensorValue = R2;
 
if (buttonState == HIGH) { //pressing the button will produce a LOW state 0V 
digitalWrite(LEDG,HIGH); //the led with turn on 
Serial.println("Button Trigger");
setval = R2;
Serial.println(R2); 
}else {
 digitalWrite(LEDG,LOW); 
 digitalWrite(LEDY,LOW);
 Serial.println(R2);
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
  Serial.println("Waiting for Sate");
  digitalWrite(LEDG,HIGH);
  //digitalWrite(buzzer,LOW);
  Serial.println(setval);
  Serial.println(checkval);
  }
}else{
 Serial.println("State Not Set"); 
 Serial.println(R2);
 digitalWrite(LEDG,HIGH);
 delay(100); 
 digitalWrite(LEDG,LOW);
 delay(100);
}

}
}
// ------------- Print Value ---------


}



