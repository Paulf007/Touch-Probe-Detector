# Touch-Probe-Detector
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
Yello Led / Green Led -   Blink   - Time out ( 100 sec) this is to preserve battery unit needs to be switched off and on to reset
