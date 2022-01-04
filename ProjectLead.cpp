#include "ProjectLead.h"
#include "User.h"
#include "TeamMember.h"
#include "Project.h"
#include <string>
#include <iostream>
// file for ProjectLead class

ProjectLead::ProjectLead() : User(){type = lead;}
ProjectLead::ProjectLead(string s) : User(s){type = lead;}
ProjectLead::~ProjectLead(){
  delete project;
}

Project* ProjectLead::viewProject() {return project;}

// invites user to project
void ProjectLead::inviteUser(string u, int i) { // make this into string and create user
    if (project->nameExist(u)) {
      cout << "\nUser cannot be added.\n";
    }
    else{
      User * us = nullptr;
      if (i == 1) {
        us = new ProjectLead(u);
      }
      else {
        us = new TeamMember(u);
      }
      us->setProject(project);
      if (i == 1) {
        project->addLeads(us);
      }
      else {
        project->addTeam(us);
      }
    }
}

void ProjectLead::changeDeadlineOfSprintBy(int i) {
  // gets project of lead and changes the deadline sprint by given int
    Project* p = project;
    vector<Sprint*> v = p->getInProg();
    int size = v.size();
    if (size != 0) {
      v[size-1]->changeTimeFrameBy(i);
    }
}

// adds issue to todo of lead's project
void ProjectLead::addIssueToDo(Issue * i) {
    project->addToDo(i);
}

// remove member from project
void ProjectLead::removeMember(string u) {
    bool inHere = false;
    if (project->nameExist(u)) {
      vector<User*> pl = project->getLeads();
      for (int p = 0; p < pl.size(); p++) {
        if (pl[p]->getName().compare(u) == 0) {
          pl.erase(pl.begin() + p);
        }
      }
      vector<User*> tm = project->getTeam();
      for (int p = 0; p < tm.size(); p++) {
        if (tm[p]->getName().compare(u) == 0) {
          tm.erase(tm.begin() + p);
        }
      }
    }
}

// delete issue
void ProjectLead::deleteIssue(Issue * i) {
    project->removeToDo(i);
    for (auto s : sprints) {
        project->removeIssueInProgress(s, i);
    }
    project->removeDone(i);
}

// makes project and assigns the ProjectLead to be owner of project
// and sets ProjectLead's project as the new one
void ProjectLead::makeProject(string s) {
    Project* p =  new Project(s, this);
    setProject(p);
    //delete p; to do later
}

// changes the deadline of the project by the gven int
void ProjectLead::changeDeadlineOfProject(int i) {
  project->setDeadline(i);
}

// changes name of the projcet
void ProjectLead::changeNameOfProj(string s) {
  project->setTitle(s);
}

// creates the sprint with given timeframe
void ProjectLead::createSprint(int i) {
  // random number generated of how many issues will be in sprint
  int numJobs = rand() % 5 + 1;
  vector<Issue*> move;
  // gets list of issues to move to from todo
  vector<Issue*> cop = project->getToDo();
  
  // while num jobs is greater than 0
  while (numJobs > 0) {
    // create an issue ptr
    Issue* temp = nullptr;
    // goes through list of issues in todo
    for (int i = 0; i < cop.size(); i++) {
      if (temp == nullptr) { // if null, then make first item to be temp
        temp = cop[i];
      }
      // if the next issue has greaer priority make that the new temp
      else if (temp->getPriority() <= cop[i]->getPriority()) {
        temp = cop[i];
      }
    }
    // in the end will be left with ptr that has greater priority
    // push back that ptr to issues that will be moved to sprint
    move.push_back(temp);
    // reduce numjobs by 1
    numJobs--;
  }
  // remove the issues in move in toDo
  for (auto m : move) {
    project->removeToDo(m);
  }
  // creates a sprint using list of issues and timeframe
  Sprint* s = new Sprint(move, i);
  // adds sprint to in progress
  project->addInProg(s);
  addSprint(s);
}

void ProjectLead::addIssueToSprint(Sprint* s, Issue* i) {
  vector<Sprint*> spr = project->getInProg();
  string name = s->getName();
  // goes through the list of sprints
  for (auto j : spr) {
    // finds the sprint to add the given issue too
    if(name.compare(j->getName())==0) {
      j->addJob(i);
    }
  }
}

void ProjectLead::changeIssueName(string iss, string n) {
  // get the vectors of todo, inprogress, and done
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  // bool which will return true is issue has been found
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the name to given string
  for (auto a : td) {
    // if found, we perform function
    if (iss.compare(a->getId()) == 0) {
      a->setId(n);
      isin = true;
    }
  }
  // if issue has not been found we see if in progress
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        // if found we perform function
        if (iss.compare(c->getId()) == 0) {
          c->setId(n);
          isin = true;
        }
      }
    }
  }
  // if issue has not been found we see if in workdone
  if(!isin) {
    for (auto e : d) {
      // if issue is found we perform action
      if (iss.compare(e->getId()) == 0) {
        e->setId(n);
        isin = true;
      }
    }
  }
  // if not we send message, not found
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}

void ProjectLead::changeIssuePriority(string iss, int n) {
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the priority to given int
  for (auto a : td) {
    if (iss.compare(a->getId()) == 0) {
      a->setPriority(n);
      isin = true;
    }
  }
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        if (iss.compare(c->getId()) == 0) {
          c->setPriority(n);
          isin = true;
        }
      }
    }
  }
  if(!isin) {
    for (auto e : d) {
      if (iss.compare(e->getId()) == 0) {
        e->setPriority(n);
        isin = true;
      }
    }
  }
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}

void ProjectLead::changeIssueType(string iss, string n) {
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the issuetype using given string
  for (auto a : td) {
    if (iss.compare(a->getId()) == 0) {
      a->setIType(n);
      isin = true;
    }
  }
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        if (iss.compare(c->getId()) == 0) {
          c->setIType(n);
          isin = true;
        }
      }
    }
  }
  if(!isin) {
    for (auto e : d) {
      if (iss.compare(e->getId()) == 0) {
        e->setIType(n);
        isin = true;
      }
    }
  }
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}

void ProjectLead::changeIssueStatus(string iss, string n) {
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the issue status using given string
  for (auto a : td) {
    if (iss.compare(a->getId()) == 0) {
      a->setStatus(n);
      isin = true;
    }
  }
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        if (iss.compare(c->getId()) == 0) {
          c->setStatus(n);
          isin = true;
        }
      }
    }
  }
  if(!isin) {
    for (auto e : d) {
      if (iss.compare(e->getId()) == 0) {
        e->setStatus(n);
        isin = true;
      }
    }
  }
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}

void ProjectLead::changeIssueTime(string iss, int n) {
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the timeframe to given string
  for (auto a : td) {
    if (iss.compare(a->getId()) == 0) {
      a->setTime(n);
      isin = true;
    }
  }
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        if (iss.compare(c->getId()) == 0) {
          c->setTime(n);
          isin = true;
        }
      }
    }
  }
  if(!isin) {
    for (auto e : d) {
      if (iss.compare(e->getId()) == 0) {
        e->setTime(n);
        isin = true;
      }
    }
  }
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}

void ProjectLead::changeIssueDate(string iss, string n) {
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the date created to given string
  for (auto a : td) {
    if (iss.compare(a->getId()) == 0) {
      a->setDate(n);
      isin = true;
    }
  }
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        if (iss.compare(c->getId()) == 0) {
          c->setDate(n);
          isin = true;
        }
      }
    }
  }
  if(!isin) {
    for (auto e : d) {
      if (iss.compare(e->getId()) == 0) {
        e->setDate(n);
        isin = true;
      }
    }
  }
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}

void ProjectLead::changeIssueComments(string iss, string n) {
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the comments to given string
  for (auto a : td) {
    if (iss.compare(a->getId()) == 0) {
      a->setComments(n);
      isin = true;
    }
  }
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        if (iss.compare(c->getId()) == 0) {
          c->setComments(n);
          isin = true;
        }
      }
    }
  }
  if(!isin) {
    for (auto e : d) {
      if (iss.compare(e->getId()) == 0) {
        e->setComments(n);
        isin = true;
      }
    }
  }
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}

void ProjectLead::changeIssueDescript(string iss, string n) {
  vector<Issue*> td = project->getToDo();
  vector<Sprint*> ip = project->getInProg();
  vector<Issue*> d = project->getDone();
  bool isin = false;
  // finds the issue in either todo, inprogress, or done and changes the description to given string
  for (auto a : td) {
    if (iss.compare(a->getId()) == 0) {
      a->setDescription(n);
      isin = true;
    }
  }
  if (!isin) {
    for (auto b : ip) {
      vector<Issue*> t = b->getJobs();
      for (auto c : t) {
        if (iss.compare(c->getId()) == 0) {
          c->setDescription(n);
          isin = true;
        }
      }
    }
  }
  if(!isin) {
    for (auto e : d) {
      if (iss.compare(e->getId()) == 0) {
        e->setDescription(n);
        isin = true;
      }
    }
  }
  if(!isin) {
    cout << "\nIssue does not exist" << endl;
  }
}
