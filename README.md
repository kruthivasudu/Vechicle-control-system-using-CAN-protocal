The main aim of this project is to display the engine temperature along with 
alert message, reverse alert and control the indicators using CAN protocol.

There are three Nodes in the project each node communicate with out node through CAN.

MAIN NODE: In continuous loop, Read the temperature information and display it on LCD. 
And set the limit for engine temperature in the application program. If current temperature is 
beyond the limit value, then give the indication by using one LED/LED’S. And based on the 
interrupt generated, need to send the indicator signal to the indicator node. And one more 
task of this main node is receiving the reverse alert node information and give the indication 
(LED/BUZZER ON/OFF) based on the value received by reverse alert node.


INDICATOR NODE: Continuously waiting for the data from the main NODE using CAN.  
If any data is received from main NODE, based on that it is controlling the indicator signals 
connected to microcontroller. Refer the block diagram for how to give the indicator signals 
with the help of LED’S. 



REVERSE NODE: Continuously reading the GP2D12 sensor information with the 
help of on chip ADC and set one limit value to the sensor reading. If the sensor value is 
below the limit value sends logic 1 to the main node using CAN protocol. Or if the sensor 
value is greater than the limit value then sends the logic 0 to the main node using CAN 
protocol.
