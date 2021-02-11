#ifndef PROFILEMANAGER_H_
#define PROFILEMANAGER_H_
#include <iostream>
#include <fstream>
using namespace std;

#define PROFILE_NAME_LENGTH 50
#define SIZE_ENLARGE_PER_STEP 50

typedef struct profile_ {
	char name[PROFILE_NAME_LENGTH + 1];
	int points;
}Profile;


class ProfileManager {
public:
	ProfileManager();
	virtual ~ProfileManager();
	void addProfile(string name, string str_points);
	void updateProfile(string name, int points);
	void outFile(ofstream& outFile);
	Profile* searProfile(string name);
private:
	int m_size;
	int m_used;
	Profile* p_head;
};

#endif /* PROFILEMANAGER_H_ */
