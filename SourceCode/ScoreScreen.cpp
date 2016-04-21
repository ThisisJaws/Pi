#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(irr::gui::IGUIEnvironment *guiEnvironment){
	guienv = guiEnvironment;

	//Read in the data from the file
	readFromFile(SCORE_FILE);

	mostRecentScore = 0;
	currentLetter = 0;
	nameEntered = false;
	now = 0;
	then = 0;
	frameDeltaTime = 0;
	flashCurrent = 0;
	flashWait = 0.25f;

	//Init all gui elements
	finalScore = guienv->addStaticText(L"Final Score: ERROR", irr::core::rect<irr::s32>(0, 10, 800, 40));
	finalScore->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_UPPERLEFT);
	instructionsText = guienv->addStaticText(L"Enter your name below then press ACCEPT", irr::core::rect<irr::s32>(0, 50, 800, 80));
	instructionsText->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_UPPERLEFT);

	int x = 336, y = 100;
	for(int i = 0; i < NAME_LENGTH; i++){
		playerName[i] = guienv->addStaticText(L"A", irr::core::rect<irr::s32>(x, y, x + 30, y + 40));
		x += 34;
	}

	x = 10; y = 160;
	for(int i = 0; i < MAX_DISPLAY; i++){
		irr::core::stringw count;
		count += (i + 1);
		scoreNumbers[i] = guienv->addStaticText(count.c_str(), irr::core::rect<irr::s32>(x, y, x + 780, y + 40));
		scoreNumbers[i]->setVisible(false);
		y += 45;
	}

	//Hide all the elements
	displayScore(false);

	//Make sure the text variables are reset
	resfreshScoreBoard();
}

ScoreScreen::~ScoreScreen(){
	//Write to file on destruct
	writeToFile(SCORE_FILE);
}

bool ScoreScreen::waitForPlayerName(EventReceiver *receiver, irr::u32 realTime){
	if(nameEntered){
		return true;
	}

	//Work out frame delta time to make the letters flash
	now = realTime;
	frameDeltaTime = (irr::f32)(now - then) / 1000.0f;
	then = now;

	//If the player presses enter then add the name to the score
	if(receiver->isStartPressed()){
		irr::core::stringc name;
		for(int i = 0; i < NAME_LENGTH; i++){
			name += playerName[i]->getText();
		}
		addNameToRecentScore(name);
		playerName[currentLetter]->setVisible(true);
		nameEntered = true;
	}

	//Chane the letter when the player presses up or down
	if(receiver->isUpPressed()){
		//Get the letter in each box, increment, then set
		irr::core::stringw letter = playerName[currentLetter]->getText();
		if(letter[0] < 'Z'){
			letter[0]++;
			playerName[currentLetter]->setText(letter.c_str());
		}
	} else if(receiver->isDownPressed()){
		//Get the letter in each box, de-increment, then set
		irr::core::stringw letter = playerName[currentLetter]->getText();
		if(letter[0] > 'A'){
			letter[0]--;
			playerName[currentLetter]->setText(letter.c_str());
		}
	}

	//Move to the next letter when the player presses right
	if(receiver->isRightPressed()){
		if(currentLetter + 1 < NAME_LENGTH){
			playerName[currentLetter]->setVisible(true);
			currentLetter++;
		}
	} else if(receiver->isLeftPressed()){
		if(currentLetter > 0){
			playerName[currentLetter]->setVisible(true);
			currentLetter--;
		}
	}

	//Make the current letter flash
	if(flashCurrent >= flashWait){
		playerName[currentLetter]->setVisible(!playerName[currentLetter]->isVisible());
		flashCurrent = 0;
	} else{
		flashCurrent += frameDeltaTime;
	}


	return false;
}

void ScoreScreen::addScore(unsigned int score){
	//Set the most recent score
	mostRecentScore = score;
	irr::core::stringw finalScoreText("Final Score: ");
	finalScoreText += score;
	finalScore->setText(finalScoreText.c_str());
}

void ScoreScreen::displayScore(const bool &display){
	//Display the final score
	finalScore->setVisible(display);

	//Display the 'instructions'
	instructionsText->setVisible(display);

	//Display the player's name
	for(int i = 0; i < NAME_LENGTH; i++){
		playerName[i]->setVisible(display);
	}

	//Set the visibility of the numbers
	for(int i = 0; i < MAX_DISPLAY; i++){
		scoreNumbers[i]->setVisible(display);
	}
}

void ScoreScreen::reset(){
	currentLetter = 0;
	nameEntered = false;
}

void ScoreScreen::addNameToRecentScore(const irr::core::stringc &playerName){
	//Remove any spaces from the string
	std::string newName = playerName.c_str();
	newName.erase(std::remove_if(newName.begin(), newName.end(), isspace), newName.end());
	//Add it onto the vector
	scores.push_back(scoreData(newName.c_str(), mostRecentScore));
	//Then sort the vector
	sortVector(scores);

	//Make sure the text variables are reset
	resfreshScoreBoard();
}

void ScoreScreen::resfreshScoreBoard(){
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
