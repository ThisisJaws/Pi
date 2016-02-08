#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(irr::gui::IGUIEnvironment *guiEnvironment){
	guienv = guiEnvironment;

	//Read in the data from the file
	readFromFile(SCORE_FILE);

	mostRecentScore = 0;

	//Init all gui elements then hide them
	finalScore = guienv->addStaticText(L"Final Score: DISPLAY TEST", irr::core::rect<irr::s32>(0, 10, 800, 40), true);
	finalScore->setVisible(false);

	instructionsText = guienv->addStaticText(L"Enter your name then press R", irr::core::rect<irr::s32>(0, 50, 800, 80), true);
	instructionsText->setVisible(false);

	int x = 10, y = 160;
	for(int i = 0; i < MAX_DISPLAY; i++){
		irr::core::stringw count;
		count += (i + 1);
		scoreNumbers[i] = guienv->addStaticText(count.c_str(), irr::core::rect<irr::s32>(x, y, x + 780, y + 40), true);
		scoreNumbers[i]->setVisible(false);
		y += 35;
	}

	playerName = guienv->addEditBox(L"NAME", irr::core::rect<irr::s32>(0, 90, 800, 120), true);
	playerName->setVisible(false);

	//Make sure the text variables are reset
	resfreshScreen();
}

ScoreScreen::~ScoreScreen(){
	//Write to file on destruct
	writeToFile(SCORE_FILE);
}

void ScoreScreen::addScore(unsigned int score){
	//Set the most recent score
	mostRecentScore = score;
	irr::core::stringw finalScoreText("Final Score: ");
	finalScoreText += score;
	finalScore->setText(finalScoreText.c_str());
}

void ScoreScreen::addName(const irr::core::stringc &playerName){
	//Add it onto the vector
	scores.push_back(scoreData(playerName, mostRecentScore));
	//Then sort the vector
	sortVector(scores);

	//Make sure the text variables are reset
	resfreshScreen();
}

void ScoreScreen::displayScore(const bool &display){
	//Display the final score
	finalScore->setVisible(display);

	//Display the 'instructions'
	instructionsText->setVisible(display);

	//Display the player's name
	playerName->setVisible(display);

	//Set the visibility of the numbers
	for(int i = 0; i < MAX_DISPLAY; i++){
		scoreNumbers[i]->setVisible(display);
	}
}

void ScoreScreen::resfreshScreen(){
	//Update each score text
	for(int i = 0; i < MAX_DISPLAY; i++){
		//Change the text to the score data
		irr::core::stringw text;
		text += (i + 1);
		text += ": ";
		if(i < scores.size()){
			text += scores.at(i).playerName;
			text += " ";
			text += scores.at(i).finalScore;
		}
		scoreNumbers[i]->setText(text.c_str());
	}
}

void ScoreScreen::readFromFile(const std::string &file){
	//Open the file
	std::ifstream scoreFile(file);
	//The string that will hold each line of the file
	std::string line;

	if(scoreFile.is_open()){
		//Loop through each line
		while(std::getline(scoreFile, line)){
			//Get each 'word' (name then score) line by line
			std::stringstream stream(line);
			//Variables to hold the data
			std::string name;
			unsigned int score;
			//Insert the data into the variables
			stream >> name;
			stream >> score;
			//Push the scores onto the vector
			scores.push_back(scoreData(name.c_str(), score));
		}

		//Close the file when done
		scoreFile.close();
	} else{
		printf("Unable to open score file for reading");
	}
}

void ScoreScreen::writeToFile(const std::string &file){
	//Open the file
	std::ofstream scoreFile(file);

	if(scoreFile.is_open()){
		//Write in the score data
		for(int i = 0; i < scores.size(); i++){
			scoreFile << scores.at(i).playerName.c_str() << " " << scores.at(i).finalScore << "\n";
		}
		//Close the file
		scoreFile.close();
	} else{
		printf("Unable to open score file for writing");
	}
}

void ScoreScreen::sortVector(std::vector<scoreData> &vectorToSort){
	//Sort the vector using the structure
	std::sort(scores.begin(), scores.end(), more_than_sort());
}
