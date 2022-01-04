#include "TeamMember.h"
#include "types.h"
#include <string>
#include <iostream>

class Project;

// file with functions, constructors, and destructor of teammember class

using namespace std;

// empty construcor for TeamMember object
TeamMember::TeamMember() : User() {type = member;};

// constructor that takes in string for teamemeber object
TeamMember::TeamMember(string s) : User(s) {type = member;};

// destructor for TeamMember
TeamMember::~TeamMember() {};

// create new issue -> sent to to do
void TeamMember::addIssueToDo(string s, IssueType i, string d, string des, string com, int pri, int time) {
  // member creates an issue
  Issue* is = new Issue(s, this, i, pri, d, des, com, time);
  // adds it to their task
  addIssue(is);
  // adds it toDo in project
  project->addToDo(is);
}

// user can comment issue + assign issue to current user
void TeamMember::addToMyIssue(Issue* i) {
  i->setAssignee(this);
  addIssue(i);
}

// add given string as comment to given issue
void TeamMember::addCommentToIssue(Issue * i, string s) {
  i->setComments(s);
}
