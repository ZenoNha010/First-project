#include <iostream>
#include <string>
#include <cstdlib> //
#include <conio.h>
#include <fstream> // For file IO
#include <ctime> //Use for funtion time
#include "system.h" // Header file
#include "tirtle.h"
using namespace std;


    /*
         -----------------------------------------------
        |               Function for Admin              |
         -----------------------------------------------
    */
void Admin(list* ls) {
    int choice;
    clearConsole();
    ani();
    _getch;
    do {
        clearConsole();
        cout << YELLOW << R"(
                                                        Admin options:
                                                        1]. View all accounts
                                                        2]. Delete an account
                                                        3]. View all transection
                                                        4]. Exit
                                                        Enter your choice: )" << RESET;
        cin >> choice;
        switch (choice) {
            case 1: {
                clearConsole();
                displayAllAccounts(ls);     // Display All Accounts
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;
            }
            case 2: {
                clearConsole();
                string name;
                char sure;
                cout << YELLOW << R"(
                                                        Enter Account name: )" << RESET;
                cin >> name;
                cout << YELLOW << R"(
                                                        Are you sure you want to delete this account? (y/n): )" << RESET;
                cin >> sure;
                if (sure == 'y' || sure == 'Y') {
                    deleteAccount(ls, name);
                } else {
                    cout << "Account deletion canceled." << endl;
                }
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;
            }
            case 3:{
                clearConsole();
                 displayTransaction(ls);
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;

            }
            case 4: {
                return;
            }
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 4);
}

    /*
         -----------------------------------------------
        |               Function for User Account       |
         -----------------------------------------------
    */
void Useracc(list* ls, string name, string password);
bool update(list* ls, int Number) {
    clearConsole();
    element* current = ls->head;
    bool success = false;
if(!success){

    if(Number == 1){
        while (current != nullptr) {
            string Password = getPassword();
            string Confirm = getPasswordconfirm();
                if (Password == Confirm) {
                    current->data.password = Password;
                    saveCustomersToFile(ls);
                    cout << YELLOW << R"(                                                                Password change sucessful. )" << endl<< RESET;
                    success = true;
                    clearConsole();
                    Useracc(ls ,current->data.name,Password);

                    break;

                }else{
                    clearConsole();
                    cout << YELLOW << R"(                                                                Your password not match. )" << endl<< RESET;
                }

                current = current->next;
            }

    }else if(Number == 2){
        clearConsole();
        while (current != nullptr) {
            string name;
            string confirmName;
            cout << YELLOW << R"(                                                                Enter your new name: )" << RESET;
            cin >> name;
            cout << YELLOW << R"(                                                                ConfirmName: )" << RESET;
            cin >> confirmName;
                if (name == confirmName) {
                    current->data.name = name;
                    saveCustomersToFile(ls);
                    cout << YELLOW << R"(                                                                Your name change sucessful. )" << endl<< RESET;

                    Useracc(ls ,name,current->data.password);
                    success = true;
                    break;

                }else{
                    clearConsole();
                    cout << YELLOW << R"(                                                                Your name not match. )" << endl<< RESET;
                }
                current = current->next;
            }
    }else if(Number == 3){
        clearConsole();
        while (current != nullptr) {
            string Gmail;
            string confirmGmail;
            cout << YELLOW << R"(                                                                Enter your new Gmail: )" << RESET;
            cin >> Gmail;
            cout << YELLOW << R"(                                                                ConfirmGmail: )" << RESET;
            cin >> confirmGmail;
                if (Gmail == confirmGmail) {
                    current->data.Gmail = Gmail;
                    saveCustomersToFile(ls);
                    cout << YELLOW << R"(                                                                Your gmail change sucessful. )" << endl<< RESET;
                    success = true;

                    Useracc(ls ,current->data.name,current->data.password);
                    break;

                }else{
                    clearConsole();
                    cout << YELLOW << R"(                                                                Your gmail not match. )" << endl<< RESET;
                }
                current = current->next;
            }
    }

}

}

void Setting(list* ls){
    int choice;
    cout << YELLOW << R"(
                                                                *****************************************
                                                                *                Setting                *
                                                                *****************************************
                                                                * 1. Change Password                    *
                                                                * 2. Change Name                        *
                                                                * 3. Change Gmail                       *
                                                                * 4. Exit                               *
                                                                *****************************************
                                                                Enter your choice: )" << RESET;
        cin >> choice;
    switch(choice){
        case 1:{
            clearConsole();
            string Name;
                bool success = false;
                while(!success){
                    cout << YELLOW << R"(
                                                                Enter your account name:  )" << RESET;
                    cin >> Name;
                    string oldpassword = getOldPassword();
                    element* current = ls->head;
                    while (current != nullptr){
                        if (current->data.name == Name && current->data.password == oldpassword) {
                            update(ls,choice);
                            success = true;
                            break;
                        }
                        current = current->next;
                    }
                    clearConsole();
                    if(!success){

                        cout << YELLOW << R"(
                                                                Your password or name is incorrect.  )" <<endl<< RESET;
                    }
                }
            break;
        }
        case 2:{
            clearConsole();
            string Name;
                bool success = false;
                while(!success){
                    cout << YELLOW << R"(
                                                                Enter your account name:  )" << RESET;
                    cin >> Name;
                    string oldpassword = getOldPassword();
                    element* current = ls->head;
                    while (current != nullptr){
                        if (current->data.name == Name && current->data.password == oldpassword) {
                            update(ls,choice);
                            success = true;
                            break;
                        }
                        current = current->next;
                    }
                    clearConsole();
                    if(!success){

                        cout << YELLOW << R"(
                                                                Your password or name is incorrect.  )" <<endl<< RESET;
                    }
                }
            break;
        }
        case 3:{
            clearConsole();
            string Name;
                bool success = false;
                while(!success){
                    cout << YELLOW << R"(
                                                                Enter your account name:  )" << RESET;
                    cin >> Name;
                    string oldpassword = getOldPassword();
                    element* current = ls->head;
                    while (current != nullptr){
                        if (current->data.name == Name && current->data.password == oldpassword) {
                            update(ls,choice);
                            success = true;
                            break;
                        }
                        current = current->next;
                    }
                    clearConsole();
                    if(!success){

                        cout << YELLOW << R"(
                                                                Your password or name is incorrect.  )" <<endl<< RESET;
                    }
                }
            break;
        }
        case 4:
            return;
            break;
        default:
            cout <<"Invilid number."<<endl;
            break;


    }

}

void Useracc(list* ls, string name, string password) {
    int choice;
    clearConsole();
    ani();
    _getch;
    do {
        clearConsole();
        cout << YELLOW << R"(
                                                                *****************************************
                                                                *      Welcome to the Bank System       *
                                                                *****************************************
                                                                * 1. Deposit money                      *
                                                                * 2. Withdraw money                     *
                                                                * 3. Exchange Money                     *
                                                                * 4. Check AccountBalance               *
                                                                * 5. Transfer Money                     *
                                                                * 6. Setting                            *
                                                                * 7. Exit                               *
                                                                *****************************************
                                                                Enter your choice: )" << RESET;
        cin >> choice;

        switch (choice) {
            case 1: {
                clearConsole();
                deposit(ls, name, password);
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;
            }
            case 2: {
                clearConsole();
                withdraw(ls, name, password);
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;
            }
            case 3: {
                exchange(ls, password);
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;
            }
            case 4: {
                clearConsole();
                displayAccountBalance(ls, name, password);
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;
            }
            case 5: {
                transfer(ls, password);
                
                break;
            }
            case 6: {
                clearConsole();
                Setting(ls);
                break;
            }
            case 7: {
                return;
            }
            default: {
                cout << YELLOW << R"(
                                                        Invalid choice. Please try again.  )" << RESET;
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
            }
        }
    } while (choice != 6);
}

    /*
         -----------------------------------------------
        |               Display Menu                   |
         -----------------------------------------------
    */

void display(list* ls) {
    int choice;
    clearConsole();
    Bankpage();
    _getch();
    do {
        clearConsole();
        cout << BLUE << R"(
                                                                *****************************************
                                                                *      Welcome to the Bank System       *
                                                                *****************************************
                                                                * 1. Create account                     *
                                                                * 2. Login                              *
                                                                * 3. Exit                               *
                                                                *****************************************
                                                                Enter your choice: )" << RESET;

        cin >> choice;

        switch (choice) {
            case 1: {
                clearConsole();
                addAccount(ls);
                element*curr=ls->head;
                Useracc(ls,curr->data.name,curr->data.password);
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
                break;
            }
            case 2: {
                clearConsole();
                string name, Password;
                bool success = false;
                while(!success){
                    cout << YELLOW << R"(
                                                                Enter your name:  )" << RESET;
                    cin >> name;
                    Password = getPasswordlogin();

                    if (name == "Admin" && Password == "Admin12@") {
                        Admin(ls);
                        success = true;
                    } else {
                        element* t = ls->head;
                        while (t != nullptr) {
                            if (t->data.name == name && t->data.password == Password) {
                                Useracc(ls, name, Password);
                                success = true;
                                break;
                            }
                            t = t->next;
                        }
                    }
                    clearConsole();
                    if (!success) {
                        cout << YELLOW << R"(
                                                                Your name or password is incorrect.  )" << RESET;

                    }
                }

                break;
            }
            case 3:
                return;
            default:
                cout << YELLOW << R"(
                                                                Invalid choice. Please try again.  )" << RESET;
                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                _getch();
        }
    } while (choice != 3);
}

int main() {
    list* ls = createemptylist();
    loadAccountsFromFile(ls);
    display(ls);
    return 0;
}
