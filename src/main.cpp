#include <Arduino.h>
#include <Keyboard.h>

#define KEY_LEFT_CTRL  0x80
#define KEY_LEFT_ALT   0x82

int JOYSTICK_NORTH = 2;
int JOYSTICK_EAST = 5;
int JOYSTICK_SOUTH = 3;
int JOYSTICK_WEST = 4;

int ARCADE_BUTTON_UP = 6;
int ARCADE_BUTTON_LEFT = 7;
int ARCADE_BUTTON_RIGHT = 8;
int ARCADE_BUTTON_DOWN = 9;

int META_BUTTON_1 = 15;
int META_BUTTON_2 = 14;
int META_BUTTON_3 = 16;
int META_BUTTON_4 = 10;

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
  if(accumulator == 1){
    accumulator = 0;

    if(digitalRead(JOYSTICK_NORTH) == LOW){
      //NORTH
      Keyboard.write(KEY_UP_ARROW);
    }
    if(digitalRead(JOYSTICK_EAST) == LOW){
      //EAST
      Keyboard.write(KEY_RIGHT_ARROW);
    }
    if(digitalRead(JOYSTICK_SOUTH) == LOW){
      //SOUTH
      Keyboard.write(KEY_DOWN_ARROW);
    }
    if(digitalRead(JOYSTICK_WEST) == LOW){
      //WEST
      Keyboard.write(KEY_LEFT_ARROW);
    }

    if(digitalRead(ARCADE_BUTTON_UP) == HIGH){
      //ARCADE BUTTON UP
      Keyboard.write('w');
    }
    if(digitalRead(ARCADE_BUTTON_LEFT) == HIGH){
      //ARCADE BUTTON LEFT
      Keyboard.write('a');
    }
    if(digitalRead(ARCADE_BUTTON_RIGHT) == HIGH){
      //ARCADE BUTTON RIGHT
      Keyboard.write('d');
    }
    if(digitalRead(ARCADE_BUTTON_DOWN) == HIGH){
      //ARCADE BUTTON DOWN
      Keyboard.write('s');
    }
    

    if(digitalRead(META_BUTTON_1) == HIGH){
      //ARCADE BUTTON UP  
      Keyboard.write(KEY_ESC);
    }
    if(digitalRead(META_BUTTON_2) == HIGH){
      //ARCADE BUTTON LEFT
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('1');
      Keyboard.release(KEY_LEFT_ALT);

    }
    if(digitalRead(META_BUTTON_3) == HIGH){
      //ARCADE BUTTON RIGHT
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('3');
      Keyboard.release(KEY_LEFT_ALT);

    }
    if(digitalRead(META_BUTTON_4) == HIGH){
      //ARCADE BUTTON DOWN
      Keyboard.write(KEY_RETURN);
    }
  }
}

void loop() {
}
