#ifndef ISSUE_TRACKING_SYSTEM_CS3520_TEAMMEMBER_H
#define ISSUE_TRACKING_SYSTEM_CS3520_TEAMMEMBER_H

#include "User.h"
#include "Project.h"
#include "Issue.h"
#include "Sprint.h"

// header file for TeamMember class (child class of User)

// forward declarations
class User;
class Issue;
class Project;
class Sprint;

class TeamMember : public User {
public:
    // empty constructor for TeamMember object
    TeamMember();

    // constructor that takes in string for TeamMember object
    TeamMember(string s);

    // destructor for TeamMember object
    ~TeamMember();
    
    // create new issue -> sent to to do
    void addIssueToDo(string s, IssueType i, string d, string des, string com, int pri, int time);

    // user can comment issue + assign issue to current user
    void addToMyIssue(Issue * i);

    // adds given string as comment to given issue
    void addCommentToIssue(Issue* i , string s);
};


#endif //ISSUE_TRACKING_SYSTEM_CS3520_TEAMMEMBER_H
