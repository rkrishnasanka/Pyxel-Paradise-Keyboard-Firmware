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
  if(accumulator == 10){
    accumulator = 0;

    //Loop through and check all the pins
    if(digitalRead(2) == LOW){
      //Up
      Keyboard.write('w');
    } else if(digitalRead(3) == LOW){
      //Left
      Keyboard.write('a');
    } else if(digitalRead(4) == LOW){
      //Down
      Keyboard.write('s');
    } else if(digitalRead(5) == LOW){
      //Right
      Keyboard.write('d');
    } else if(digitalRead(6) == LOW){
      //Screenshot
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('1');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(7) == LOW){
      //Reset the recording start time
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('2');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(8) == LOW){
      //Save the screencapture
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('3');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(9) == LOW){
      //Toogle the Performance Monitor
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('0');
      Keyboard.release(KEY_LEFT_ALT);
    } else if(digitalRead(10) == LOW){
      //North
      Keyboard.write('u');
    } else if(digitalRead(16) == LOW){
      //East
      Keyboard.write('i');
    } else if(digitalRead(14) == LOW){
      //South
      Keyboard.write('o');
    } else if(digitalRead(15) == LOW){
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
