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
Yellow Led           - Blink   - Compared value not set , need to push button
                    - Solid   - Value is set and are waiting to state change
                    - Off     - State has changed and you have touch down
Green Led and Buz   - Indicate button press to set state
                    - Solid state has changed and touch down is achieved.
*/

// -------------- Calculation Value for the Resistance -----------
int Vin=5; //voltage at 5V pin of arduino
float Vout=0; //voltage at A0 pin of arduino
float R1=4700; //value of known resistance
float R2=0; //value of unknown resistance
int a2d_data=0; 
float buffer=0;
float open_ct=2401700.00; // The value that is shown if the circuit is open.

// ------------ Setup to monitor the peak value at a certin time interval and then report if it chnages. 
int peakValue = 0;
int threshold = 500; 
int noise = 0;
int setval = 0;
long lastMsg = 0;
char msg[50];
int value = 0;

const int8_t buzzer = 8;
const int8_t led_yl = 9;
const int8_t led_gr = 10;
const int8_t led_rd = 11;
const int8_t btn_push = 12;

void setup() {
 Serial.begin(115200); 
    // Turn LCD backlight on
  pinMode(led_yl, OUTPUT);
  digitalWrite(led_yl, HIGH);
  delay(100); 
  //digitalWrite(led_yl, LOW);
  delay(100);
  digitalWrite(led_yl, HIGH); 
  pinMode(led_rd, OUTPUT);
  digitalWrite(led_rd, HIGH);
  delay(100);
  //digitalWrite(led_rd, LOW);
  delay(100);
  digitalWrite(led_rd, HIGH);
  pinMode(led_gr, OUTPUT);
  digitalWrite(led_gr, HIGH);
  delay(100);
  //digitalWrite(led_gr, LOW);
  delay(100);
  digitalWrite(led_gr, HIGH);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  digitalWrite(led_rd, HIGH);
  digitalWrite(led_yl, HIGH);
  digitalWrite(led_gr, HIGH);
  delay(400);
  digitalWrite(buzzer, LOW);
   digitalWrite(led_rd,LOW);
  digitalWrite(led_yl, LOW);
  digitalWrite(led_gr, LOW);
  pinMode(btn_push, INPUT);





}


void loop() {

 unsigned int x;
    unsigned int samples = 1024;
    unsigned long int accumulator = 0; // initialize accumulator
    for (x = 0; x < samples; x++) {
        accumulator += analogRead(A0);
    }
    
// --------------- Compare Values --------------

a2d_data=accumulator / samples;

buffer=a2d_data*Vin;
Vout=(buffer)/1024.0;
buffer=Vout/(Vin-Vout); 
R2=R1*buffer;



if(R2 >= open_ct)
{ digitalWrite(buzzer,LOW);
  Serial.println(R2);
  digitalWrite(led_rd, LOW);       
  Serial.println("Please Connect Probes");
  delay(500);                  
  digitalWrite(led_rd, HIGH);       
  Serial.println("Please Connect Probes");
  delay(500);  
  digitalWrite(led_rd, LOW);   
  Serial.println("Please Connect Probes");
  delay(500); 
  digitalWrite(led_rd, LOW);
  Serial.println("Please Connect Probes");

}
else
{
digitalWrite(led_rd, LOW);
int sensorValue = R2;
int buttonState = digitalRead(btn_push); //read the state of the button input 
if (buttonState == LOW) { //pressing the button will produce a LOW state 0V 
digitalWrite(led_gr,HIGH); //the led with turn on 
Serial.println("Button Trigger");
setval = R2 ;
Serial.println(R2); 
} else{ 
digitalWrite(led_gr,LOW); //the led with turn off 
} 

}

// -------------- Compare Set Val with Current Val
if (setval > 0 ){
  int checkval = R2 + noise ;
  if (checkval < setval ){
    Serial.println("State Changed");
    digitalWrite(led_gr,HIGH); //the led with turn on
    digitalWrite(led_yl,LOW);
    digitalWrite(buzzer,HIGH); 
    Serial.println(R2);
  }else{
  Serial.println("Waiting for Sate");
  digitalWrite(led_yl,HIGH);
  digitalWrite(buzzer,LOW);
  Serial.println(setval);
  Serial.println(R2);
  }
}else{
 Serial.println("State Not Set"); 
 digitalWrite(led_yl,HIGH);
 delay(500); 
 digitalWrite(led_yl,LOW);
 delay(500);
}
  
     }


