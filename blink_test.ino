/* 
	FPS_Enroll.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	This simple sketch turns the LED on and off similar to the Arduino blink sketch.
	It is used to show that communications are working.
*/

#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

// Hardware setup - FPS connected to:
//	  digital pin 10(arduino rx, fps tx)
//	  digital pin 11(arduino tx - 560ohm resistor fps tx - 1000ohm resistor - ground)
//		this brings the 5v tx line down to about 3.2v so we dont fry our fps

FPS_GT511C3 fps(10, 11);

void setup(){
	Serial.begin(9600);
	fps.UseSerialDebug = true; // so you can see the messages in the serial debug screen
	fps.Open();
}


void loop(){
	// FPS Blink LED Test
	fps.SetLED(true); // turn on the LED inside the fps
	delay(1000);
	fps.SetLED(false);// turn off the LED inside the fps
	delay(1000);
}

//Followed the steps of a tutorial given by Nodcah Josh Hawley for Sparkfun
