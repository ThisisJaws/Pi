#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include <vector>
#include <algorithm>
#include <string>

#include "irrlicht.h"

//How many names to display
#define MAX_DISPLAY 10

/*
 * Score screen class will hold all of the data for the scores and 
 * read and write any files associated with such
 */

class ScoreScreen{
	//VARIABLES
private:
	//Reference to the gui environment
	irr::gui::IGUIEnvironment *guienv;

	//Structure to hold the score and name
	struct scoreData{
		std::string playerName;
		unsigned int finalScore;

		scoreData(const std::string &name, const unsigned int &score){
			playerName = name;
			finalScore = score;
		}
	};

	//Vector of scores
	std::vector<scoreData> scores;

	//Text elements to display all of the scores
	irr::gui::IGUIStaticText *finalScore;
	irr::gui::IGUIStaticText *instructionsText;
	irr::gui::IGUIStaticText *scoreNumbers[MAX_DISPLAY];

	//FUNCTIONS
public:
	//constructor
	ScoreScreen(irr::gui::IGUIEnvironment *guiEnvironment);

	//Adds a score onto the vector
	void addScore(const std::string &playerName, const unsigned int &score);

	//Displays the score on screen
	void displayScore(const bool &display);

	//Call to write the score to file
	void writeToFile();

private:
	//Sorts a vector from highest to lowest
	void sortVector(std::vector<scoreData> &vectorToSort);
};

#endif
