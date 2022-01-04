#ifndef ISSUE_TRACKING_SYSTEM_CS3520_USER_H
#define ISSUE_TRACKING_SYSTEM_CS3520_USER_H

// header file for user class

#include <vector>
#include <string>
#include "types.h"
class Project;
class Issue;
class Sprint;

using namespace std;

// User class
class User {
protected:
// properties of user file
    string name;
    UserType type;
    Project* project;
    vector<Issue*> tasks;
    vector<Sprint*> sprints;
public:
    // empty constructor for User class
    User();

    // constructor with name parameter for USer class
    User(string s);

    // get the name of the user
    string getName();

    // sets the name of the user using the given string
    void setName(string s);

    // returns the project of the user
    Project* getProject();

    // sets the project of the user using the given pointer
    void setProject(Project* p);

    // gets the list of issues of the user
    vector<Issue*> getIssues();

    // adds given issue to list
    void addIssue(Issue* i);

    // remove given issue in list
    void removeIssue(Issue* o);

    // gets the list of sprints of the user
    vector<Sprint*> getSprints();

    // adds given sprint in list
    void addSprint(Sprint* s);

    // remove given sprint in list
    void removeSprint(Sprint* s);

    // prints user's project
    void printProject();

    // file output for persistence
    void output();

    // prints issue that belongs to user
    void printIssue(string s);

    // prints the sprint of user
    void printSprint(string s);

    UserType getType();
};


#endif //ISSUE_TRACKING_SYSTEM_CS3520_USER_H
