#ifndef ISSUE_TRACKING_SYSTEM_CS3520_SPRINT_H
#define ISSUE_TRACKING_SYSTEM_CS3520_SPRINT_H

// header file Sprint class

#include <string>
#include <vector>
class Issue;

using namespace std;

// Sprint class
class Sprint {
protected:
    // name of Sprint
    string name;
    // issues in Sprint
    vector<Issue*> jobs;
    // how long the sprint will last
    int timeFrame;

public:
    // empty constructor to create Sprint Object
    Sprint();
    
    // constructor that takes in a list of Issue ptrs on int to create Sprint object
    Sprint(vector<Issue*> i, int t);

    // constructor that takes in a list of Issue pointers to create Sprint object
    Sprint(vector<Issue*> i);

    // destructor of Sprint object
    ~Sprint();

    // gets the name of the Sprint
    string getName();

    // changes the name of sprint using the given string
    void setName(string d);

    // gets the timeFrame of the sprint
    int getTimeFrame();

    // sets timeframe by given int
    void setTimeFrame(int i);

    // changes the sprint by reducing timeFrame given int
    void changeTimeFrameBy(int d);

    // returns the size of the jobs Sprint has
    int numJobs();

    // gets the vector of issue ptr
    vector<Issue*> getJobs();

    // adds Issue ptr to  sprint
    void addJob(Issue* s);

    // removes Issue ptr to sprint to move to done
    vector<Issue*> removeDoneJobs();

     // removes Issue ptr of sprint to move back todo
    vector<Issue*> removeNotDone();

    // removes Issue ptr to sprint
    void removeJob(Issue * j);

    // runs the sprint and changes the deadlines of Sprint and it's jobs
    vector<vector<Issue*>> runSprint(int i);

    // prints out sprint
    void printSprint();

    // does the issue exist in sprint
    bool issueInHere(Issue* i);

    // file output for persistence
    void output();
};


#endif //ISSUE_TRACKING_SYSTEM_CS3520_SPRINT_H
