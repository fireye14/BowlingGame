
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include<iostream>

using namespace std;

#define NUM_FRAMES 10
#define NUM_PINS 10

class Game
{
  protected:
	
    //declare a frame structure
    struct Frame
    {
       int first_throw;
       int second_throw;
       int third_throw;
       Frame *next;
       
       Frame(int throw1, int throw2, int throw3, Frame *next1 = NULL)
       {
          first_throw = throw1;
          second_throw = throw2;
          third_throw = throw3;
          next = next1;
       }   
	   
    };
    
    Frame *firstFrame;    //first frame pointer     
    
    
  public:
	Game() { firstFrame = NULL;  }                              // Constructor
   ~Game();                                                     // Destructor
    //initialize throw3 as -1 if the argument is not given
    void addFrame(int throw1, int throw2, int throw3 = -1);
    //return the current total score
    int getScore();
};

#endif
