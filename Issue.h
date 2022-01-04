#ifndef ISSUE_TRACKING_SYSTEM_CS3520_ISSUE_H
#define ISSUE_TRACKING_SYSTEM_CS3520_ISSUE_H

#include <string>
#include "types.h"
#include "User.h"
#include "Project.h"
#include "Sprint.h"

// headerfile for Issue class

class User;

using namespace std;

// Issue class
class Issue {
protected:
// properties of Issue
    string iD;
    IssueType type;
    User* reporter;
    User* assignee;
    int priority;
    StatusType status;
    string createdDate;
    string description;
    string comments;
    int timeFrame;
public:
    // empty constructor for Issue object
    Issue();
    // constructor that takes in issue name and user ptr as reporter
    Issue(string s, User* u);
    // constructor that takes in issue name, user ptrs for reporter and assignee
    Issue(string s, User* u, User* u2);
    // constructor that takes in string, type, user ptr, priority, date, desc, comments.
    Issue(string s, User* u, IssueType t, int p, string d, string des, string c, int f);
    // constructor that takes in all properties for Issue object
    Issue(string s, IssueType i, User* r, User* a, int p, StatusType st, string c, string d, string cc, int t);
    // returns the unique iD of the issue
    string getId();
    // changes the iD name to given string
    void setId(string I);

    // returns the Issue Type as a string
    string getIType();

    // changes the type of the Issue
    void setIType(string I);

    // returns the pointer of the reporter
    User* getReporter();

    // sets the pointer of user as reporter
    void setReporter(User* r);

    // returns the pointer of the assigned user
    User* getAssignee();

    // sets the assigned user as the pointer
    void setAssignee(User* a);

    // returns the priority of the issue
    int getPriority();

    // sets the priority of the issue by given int
    void setPriority(int p);

    // gets the status of the Issue
    string getStatus();

    // sets the status of the issue depending on the given string
    void setStatus(string s);

    // returns the date of the issue
    string getDate();

    // changes the date of the issue using given string
    void setDate(string s);

    // returns the comments of the issue
    string getComments();

    // changes the comments of the issues using given string
    void setComments(string c);

    // returns the description of issue
    string getDescription();

    // changes the description using given string
    void setDescription(string d);

    // gets the timeFrame of the issue
    int getTime();

    // changes the timeFrame of the issue
    void setTime(int i);

    // changes the timeFrame of the issue by subtracting the given int from timeFrame
    void changeTimeBy(int t);
    
    // prints the issue
    void printIssue();

    // file output for persistence
    void output();
};

#endif //ISSUE_TRACKING_SYSTEM_CS3520_ISSUE_H
