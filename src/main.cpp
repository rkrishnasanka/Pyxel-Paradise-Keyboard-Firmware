#include <Arduino.h>
#include <Keyboard.h>

#define KEY_LEFT_CTRL  0x80
#define KEY_LEFT_ALT   0x82

int inputpins[12] = {2,3,4,5,6,7,8,9,10,16,14,15};
unsigned int accumulator = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<7; i++){
    pinMode(inputpins[i], INPUT);
    digitalWrite(inputpins[i], HIGH);
  }

  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

// Interrupt is called once a millisecond,
SIGNAL(TIMER0_COMPA_vect)
{
  accumulator++;
  if(accumulator == 100){
    accumulator = 0;

    //Loop through and check all the pins
    if(digitalRead(2) == HIGH){
      //Up
      Keyboard.write('w');
    } else if(digitalRead(3) == HIGH){
      //Left
      Keyboard.write('a');
    } else if(digitalRead(4) == HIGH){
      //Down
      Keyboard.write('s');
    } else if(digitalRead(5) == HIGH){
      //Right
      Keyboard.write('d');
    } else if(digitalRead(6) == HIGH){
      //Screenshot
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('1');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(7) == HIGH){
      //Reset the recording start time
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('2');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(8) == HIGH){
      //Save the screencapture
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('3');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(9) == HIGH){
      //Toogle the Performance Monitor
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('0');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(10) == HIGH){
      //North
      Keyboard.write('u');
    } else if(digitalRead(16) == HIGH){
      //East
      Keyboard.write('i');
    } else if(digitalRead(14) == HIGH){
      //South
      Keyboard.write('o');
    } else if(digitalRead(15) == HIGH){
      //West
      Keyboard.write('p');
    }
  }

}

void loop() {
  // // put your main code here, to run repeatedly:
  // if (digitalRead(buttonPin) == 0){
  //
  // }
}
