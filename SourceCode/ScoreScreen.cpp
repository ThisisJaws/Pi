#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(irr::gui::IGUIEnvironment *guiEnvironment){
	guienv = guiEnvironment;

	//Init all gui elements then hide them
	finalScore = guienv->addStaticText(L"Final Score: DISPLAY TEST", irr::core::rect<irr::s32>(0, 10, 300, 40));
	finalScore->setVisible(false);
}

void ScoreScreen::addScore(const std::string &playerName, const unsigned int &score){
	//Add it onto the vector
	scores.push_back(scoreData(playerName, score));
	//Then sort the vector
	sortVector(scores);
}

void ScoreScreen::displayScore(const bool &display){
	finalScore->setVisible(display);
	//instructionsText->setVisible(display);
	//for(int i = 0; i < MAX_DISPLAY; i++){
	//	scoreNumbers[i]->setVisible(display);
	//}
}

void ScoreScreen::writeToFile(){

}

void ScoreScreen::sortVector(std::vector<scoreData> &vectorToSort){
	
}
