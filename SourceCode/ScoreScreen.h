#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include <vector>
#include <algorithm>

#include "irrlicht.h"

//How many names to display
#define MAX_DISPLAY 10

//Location of the score file
#define SCORE_FILE "Assets/Score.sts"

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
		irr::core::stringw playerName;
		unsigned int finalScore;
		scoreData(const irr::core::stringw &name, const unsigned int &score){
			playerName = name;
			finalScore = score;
		}
	};

	//Most recent score for easy display
	unsigned int mostRecentScore;

	//Vector of scores
	std::vector<scoreData> scores;

	//Text elements to display all of the scores
	irr::gui::IGUIStaticText *finalScore;
	irr::gui::IGUIStaticText *instructionsText;
	irr::gui::IGUIStaticText *scoreNumbers[MAX_DISPLAY];

	//Structure used for sorting
	struct more_than_sort{
		inline bool operator() (const scoreData &sc1, const scoreData &sc2){
			return (sc1.finalScore > sc2.finalScore);
		}
	};

	//FUNCTIONS
public:
	//constructor
	ScoreScreen(irr::gui::IGUIEnvironment *guiEnvironment);

	//Adds a score onto the vector
	void addScore(const irr::core::stringw &playerName, const unsigned int &score);

	//Displays the score on screen
	void displayScore(const bool &display);

	//Call to write the score to file
	void writeToFile();

private:
	//Sorts a vector from highest to lowest
	void sortVector(std::vector<scoreData> &vectorToSort);
};

#endif
