
//=================================================================================
// Name         : DS Assignment#3
// Author       :
// Version      : 1.0
// Date Created : 03-20-2022
// Date Modified:
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "contactbst.h"
#include "myvector.h"
#include "contact.h"



using namespace std;

//==========================================================
void listCommands()
{
    cout<<"----------------------------------"<<endl;
    cout<<"import <path>      :Import contacts from a CSV file"<<endl
        <<"export <path>      :Export contacts to a CSV file"<<endl
        <<"add                :Add a new contact"<<endl
        <<"edit <key>         :Update a contact's details"<<endl
        <<"del <key>          :Delete a contact"<<endl
        <<"searchFor <key>    :Search for a contact"<<endl
        <<"markfv <key>       :Mark as favourite"<<endl
        <<"umarkfv <key>      :Unmark as favourite"<<endl
        <<"printASC           :Print contacts in ascending order"<<endl
        <<"printDES           :Print contacts in descending order"<<endl
        <<"printfv            :Print all favourite contacts"<<endl
        <<"help               :Display the available commands"<<endl
        <<"exit               :Exit the program"<<endl;
}

int main(void)
{
    ContactBST myContactBST;
    string entercommand;
    string command;
    string argument;
    string userinput, d;
    int number = 0;

    while(true)
    {
        Node* root = myContactBST.getRoot();
        userinput = "";
        d = "";
        command = "";
        argument = "";
        number = 0;
        cout<<endl;
        listCommands();
        cout<<">";
        getline(cin, userinput);
        for (int i=0; i<userinput.length(); ++i)
        {
            if (userinput[i] != ' ' && number == 0)
            {
                d = d + userinput[i];
                if (i == userinput.length() - 1) {
                    command = d;
                }
            }
            else if(userinput[i] == ' ' && number == 0)
            {
                command = d;
                number = 1;
                d = "";
            }
            else
            {
                d = d + userinput[i];
            }
        }
        argument = d;

        if(command == "add")
        {
            myContactBST.insert_collection();
        }
        else if (command == "del")
        {
            myContactBST.remove_helper(argument);
        }
        else if(command == "searchFor")
        {
            myContactBST.search(root, argument);
        }
        else if(command == "markfv")
        {
            myContactBST.markFav(root, argument);
        }
        else if(command == "umarkfv")
        {
            myContactBST.unmarkFav(root, argument);
        }
        else if(command == "edit")
        {
            myContactBST.update(root, argument);
        }
        else if (command == "import")
        {
            cout<<myContactBST.importCSV(root, argument);
        }
        else if (command == "export")
        {
            cout<<myContactBST.exportCSV(root, argument);
        }
        else if(command == "printASC")
        {
            myContactBST.printASC(root);
        }
        else if (command == "printDES")
        {
            myContactBST.printDES(root);
        }
        else if(command == "printfv")
        {
            myContactBST.printFav(root);
        }
        else if(command == "help")
        {
            listCommands();
        }
        else if(command == "exit")
        {
            break;
        }
        else
        {
            cout<<"Invalid command"<<endl;
        }
    }

    return 0;
}
