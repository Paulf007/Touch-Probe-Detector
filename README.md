# Touch-Probe-Detector
Arduino project to detect the change of resistance. 

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
