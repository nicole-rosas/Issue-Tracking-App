#include <fstream>
#include "Project.h"

// file for functions, constructors, and destructors of Project

// empty constructor for Project object
Project::Project() {
    this->title = "Main Project";
    this->toDo = {};
    this->inProgress = {};
    this->workDone = {};
    this->projectOwner = nullptr;
    this->projectLeads = {};
    this->teamMembers = {};
    this->deadlineIn = 10;
}
// constructor for Project object with title properties & projectOwner
Project::Project(string s, User* u) {
    this->title = s;
    this->toDo = {};
    this->inProgress = {};
    this->workDone = {};
    this->projectOwner = u;
    this->projectLeads = {};
    this->teamMembers = {};
    this->deadlineIn = 15;
}
// constructor for Project object with title properties & projectOwner & deadline
Project::Project(string s, User* u, int i) {
    this->title = s;
    this->toDo = {};
    this->inProgress = {};
    this->workDone = {};
    this->projectOwner = u;
    this->projectLeads = {};
    this->teamMembers = {};
    this->deadlineIn = i;
}
// destructor for Project object
Project::~Project() {};

// gets the title of the Project
string Project::getTitle() {return title;}

// sets the title of project as given string
void Project::setTitle(string s) {this->title = s;}

// gets the vector of to do issues 
vector<Issue*> Project::getToDo() {return toDo;}

// gets the deadline of the project
int Project::getDeadline() {return deadlineIn;}

// sets the deadline of the project by the given int
void Project::setDeadline(int i) {this->deadlineIn = i;}

// adds given issue to the to do list in project
void Project::addToDo(Issue* i) {toDo.push_back(i);}

// remove the given issue in to do
void Project::removeToDo(Issue* j) {
  // goes through todo and finds issue
    for (int i = 0; i < toDo.size(); i++) {
        if (toDo[i]->getId().compare(j->getId()) == 0) {
            toDo.erase(toDo.begin() + i);
        }
    }
}

// returns the list of sprints
vector<Sprint*> Project::getInProg() {return inProgress;}

// adds an issue to In Progress
void Project::addInProg(Sprint* s) {inProgress.push_back(s);}

// remvoes given issue to in Progress
void Project::removeInProg(Sprint* s) {
    // goes through list and finds sprint to be removed
    for (int i = 0; i < inProgress.size(); i++) {
        if (inProgress[i]->getName().compare(s->getName()) == 0) {
            inProgress.erase(inProgress.begin() + i);
        }
    }
}

// removes issue in Inprogress
void Project:: removeIssueInProgress(Sprint* t, Issue* s) {
  // goes inside and finds sprint to remove job
    for (int i = 0; i < inProgress.size(); i++) {
        if (inProgress[i]->getName().compare(t->getName()) == 0) {
            inProgress[i]->removeJob(s);
        }
    }
}

// gets the list of issues in done
vector<Issue*> Project::getDone() {return workDone;}

// adds an issue to done
void Project::addDone(Issue* i) {workDone.push_back(i);}

// removes an issue in Done
void Project::removeDone(Issue* j) {
    for (int i = 0 ; i < workDone.size(); i++) {
        if (workDone[i]->getId().compare(j->getId()) == 0) {
            workDone.erase(workDone.begin() + i);
        }
    }
}

// gets the user who is owner of projects
User* Project::getOwner() {return projectOwner;}

// sets the given user as owner of project
void Project::setOwner(User* u) {this->projectOwner = u;}

// gets the list of users who are project leads
vector<User*> Project::getLeads() {return projectLeads;}

// adds user to list of project leads
void Project::addLeads(User* u) {projectLeads.push_back(u);}

// removes a user from project leads
void Project::removeLeads(User* u) {
  // goes inside list of leads and finds user to remove
    for (int i = 0 ; i < projectLeads.size(); i++) {
        if (projectLeads[i]->getName().compare(u->getName())) {
            projectLeads.erase(projectLeads.begin() + i);
        }
    }
}

// gets the list of team members
vector<User*> Project::getTeam() {return teamMembers;}

// adds a user to list of team members
void Project::addTeam(User* u) {teamMembers.push_back(u);}

// removes members from list of team members
void Project::removeTeam(User* u) {
  // goes in list and finds member to remove
    for (int i = 0 ; i < teamMembers.size(); i++) {
        if (teamMembers[i]->getName().compare(u->getName()) == 0) {
            teamMembers.erase(teamMembers.begin() + i);
        }
    }
}

// checks if the given string exists as a name of user in project
// if it does return true
bool Project::nameExist(string s) {
    if (s.compare(getOwner()->getName()) == 0) {
        return true;
    }
    for (auto l : projectLeads) {
        if (s.compare(l->getName()) == 0) {
            return true;
        }
    }
    for (auto m : teamMembers) {
        if (s.compare(m->getName()) == 0) {
            return true;
        }
    }
    return false;
}

void Project::output() {
    ofstream out(PFILE, ios_base::app);
    out << title << endl;
    out << toDo.size();
    for(auto td : toDo) {
        out << " " << td->getId();
    }
    out << endl;
    out << inProgress.size();
    for(auto ip : inProgress) {
        out << " " << ip->getName();
    }
    out << endl;
    out << workDone.size();
    for(auto wd : workDone) {
        out << " " << wd->getId();
    }
    out << endl;
    out << projectOwner->getName() << endl;
    out << projectLeads.size();
    for(auto pl : projectLeads) {
        out << " " << pl->getName();
    }
    out << endl;
    out << teamMembers.size();
    for(auto tm : teamMembers) {
        out << " " << tm->getName();
    }
    out << endl;
    out << deadlineIn << endl;

    out << endl; // last newline
    out.close();
}

void Project::save() {
    // first, clear all the files
    ofstream out(PFILE);
    out.open(IFILE);
    out.open(SFILE);
    out.open(UFILE);
    out.close();
    output();
    for(auto it : toDo) { // output all the to do issues
        it->output();
    }
    for(auto it : inProgress) { // output all the sprints, and all the issues those sprints contain
        it->output();
        for(auto buriedIssue : it->getJobs()) {
            buriedIssue->output();
        }
    }
    for(auto it : workDone) { // output all the done issues
        it->output();
    }
    projectOwner->output(); // output the owner
    for(auto it : projectLeads) { // output all the leads
        it->output();
    }
    for(auto it : teamMembers) { // output all the team members
        it->output();
    }
}

// makes a sprint from the projects
void Project:: runASprint(int i) {
  int size = getInProg().size();
  Sprint* s = getInProg()[size - 1];
  // simulate sprint
  vector<vector<Issue*>> vecs = s->runSprint(i);
  // add the done issues to workdone
  vector<Issue*> done = vecs[0];
  for (auto d : done) {
    getDone().push_back(d);
  }
  // add the not done issues to todo
  vector<Issue*> notdone = vecs[1];
  for (auto w : notdone) {
    getToDo().push_back(w);
  }
}
