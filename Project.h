#ifndef ISSUE_TRACKING_SYSTEM_CS3520_PROJECT_H
#define ISSUE_TRACKING_SYSTEM_CS3520_PROJECT_H

#include "User.h"
#include "Project.h"
#include "Issue.h"
#include "Sprint.h"
#include <vector>
#include <string>

// header file for Project class

// forward declarations
class Issue;
class Sprint;
class User;
class ProjectLead;

using namespace std;

// Project class
class Project {
protected:
// properties of Project
    string title;
    vector<Issue*> toDo;
    vector<Sprint*> inProgress;
    vector<Issue*> workDone;
    User* projectOwner;
    vector<User*> projectLeads;
    vector<User*> teamMembers;
    int deadlineIn;
public:
    // empty constructor for Project object
    Project();
    // constructor for Project object with title properties & projectOwner
    Project(string s, User* u);
    // constructor for Project object with title properties & projectOwner & deadline
    Project(string s, User* u, int d);
    // destructor for Project object
    ~Project();

    // gets the title of the project
    string getTitle();

    // sets the title of project to given string
    void setTitle(string s);

    // gets the todo list of project
    vector<Issue*> getToDo();

    // adds issue to todo
    void addToDo(Issue* i);

    // removes given issue in todo
    void removeToDo(Issue* j);


    // gets the deadline of the project
    int getDeadline();

    // sets the deadline of the project to given int
    void setDeadline(int i);


    // gets the list of sprints in inrpogress
    vector<Sprint*> getInProg();

    // adds issue to inprogress
    void addInProg(Sprint* s);

    // removes given sprint in inprogress
    void removeInProg(Sprint* s);

    // removes issues in given sprint in progress
    void removeIssueInProgress(Sprint * t, Issue* i);

    // gets list of issues in done
    vector<Issue*> getDone();

    // addes issue to done
    void addDone(Issue* i);

    // removes given issue in done
    void removeDone(Issue* j);

    // gets the owner which is user of project
    User* getOwner();

    // sets the owner as given user
    void setOwner(User* u);


    // gets the list of users that are projectleads
    vector<User*> getLeads();

    // adds a user to list of project leads
    void addLeads(User* u);

    // removes given user  in project leads
    void removeLeads(User* u);

    // gets the list of team members
    vector<User*> getTeam();

    // adds given user to list of teamMembers
    void addTeam(User* u);

    // removes given user from list of team members
    void removeTeam(User* u);

    // checks if the username exists within project
    bool nameExist(string s);

    // file output for persistence
    void output();

    // output everything to all the files
    void save();

    // runs sprint in project
    void runASprint(int i);
};


#endif //ISSUE_TRACKING_SYSTEM_CS3520_PROJECT_H
