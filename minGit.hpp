// #pragma once
#include <iostream>

using namespace std;

struct singlyNode{

  string fileName;     // Name of local file
  string fileVersion;  // // Name of file in .minigit folder
  singlyNode* next;  

};

struct doublyNode{

    int commitNumber;
    singlyNode* head;
    doublyNode* prev;
    doublyNode* next;
};

class minGit{

    public:
    
            minGit();
            ~minGit();
            void newRepository();
            void insert();
            void deleteNode();
            void commit();
            void checkout(int fileNumber);
 
    private: 

            doublyNode* head; 

            

};
