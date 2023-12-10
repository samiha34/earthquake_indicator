// Define pin numbers for components

#define buzzer 12

#define x A0

#define y A1

#define z A2  

 

// Variables for storing average sensor readings and timing

int xsample = 0;

int ysample = 0;

int zsample = 0;

long start;  // To store the start time for buzzer activation

int b = 0;   // Buzzer state (0 - off, 1 - on)

 

// Constants for sensor readings and buzzer control

#define samples 50   // Number of samples to average during setup

#define maxVal 20     // Maximum difference allowed for each axis

#define minVal -20    // Minimum difference allowed for each axis

#define buzTime 2000  // Buzzer activation time in milliseconds

 

void setup()

{

 // Start serial communication for debugging

 Serial.begin(9600);

 delay(1000);

 

 // Set buzzer pin as an output

 pinMode(buzzer, OUTPUT);

 

 // Initialize buzzer state and turn it off

 b = 0;

 digitalWrite(buzzer, b);

 

 // Average sensor readings for calibration

 for (int i = 0; i < samples; i++) {

   xsample += analogRead(x);

   ysample += analogRead(y);

   zsample += analogRead(z);

 }

 

 // Calculate average readings

 xsample /= samples;

 ysample /= samples;  

 zsample /= samples;  

}

 

void loop()

{

 // Read current sensor values

 int value1 = analogRead(x);

 int value2 = analogRead(y);

 int value3 = analogRead(z);

 

 // Calculate the differences between current readings and calibrated averages

 int xValue = xsample - value1;

 int yValue = ysample - value2;

 int zValue = zsample - value3;

 

 // Check if any axis exceeds the allowed difference range

 if (xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal) {

   // If the buzzer is currently off, record the start time

   if (b == 0)

     start = millis();

   // Set buzzer state to on

   b = 1;

 } else if (b == 1) {

   // If the buzzer has been on for the specified time, turn it off

   if (millis() >= start + buzTime)

     b = 0;

 }

 // Control the buzzer based on its state

 digitalWrite(buzzer, b);

 

 // Print sensor values for debugging

 Serial.print("x=");

 Serial.println(xValue);

 Serial.print("y=");

 Serial.println(yValue);

 Serial.print("z=");

 Serial.println(zValue);  

 Serial.println(" $");

}
