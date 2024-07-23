#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>
#include <ctime>
#include <conio.h>
#include <dirent.h>

using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string getPassword() {
    string password;
    char ch;
    cout << YELLOW << R"(                           Enter your password: )" << RESET;
                                                        
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

string getPasswordconfirm() {
    string password;
    char ch;
    cout << YELLOW << R"(                           Confirm your password: )" << RESET;
                                                        
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

string getOldPassword() {
    string password;
    char ch;
    cout << YELLOW << R"(                       Enter old password: )" << RESET;
                                                        
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

struct inf {
    string name;
    double balance;
    string password;
    string confirm;
    string Gmail;
    double  usdbalance;
    double  khbalance;
};

struct element {
    inf data;
    element* next;
};

struct list {
    int n;
    element* head;
    element* tail;
};

list* createemptylist() {
    list* ls = new list;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void add(list* ls, inf data) {
    element* e = new element;
    e->data = data;
    e->next = ls->head;
    ls->head = e;
    if (ls->n == 0) {
        ls->tail = e;
    }
    ls->n += 1;
}

string currentDate() {
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    string year = to_string(1900 + localTime->tm_year);
    string month = to_string(1 + localTime->tm_mon);
    string day = to_string(localTime->tm_mday);

    string currentDate = year + '-' + month + '-' + day;
    return currentDate;
}

void saveCustomersToFile(list* l) {
    const char* folder = "BankManagment";
    _mkdir(folder);
    string customerFile = string(folder) + "/" + "CustomerInformation.csv";
    ofstream accountFile(customerFile);
    if (accountFile.is_open()) {
        accountFile << "Email,NAME,BALANCE,PASSWORD" << endl;
        element* e = l->head;
        while (e != nullptr) {
            accountFile << e->data.Gmail << "," << e->data.name << "," << e->data.balance << "," << e->data.password << endl;
            e = e->next;
        }
        accountFile.close();
    } else {
        cout << YELLOW << R"(                           Unable to open file:)" << RESET;
                                                      
        cout << " " << customerFile << endl;
    }
}

void loadAccountsFromFile(list* ls) {
    const char* folder = "BankManagment";
    string customerFile = string(folder) + "/" + "CustomerInformation.csv";
    ifstream accountFile(customerFile);
    if (accountFile.is_open()) {
        string line;
        getline(accountFile, line); // skip header
        while (getline(accountFile, line)) {
            inf account;
            size_t pos = 0;

            pos = line.find(',');
            account.Gmail = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            account.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            account.balance = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            account.password = line;

            add(ls, account);
        }
        accountFile.close();
    } else {
        cout << "Unable to open file: " << customerFile << endl;
    }
}

void makemainFolder() {
    const char* mainFolder = "BankQueue";
    if (_mkdir(mainFolder)) {
        return;
    }
}
void addAccount(list* ls) {
    makemainFolder();
    inf newAccount;
    bool success = false;
    clearConsole();
    cout << YELLOW << R"(
                                                        Create Account
                                                        Enter Account name:  )" << RESET;
    cin >> newAccount.name;
    cout << YELLOW << R"(                                                        Enter account Email:  )" << RESET;
                                                       
    cin >> newAccount.Gmail;
    newAccount.balance = 0;
    newAccount.password = getPassword();
    while (!success) {
        newAccount.confirm = getPasswordconfirm();
        if (newAccount.confirm == newAccount.password) {
            add(ls, newAccount);
            saveCustomersToFile(ls);
            cout << YELLOW << R"(                                                  Account created successfully. )" << RESET;
                                                        
            cout << endl;
            success = true;
        } else {
            cout << YELLOW << R"(                                                   Password confirmation does not match. Please try again. )" << RESET;
                                                        
        }
    }
}

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
                    cout << YELLOW << R"(                                               Password change sucess. )" << endl<< RESET;
                                                         
                    success = true;
                    break;
               
                } 
                current = current->next;
            }

    }else if(Number == 2){
        while (current != nullptr) {
            string name;
            string confirmName;
            cout << "Enter your name: "; cin >> name;
            cout << "ConfirmName: "; cin >> confirmName;
                if (name == confirmName) {
                    current->data.name = name;
                    saveCustomersToFile(ls);
                    cout << YELLOW << R"(                                               Your name change sucess. )" << endl<< RESET;
                                                         
                    success = true;
                    break;
               
                } 
                current = current->next;
            }
    }else if(Number == 3){
        while (current != nullptr) {
            string Gmail;
            string confirmGmail;
            cout << "Enter your Gmail: "; cin >> Gmail;
            cout << "ConfirmGmail: "; cin >> confirmGmail;
                if (Gmail == confirmGmail) {
                    current->data.Gmail = Gmail;
                    saveCustomersToFile(ls);
                    cout << YELLOW << R"(                                               Your name change sucess. )" << endl<< RESET;                              
                    success = true;
                    break;
               
                } 
                current = current->next;
            }
    }
    
        if(!success){
            cout << YELLOW << R"(                                                    Your password does not match. )" << endl<< RESET;
        }
       
}
cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
_getch();
}
void Setting(list* ls){
    int choice;
    cout << YELLOW << R"(     
                                                        1. Change Password  
                                                        2. Change Name
                                                        3. Change Gmail
                                                        Enter your choice:)" << RESET;
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
        default:
            cout <<"Invilid number."<<endl;
            break;

            
    }

}
void logTransaction(list* l, string transaction, double amount, string name) {
    const char* folder = "BankManagment";
    _mkdir(folder);
    string transactionFile = string(folder) + "/" + "TransactionInformation.csv";
    ofstream openfile(transactionFile, ios::app);
    if (openfile.is_open()) {
        openfile << "NAME,TRANSACTION,AMOUNT,DATE" << endl;
        element* e = l->head;
        while (e != nullptr) {
            if (e->data.name == name) {
                openfile << e->data.name << "," << transaction << "," << amount << "," << currentDate() << endl;
                break;
            }
            e = e->next;
        }
        openfile.close();
    } else {
        cout << "Unable to open file: " << transactionFile << endl;
    }
}
void logTransactionKH(list* l, string transaction, double amount, string name) {
    const char* folder = "BankManagment";
    _mkdir(folder);
    string transactionFile = string(folder) + "/" + "TransactionInformation.csv";
    ofstream openfile(transactionFile, ios::app);
    if (openfile.is_open()) {
        openfile << "NAME,TRANSACTION,AMOUNT,DATE" << endl;
        element* e = l->head;
        while (e != nullptr) {
            if (e->data.name == name) {
                openfile << e->data.name << "," << transaction << "," << amount << "(riel)," << currentDate() << endl;
                break;
            }
            e = e->next;
        }
        openfile.close();
    } else {
        cout << "Unable to open file: " << transactionFile << endl;
    }
}
double USDtoRiel(double usd) {
    return usd * 4100;
}

double RieltoUSD(double riel) {
    return riel / 4100;
}
void exchange(list* ls, string password) {
    double amount;
    int option;
    cout << "1. Exchange USD($) to RIEL(៛)" << endl;
    cout << "2. Exchange RIEL(៛) to USD($)" << endl;
    cout << "Enter your choice: ";
    cin >> option;

    element* e = ls->head;
    while (e != nullptr) {
        if ( e->data.password == password) {
            if (option == 1) {
                cout << "Enter your USD amount: ";
                cin >> amount;
                if (amount > e->data.usdbalance) {
                    cout << "Insufficient balance. Exchange failed." << endl;
                } else {
                    e->data.usdbalance -= amount;
                    double riel = USDtoRiel(amount);
                    e->data.khbalance += riel;
                    cout << "Exchanged " << amount << " USD to " << riel << " RIEL." << endl;
                    cout << "Your balance now: " << e->data.usdbalance << " USD and " << e->data.khbalance << " RIEL." << endl;
                    logTransactionKH(ls, "Exchange to RIEL", amount, e->data.name);
                }
            } else if (option == 2) {
                cout << "Enter your RIEL amount: ";
                cin >> amount;
                if (amount > e->data.khbalance) {
                    cout << "Insufficient balance. Exchange failed." << endl;
                } else {
                    e->data.khbalance -= amount;
                    double usd = RieltoUSD(amount);
                    e->data.usdbalance += usd;
                    cout << "Exchanged " << amount << " RIEL to " << usd << " USD." << endl;
                    cout << "Your balance now: " << e->data.usdbalance << " USD and " << e->data.khbalance << " RIEL." << endl;
                    logTransaction(ls, "Exchange to USD", amount, e->data.name);
                }
            } else {
                cout << "Invalid choice." << endl;
            }
            saveCustomersToFile(ls);
            return;
        }
        e = e->next;
    }
    cout << "Your Gmail or password is wrong! Please try again." << endl;
}
void deposit(list* ls, string name, string password) {
    element* e = ls->head;
    while (e != nullptr) {
        if (e->data.name == name && e->data.password == password) {
            double depositAmount;
            cout << YELLOW << R"(                                                      Enter your deposit amount: )" << RESET;
                                                        
            cin >> depositAmount;
            e->data.balance += depositAmount;
            cout << YELLOW << R"(                                                      You deposited: )" << RESET<< depositAmount << endl;
                                                        
            cout << YELLOW << R"(                                                      Please confirm the amount (Y/N): )" << RESET;
                                                        
            char confirm;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                cout << YELLOW << R"(                                                   Deposit successful. )" << RESET;
                                                        
                cout << YELLOW << R"(                                                   Your balance now: )" <<e->data.balance << " $" << endl<< RESET;
                                                                                                
                cout << endl;
                logTransaction(ls, "Deposit", depositAmount, name);
                saveCustomersToFile(ls);
                return;
            } else {
                cout << YELLOW << R"(                                                   Deposit cancelled. )" <<e->data.balance << " $" << endl<< RESET;
                                                        
                e->data.balance -= depositAmount;
            }
            return;
        }
        e = e->next;
    }
    cout << YELLOW << R"(                                            Your name or password is incorrect! Please try again. )" << RESET;
                                                        
}

void withdraw(list* ls, string name, string password) {
    element* e = ls->head;
    while (e != nullptr) {
        if (e->data.name == name && e->data.password == password) {
            double draw;
            cout << YELLOW << R"(
                                                                                        Enter the amount to withdraw: )" << RESET;
            
            cin >> draw;
            cout << YELLOW << R"(
                                                                                        You withdraw: )"  << RESET<<draw<< endl ;
            if (draw > e->data.balance) {
                cout << YELLOW << R"(
                                                                                        Insufficient balance. Withdrawal failed. )" << RESET;
                
            } else {
                cout << YELLOW << R"(
                                                                                        Please confirm the amount (Y/N): )" << RESET;
                char confirm;
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    e->data.balance -= draw;  // Deduct the amount
                    cout << YELLOW << R"(
                                                        Withdrawal successful. )" << endl<< RESET;
                    cout << YELLOW << R"(
                                                        Your balance now: )" << RESET<<e->data.balance<<" $"<< endl;
                    logTransaction(ls, "Withdraw", draw, name);
                    saveCustomersToFile(ls);
                    return;
                } else {
                    
                }
            }
            return;
        }
        e = e->next;
    }
    cout << YELLOW << R"(
                                                       Your name or password is incorrect! Please try again.)" <<endl<< RESET;
}


void displayAllAccounts(list* ls) {
    element* e = ls->head;
    cout << "NAME\tGmail" << endl;
    while (e != nullptr) {
        cout << e->data.name<< "\t" <<e->data.Gmail  << endl;
        e = e->next;
    }
}

void displayAccountBalance(list* ls, const string& accountName, const string& password) {
    // Search in the linked list
    element* current = ls->head;
    bool found = false;

    while (current != nullptr) {
        if (current->data.name == accountName && current->data.password == password) {                            
            cout << "Name: " << current->data.name << endl;
            cout << "Balance: " << current->data.balance << " $" << endl;
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found) {
        // Search in the file system
        const char* folder = "BankQueue/Accounts";
        string filename = string(folder) + "/" + accountName + ".csv";
        ifstream accountFile(filename);

        if (accountFile.is_open()) {
            string line;
            string filePassword;
            double fileBalance;
            while (getline(accountFile, line)) {
                if (line.find("Password: ") == 0) {
                    filePassword = line.substr(10);
                } else if (line.find("Balance: ") == 0) {
                    fileBalance = stod(line.substr(9));
                }
            }
            accountFile.close();

            if (filePassword == password) {
                cout << "Account found in the file system:" << endl;
                cout << "Name: " << accountName << endl;
                cout << "Balance: " << fileBalance << " $" << endl;
            } else {
                cout << "Password is incorrect." << endl;
            }
        } else {
            cout << "Account does not exist." << endl;
        }
    }
}

void deleteAccount(list* ls, const string& accountName) {
    // Find the account in the linked list
    element* current = ls->head;
    element* prev = nullptr;

    while (current != nullptr && current->data.name != accountName) {
        prev = current;
        current = current->next;
    }

    // Check if the account was found
    if (current == nullptr) {
        cout << "Account not found." << endl;
        return;
    }

    // Ensure the account balance is zero before deletion
    if (current->data.balance != 0) {
        cout << "Account balance is not zero. Cannot delete account." << endl;
        return;
    }

    // Remove the account from the linked list
    if (prev == nullptr) {
        ls->head = current->next;
    } else {
        prev->next = current->next;
    }

    if (current == ls->tail) {
        ls->tail = prev;
    }

    delete current;
    ls->n -= 1;
    cout << "Account deleted from the linked list." << endl;

    // Update the file system
    saveCustomersToFile(ls);
}