// 12.15.2021
// Issue Tracking System


// main file for system

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

#include "Issue.h"
#include "User.h"
#include "Sprint.h"
#include "Project.h"
#include "ProjectLead.h"

using namespace std;

User * login(Project * project);

int main() {
    srand (time(NULL));
    string breaker = "------------------------\n";
    int choice1;

    // project name
    cout << "Issue Tracking System" << endl;
    cout << breaker;
    cout << "1 - Upload Existing Project? \n2 - Create New Project?" << endl;
    // take in user's input
    cout << "enter 1 or 2: ";
    cin >> choice1;
    // if input is incorrect, we keep asking user
    while (cin.fail() || (choice1 > 2 || choice1 < 1)) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please enter 1 or 2" << endl;
        cin >> choice1;
    }
    cout << breaker;
    Project * THEPROJECT = nullptr; // we'll assign this later
    User * loggedInUser = nullptr; // also assign this later
    // depending on their choice we go to different paths
    switch (choice1) {
        // loading project from file
        case 1: {
            // will need these later
            auto * project = new Project;
            string toDoIssues;
            string inProgressSprints;
            string workDoneIssues;
            string projectOwnerName;
            string projectLeads;
            string projectMembers;

            vector<Issue*> issues;
            map<Issue*, string> issueReporters;
            map<Issue*, string> issueAssignees;
            vector<Sprint*> sprints;
            map<Sprint*, string> sprintIssues;
            vector<User*> users;
            map<User*, string> userTasks;
            map<User*, string> userSprints;
            // read the project file (for the title)
            ifstream p(PFILE);
            string s1;
            int i1;
            getline(p, s1);
            project->setTitle(s1);
            getline(p, toDoIssues);
            getline(p, inProgressSprints);
            getline(p, workDoneIssues);
            getline(p, projectOwnerName);
            getline(p, projectLeads);
            getline(p, projectMembers);

            // read and create all the issues
            int numIssues;
            ifstream i(IFILE);
            i >> numIssues;
            i >> s1; // newline
            for(int count = 0; count < numIssues; count++) {
                auto * is = new Issue;
                issues.push_back(is);
                i >> s1;
                is->setId(s1);
                i >> s1;
                is->setIType(s1);
                i >> s1;
                issueReporters.insert({is, s1});
                i >> s1;
                issueAssignees.insert({is, s1});
                i >> i1;
                is->setPriority(i1);
                i >> s1;
                is->setStatus(s1);
                i >> s1;
                is->setDate(s1);
                getline(i, s1);
                is->setDescription(s1);
                getline(i, s1);
                is->setComments(s1);
                i >> i1;
                is->setTime(i1);
                i >> s1; // newline for end of issue
            }

            // read and create all the sprints
            ifstream sprintStream(SFILE);
            int numSprints;
            sprintStream >> numSprints;
            sprintStream >> s1; // newline
            for(int count = 0; count < numSprints; count++) {
                auto * sp = new Sprint;
                sprints.push_back(sp);
                sprintStream >> s1;
                sp->setName(s1);
                sprintStream >> i1;
                sp->setTimeFrame(i1);
                getline(sprintStream, s1); // list of all the issues, technically we could do this now, but we won't
                sprintIssues.insert({sp, s1});
                sprintStream >> s1; // newline
            }

            // read and create all the users
            int numUsers;
            ifstream u(UFILE);
            i >> numUsers;
            i >> s1; // newline
            for(int count = 0; count < numUsers; count++) {
                string type;
                u >> type;
                User *us = nullptr; // haven't picked a class yet
                if(type == "0") {
                    us = new User;
                } else if(type == "1") {
                    us = new TeamMember;
                } else if(type == "2") {
                    us = new ProjectLead;
                }
                u >> s1;
                us->setName(s1);
                getline(u, s1); // list of all the sprints, technically we could do this now, but we won't
                userSprints.insert({us, s1});
                getline(u, s1); // list of all the issues of this user
                userTasks.insert({us, s1});
                u >> s1; // newline
            }

            // now that we've created all the objects (and pointers to objects), we can assign the pointers to actual things
            stringstream ss(toDoIssues); // project's to do issues
            int numToDoIssues;
            ss >> numToDoIssues;
            for(int count = 0; count < numToDoIssues; count++) {
                string issueName;
                ss >> issueName;
                for(auto it : issues) {
                    if(it->getId() == issueName) {
                        project->addToDo(it);
                        break;
                    }
                }
            }
            ss.str(inProgressSprints); // project's sprints
            int numInProgressSprints;
            ss >> numInProgressSprints;
            for(int count = 0; count < numInProgressSprints; count++) {
                string sprintName;
                ss >> sprintName;
                for(auto it : sprints) {
                    if(it->getName() == sprintName) {
                        project->addInProg(it);
                        break;
                    }
                }
            }
            ss.str(workDoneIssues); // project's done issues
            int numDoneIssues;
            ss >> numDoneIssues;
            for(int count = 0; count < numDoneIssues; count++) {
                string issueName;
                ss >> issueName;
                for(auto it : issues) {
                    if(it->getId() == issueName) {
                        project->addDone(it);
                        break;
                    }
                }
            }
            for(auto it : users) { // find the project owner
                if(it->getName() == projectOwnerName) {
                    project->setOwner(it);
                    break;
                }
            }
            ss.str(projectLeads); // project's leaders
            int numProjectLeads;
            ss >> numProjectLeads;
            for(int count = 0; count < numProjectLeads; count++) {
                string leadName;
                ss >> leadName;
                for(auto it : users) {
                    if(it->getName() == leadName) {
                        project->addLeads(it);
                        break;
                    }
                }
            }
            ss.str(projectMembers); // project's members
            int numProjectMembers;
            ss >> numProjectMembers;
            for(int count = 0; count < numProjectMembers; count++) {
                string memberName;
                ss >> memberName;
                for(auto it : users) {
                    if(it->getName() == memberName) {
                        project->addTeam(it);
                        break;
                    }
                }
            }

            for(const auto &currentPair : issueReporters) { // issue reporter
                for(auto user : users) {
                    if(user->getName() == currentPair.second) {
                        currentPair.first->setReporter(user);
                        break;
                    }
                }
            }
            for(const auto &currentPair : issueAssignees) { // issue assignee
                for(auto user : users) {
                    if(user->getName() == currentPair.second) {
                        currentPair.first->setReporter(user);
                        break;
                    }
                }
            }
            for(const auto &currentPair : sprintIssues) { // issues in a sprint
                Sprint * currentSprint = currentPair.first;
                stringstream ss(currentPair.second);
                int numIssuesInSprint;
                ss >> numIssuesInSprint;
                for(int count = 0; count < numIssuesInSprint; count++) {
                    string issueName;
                    ss >> issueName;
                    for(auto it : issues) {
                        if(it->getId() == issueName) {
                            currentSprint->addJob(it);
                            break;
                        }
                    }
                }
            }
            for(const auto &currentPair : userTasks) { // user's tasks
                User * currentUser = currentPair.first;
                stringstream ss(currentPair.second);
                int numTasksForUser;
                ss >> numTasksForUser;
                for(int count = 0; count < numTasksForUser; count++) {
                    string taskName;
                    ss >> taskName;
                    for(auto it : issues) {
                        if(it->getId() == taskName) {
                            currentUser->addIssue(it);
                            break;
                        }
                    }
                }
            }
            for(const auto &currentPair : userSprints) { // user's sprints
                User * currentUser = currentPair.first;
                stringstream ss(currentPair.second);
                int numSprintsForUser;
                ss >> numSprintsForUser;
                for(int count = 0; count < numSprintsForUser; count++) {
                    string issueName;
                    ss >> issueName;
                    for(auto it : sprints) {
                        if(it->getName() == issueName) {
                            currentUser->addSprint(it);
                            break;
                        }
                    }
                }
            }
            THEPROJECT = project;
            loggedInUser = login(project);
        }
            // new project to make
        case 2: {
            string username;
            // asks user to enter an id
            cout << "Enter a unique userID: ";
            cin >> username;
            string projectname;
            // asks user to enter name for project
            cout << "Enter the project's name: ";
            cin >> projectname;
            // make user projectLead and makes new project
            auto* n = new ProjectLead(username);
            n->makeProject(projectname);
            THEPROJECT = n->getProject();
            loggedInUser = n;

            //delete n
            break;
        }
    }
    bool makeMoves = true;
    cout << breaker;
    while(makeMoves) { // main software loop
        /*
         * for both types of users, they first get a choice between looking at their own stuff and looking at the whole project
         *      plus logging out or quitting
         * their own stuff is this list
         * 1. project state
         * 2. details of user's sprints
         * 3. details of user's issues
         * 4. back
         * project stuff is this
         * 1. view project
         * 2. view to do
         * 3. view in progress
         * 4. view work done
         * 5. create a new issue
         * 6. view an issue
         * 7. update an issue in to do or sprint
         * 8. save project
         * 9. back
         *
         * leads also get fun stuff like
         * changing the name or deadline of the project
         * create new users
         * remove users
         * delete an issue
         *
         * the owner gets
         * delete the project
         */
        if(loggedInUser->getType() == lead) { // get access to fun stuff
            cout << "Would like to:\n1 - View current status\n2 - View Project Status\n3 - Logout\n4 - Quit\n5 - Run a Sprint" << endl;
            int answer;
            cin >> answer;
            if(answer == 1) { // current status
                bool insideStatus = true;
                while (insideStatus) {
                    cout << breaker;
                    cout << "Would like to:\n1 - Check Project\n2 - View your Sprints\n3 - View your Issues\n4 - Return"
                         << endl;
                    cin >> answer;
                    switch (answer) {
                        case 1:
                            loggedInUser->printProject();
                            break;
                        case 2:
                            for (auto it: loggedInUser->getSprints()) {
                                it->printSprint();
                            }
                            break;
                        case 3:
                            for (auto it: loggedInUser->getIssues()) {
                                it->printIssue();
                            }
                            break;
                        case 4:
                            insideStatus = false;
                            break;
                        default:
                            cout << "Not a valid choice" << endl;
                    }
                }
            } else if(answer == 2) { // project
                bool insideProject = true;
                while(insideProject) {
                    cout << "Do you want to:\n1 - View Entire Project\n2 - View to do\n3 - View In Progress";
                    cout << "\n4 - View Work Done\n5 -Create a new Issue\n6 - View an Issue\n7 - Update an Issue"
                            "\n8 - Edit Project\n9 - New User\n10 - Remove User\n11 - Delete Issue\n12 - Save Project\n13 - Return\n";
                    if(THEPROJECT->getOwner() == loggedInUser) {
                        cout << "666 - Delete this Entire Project\n";
                    }
                    // take in user's choice
                    cin >> answer;
                    // if incorrect option
                    while (cin.fail() || (answer < 1 || (answer > 13 && answer != 666))) {
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Please enter 1, 2, 3, 4, 5, 6, 7, or 8" << endl;
                        cin >> answer;
                    }
                    cout << breaker;
                    if (answer == 1) {
                        cout << "View Project" << endl;
                        loggedInUser->printProject();
                    }
                    else if (answer == 2) {
                        cout << "Viewing To Do" << endl;
                        for (auto it: THEPROJECT->getToDo()) {
                            it->printIssue();
                        }
                    }
                    else if (answer == 3) {
                        cout << "Viewing In Progress" << endl;
                        for (auto it: THEPROJECT->getInProg()) {
                            it->printSprint();
                        }
                    }
                    else if (answer == 4) {
                        cout << "Viewing Work Done" << endl;
                        for (auto it: THEPROJECT->getDone()) {
                            it->printIssue();
                        }
                    }
                    else if (answer == 5) {
                        cout << "Creating a new Issue" << endl;
                        cout << "Issue's ID?" << endl;
                        string s1;
                        cin >> s1;
                        auto *newIssue = new Issue(s1, loggedInUser);
                        THEPROJECT->addToDo(newIssue);
                        cout << "Issue type? (UserStory, Task, Build, Test, Debug, Documentation)" << endl;
                        cin >> s1;
                        newIssue->setIType(s1);
                        cout << "Issue's priority?" << endl;
                        int i1;
                        cin >> i1;
                        newIssue->setPriority(i1);
                        newIssue->setStatus("Open");
                        cout << "Issue date?" << endl;
                        cin >> s1;
                        newIssue->setDate(s1);
                        cout << "Issue description?" << endl;
                        cin >> s1;
                        newIssue->setDescription(s1);
                        cout << "Issue time frame?" << endl;
                        cin >> i1;
                        newIssue->setTime(i1);
                        cout << "Issue created. Would you like to assign it to yourself? (Y/N)" << endl;
                        cin >> s1;
                        if (s1 == "Y") {
                            newIssue->setAssignee(loggedInUser);
                        }
                    }
                    else if (answer == 6) {
                        cout << "Issue's name?" << endl;
                        string issueName;
                        cin >> issueName;
                        bool found = false;
                        for(auto it : THEPROJECT->getToDo()) { // look through to do issues
                            if(it->getId() == issueName) {
                                it->printIssue();
                                found = true;
                                break;
                            }
                        }
                        if(!found) { // look through in progress issue
                            for(auto it: THEPROJECT->getInProg()) {
                                for(auto it2: it->getJobs()) {
                                    if(it2->getId() == issueName) {
                                        it2->printIssue();
                                        found = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if(!found) { // look through done issues
                            for (auto it: THEPROJECT->getDone()) {
                                if(it->getId() == issueName) {
                                    it->printIssue();
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if(!found) { // if it wasn't in any of those it doesn't exist
                            cout << "Issue does not exist currently." << endl;
                        }
                    }
                    else if (answer == 7) { // adding comments to an issue or assigning it to themselves
                        cout << "Issue's name?" << endl;
                        string issueName;
                        cin >> issueName;
                        bool found = false;
                        for(auto it : THEPROJECT->getToDo()) { // look through to do issues
                            if(it->getId() == issueName) {
                                cout << "Would you like to add a comment (1) or assign it to yourself (2)?" << endl;
                                int ans;
                                cin >> ans;
                                if(ans == 2) {
                                    it->setAssignee(loggedInUser);
                                    loggedInUser->addIssue(it);
                                    cout << "Assigned." << endl;
                                } else {
                                    cout << "Write comment:" << endl;
                                    string comment;
                                    getline(cin, comment);
                                    it->setComments(comment);
                                }
                                found = true;
                                break;
                            }
                        }
                        if(!found) { // look through in progress issue
                            for(auto it: THEPROJECT->getInProg()) {
                                for(auto it2: it->getJobs()) {
                                    if(it2->getId() == issueName) {
                                        cout << "Would you like to add a comment (1) or assign it to yourself (2)?" << endl;
                                        int ans;
                                        cin >> ans;
                                        if(ans == 2) {
                                            it2->setAssignee(loggedInUser);
                                            loggedInUser->addIssue(it2);
                                            cout << "Assigned." << endl;
                                        } else {
                                            cout << "Write comment:" << endl;
                                            string comment;
                                            getline(cin, comment);
                                            it2->setComments(comment);
                                        }
                                        found = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if(!found) { // look through done issues
                            for (auto it: THEPROJECT->getDone()) {
                                if(it->getId() == issueName) {
                                    cout << "Would you like to add a comment (1) or assign it to yourself (2)?" << endl;
                                    int ans;
                                    cin >> ans;
                                    if(ans == 2) {
                                        it->setAssignee(loggedInUser);
                                        loggedInUser->addIssue(it);
                                        cout << "Assigned." << endl;
                                    } else {
                                        cout << "Write comment:" << endl;
                                        string comment;
                                        getline(cin, comment);
                                        it->setComments(comment);
                                    }
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if(!found) { // if it wasn't in any of those it doesn't exist
                            cout << "Issue does not exist currently." << endl;
                        }
                    }
                    else if (answer == 8) { // edit the project
                        cout << "Do you want change the title (1) or deadline (2)?" << endl;
                        int ans;
                        cin >> ans;
                        while (cin.fail() || (ans != 1 && ans != 2)) {
                            cin.clear();
                            cin.ignore(256, '\n');
                            cout << "Please enter 1 or 2" << endl;
                            cin >> answer;
                        }
                        if(ans == 1) {
                            cout << "Insert new title" << endl;
                            string newTitle;
                            getline(cin, newTitle);
                            THEPROJECT->setTitle(newTitle);
                        } else if(ans == 2) {
                            cout << "Insert new deadline" << endl;
                            int newDeadline;
                            cin >> newDeadline;
                            THEPROJECT->setDeadline(newDeadline);
                        }
                    }
                    else if (answer == 9) { // adding a new user
                        cout << "What is this new user's name?" << endl;
                        string newName;
                        cin >> newName;
                        cout << "Is this user a project lead(1) or a team member (2)?" << endl;
                        int ans;
                        cin >> ans;
                        while (cin.fail() || (ans != 1 && ans != 2)) {
                            cin.clear();
                            cin.ignore(256, '\n');
                            cout << "Please enter 1 or 2" << endl;
                            cin >> answer;
                        }
                        if(ans == 1) {
                            auto *p = new ProjectLead(newName);
                            THEPROJECT->addLeads(p);
                        } else if(ans == 2) {
                            auto *t = new TeamMember(newName);
                            THEPROJECT->addTeam(t);
                        }
                        cout << "User added" << endl;
                    }
                    else if (answer == 10) {
                        cout << "What is the user's name?" << endl;
                        string userName;
                        cin >> userName;
                        bool userFound = false;
                        if(loggedInUser->getName() == userName) {
                            cout << "You cannot remove yourself" << endl;
                        } else if(THEPROJECT->getOwner()->getName() == userName) {
                            cout << "You cannot remove the owner" << endl;
                        } else {
                            for(auto it : THEPROJECT->getLeads()) {
                                if(it->getName() == userName) {
                                    THEPROJECT->removeLeads(it);
                                    userFound = true;
                                    break;
                                }
                            }
                            for(auto it : THEPROJECT->getTeam()) {
                                if(it->getName() == userName) {
                                    THEPROJECT->removeTeam(it);
                                    userFound = true;
                                    break;
                                }
                            }
                            if(!userFound) {
                                cout << "User was not found" << endl;
                            }
                        }
                    }
                    else if (answer == 11) { // delete an issue
                        cout << "Issue's name?" << endl;
                        string issueName;
                        cin >> issueName;
                        bool found = false;
                        for(auto it : THEPROJECT->getToDo()) { // look through to do issues
                            if(it->getId() == issueName) {
                                THEPROJECT->removeToDo(it);
                                cout << "Issue removed" << endl;
                                found = true;
                                break;
                            }
                        }
                        if(!found) { // look through in progress issue
                            for(auto it: THEPROJECT->getInProg()) {
                                for(auto it2: it->getJobs()) {
                                    if(it2->getId() == issueName) {
                                        THEPROJECT->removeIssueInProgress(it, it2);
                                        cout << "Issue Removed" << endl;
                                        found = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if(!found) { // look through done issues
                            for (auto it: THEPROJECT->getDone()) {
                                if(it->getId() == issueName) {
                                    THEPROJECT->removeDone(it);
                                    cout << "Removed Issue" << endl;
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if(!found) { // if it wasn't in any of those it doesn't exist
                            cout << "Issue does not exist currently." << endl;
                        }
                    }
                    else if (answer == 12) { // save
                        cout << "Saving Project" << endl;
                        THEPROJECT->save();
                        cout << "Saved to Drive" << endl;
                    }
                    else if (answer == 13) { // return
                        insideProject = false;
                    }
                    else if (answer == 666 && THEPROJECT->getOwner() == loggedInUser) {
                        cout << "Are you sure you want to delete the entire project(Y/N)?" << endl;
                        string ans;
                        cin >> ans;
                        if(ans == "Y") {
                            cout << "Deleting entire project." << endl;
                            THEPROJECT = nullptr;
                            loggedInUser = nullptr;
                            return(0);
                        }

                    }
                }
            } else if(answer == 3) { // logout
                loggedInUser = login(THEPROJECT);
            } else if(answer == 4) { // quit
                cout << "Quitting program" << endl;
                makeMoves = false;
            } else if(answer == 5) {
                cout << "How long to run for (1-7 preferred)?" << endl;
                int timeLength;
                cin >> timeLength;
                cout << "Running a sprint" << endl;
                THEPROJECT->runASprint(timeLength);
            }
        }
        else { // don't get access to fun stuff
            cout << "Would like to:\n1 - View current status\n2 - View Project Status\n3 - Logout\n4 - Quit\n5 - Run a Sprint" << endl;
            int answer;
            cin >> answer;
            if(answer == 1) { // current status
                bool insideStatus = true;
                while (insideStatus) {
                    cout << breaker;
                    cout << "Would like to:\n1 - Check Project\n2 - View your Sprints\n3 - View your Issues\n4 - Return"
                         << endl;
                    cin >> answer;
                    switch (answer) {
                        case 1:
                            loggedInUser->printProject();
                            break;
                        case 2:
                            for (auto it: loggedInUser->getSprints()) {
                                it->printSprint();
                            }
                            break;
                        case 3:
                            for (auto it: loggedInUser->getIssues()) {
                                it->printIssue();
                            }
                            break;
                        case 4:
                            insideStatus = false;
                            break;
                        default:
                            cout << "Not a valid choice" << endl;
                    }
                }
            } else if(answer == 2) { // project
                bool insideProject = true;
                while(insideProject) {
                    cout << "Do you want to:\n1 - View Entire Project\n2 - View to do\n3 - View In Progress";
                    cout << "\n4 - View Work Done\n5 -Create a new Issue\n6 - View an Issue\n7 - Update an Issue\n8 - Save Project\n9 - Return\n";
                    // take in user's choice
                    cin >> answer;
                    // if incorrect option
                    while (cin.fail() || (answer < 1 || answer > 9)) {
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Please enter 1, 2, 3, 4, 5, 6, 7, or 8" << endl;
                        cin >> answer;
                    }
                    cout << breaker;
                    if (answer == 1) {
                        cout << "View Project" << endl;
                        loggedInUser->printProject();
                    }
                    else if (answer == 2) {
                        cout << "Viewing To Do" << endl;
                        for (auto it: THEPROJECT->getToDo()) {
                            it->printIssue();
                        }
                    }
                    else if (answer == 3) {
                        cout << "Viewing In Progress" << endl;
                        for (auto it: THEPROJECT->getInProg()) {
                            it->printSprint();
                        }
                    }
                    else if (answer == 4) {
                        cout << "Viewing Work Done" << endl;
                        for (auto it: THEPROJECT->getDone()) {
                            it->printIssue();
                        }
                    }
                    else if (answer == 5) {
                        cout << "Creating a new Issue" << endl;
                        cout << "Issue's ID?" << endl;
                        string s1;
                        cin >> s1;
                        auto *newIssue = new Issue(s1, loggedInUser);
                        THEPROJECT->addToDo(newIssue);
                        cout << "Issue type? (UserStory, Task, Build, Test, Debug, Documentation)" << endl;
                        cin >> s1;
                        newIssue->setIType(s1);
                        cout << "Issue's priority?" << endl;
                        int i1;
                        cin >> i1;
                        newIssue->setPriority(i1);
                        newIssue->setStatus("Open");
                        cout << "Issue date?" << endl;
                        cin >> s1;
                        newIssue->setDate(s1);
                        cout << "Issue description?" << endl;
                        cin >> s1;
                        newIssue->setDescription(s1);
                        cout << "Issue time frame?" << endl;
                        cin >> i1;
                        newIssue->setTime(i1);
                        cout << "Issue created. Would you like to assign it to yourself? (Y/N)" << endl;
                        cin >> s1;
                        if (s1 == "Y") {
                            newIssue->setAssignee(loggedInUser);
                        }
                    }
                    else if (answer == 6) {
                        cout << "Issue's name?" << endl;
                        string issueName;
                        cin >> issueName;
                        bool found = false;
                        for(auto it : THEPROJECT->getToDo()) { // look through to do issues
                            if(it->getId() == issueName) {
                                it->printIssue();
                                found = true;
                                break;
                            }
                        }
                        if(!found) { // look through in progress issue
                            for(auto it: THEPROJECT->getInProg()) {
                                for(auto it2: it->getJobs()) {
                                    if(it2->getId() == issueName) {
                                        it2->printIssue();
                                        found = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if(!found) { // look through done issues
                            for (auto it: THEPROJECT->getDone()) {
                                if(it->getId() == issueName) {
                                    it->printIssue();
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if(!found) { // if it wasn't in any of those it doesn't exist
                            cout << "Issue does not exist currently." << endl;
                        }
                    }
                    else if (answer == 7) { // adding comments to an issue or assigning it to themselves
                        cout << "Issue's name?" << endl;
                        string issueName;
                        cin >> issueName;
                        bool found = false;
                        for(auto it : THEPROJECT->getToDo()) { // look through to do issues
                            if(it->getId() == issueName) {
                                cout << "Would you like to add a comment (1) or assign it to yourself (2)?" << endl;
                                int ans;
                                cin >> ans;
                                if(ans == 2) {
                                    it->setAssignee(loggedInUser);
                                    loggedInUser->addIssue(it);
                                    cout << "Assigned." << endl;
                                } else {
                                    cout << "Write comment:" << endl;
                                    string comment;
                                    getline(cin, comment);
                                    it->setComments(comment);
                                }
                                found = true;
                                break;
                            }
                        }
                        if(!found) { // look through in progress issue
                            for(auto it: THEPROJECT->getInProg()) {
                                for(auto it2: it->getJobs()) {
                                    if(it2->getId() == issueName) {
                                        it2->printIssue();
                                        found = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if(!found) { // look through done issues
                            for (auto it: THEPROJECT->getDone()) {
                                if(it->getId() == issueName) {
                                    it->printIssue();
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if(!found) { // if it wasn't in any of those it doesn't exist
                            cout << "Issue does not exist currently." << endl;
                        }
                    }
                    else if (answer == 8) { // save
                        cout << "Saving Project" << endl;
                        THEPROJECT->save();
                        cout << "Saved to Drive" << endl;
                    }
                    else if (answer == 9) { // return
                        insideProject = false;
                    }
                }
            } else if(answer == 3) { // logout
                loggedInUser = login(THEPROJECT);
            } else if(answer == 4) { // quit
                cout << "Quitting program" << endl;
                makeMoves = false;
            } else if(answer == 5) {
                cout << "How long to run for (1-7 preferred)?" << endl;
                int timeLength;
                cin >> timeLength;
                cout << "Running a sprint" << endl;
                THEPROJECT->runASprint(timeLength);
            }
        }
    }
}

User * login(Project * project) {
    cout << "Enter a username" << endl;
    while(true) {
        string username;
        cin >> username;
        if(username == project->getOwner()->getName()) {
            cout << "Login Successful." << endl;
            return project->getOwner();
        } else {
            for(auto it : project->getLeads()) {
                if(it->getName() == username) {
                    cout << "Login Successful." << endl;
                    return it;
                }
            }
            for(auto it : project->getTeam()) {
                if(it->getName() == username) {
                    cout << "Login Successful." << endl;
                    return it;
                }
            }
        }
        cout << "Not a valid username, please try again." << endl;
    }
}