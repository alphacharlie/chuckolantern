/*
 
 Rainbowduino v3.0 Motion Sensing Jack-O-Lantern

   Simple sketch does a 'stuttering' pattern when motion is sensed... to make an interactive jack-o-lantern! 
 
*/
 
#include <Rainbowduino.h>
 
 
// HSV to RGB array 
 
unsigned char RED[64] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,171,154,137,119,102,85,
68,51,34,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,35,52};
 
unsigned char GREEN[64] = {0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,170,154,136,120,102,86,68,52,34,18,0,0,0,0};
 
unsigned char BLUE[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,34,52,68,86,102,120,136,154,170,188,
204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};

unsigned int _delay;
unsigned int _change; 

int motionPin = 3;
int motionSense = 0;


void setup()
{
  Rb.init(); //initialize Rainbowduino driver
  pinMode(motionPin, INPUT); 
}
 
unsigned int z,x,y;

void stutter()
{
    // start on red then stutter to random colors until motion sensor deactivates
    int _step = random(10, 60);
    for(z=0; z < 64 ;z+=_step)
    {
      for(x=0;x<8;x++)
      {
        for(y=0;y<8;y++)
        {
          //Paint random colors
          //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes
          Rb.setPixelXY(x,y,RED[z],GREEN[z],BLUE[z]); //uses R, G and B color bytes
        }
      }
      delay(180);
      motionSense = digitalRead(motionPin);
      if(motionSense == 0)
        return;
    }
    
}

void fast()
{
    // change colors quickly until motion sensor deactivates

    for(z=63; z > 0 ;z--)
    {
      for(x=0;x<8;x++)
      {
        for(y=0;y<8;y++)
        {
          //Paint random colors
          //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes

          Rb.setPixelXY(x,y,RED[z],GREEN[z],BLUE[z]); //uses R, G and B color bytes
      
        }
      }
      delay(20);
      motionSense = digitalRead(motionPin);
      if(motionSense == 0)
        return;
    }
 
}

void gradual()
{
    // gradually change colors until motion is sensed...

    for(z=63; z > 0 ;z--)
    {
      for(x=0;x<8;x++)
      {
        for(y=0;y<8;y++)
        {
          //Paint random colors
          //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes
          Rb.setPixelXY(x,y,RED[z],GREEN[z],BLUE[z]); //uses R, G and B color bytes
      
        }
      }
      delay(200);
      motionSense = digitalRead(motionPin);
      if(motionSense == 1)
        return;
    }

}

void flicker()
{
    // try to flicker like a candle...
    int baseColor = 6; //between 0 and 63
    int flickerLength = 10; //length of flicker in MS
    if(random(100) > 85)
    {
      for(x=0;x<8;x++)
      {
        for(y=0;y<8;y++)
        {
          //Paint random colors
          //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes
          Rb.setPixelXY(x,y,0,0,0); //uses R, G and B color bytes
        }
      }
      delay(random(flickerLength));
    }
    else
    {
      int offset = random(6); //how much to randomize color
      for(x=0;x<8;x++)
      {
        for(y=0;y<8;y++)
        {
          //Paint random colors
          //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes
          Rb.setPixelXY(x,y,RED[baseColor + offset],GREEN[baseColor + offset],BLUE[baseColor + offset]); //uses R, G and B color bytes
      
        }
      }
      delay(random(400)); //how long to delay before checking for another flicker...
      motionSense = digitalRead(motionPin);
      if(motionSense == 1)
        return;
    }

}
void loop()
{
   if (motionSense == 1)
   {
    stutter(); //or do -
    // fast();
   }
   else flicker(); // or do -
   //   gradual();
}
