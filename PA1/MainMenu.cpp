#include "MainMenu.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

MainMenu::MainMenu() {
	// TODO Auto-generated constructor stub
	init();
	m_name = "";
	m_score = 0;
}

MainMenu::~MainMenu() {
	// TODO Auto-generated destructor stub
}


void MainMenu::showGameRules(){
	cout << INFO_GAME_RULES;
}

string MainMenu::inputName(){
	string tmpName;
	do {
		cout << "Please input your name: ";
		cin >> tmpName;
		if(tmpName.length() > 0 && tmpName.length() <= PROFILE_NAME_LENGTH)
			break;
		else if(tmpName.length() <= 0){
			cout << "Please input a valid name" << endl;
		}
		else {
			cout << "name length should not be larger than " << PROFILE_NAME_LENGTH << endl;
		}
	}while(true);
	return tmpName;
}

int MainMenu::inputNumberofQuestions(){
	int numberofquestions;
	do {
		cout << "Please input how many commands/questions to generate for matching: ";
		cin >> numberofquestions;
		if(numberofquestions >= 5 && numberofquestions <= 30)
			break;
		else if(numberofquestions <5 ){
			cout << "need be larger than 5" << endl;
		}
		else {
			cout << "need be less than 30" << endl;
		}
	}while(true);
	return numberofquestions;
}

void MainMenu::showPrompt(int index, CmdNode<string>* p_Node, string cmdName){
	int cmd_length = cmdName.length();
	if(index == 0){
		cout << cmdName;
	}
	else
		cmd_length = 0;

	string left_string = p_Node->getDescription();
	left_string = to_string(index + 1) + ". " + left_string;
	int left_count = left_string.length();
	while(left_count > 0){
		for(int i = 0; i < 30 - cmd_length; i ++){
			cout << ' ';
		}
		cmd_length = 0;
		cout.width(-60);
		if(left_count > 60){
			string cur_left = left_string.substr(0, 60);
			left_string = left_string.substr(60, left_count - 59);
			cout << cur_left << endl;
			left_count = left_string.length();
		}
		else {
			cout << left_string << endl << endl;
			left_count = 0;
		}
	}
}

int MainMenu::getChoice(int right_choice, CmdNode<string>* p_targetNode, CmdNode<string>* p_SpareNode_1, CmdNode<string>* p_SpareNode_2, int asked){
	int index = 0;
	int spare_displayed = false;
	while( index < 3){
		if(index == right_choice) {
			showPrompt(index, p_targetNode, p_targetNode->getName());
		}
		else {
			if(spare_displayed == false)
				showPrompt(index, p_SpareNode_1,  p_targetNode->getName());
			else
				showPrompt(index, p_SpareNode_2,  p_targetNode->getName());
			spare_displayed = true;
		}
		index ++;
	}

	int userChoice;
	cout << "User input scenario " << asked + 1 << ":";
	do {
		cin >> userChoice;
		if(userChoice >=0  && userChoice <= 3)
			break;
		else {
			cout << "Please choose option 1-3" << endl;
		}
	}while(true);
	return userChoice;
}

void MainMenu::playGame(Profile* p_Profile){
	if(p_Profile == NULL) {
		m_name = inputName();
	}
	else {
		m_name = p_Profile->name;
		m_score = p_Profile->points;
	}
	int numberofquestions = inputNumberofQuestions();
	linkedlist.resetFlag();

	int asked = 0;
	int target_index;
	int count_not_asked;
	int righ_choice = -1;

	while(asked < numberofquestions){
		count_not_asked = linkedlist.getCount() - asked;
		target_index = rand() % count_not_asked;
		CmdNode<string>* p_targetNode = linkedlist.getAskedNode(target_index);
		CmdNode<string>* p_SpareNode_1 = linkedlist.getUnAskedNode(p_targetNode, NULL);
		CmdNode<string>* p_SpareNode_2 = linkedlist.getUnAskedNode(p_targetNode, p_SpareNode_1);

		righ_choice = rand() % 3;

		int userChoice = getChoice(righ_choice, p_targetNode, p_SpareNode_1, p_SpareNode_2, asked);
		if(righ_choice + 1 == userChoice){
			m_score ++;
			cout << "Correct! " << p_targetNode->getName() << " - " << p_targetNode->getDescription();
			cout << "You have been awarded 1 point. Your point total is " << m_score << "." << endl;
		}
		else {
			m_score --;
			cout << "Incorrect! " << p_targetNode->getName() << " - " << p_targetNode->getDescription();
			cout << "You have lost 1 point. Your point total is " << m_score << "." << endl;
		}

		p_targetNode->setFlag(true);
		asked ++;
	}
	profilemanager.updateProfile(m_name, m_score);
}

void MainMenu::loadGame(){
	string profileName;
	Profile* p_Profile;
	do {
		cout << "Please input the profile name to load: ";
		cin >> profileName;
		p_Profile = profilemanager.searProfile(profileName);
		if(p_Profile != NULL){
			break;
		}
		else {
			cout << profileName << " not found" << endl;
		}
	}while(true);

	cout << "Current score: " << p_Profile->points << endl;

	playGame(p_Profile);
}

void MainMenu::addCommand(){
	string cmdName;
	string cmdPrompt;
	do {
		cout << "Please input the command to add: ";
		cin >> cmdName;
		if(linkedlist.existsCmd(cmdName) == true){
			cout << "duplicate command found" << endl;
		}
		else if(cmdName == "quits"){
			return;
		}
		else if(cmdName.length() == 0){
			cout << "Please input valid command" << endl;
		}
		else {
			break;
		}
	}while(true);

	do {
		cout << "Please input the description: ";
		getchar();
		getline(cin, cmdPrompt, '\n');
		if(cmdPrompt == "quits"){
			return;
		}
		else if(cmdPrompt.length() == 0){
			cout << "Please input valid description" << endl;
		}
		else {
			break;
		}
	}while(true);

	linkedlist.insertAtFront(cmdName, cmdPrompt);
	cout << cmdName << " added" << endl;
}

void MainMenu::removeCommand(){
	string cmdName;
	do {
		cout << "Please input the command to remove: ";
		cin >> cmdName;
		if(linkedlist.existsCmd(cmdName) == false){
			cout << "command not found" << endl;
		}
		else if(cmdName == "quits"){
			return;
		}
		else if(cmdName.length() == 0){
			cout << "Please input valid command" << endl;
		}
		else {
			break;
		}
	}while(true);

	linkedlist.removeNode(cmdName);
	cout << cmdName << " removed" << endl;
}

void MainMenu::saveCmdCsvFile(string csfFile){
    ofstream outFile;
    outFile.open(csfFile, ios::out);
    linkedlist.outFile(outFile);
    outFile.close();
}

void MainMenu::saveProfilesFile(string csfFile){
    ofstream outFile;
    outFile.open(csfFile, ios::out);
    profilemanager.outFile(outFile);
    outFile.close();
}

void MainMenu::exitGame(){
	saveCmdCsvFile("commands.csv");
	saveProfilesFile("profiles.csv");
	cout << "Game Exited" << endl;
}

void MainMenu::loadCommands(){
	ifstream in("commands.csv");
	string cmdName;
	string cmdDescription;
	if (in.fail()){
		cout << "commands.csv not found" <<endl;
		exit(-1);
	}

    while(in.good() )
    {
    	getline(in, cmdName, ',');
    	getline(in, cmdDescription, '\n');
    	if(cmdName.empty() || cmdDescription.empty())
    		break;
    	cmdDescription = cmdDescription.substr(1, cmdDescription.length()-2);
    	linkedlist.insertAtFront(cmdName, cmdDescription);
    }
    in.close();
}

void MainMenu::loadProfiles(){
	ifstream in("profiles.csv");
	string name;
	string str_points;
	if (in.fail()){
		cout << "profiles.csv not found" <<endl;
		exit(-1);
	}

    while(in.good() )
    {
    	getline(in, name, ',');
    	getline(in, str_points, '\n');
    	if(name.length() == 0 || str_points.length() == 0)
    		break;
    	profilemanager.addProfile(name, str_points);
    }
    in.close();
}

void MainMenu::init(){
	loadCommands();
	loadProfiles();
}

void MainMenu::launch(){
	int option;
	bool quit_flag = false;

	while(quit_flag == false) {
		cout << INFO_MAIN_MENU;
		cin >> option;
		switch(option) {
		case 1:
			showGameRules();
			break;
		case 2:
			playGame(NULL);
			break;
		case 3:
			loadGame();
			break;
		case 4:
			addCommand();
			break;
		case 5:
			removeCommand();
			break;
		case 6:
			exitGame();
			quit_flag = true;
			break;
		default:
			printf("Unknown option. \n");
			break;
		}
	}
}
