#include "Game.h"
#include "stringmanip.h"
#include <sstream>

using namespace std;


int main()
{
	
	//create a game
	Game game;
	
	//strings to hold user input to be validated
	string first_throw_input, second_throw_input, third_throw_input;
	
	//flags used to determine validity of user input
	bool is_valid_input = true, valid_throw_one, valid_throw_two, valid_throw_three;
	
	//int variables to receive value of user input if possible
	int first_throw_score = 0;
	int second_throw_score = 0;
	int third_throw_score = 0;
	
	//iterate over 'NUM_FRAMES - 1' frames
	for(int i = 1; i < NUM_FRAMES; i++)
	{
		
		do
		{
			
			//ask for and get score of first throw
			cout << "Frame " << i << ", throw 1:   ";
			getline(cin, first_throw_input);
			
			//check to see if a strike was thrown
			if(trim_copy(first_throw_input) == to_string(NUM_PINS))
			{
				//a strike was thrown: inform the user and add the frame to the game
				cout << "STRIKE!!" << endl << endl;
				game.addFrame(NUM_PINS, 0);
				
				//set bool to true so we can move on to the next frame
				is_valid_input = true;
				
			} //end if
			
			else
			{
				//a strike was not thrown: ask for and get score of the second throw
				cout << "Frame " << i << ", throw 2:   ";
				getline(cin, second_throw_input);
			
				//trim the inputs then put them into streams
				stringstream convert1(trim_copy(first_throw_input));
				stringstream convert2(trim_copy(second_throw_input));
			
				//validate inputs
				//valid only if the entire stream can be stored in an int variable AND within appropriate score range
				valid_throw_one = convert1 >> first_throw_score && !(convert1 >> first_throw_input) && first_throw_score >= 0 && first_throw_score <= NUM_PINS;
				valid_throw_two = convert2 >> second_throw_score && !(convert2 >> second_throw_input) && second_throw_score >= 0 && second_throw_score <= NUM_PINS;
				//valid input only if both scores are valid
				is_valid_input = valid_throw_one && valid_throw_two;
				
				if(!is_valid_input)
				{
					//either a character other than a numeral was entered or a number outside our range
					cout << "Oops! Please only enter scores between 0 and " << NUM_PINS << ". Please try again" << endl << endl;
				} //end if
				
				else if(first_throw_score + second_throw_score > NUM_PINS)
				{
					//both valid inputs, but their sum was too large
					cout << "The two throw scores you have entered exceed the maximum of " << NUM_PINS << ". Please try again" << endl << endl;
					is_valid_input = false;
				} //end else if
				
				else
				{
					//completely valid input: display appropriate message, add the frame to the game, and move on to the next frame
					int pins_down = first_throw_score + second_throw_score;
					string message = pins_down == NUM_PINS ? "Spare!" : "You knocked down " + to_string(pins_down) + " pins this frame.";
					cout << message << endl << endl;
					
					game.addFrame(first_throw_score, second_throw_score);
				} //end else
				
				
			} //end else
			
		} while(!is_valid_input); //keep asking user for input before moving to the next frame until valid throws are entered
		cout << "Your score is " << game.getScore() << endl << endl;
	} //end for
	
	
	//get inputs for final frame
	do
	{
		
	
	
		//ask for and get score of first two throws
		cout << "Frame " << NUM_PINS << ", throw 1:   ";
		getline(cin, first_throw_input);
		
		//check if a strike was thrown
		if(trim_copy(first_throw_input) == to_string(NUM_PINS)) cout << "STRIKE!! You get another rack!" << endl << endl;
		
		cout << "Frame " << NUM_PINS << ", throw 2:   ";
		getline(cin, second_throw_input);
		
		//can only get a strike on the second throw if the first throw was also a strike
		if(trim_copy(first_throw_input) == to_string(NUM_PINS) && trim_copy(second_throw_input) == to_string(NUM_PINS)) cout << "STRIKE!! You get one throw on another rack!" << endl << endl;
		
		//trim the inputs then put them into streams
		stringstream convert1(trim_copy(first_throw_input));
		stringstream convert2(trim_copy(second_throw_input));
	
		//validate inputs
		//valid only if the entire stream can be stored in an int variable AND within appropriate score range
		valid_throw_one = convert1 >> first_throw_score && !(convert1 >> first_throw_input) && first_throw_score >= 0 && first_throw_score <= NUM_PINS;
		valid_throw_two = convert2 >> second_throw_score && !(convert2 >> second_throw_input) && second_throw_score >= 0 && second_throw_score <= NUM_PINS;
		//valid input only if both scores are valid
		is_valid_input = valid_throw_one && valid_throw_two;
		
		if(!is_valid_input)
		{
			//either a character other than a numeral was entered or a number outside our range
			cout << "Oops! Please only enter scores between 0 and " << NUM_PINS << ". Please try again." << endl << endl;
		}
		else if(first_throw_score != NUM_PINS && first_throw_score + second_throw_score > NUM_PINS)
		{
			//both valid inputs, but their sum was too large after not throwing a strike on the first throw
			cout << "The two throw scores you have entered exceed the maximum of " << NUM_PINS << ". Please try again" << endl << endl;
			is_valid_input = false;
		} //end else if
		else if(first_throw_score + second_throw_score < NUM_PINS)
		{
			//didn't get a strike or a spare in the first two throws: don't ask for a third input
			cout << "You knocked down " + to_string(first_throw_score + second_throw_score) + " pins this frame." << endl << endl;
			game.addFrame(first_throw_score, second_throw_score);
		}
		
		////////
		//situations in which a third throw is asked for
		////////
		else
		{
			bool spare = false;
			int pins_down;
			
			if(first_throw_score != NUM_PINS && first_throw_score + second_throw_score == NUM_PINS)
			{
				//first throw wasn't a strike, but first two throws add up to a spare
				cout << "Spare! You get another throw!" << endl << endl;
				spare = true;
			}
			
			//ask for and get score of third throw
			cout << "Frame " << NUM_PINS << ", throw 3:   ";
			getline(cin, third_throw_input);
		
			if(trim_copy(third_throw_input) == to_string(NUM_PINS) && (spare || second_throw_score == NUM_PINS) ) 
			{
				//third throw was a strike; this means either that the first two throws were a spare, or the second throw was a strike
				cout << "STRIKE!!" << endl << endl;
				
				//add the frame and let the user know how many pins were knocked down in this frame
				pins_down = first_throw_score + second_throw_score + NUM_PINS;
			    cout << "You knocked down " << pins_down << " pins this frame." << endl << endl;
				game.addFrame(first_throw_score, second_throw_score, NUM_PINS);	
			}
			else
			{
				//trim the input then put into stream
				stringstream convert3(trim_copy(third_throw_input));
			
				//validate input
				//valid only if the entire stream can be stored in an int variable AND within appropriate score range
				valid_throw_three = convert3 >> third_throw_score && !(convert3 >> third_throw_input) && third_throw_score >= 0 && third_throw_score <= NUM_PINS;
		
				is_valid_input = valid_throw_three;
				
				if(!is_valid_input)
				{
					//either a character other than a numeral was entered or a number outside our range
					cout << "Oops! Please only enter scores between 0 and " << NUM_PINS << ". Please try again." << endl << endl;
				}
				else if(first_throw_score == NUM_PINS && second_throw_score != NUM_PINS && second_throw_score + third_throw_score > NUM_PINS)
				{
					//a strike was thrown on the first throw but not on the second throw... 
					//this means that the sum of throws 2 and 3 cannot exceed NUM_PINS
					cout << "The second and third throw scores you have entered exceed the maximum of " << NUM_PINS << ". Please try again" << endl << endl;
					is_valid_input = false;
				}
				else
				{	
					//all valid inputs: check for spare on the last two throws, show frame score, and add the frame
					if(first_throw_score == NUM_PINS && second_throw_score != NUM_PINS && second_throw_score + third_throw_score == NUM_PINS)
					{
						//first throw strike = new rack for second throw
						//second throw was not a strike, but then a spare was thrown on third throw
						
						cout << "Spare!" << endl;
					}
					pins_down = first_throw_score + second_throw_score + third_throw_score;
					cout << "You knocked down " << pins_down << " pins this frame." << endl << endl;
					
					game.addFrame(first_throw_score, second_throw_score, third_throw_score);
				}
				
			}
			
		}
	} while(!is_valid_input);
	
	cout << "Your final score is " << game.getScore() << endl << endl;

	
	system("PAUSE");
    return 0;
}
