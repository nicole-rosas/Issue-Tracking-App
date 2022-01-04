#ifndef ISSUE_TRACKING_SYSTEM_CS3520_PROJECTLEAD_H
#define ISSUE_TRACKING_SYSTEM_CS3520_PROJECTLEAD_H

#include "User.h"
#include "Project.h"
#include "Issue.h"
#include "Sprint.h"
#include "TeamMember.h"

// header file for project lead class

// forward declarations
class User;
class Issue;
class Sprint;
class Project;

class ProjectLead : public User {
public:
    // empty constructor for ProjectLead class
    ProjectLead();

    // constructor for ProjectLead class that takes in their name
    ProjectLead(string s);

    // destructor for ProjectLead class
    ~ProjectLead();

    // ProjectLead can view their project // not sure if should be void or ptr
    Project* viewProject();

    // invites given user to projectleads'project
    void inviteUser(string u, int i);

    // modifies the deadline of the sprint in project to given int
    void changeDeadlineOfSprintBy(int i);

    // adds given issue to to-do of project
    void addIssueToDo(Issue* i);

    // removes given member from project
    void removeMember(string u);

    // delete issue
    void deleteIssue(Issue * i);

    // makes new project using the given name of string
    void makeProject(string s);

    // changes deadline of project to given int
    void changeDeadlineOfProject(int i);

    // changes name of project to given string
    void changeNameOfProj(string s);

    // creates a sprint
    void createSprint(int i);

    // adds issue to sprint
    void addIssueToSprint(Sprint* s, Issue* i);

    // changes the issue name
    void changeIssueName(string i, string s);

    // changes the issue's description
    void changeIssueDescript(string iss, string n);
    
    // changes the issue's comments
    void changeIssueComments(string iss, string n);

    // changes the issue's date
    void changeIssueDate(string iss, string n);

    // changes the issue's timeframe
    void changeIssueTime(string iss, int n);

    // changes the issue's status
    void changeIssueStatus(string iss, string n);

    // changes the issue's type
    void changeIssueType(string iss, string n);

    // changes the issues' priority
    void changeIssuePriority(string iss, int n);
};

#endif //ISSUE_TRACKING_SYSTEM_CS3520_PROJECTLEAD_H
