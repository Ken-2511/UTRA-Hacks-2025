#include <math.h>

#define LEFT 20;
#define UP 21;
#define RIGHT 22;
#define DOWN 23;

#define LEFT_TURN 25;
#define RIGHT_TURN 26;
#define STRAIGHT = 27;

int colours[5] = {RED, GREEN, BLUE, GREEN, BLUE};
int idx, greenPosX, greenPosY, bluePosX, bluePosY;

int currentDirection = UP;
int posX, posY;

int getDirectionTravelling(int turn);

const int radius = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  idx = 0;
  posX = 0;
  posY = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (idx < 5){
    if (getSensorDistanceCm() == 25){
      //randomly turn left or right 90 degrees
    } else {
      moveForward(150);
    }
    
    // calculate posX and posY
    if (currentDirection == LEFT){
      posX -= 1;
    } else if (currentDirection == UP){
      posY += 1;
    } else if (currentDirection == RIGHT){
      posX += 1;
    } else if (currentDirection == DOWN){
      posY -= 1;
    }

    int colour = getColour();
    if (colour == colours[idx]){
      switch (idx) {
        case 0: // red

          // !!!blink and mark position

          idx++;
          break;
        case 1: // first green

          // !!!blink and mark position

          green_pos_x = posX;
          green_pos_y = posY;

          idx++;
          break;
        case 2: // first blue

          // !!!blink and mark position

          blue_pos_x = posX;
          blue_pos_y = posY;

          idx++;
          break;
        case 3: // second green
          if (hypot(green_pos_x - posX, green_pos_y - posY) > radius){
            // !!!blink and mark position
            idx++;
          }
          break;
        case 4: // second blue
          if (hypot(blue_pos_x - posX, blue_pos_y - posY) > radius){
            // !!!blink and mark position
            idx++;
          }
          break;
      }
    }
  }
}

int getDirectionTravelling(int turn){
  if (turn == RIGHT_TURN){
    if (currentDirection == LEFT){
      currentDirection = UP;
    } else if (currentDirection == UP){
      currentDirection = RIGHT;
    } else if (currentDirection == RIGHT){
      currentDirection = DOWN;
    } else if (currentDirection == DOWN){
      currentDirection = LEFT;
    } else {
      serialPrintln("error: invalid current direction")
    }
  } else if (turn == LEFT_TURN){
    if (currentDirection == LEFT){
      currentDirection = DOWN;
    } else if (currentDirection == UP){
      currentDirection = LEFT;
    } else if (currentDirection == RIGHT){
      currentDirection = UP;
    } else if (currentDirection == DOWN){
      currentDirection = RIGHT;
    } else {
      serialPrintln("error: invalid current direction")
    }
  }
}
