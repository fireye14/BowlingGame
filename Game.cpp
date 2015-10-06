#include "Game.h"

using namespace std;


void Game::addFrame(int throw1, int throw2, int throw3) 
{
    if(firstFrame == NULL)
    
         //create the first frame if the game is empty
         firstFrame = new Frame(throw1, throw2, throw3);
    else
    {
         //start at the first frame 
         Frame *framePtr = firstFrame;
         
         //use framePtr to traverse to the end of the list
         while(framePtr->next != NULL)
              framePtr = framePtr->next;
               
         //insert a new frame at the end of the list
         framePtr->next = new Frame(throw1, throw2, throw3);
    }
}

int Game::getScore()
{
	Frame *framePtr = firstFrame;  //start at the first frame
	int throw1 = 0, throw2 = 0, throw3 = 0;    //throw scores
	int frame_score = 0;           //score of a frame
	int final_score = 0;           //score at the end of the game
	
	while(framePtr != NULL)
	{
		throw1 = framePtr->first_throw;
		throw2 = framePtr->second_throw;
		throw3 = framePtr->third_throw;
		
		frame_score = throw1 + throw2;
		
		//on final frame if throw3 != -1, which also means framePtr->next == NULL
		if(throw3 != -1) frame_score += throw3;
		   
		if(throw1 == NUM_PINS && framePtr->next != NULL)
		{
			//a strike was thrown AND at least the next frame has been thrown
			//add the next two throws to this frame's score, if they have been thrown
			frame_score += framePtr->next->first_throw + framePtr->next->second_throw;
			
			if(framePtr->next->first_throw == NUM_PINS && framePtr->next->next != NULL)
			{
				//a strike was thrown on the frame afer the current frame
				//add the next frame's first throw if it has been thrown
				frame_score += framePtr->next->next->first_throw;
			}
			
		}
		else if(throw1 + throw2 == NUM_PINS && framePtr->next != NULL)
		{
			//a spare was thrown on this frame AND at least the next frame has been thrown
			//add the next throw to this frame's score
			frame_score += framePtr->next->first_throw;			
			
		}
		
		final_score += frame_score;
		framePtr = framePtr->next;
	}
	
	return final_score;
	
}

Game::~Game()
{
	Frame *framePtr = firstFrame;  //start at the first frame
	
	while (framePtr != NULL)
	{
		//garbage keeps track of frame to be deleted
		Frame *garbage = framePtr;

        //move on to the next frame
		framePtr = framePtr->next;
		
		//delete the garbage
		delete garbage;
	}
}
