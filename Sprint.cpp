#include "Sprint.h"
#include "Issue.h"
#include <string>
#include <iostream>
#include <fstream>

// functions, constructors and destructors of sprint class

using namespace std;

int counter3 = 0;

// empty constructor to create Sprint object
Sprint::Sprint() {
    this->name = "Sprint " + to_string(counter3);
    counter3++;
    this->jobs = {};
    int timeFrame = 7;
}
// constructor that takes in a list of Issue pointers, an int to create Sprint object
Sprint::Sprint(vector<Issue*> i, int t) {
    this->name = "Sprint " + to_string(counter3);
    counter3++;
    this->jobs = i;
    this->timeFrame = t;
}
// constructor that takes in a list of Issue pointers to create Sprint object
Sprint::Sprint(vector<Issue*> i) {
    this->name = "Sprint " + to_string(counter3);
    counter3++;
    this->jobs = i;
    this->timeFrame = rand() % 14 + 7;
}
Sprint::~Sprint() {
  // delete ptrs
};

// gets the string which is name of sprint
string Sprint::getName() {return name;}
// changes the name of sprint using the given string
void Sprint::setName(string d) {this->name = d;}

// gets the timeFrame of the sprint
int Sprint::getTimeFrame() {return timeFrame;}
// set timeframe of sprint by given int
void Sprint::setTimeFrame(int i) {this->timeFrame = i;}
// changes the sprint by reducing timeFrame given int
void Sprint::changeTimeFrameBy(int d) {
    if (d < timeFrame) {
        this->timeFrame = timeFrame - d;
    }
    else {
        this->timeFrame = 0;
    }
}

// returns the size of the jobs Sprint has
int Sprint::numJobs() {
    int num = 0;
    for (auto j : jobs) {
        num++;
    }
    return num;
}

// returns the list of issues
vector<Issue*> Sprint::getJobs() {return jobs;}


// adds an issue to list of issues
void Sprint::addJob(Issue* s) {
    jobs.push_back(s);
}

// removes issues that are done
vector<Issue*> Sprint::removeDoneJobs() {
  vector<Issue*> vec;
  // go through vector and see which have already been completed
    for (int i = 0; i < numJobs(); i++) {
        if (jobs[i]->getTime() == 0) {
            // changes status to done
            jobs[i]->setStatus("Done");
            // adds issue to vector
            vec.push_back(jobs[i]);
            // removes issue from sprint
            jobs.erase(jobs.begin() + i);
        }
    }
    return vec; // will return issues that will be moved to done
}

// removes issues that are not done from sprint
vector<Issue*> Sprint::removeNotDone() {
  vector<Issue*> vec;
  // go through vector and see which have not been completed
    for (int i = 0; i < numJobs(); i++) {
        if (jobs[i]->getTime() != 0) {
            // changes status to done
            jobs[i]->setStatus("Overdue");
            // adds issue to vector
            vec.push_back(jobs[i]);
            // removes issue from sprint
            jobs.erase(jobs.begin() + i);
        }
    }
    return vec; // will return issues that will be moved to done
}

// remove given issue from list of issues
void Sprint::removeJob(Issue * j) {
  // finds issue in list of issues and removes it
    for (int i = 0; i < numJobs(); i++) {
        if (jobs[i]->getId().compare(j->getId()) == 0) {
            jobs.erase(jobs.begin() + i);
        }
    }
}

// runs sprint and changes the days left before sprint is over and issues are due
vector<vector<Issue*>> Sprint::runSprint(int i) {
  vector<vector<Issue*>> vec;
    changeTimeFrameBy(i);
    for (auto j : jobs) {
        j->changeTimeBy(i);
    }
    // remove jobs that are done
    vec.push_back(removeDoneJobs());
    vec.push_back(removeNotDone());
  return vec;
}

// prints sprint
void Sprint::printSprint() {
    cout << "Sprint: " << getName();
    cout << "Time left for Sprint: " << getTimeFrame() << endl;
    // goes through list of issues and prints issue
    vector<Issue*> j = getJobs();
    for (auto i : j) {
        i->printIssue();
        cout << endl;
    }
}

// checks if the issue is inside sprint
bool Sprint::issueInHere(Issue* i) {
  bool myb = false;
  vector<Issue*> vec = getJobs();
  // if issue exists then we rturn true
  for (auto j : vec) {
    if (i->getId().compare(j->getId())== 0) {
      myb = true;
    }
  }
  return myb;
}

void Sprint::output() {
    ofstream out(SFILE, ios_base::app);
    out << name << endl;
    out << timeFrame << endl;
    out << numJobs();
    for(auto j : jobs) {
        out << " " << j->getId();
    }
    out << endl;
    out << endl;
    out.close();
}