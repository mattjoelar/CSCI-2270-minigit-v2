#include "minGit.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdio.h>

namespace fs = std::filesystem;

using namespace std;


////////////////////////////////////////////////////////////////////////////

// Status : Finished logic for insert ,remove ,constructor and newRepo
// !!!!! testing needed for insert and remove (to finish)!!!!!
//TODO : commit and checkout 
//Also print repo but that's fairly straightforward 

///////////////////////////////////////////////////////////////////////////

minGit::minGit(){

   head = new doublyNode;
   head->next = NULL;
   head->prev = NULL;
   head->commitNumber = 1;
};

minGit::~minGit(){

    // not the important other main functions are ; could be finished later

  
}

void minGit::newRepository(){
    
    //making a new directory called in current folder called .minigit
    auto path = fs::current_path();

    fs::create_directory(".minigit");

    fs::current_path(".minigit");

}

string corrFile(string fname,int val){

string fileType;
string fileName;
string corrFile;

for(int i = 0; i<fname.length();i++){
    if(fname[i] == '.'){
        for(int j = i ; j<fname.length();j++){
            fileType = fileType + fname[j];
        }
        break;
    }

fileName = fileName + fname[i];
}
string value = to_string(val);
corrFile = ".minigit/" + fileName + "_0" + value + fileType;

return corrFile;




}

void minGit::insert(){

// enter file name 
// search and traverse directory for file.
 //If it exists then user should be told to input a proper one

//search the single linked list if a file is added ? if its added then it cant be added twice

//  A new SLL node gets added containing the name of the input file, name of the repository file, as well as a pointer to the next node. The repository file name should be
//the combination of the original file name and the version number. For example, if user
//file help.txt is added, the new file to be saved in the .minigit repository should be
//named help00.txt, where 00 is the version number. (The initial file version should
//be 00.)

string userInp;
ofstream file; //Needed to be ofstream to create new files.

while(!file.is_open()){
    cout << "Please enter the filename" << endl;
    getline(cin,userInp);
    file.open(userInp);
}

singlyNode* curr= head->head; 
while(curr !=NULL){ //Tested, works.
    if(curr->fileName == userInp){
        cout << "Sorry file has already been added" << endl;
        return;
    }
    curr = curr->next;
    
}

singlyNode* insert = new singlyNode();
insert->fileName = userInp;
insert->fileVersion = corrFile(userInp,0);
insert->next = NULL;

if(head->head != NULL){
    insert->next = head->head;
    head->head = insert;
}
else{

    head->head = insert;
    head->head->next = NULL;
}


}

void minGit::deleteNode(){

//Prompt user to enter a file name

//Check the SLL for whether the file exists in the current version of the repository

//If found, delete the SLL node

string userInp;

cout << "Enter the name of the file to be deleted:" << endl;
getline(cin,userInp);

singlyNode* curr = head->head;
singlyNode* prev = NULL;

while(curr != NULL){
    if (curr->fileName == userInp) break;
    else{
        prev = curr;
        curr = curr->next;
    }
}

if(curr == NULL){
    cout << "Filename does not exist" << endl;
    return;
}
else{

    if(prev == NULL){
        head->head = curr->next;
        delete curr;
    }
    else{
        prev->next = curr->next;
        delete curr;
    }
    const char * c = userInp.c_str();
    remove(c);


}


}

void minGit::commit(){

//The current SLL should be traversed in its entirety, and for every node
singlyNode* curr = head->head;
while(curr != NULL)
{
    //curr->fileVersion
}
    //Check whether the corresponding fileVersion file exists in .minigit directory.
    // If the fileVersion file does not exist, copy the file from the current directory
    // into the .minigit directory. The newly copied file should get the name from the
    //  node’s fileVersion member. (Note: this will only be the case when a file is
    //  added to the repository for the first time.)

    // If the fileVersion file does exist in .minigit, check whether the current directory file has been changed (i.e. has it been changed by the user?) with respect to
    // the fileVersion file. (To do the comparison, you can read in the file from the
    // current directory into one string and read in the file from the .minigit directory
    // into another string, and check for equality.)1 Based on the comparison result, do
    // the following:(equality check)
                    //File is unchanged: do nothing
                    //File is changed: copy the file from the current directory to the .minigit
                           //  directory, and give it a name with the incremented version number. Also,
                           //  update the SLL node member fileVersion to the incremented name

//Once all the files have been scanned, the final step of the commit will create a new
//Doubly Linked List node of the repository. An exact (deep) copy of the SLL from the
//previous node shall be copied into the new DLL node. The commit number of the new
//DLL node will be the previous nodes commit number incremented by one.




}

void minGit::checkout(int fileNumber){

///If the user chooses to checkout a version, they should be prompted to enter a commit number.
//For a valid commit number, the files in the current directory should be overwritten by the
//the corresponding files from the .minigit directory. (It is a good idea to issue a warning to
//the user that they will loose their local changes if they checkout a different version before
//making a commit with their current local changes.) <-- Must issue Warning!!!

//This step will require a search through the DLL for a node with matching commit number2
//. Also note that you must disallow add, remove, and commit operations when the current
//version is different from the most recent commit (the last DLL node)

}