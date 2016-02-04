#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(irr::gui::IGUIEnvironment *guiEnvironment){
	guienv = guiEnvironment;

	//Init all gui elements then hide them
	finalScore = guienv->addStaticText(L"Final Score: DISPLAY TEST", irr::core::rect<irr::s32>(0, 10, 300, 40), true);
	finalScore->setVisible(false);
	instructionsText = guienv->addStaticText(L"INSTRUCTIONS DISPLAY TEST", irr::core::rect<irr::s32>(0, 30, 300, 60), true);
	instructionsText->setVisible(false);
	int x = 10, y = 65;
	for(int i = 0; i < MAX_DISPLAY; i++){
		irr::core::stringw count;
		count += (i + 1);
		scoreNumbers[i] = guienv->addStaticText(count.c_str(), irr::core::rect<irr::s32>(x, y, x + 300, y + 30), true);
		scoreNumbers[i]->setVisible(false);
		y += 35;
	}
}

void ScoreScreen::addScore(const irr::core::stringw &playerName, const unsigned int &score){
	//Add it onto the vector
	scores.push_back(scoreData(playerName, score));
	//Then sort the vector
	sortVector(scores);
}

void ScoreScreen::displayScore(const bool &display){
	finalScore->setVisible(display);
	instructionsText->setVisible(display);
	for(int i = 0; i < MAX_DISPLAY; i++){
		//change the text to the score data
		irr::core::stringw text;
		text += (i + 1);
		if(i < scores.size()){
			text += scores.at(i).playerName;
			text += ": ";
			text += scores.at(i).finalScore;
		}
		scoreNumbers[i]->setText(text.c_str());
		scoreNumbers[i]->setVisible(display);
	}
}

void ScoreScreen::writeToFile(){

}

void ScoreScreen::sortVector(std::vector<scoreData> &vectorToSort){
	
}
