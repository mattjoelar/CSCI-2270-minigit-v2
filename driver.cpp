#include "minGit.hpp"//// ung
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

void displayMenu();

void handleUserInput(minGit& miniGit);

int main(int argc, char* argv[]) {

    minGit miniGit;

    miniGit.newRepository();
    
    handleUserInput(miniGit);


    return 0;

}

void handleUserInput(minGit& miniGit){

  bool quit = false;
  string s_input;
  int input;


 // should be another while loop
   // char inp;
       // cout << "Do you want to Initialize(y/n)?" << endl;
      //  cin >> inp;

     //   switch(inp){

       //     case 'y' : 
                  //initialize repository 
                  //  miniGit.newRepository();
                  //     break;
       //     case 'n' :
                     //  break;
         //   default :
                //      continue;
       // }



  while (!quit)
    {
      
        displayMenu();

        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
          
            input = 10;
        }

         switch (input)
        {
            case 1: {
    
                miniGit.insert();

                break;
            }
            case 2: {

                miniGit.deleteNode();

                break;
            }
            case 3: {

                miniGit.commit();

                break;
            }
            case 4: {


                
                string userInp;
                cout << "WARNING! Entering a valid commit number will overwrite your local changes." << endl;
                cout << "Enter commit number if you wish to proceed, otherwise enter 'Stop'." << endl;
                getline(cin, userInp);


                if(userInp == "Stop" || userInp == "stop")
                {
                    break;
                }
            else
                {
                    
                    miniGit.checkout(stoi(userInp));
                    break; 
                }

            }
            // I think there should also be a print repo option here as well?
            case 5: {
                
                quit = true; 
                cout << "Quitting" << endl;


                break;
            }
            default : 
                cout << "Invalid Input" << endl; 
                break;  
        }    

    }
}


void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Add a file " << endl;
    cout << " 2. Remove a file " << endl;
    cout << " 3. Commit changes " << endl;
    cout << " 4. Checkout " << endl;
    cout << " 5. Quit [DElETES ALL SAVES]" << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
