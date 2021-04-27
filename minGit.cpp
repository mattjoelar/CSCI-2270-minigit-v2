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
    //cout << "1" << endl; 
    // not the important other main functions are ; could be finished later
    if(head != NULL)
    {   //cout << "2" << endl; 
        doublyNode *temp = head;
        doublyNode *next = temp->next;
        
        while(temp!=NULL)
        {   
            //cout << "3" << endl; 
            if(temp->head != NULL){
                //cout << "4" << endl; 
                singlyNode *tempS = temp->head;
                singlyNode *nextS = temp->head->next; 
                while(tempS!=NULL)
                {  // cout << "5" << endl; 
                    delete tempS;
                   // cout << "6" << endl; 
                    tempS = nextS; 
                   // cout << "6.5" << endl; 
                    if(tempS!=NULL)
                    {
                        nextS = tempS-> next; 
                    }
                    else {nextS = NULL;}
                    

                }
            }
            //cout << "7" << endl; 
            delete temp;
           // cout << "8" << endl; 
            temp = next;
            //cout << "9" << endl;
            if(temp!=NULL)
            {
                next = temp->next;
            }
            else 
            {
                next = NULL; 
            } 
            //cout << "10" << endl; 
        }
    }
  
}

void minGit::newRepository(){
    
    //making a new directory called in current folder called .minigit
    auto path = fs::current_path();

    fs::create_directory(".minigit");

    //fs::current_path(".minigit"); This prevents the add function from checking the work space folder, maybe we implement it when we need to search the miniGit directory.

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
corrFile =  fileName + "_0" + value + fileType;
//".minigit/"
return corrFile;




}

void minGit::insert(){

    // enter file name 
    // search and traverse directory for file.
    //If it does NOT exists then user should be told to input a proper one

    //search the single linked list if a file is added ? if its added then it cant be added twice

    //  A new SLL node gets added containing the name of the input file, name of the repository file, as well as a pointer to the next node. The repository file name should be
    //the combination of the original file name and the version number. For example, if user
    //file help.txt is added, the new file to be saved in the .minigit repository should be
    //named help00.txt, where 00 is the version number. (The initial file version should
    //be 00.)


    string userInp;
    ifstream file; //Needed to be ofstream to create new files.  //Changed to ifstream I dont think we create files in this step, only adding them to the SLL if they are in the directory
    system("cd .."); 
    while(!file.is_open()){
        cout << "Please enter the filename" << endl;
        //cout << fs::current_path() << endl; 
        
       // cout << fs::current_path() << endl; 
        getline(cin,userInp);
        
        file.open(userInp);

        //fs::current_path("gitrepo"); // the directory used for the workspace, will need to look into this for other machine directories. 

        if (file.is_open()) // if the file given is found the current directory, adds to the link list
        {   
            singlyNode* curr= head->head; 
            while(curr !=NULL){ //Tested, works.
            if(curr->fileName == userInp){
                cout << "Sorry file has already been added" << endl;
                return;
            }
            curr = curr->next;
            }
            cout << "Your file has been added. Choose the COMMIT(3) option to save." << endl; 
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
        

       // fs::current_path(".minigit");

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



int _nextVersion (string fileVersion){ // returns the next version of the file, just the number as the int. Works with corrFile function. 

    int versionNumber; 
    string finalNumber; 

    for(int i = 0; i < fileVersion.size(); i++)
    {
        if(isdigit(fileVersion[i]))
        {
            finalNumber = finalNumber + fileVersion[i];
        }
    }
    
    versionNumber = stoi(finalNumber) + 1;

    return versionNumber; 
    
}


bool _fileChange(string filename, string minigitname){ // returns True if there is a change
    ifstream readFile;
    ifstream readMini; 
    string file;
    string mini; 
    bool change = false; 
    char line[50], f, m; 
     
    readFile.open(filename);
    readMini.open(".minigit/" + minigitname); 

    if(readFile.is_open() && readMini.is_open())
    {
        
        while( readMini.get() && readFile.get() ) // getline(readMini,miniLine) ||
        {   

            f = readFile.get();
            m = readMini.get();
            
            if (f != m){
                //cout << "Debug" << endl; 
                change = true; 
                break; 
            }  
            if((f==EOF)|| (m==EOF)){
                
                break;
            }
        }  
    }
    readFile.close();
    readMini.close();
    
    return change; 

}


void minGit::commit(){
    
    //The current SLL should be traversed in its entirety, and for every node
    doublyNode *temp = head;
    singlyNode *tempS = NULL;
    ifstream readMe; 
    ifstream readMe2; 

    string Mini = ".minigit/";
    string fileVName;
    string fileNameMini;
    string line; 

    if(temp == NULL)// Won't be trigger since on boot up the program inits
    {
        cout << "No Repository Initialized. Commit was not added." << endl; 
        return; 
    }

    tempS = temp->head;

    if(tempS == NULL) // works!
    {
        cout << "No files to commit. Commit was not added. " << endl; 
        return; 
    }
//--------------------------------------------------- Adds DLL node to the list BEFORE the head, new node becomes new head and old head is head->next. 
    doublyNode* newCommitDN = new doublyNode;
    newCommitDN->next = head;
    newCommitDN->prev = NULL;
    newCommitDN->commitNumber = head->commitNumber + 1;

    head->prev = newCommitDN;
    head = newCommitDN;
//-------------------------------------------------- Copys SLL over to new commit node
    singlyNode *newCommit = head->head;
    singlyNode *oldCommit = head->next->head;

   
    
    while(oldCommit!=NULL)
    {
        
        singlyNode* copyFile = new singlyNode();
            copyFile->fileName = oldCommit->fileName;

            
           if( _fileChange( oldCommit->fileName ,  oldCommit->fileVersion) ) //ERROR was HERE
           {
               cout << oldCommit->fileName << "'s new version has been saved. " << endl;
               copyFile->fileVersion = corrFile(oldCommit->fileName, _nextVersion(oldCommit->fileVersion));
           }
           else
           {
            copyFile->fileVersion = oldCommit->fileVersion;
           }
            copyFile->next = NULL;

            if(head->head != NULL){
                copyFile->next = head->head;
                head->head = copyFile;
            }
            else{

                head->head = copyFile;
                head->head->next = NULL;
            }
        oldCommit = oldCommit->next; 
    }

//----------------------------------------------------

//---------------------------------------------------- copying the files in the working directory to the .minigit
    tempS = temp->head; 
    while (tempS!=NULL)
    {   //cout << "tempS does NOT = null" << endl; 
        fileVName = tempS->fileVersion;
        fileNameMini = Mini + fileVName;

        readMe.open(fileNameMini);

        if(readMe.is_open()) // sees if there is a file in the minigit
        {
            //cout << "There is a file in minigit" << endl; 

            readMe2.open(tempS->fileName); // opens the current file

            if(readMe2.is_open())
            {
                //SET A BOOL LOOP TO SEE IF THERE HAS BEEN A CHANGE OR NOT OF THE FILE

                if ( _fileChange( tempS->fileName , fileVName)) ///// ERROR WAS HERE
                {
                    
                    cout << "CHANGE DETECTED IN: " << fileVName << endl; 
                    ofstream writeMe (Mini + corrFile(tempS->fileName, _nextVersion(fileVName)));
                    while(getline(readMe2,line)){
                             
                        writeMe << line << endl;
                        
                    }
                    writeMe.close(); 
                    readMe2.close();
                }
                else
                {
                    cout << tempS->fileName << " has has not changed since last commit." << endl;
                }
                
            }
            //FILE IS IN MINIGIT
            readMe.close();
                

                
        }

        else
        {
            cout << "A NEW FILE HAS BEEN COMMITED: " << tempS->fileName  << endl; 
            ofstream newWriteMe (".minigit/" + fileVName);
            // new file, add first version to minigit
            
            readMe2.open(tempS->fileName);

            if(readMe2.is_open())
            {
            // string newFileName = Mini + fileName + "001"; 

                //system(001); // place horder for the correct version number of the file
                char n; 
                while(getline(readMe2,line))
                {   
                    if(newWriteMe.is_open())
                    {
                        newWriteMe << line << endl; ;
                    }
                    
                }
                newWriteMe.close();
                readMe2.close();
            } 
        }
        tempS = tempS->next; 
    }
}

void minGit::checkout(int fileNumber){

    doublyNode* curr = head;
    singlyNode* node = head->head;
    singlyNode* temp = NULL;
    /*while(node != NULL)
    {
        temp = node->next;
        const char * removeName = (node->fileName).c_str();
        remove(removeName);
        cout << node->fileName << endl;
        delete node;
        node = temp;
        cout << node->fileName << endl;
    }*/
    while(curr != NULL)
    {
        if(curr->commitNumber == fileNumber)
        {
            singlyNode* latest = curr->head;
                while(latest != NULL)
                {
                    ofstream fileOverwrite;
                    fileOverwrite.open(latest->fileName);
                    ifstream file1;
                    file1.open(latest->fileName);
                    string line;
                    while(getline(file1, line))
                    {
                        fileOverwrite << line;
                    }
                    file1.close();
                    fileOverwrite.close();
                    latest = latest->next;
                }
            break;
        }
        else
        {
            curr = curr->next;
        }
    }
    return;

}