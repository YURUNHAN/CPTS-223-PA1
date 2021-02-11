#ifndef MAINMENU_H_
#define MAINMENU_H_
#include <iostream>

#include "LinkedList.h"
#include "ProfileManager.h"
using namespace std;

#define INFO_MAIN_MENU "1. Game Rules\n\
2. Play Game\n\
3. Load Previous Game\n\
4. Add Command\n\
5. Remove Command\n\
6. Exit\n\n"

#define INFO_GAME_RULES "1. Please choose 2 to play the game\n\
2. Please choose how many commands/questions you want to play\n\
3. For each question, there is 1 linux commmand, and 3 desciptions, please choose the right description\n\
4. Score 1 for right choose, score -1 for wrong choose\n\
5. After all question answered, you will get final score\n\
6. Only choose Exit will save the commands and your final score\n\n"


class MainMenu {
public:
	MainMenu();
	void launch();
	virtual ~MainMenu();

private:
	void showGameRules();
	void loadGame();
	void addCommand();
	void removeCommand();
	void exitGame();
	void init();
	void loadCommands();
	string inputName();
	void saveCmdCsvFile(string csfFile);
	void saveProfilesFile(string csfFile);
	int inputNumberofQuestions();
	void playGame(Profile* p_Profile);
	void loadProfiles();
	void splayGame(Profile* p_Profile);
	void updateProfile(string name, int points);
	void showPrompt(int index, CmdNode<string>* p_Node, string cmdName);
	int getChoice(int right_choice, CmdNode<string>* p_targetNode, CmdNode<string>* p_SpareNode_1, CmdNode<string>* p_SpareNode_2, int asked);
	LinkedList<string> linkedlist;
	ProfileManager profilemanager;
	string m_name;
	int m_score;
};

#endif /* MAINMENU_H_ */
