#include <string.h>
#include "ProfileManager.h"

ProfileManager::ProfileManager() {
	// TODO Auto-generated constructor stub
	m_size = SIZE_ENLARGE_PER_STEP;
	m_used = 0;
	p_head = new Profile[SIZE_ENLARGE_PER_STEP];
}

ProfileManager::~ProfileManager() {
	// TODO Auto-generated destructor stub
	if( p_head != NULL)
		delete p_head;
}

void ProfileManager::addProfile(string name, string str_points){
	if(name.length() > PROFILE_NAME_LENGTH){
		cout << "Name too long" <<endl;
		exit(-1);
	}

	if(m_used + 1 > m_size){
		m_size += SIZE_ENLARGE_PER_STEP;	//enlarge size by SIZE_ENLARGE_PER_STEP each time
		Profile* p_newHead = new Profile[m_size];
		memcpy(p_newHead, p_head, sizeof(Profile) * (m_size - SIZE_ENLARGE_PER_STEP));
		delete p_head;
		p_head = p_newHead;
	}

	memcpy(p_head + 1, p_head, sizeof(Profile) * m_used);
	memcpy(p_head[0].name, name.c_str(), name.length() + 1);
	p_head[0].points = std::stoi(str_points);
	m_used ++;
}

void ProfileManager::updateProfile(string name, int points){
	for(int i = 0; i < m_used; i ++){
		if(name == p_head[i].name){
			p_head[i].points = points;
			return;
		}
	}
	addProfile(name, std::to_string(points));
}

void ProfileManager::outFile(ofstream& outFile){
	string name;
	for(int i = 0; i < m_used; i ++){
		name = p_head[i].name;
		outFile << name << "," << p_head[i].points << endl;
	}
}

Profile* ProfileManager::searProfile(string name){
	for(int i = 0; i < m_used; i ++){
		if(p_head[i].name == name)
			return &p_head[i];
	}
	return NULL;
}
