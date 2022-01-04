#include "User.h"
#include "types.h"
#include "Issue.h"
#include "Sprint.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// functions, constructors, and destructors for user class

int counter2 = 0;

// empty constructor for User class
User::User() {
    this->name = to_string(counter2);
    counter2++;
    this->project = nullptr;
    this->tasks = {};
    this->sprints = {};
    type = user;
}
// constructor with name parameter for User class
User::User(string s) {
    this->name = s;
    this->project = nullptr;
    this->tasks = {};
    this->sprints = {};
    type = user;
}
// get the name of the user
string User::getName() {return name;}
// sets the name of the user using the given string
void User::setName(string s) {this->name = s;}

// returns the project of the user
Project* User::getProject() {return project;}
// sets the project of the user using the given pointer
void User::setProject(Project* p) {this->project = p;}

// gets the list of issues of the user
vector<Issue*> User::getIssues() {return tasks;}
// adds given issue to list
void User::addIssue(Issue* i) {tasks.push_back(i);}
// remove given issue in list
void User::removeIssue(Issue* o) {
    int s = tasks.size();
    for (int i = 0; i < s; i++) {
        if (o->getId().compare(tasks[i]->getId())) {
            tasks.erase(tasks.begin() + i);
        }
    }
}

// gets the list of sprints of the user
vector<Sprint*> User::getSprints() {return sprints;}
// adds given sprint in list
void User::addSprint(Sprint* s) {sprints.push_back(s);}
// remove given sprint in list
void User::removeSprint(Sprint* s) {
    int i = sprints.size();
    for (int j = 0; j < i; j++) {
        if (s == sprints[j]) {
            sprints.erase(sprints.begin() + j);
        }
    }
}

// prints the project of user
void User::printProject() {
    // prints out name of project
    cout << "Project: " << project->getTitle() << endl;
    cout << "inside print project" << endl;
    // prints out project owner
    cout << "Owner: " << project->getOwner()->getName();
    // prints out project leads
    cout << "Project leads: ";
    vector<User*> pl = project->getLeads();
    // if vector is empty print this
    if (pl.size() == 0) {
      cout << "No Project Leads" << endl;
    }
    else {// print out vector
      for (int i = 0 ; i < pl.size(); i++) {
          cout << pl[i]->getName() << endl;
      }
    }
    // prints out team teamMembers
    cout << "Team Members: ";
    vector<User*> tm = project->getTeam();
    // if vector is empty print this
    if (tm.size() == 0) {
      cout << "No Team Members" << endl;
    }
    else {// print out vector
      for (int i = 0 ; i < tm.size(); i++) {
        cout << tm[i]->getName() << endl;
      }
    }
    // prints out issues in to do
    vector<Issue*> td = project->getToDo();
    cout << "Issues in To Do" << endl;
    // if vector is empty print this
    if (td.size() == 0) {
      cout << "No Issues in To Do" << endl;
    }
    else {// print out vector
      for (auto t : td) {
        t->printIssue();
        cout << endl;
      }
    }
    vector<Sprint*> ip = project->getInProg();
    cout << "Sprints" << endl;
    // if vector is empty print this
    if (ip.size() == 0) {
      cout << "No sprints in progress" << endl;
    }
    else { // print out vector
      for (auto s : ip) {
        s->printSprint();
        cout << endl;
      }
    }
    vector<Issue*> d = project->getDone();
    cout << "Issues that are Done" << endl;
    // if vector is empty print this
    if (d.size() == 0) {
      cout << "No Issues are Done" << endl;
    }
    else {// print out vector
      for (auto t : d) {
        t->printIssue();
        cout << endl;
      }
    }
}

// prints out given issue of user
void User::printIssue(string s) {
  bool happen = false;
  vector<Issue*> is = getIssues();

  for (auto i : is) {
    if (i->getId().compare(s) == 0) {
      i->printIssue();
      cout << endl;
      happen = true;
    }
  }

  if (!happen) {
    cout << "Issue is not found in your tasks" << endl;
  }
}

// prints out given sprint
void User::printSprint(string s) {
  bool happen = false;
  vector<Sprint*> sp = getSprints();

  for (auto p : sp) {
    if (p->getName().compare(s) == 0) {
      p->printSprint();
      cout << endl;
      happen = true;
    }
  }

  if (!happen) {
    cout << "No sprint with that name." << endl;
  }
}

void User::output() {
    ofstream out(UFILE, ios_base::app);
    out << type << endl;
    out << name << endl;
    out << sprints.size();
    for(auto s : sprints) {
        out << " " << s->getName();
    }
    out << endl;
    out << tasks.size();
    for(auto t : tasks) {
        out << " " << t->getId();
    }
    out << endl;
    out << endl;
    out.close();
}

UserType User::getType() {
    return type;
}
