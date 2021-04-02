#include <map>
#include "TwitterData.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = { {"rangerPower","Smit","Rick","smitRick@gmail.com","1117","power lifting"},
                             {"kittyKat72","Smith","Kathryn","kat@gmail.com","56","health"},
                             {"lexi5","Anderson","Alexis","lexi5@gmail.com","900","education"},
                             {"savage1","Savage","Ken","ksavage@gmail.com","17","president"},
                             {"smithMan","Smith","Rick","rick@hotmail.com","77","olympics"} };
    TwitterData *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }

    ///////////////////////////////////////////////////////////////////
    //                        Map Scenario 1                         //
    ///////////////////////////////////////////////////////////////////

    // Create a new std::map
    map<string, TwitterData> usernameMap;

    // Insert all Twitter data into the std::map
    for (int i = 0; i < 5; ++i)
    {
        usernameMap[twitter_data[i].getUserName()] = twitter_data[i];
    }

    // Iterate through the std::map and print the key-value pairs
    map<string, TwitterData>::const_iterator iter;
    for (iter = usernameMap.begin(); iter != usernameMap.end(); iter++)
    {
        cout << "[" << iter->first << "]:\t" << iter->second.print() << endl;
    }
    cout << endl;
    cout << endl;

    // Find the person whose username is savage1
    iter = usernameMap.find("savage1");
    if (iter != usernameMap.end())
    {
        // print out the entire record
        cout << iter->second.print() << endl;

        // Remove this person from the map
        usernameMap.erase(iter);
    }
    cout << endl;
    cout << endl;

    ///////////////////////////////////////////////////////////////////
    //                        Map Scenario 2                         //
    ///////////////////////////////////////////////////////////////////

    // Create a new std::map
    map<string, TwitterData> emailMap;

    // Insert all Twitter data into the std::map
    for (int i = 0; i < 5; ++i)
    {
        emailMap[twitter_data[i].getEmail()] = twitter_data[i];
    }

    // Iterate through the std::map and print the key-value pairs
    for (iter = emailMap.begin(); iter != emailMap.end(); iter++)
    {
        cout << "[" << iter->first << "]:\t" << iter->second.print() << endl;
    }
    cout << endl;
    cout << endl;

    // Find the person whose email is kat@gmail.com
    iter = emailMap.find("kat@gmail.com");
    if (iter != emailMap.end())
    {
        // print out the entire record
        cout << iter->second.print() << endl;

        // Remove this person from the map
        emailMap.erase(iter);
    }

    delete[] twitter_data;
    return 0;
}