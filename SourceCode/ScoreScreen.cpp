#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(irr::gui::IGUIEnvironment *guiEnvironment){
	guienv = guiEnvironment;

	//Read in the data from the file
	readFromFile(SCORE_FILE);

	//Init all gui elements then hide them
	finalScore = guienv->addStaticText(L"Final Score: DISPLAY TEST", irr::core::rect<irr::s32>(0, 10, 600, 40), true);
	finalScore->setVisible(false);
	instructionsText = guienv->addStaticText(L"Enter your name: TEST", irr::core::rect<irr::s32>(0, 50, 500, 80), true);
	instructionsText->setVisible(false);
	int x = 10, y = 100;
	for(int i = 0; i < MAX_DISPLAY; i++){
		irr::core::stringw count;
		count += (i + 1);
		scoreNumbers[i] = guienv->addStaticText(count.c_str(), irr::core::rect<irr::s32>(x, y, x + 300, y + 30), true);
		scoreNumbers[i]->setVisible(false);
		y += 35;
	}
}

ScoreScreen::~ScoreScreen(){
	//Write to file on destruct
	writeToFile(SCORE_FILE);
}

void ScoreScreen::addScore(const irr::core::stringc &playerName, const unsigned int &score){
	//Add it onto the vector
	scores.push_back(scoreData(playerName, score));
	//Then sort the vector
	sortVector(scores);
	//Then set the most recetn score
	mostRecentScore = score;
}

void ScoreScreen::displayScore(const bool &display){
	//Set and display the final score
	irr::core::stringw finalScoreText("Final Score: ");
	finalScoreText += mostRecentScore;
	finalScore->setText(finalScoreText.c_str());
	finalScore->setVisible(display);

	//Display the 'instructions'
	instructionsText->setVisible(display);

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
		scoreNumbers[i]->setVisible(display);
	}
}

void ScoreScreen::readFromFile(std::string file){
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

void ScoreScreen::writeToFile(std::string file){
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
