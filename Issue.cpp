#include "Issue.h"
#include "User.h"
#include <iostream>
#include <string>
#include <fstream>

// file with Issue class functions, constructors, and destructors

using namespace std;

int counter1 = 1; // to create unique ints

// empty constructor for Issue object
Issue::Issue() {
    // if no name is added let int be the id
    this->iD = to_string(counter1);
    counter1++;
    this->type = UserStory;
    this->reporter = nullptr;
    this->assignee = nullptr;
    this->priority = 1;
    this->status = Open;
    this->createdDate = "";
    this->description = "";
    this->comments = "";
    this->timeFrame = 4;
}
Issue::Issue(string s, User* u) {
    this->iD = s;
    this->type = UserStory;
    this->reporter = u;
    this->assignee = nullptr;
    this->priority = 1;
    this->status = Open;
    this->createdDate = "";
    this->description = "";
    this->comments = "";
    this->timeFrame = 3;
}
Issue::Issue(string s, User* u, User* p) {
    this->iD = s;
    this->type = UserStory;
    this->reporter = u;
    this->assignee = p;
    this->priority = 1;
    this->status = Open;
    this->createdDate = "";
    this->description = "";
    this->comments = "";
    this->timeFrame = 1;}

Issue::Issue(string s, User* u, IssueType t, int p, string d, string des, string c, int f) {
    this->iD = s;
    this->type = t;
    this->reporter = u;
    this->assignee = u;
    this->priority = p;
    this->status = Open;
    this->createdDate = d;
    this->description = des;
    this->comments = c;
    this->timeFrame = f;}

// constructor that takes in all properties for Issue object
Issue::Issue(string s, IssueType i, User* r, User* a, int p, StatusType st, string c, string d, string cc, int t) {
    this->iD = s;
    this->type = i;
    this->reporter = r;
    this->assignee = a;
    this->priority = p;
    this->status = st;
    this->createdDate = c;
    this->description = d;
    this->comments = cc;
    this->timeFrame = t;
}

// returns the unique iD of the issue
string Issue::getId() { return iD;};
// changes the iD name to given string
void Issue::setId(string I) {this->iD = I;};

// returns the Issue Type as a string
string Issue::getIType() {

    switch(type) {
        case UserStory:
            return "User Story";
            break;
        case Task:
            return "Task";
            break;
        case Build:
            return "Build";
            break;
        case Test:
            return "Test";
            break;
        case Debug:
            return "Debug";
            break;
        case Documentation:
            return "Documentation";
            break;
        default:
            return "";
    }
}
// changes the type of the Issue
void Issue::setIType(string I) {
    if (I == "User Story") {
        this->iD = UserStory;
    }
    else if (I == "Task") {
        this->iD = Task;
    }
    else if (I == "Build") {
        this->iD = Build;
    }
    else if (I == "Test") {
        this->iD = Test;
    }
    else if (I == "Debug") {
        this->iD = Debug;
    }
    else if (I == "Documentation") {
        this->iD = Documentation;
    }
}

// returns the pointer of the reporter
User* Issue::getReporter() {return reporter;}
// sets the pointer of user as reporter
void Issue::setReporter(User* r) {this->reporter = r;}

// returns the pointer of the assigned user
User* Issue::getAssignee() {return assignee;}
// sets the assigned user as the pointer
void Issue::setAssignee(User* a) {this->assignee = a;}

// returns the priority of the issue
int Issue::getPriority() {return priority;}
// sets the priority of the issue by given int
void Issue::setPriority(int p) {this->priority = p;}

// gets the status of the Issueand returns as string
string Issue::getStatus() {
    switch(status) {
        case Open:
            return "Open";
            break;
        case InProgress:
            return "In Progress";
            break;
        case Done:
            return "Done";
            break;
        case OverDue:
            return "Overdue";
            break;
        default:
            return "";}
    }

// sets the status of the issue depending on the given string
void Issue::setStatus(string s) {
    if (s.compare("Open") == 0) {
        this->status = Open;
    }
    else if (s.compare("In Progress") == 0) {
        this->status = InProgress;
    }
    else if (s.compare("Done") == 0) {
        this->status = Done;
    }
    else if (s.compare("Overdue") == 0) {
        this->status = OverDue;
    }
}

// returns the date of the issue
string Issue::getDate() {return createdDate;}
// changes the date of the issue using given string
void Issue::setDate(string s) {this->createdDate = s;}

// returns the comments of the issue
string Issue::getComments() {return comments;}
// changes the comments of the isssue using given string
void Issue::setComments(string c) {this->comments = c;}

// returns the description of issue
string Issue::getDescription() {return description;}
// changes the description using given string
void Issue::setDescription(string d) {this->description = d;}

// gets the timeFrame of the issue
int Issue::getTime() {return timeFrame;}
// changes the timeFrame of the issue // by subtracting the given int from timeFrame
void Issue::setTime(int i) {this->timeFrame = i;}
void Issue::changeTimeBy(int t) {// subtracts time by given int and modifies the timeFrame of Issue
    if (t < timeFrame) {
        this->timeFrame = timeFrame - t;
    }
    else {// if int is greater then timeframe we make it 0 instead of negative number
        this->timeFrame = 0;
    }
}

void Issue::printIssue() {
    // prints out each property of Issuecout << "Issue ID: " << getId();
    cout << "\nIssue Type: " << getIType();
    User* r = getReporter();
    if (r == nullptr) {
        cout << "\nReporter: no reporter";
    }
    else {
        cout << "\nReporter: " << r->getName();
    }
    User* a = getAssignee();
    if (a == nullptr) {
        cout << "\nAssignee: no assignee";
    }
    else {
        cout << "\nAssignee: " << a->getName();
    }
    cout << "\nStatus Type: " << getStatus();
    cout << "\nTime Left:" << getTime();
    cout << "\nCreated Date: " << getDate();
    cout << "\nDescription: " << getDescription();
    cout << "\nComments: " << getComments();
}

void Issue::output() {
    ofstream out(IFILE, ios_base::app);
    out << getId() << endl;
    out << getIType() << endl;
    out << reporter->getName() << endl;
    out << assignee->getName() << endl;
    out << getPriority() << endl;
    out << getStatus() << endl;
    out << getDate() << endl;
    out << getDescription() << endl;
    out << getComments() << endl;
    out << endl;
    out.close();
}
