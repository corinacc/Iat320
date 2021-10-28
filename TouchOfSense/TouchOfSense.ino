#include <Adafruit_CircuitPlayground.h>

//claim touch pad variables
int pads[7] = {3, 2, 0, 1, 10, 6, 9};

int order[7] = {3,3,10,10,6,6,10};//1155665(twinkle twinkle little stars  order)
int input[7] = {-1,-1,-1,-1,-1,-1,-1};
int checkAmt = 0;

bool correct =false;

float threshhold = 500;

//claim note of pitches for each touch pad
float pitches[7] = {261.626, 293.665, 329.628, 349.228, 391.995, 440.0, 493.883}; //(3,2,0,1,10,6,9,)

void setup() {
  // Initialize serial.
  Serial.begin(9600);
  
  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
}

void loop() {

 //Loop over every pad & make each capcitance sensor play a different note
 for (int i = 0; i<7; i++){
  
  int x = CircuitPlayground.readCap(pads[i]);

  
   // Check if capacitive touch exceeds threshold.
  if(x > threshhold){
    
    //Play Sound
    CircuitPlayground.playTone(pitches[i], 100);
    input[checkAmt] =pads[i];
    checkAmt ++;
      
    for (int k=0; k<10; k++) 
      {
        CircuitPlayground.setPixelColor(k, 255  , 0, 255);
      }
      delay(10);
  }
  else 
  {
    for (int k=0;k<10; k++)
    {
        CircuitPlayground.setPixelColor(k, 0, 0, 0);
      }
      delay(10);
  }

      // check coorect order
      if (checkAmt ==7){
        if((input[0] == order [0] && input[1] == order [1] && input[2] == order [2] &&input[3] == order [3]&&
        input[4] == order [4] && input[5] == order [5] && input[6] == order [6]))//if all 7 input match the correct order 
        {
         
          //light up green & play tone
          for (int k=0; k<10; k++)
          {
            CircuitPlayground.setPixelColor( k, 0, 255, 0);  // green
            CircuitPlayground.playTone(1000,100);     // high pitch sound
          }
          checkAmt = 0; // reset  
          for(int k=0; k<10; k++){
            input[k]=-1;
          }
  }

    else //light up red & play tone 
    {
       for (int k=0; k<10  ; k++) 
        {
          CircuitPlayground.setPixelColor( k, 255, 0,0); // red 
          CircuitPlayground.playTone(100,100); // low pitch sound
        }
        checkAmt =0; //reset
        for (int k=0; k<7; k++) //reset input
        {
          input[k] = -1;
        }
      
    }
      }
 }
 
 delay(100);

}
