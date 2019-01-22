/*
 *Recieves a brief signal from the main module to close a relay
 */

unsigned long d; //synced delay (in µs)

void setup(){
  pinMode(2,OUTPUT); //indicator led through 10K resistor
  pinMode(4,OUTPUT); //trasistor pin that opens the garage
  digitalWrite(4, LOW);
  pinMode(0,INPUT); //input 
  delay(100); //give things time to start up
  ADCSRA &= ~(1<<ADEN); //disables ADC (Analog to Digital Converter)
  digitalWrite(2, HIGH); //indicator LED
}

void loop(){
  while(true){ //makes a loop to break out of if something goes wrong
    if(digitalRead(0)){ //finds the ATtiny's equivalent of 5ms in µs
      digitalWrite(2, LOW);
      unsigned long prevMicros = micros(); //get micros()
      if(prevMicros >= 4294907295){ //if it is within 60ms away from resetting
        d = 10700; //approximation if a reading can't be recieved
      }
      else{
        while(digitalRead(0)); //wait until the pin goes low
        d = micros() - prevMicros; //gets the delay in µs
        if(d>14000 || d<600) break; //if the signal is too far off from 10ms, break 
      }
      digitalWrite(2, HIGH);
      //use the delay to verify oncoming signal
      delayMicroseconds(d); //about 5ms
      digitalWrite(2, LOW);
      if(!digitalRead(0))break;
      delayMicroseconds(d*3); //about 15ms
      digitalWrite(2, HIGH);
      if(digitalRead(0)) break;
      delayMicroseconds(d); //about 5ms
      if(!digitalRead(0)) break;
      digitalWrite(2, LOW);
      delayMicroseconds(d*2); //about 10ms
      if(digitalRead(0)) break;
      digitalWrite(2, HIGH);
      //correct pulses were sent if the code reaches this, authenticates
      digitalWrite(4, HIGH); //transistor "presses" the button
      delay(1000);
      digitalWrite(4,LOW);
      digitalWrite(2,LOW);
      delay(1000);
      digitalWrite(2, HIGH);
    }
    digitalWrite(4, LOW);
  }
  //if the program gets here, then an incorrect sequence of pulses was sent
  delay(2000);
}

//Followed the steps of a tutorial given by Nodcah Josh Hawley for Sparkfun
