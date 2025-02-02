#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 3
bool done = false;
bool pastStart = false;
void loop() {
 if(!done){
   moveForward(150); //assume 150 speed is 1 m/s
   //elapsedTime+=0.1*1;
   if(getSensorDistanceCm()<=25){
     //assuming 0 is black, 1 is blue, 2 is green, 3 is red
     if(getColor()==BLUE){
       turnLeft(628);
       if(!pastStart){
         pastStart=true;
       }
     }
     else if(getColor()==GREEN){
       turnRight(595);
       if(!pastStart){
         pastStart=true;
       }
     }
     else if(getColor()==RED){
       turnRight(595); //assuming Uturn means turn 180 degrees and not go forward, right, forward, right, forward
       turnRight(595);
       if(!pastStart){
         pastStart=true;
       }
     }
     else if(pastStart && getColor()==BLACK){
       done = true;
     }
   }
 }
}
