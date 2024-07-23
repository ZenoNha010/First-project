#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <cctype>


using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void clearConsole() {
#ifdef _WIN32 || _WIN64 
    system("cls");
#else
    system("clear");
#endif
}
bool StrongPassword(string& password) {// Function to check if the password is strong
    if (password.length() < 6) return false; // Minimum length check

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    for (char ch : password) {
        if (islower(ch))hasLower = true;
        else if (isupper(ch)) hasUpper = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (ispunct(ch)) hasSpecial = true;
    }

    // Ensure password has all required types of characters
    return hasLower && hasUpper && hasDigit && hasSpecial;
}
string getPasswordlogin() {
     string password;
    char ch;
    cout << YELLOW << R"(                                                                Enter your password: )" << RESET;

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
string getPassword() {
    string password;
    char ch;

    do {
        password.clear(); // Clear the password on each attempt
        cout << YELLOW << R"(                       (The Password must have: lower and uppercase letters, digits, and special characters at least 6 characters long)
                                                                Enter the Password:)" << RESET;


        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // '\b' is the Backspace key
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else {
                password += ch;
                cout << BLUE << "*" << RESET;
            }
        }

        cout << endl;

        if (!StrongPassword(password)) {
            cout << RED <<                                      "Password must be at least 6 characters long and include "
                      <<                                        "uppercase, lowercase, digit, and special character. Please try again.\n" << RESET;
        }
    } while (!StrongPassword(password));

    return password;
}
string getPasswordconfirm() {
    string password;
    char ch;
    cout << endl;
    cout << YELLOW << R"(                                                                Confirm your password: )" << RESET;

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
    cout << YELLOW << R"(                                                                Enter old password: )" << RESET;

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
    double  usdbalance;
    long long  khbalance;
    string password;
    string confirm;
    string Gmail;
    string transaction;


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
int ani(){
    system("color 2a");
    system("color 0e");
    char a = 177,b = 219;
    cout<<GREEN << "\n\n\n\t\t\t\t\tLoading....."<<RESET;
    cout <<"\n\n\n";
    cout <<"\t\t\t\t\t";
    for(int i = 0;i <= 25;i++){
        cout <<a;
        Sleep(50);
        cout <<"\r";
        cout << "\t\t\t\t\t ";
    }
    for (int i = 0; i<= 25; i++){
        cout << b;
        Sleep(50);
    }
    system("pause>0");
    return 0;
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
        accountFile << "Email,NAME,USD BALANCE,RIEL BALANCE,PASSWORD" << endl;
        element* e = l->head;
        while (e != nullptr) {
            accountFile << e->data.Gmail << "," << e->data.name << "," << e->data.usdbalance<<","<<e->data.khbalance<< "," << e->data.password << endl;
            e = e->next;
        }
        accountFile.close();
    } else {
        cout << YELLOW << R"(                                   Unable to open file:)" << RESET;

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
            account.usdbalance = stod(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(',');
            account.khbalance =stod(line.substr(0,pos));
            line.erase(0, pos + 1);

            account.password = line;

            add(ls, account);
        }
        accountFile.close();
    } else {
        cout << YELLOW << R"(                                   Unable to open file:)" <<customerFile << endl<< RESET;
    }
}
  void makemainFolder(){
     const char* folder = "BankManagment";
    _mkdir(folder);
  }

void addAccount(list* ls) {
   makemainFolder();
    inf newAccount;
    bool success = false;
    clearConsole();
    cout << YELLOW << R"(                                                                Create Account
                                                                Enter Account name:  )" << RESET;

    cin >> newAccount.name;
    cout << YELLOW << R"(                                                                Enter account Email:  )" << RESET;


    cin >> newAccount.Gmail;
    newAccount.usdbalance = 0;
    newAccount.khbalance=0;
    newAccount.password = getPassword();
    while (!success) {
        newAccount.confirm = getPasswordconfirm();
        if (newAccount.confirm == newAccount.password) {
                element*e=ls->head;
            
            add(ls, newAccount);
            saveCustomersToFile(ls);
            cout << YELLOW << R"(                                                                Account created successfully. )" << RESET;

            cout << endl;
            success = true;
            }else{
                            cout << RED << R"(                                                        Account Name and Password is Already exist please try again:)   )" << RESET;

            }

        
    }
}

void logTransaction(list* l, string transaction, double amount, string name) {
    const char* folder = "BankManagment";
    _mkdir(folder);
    string transactionFile = string(folder) + "/" + "TransactionInformation.csv";
    ofstream openfile(transactionFile, ios::app);
    if (openfile.is_open()) {
        element* e = l->head;
        while (e != nullptr) {
            if (e->data.name == name) {
                     e->data.transaction=transaction;
                openfile << e->data.name << "," << e->data.transaction << "," << amount <<"(usd)"<< "," << currentDate() << endl;
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
        element* e = l->head;
        while (e != nullptr) {
            if (e->data.name == name) {
                    e->data.transaction=transaction;
                openfile << e->data.name << "," << e->data.transaction << "," << amount << "(riel)," << currentDate() << endl;
                break;
            }
            e = e->next;
        }
        openfile.close();
    } else {
        cout << "Unable to open file: " << transactionFile << endl;
    }
}

void deposit(list* ls, string name, string password) {
    element* e = ls->head;
    while (e != nullptr) {
        if (e->data.name == name && e->data.password == password) {
            long long depositAmount;
            char Op;
            cout << YELLOW << R"(
                                                                ***************************
                                                                * a.Deposit in USD        *
                                                                * b.Deposit in Riel       *
                                                                * C.Exit                  *
                                                                ***************************
                                                                Enter your choice: )" << RESET;
            cin>>Op;
            if(Op=='a'){
                    clearConsole();
                    cout << YELLOW << R"(                                                           Enter your deposit amount: )" << RESET;

                    cin >> depositAmount;
                    e->data.usdbalance += depositAmount;
                    cout << YELLOW << R"(                                                           You deposited: )" << BLUE<< depositAmount <<"USD"<<RESET<< endl;

                    cout << YELLOW << R"(                                                           Please confirm the amount (Y/N): )" << RESET;

                    char confirm;
                    cin >> confirm;
                    if (confirm == 'Y' || confirm == 'y') {
                        cout <<GREEN << R"(                                                           Deposit successful. )" << RESET;
                        cout << endl;
                        cout << YELLOW << R"(                                                           Your balance now: )" <<GREEN<<e->data.usdbalance << " USD" << endl<< RESET;


                        logTransaction(ls, "Deposit", depositAmount, name);
                        saveCustomersToFile(ls);
                        return;
                    } else {
                        cout << YELLOW << R"(                                                           Deposit cancelled. )" <<depositAmount << " USD" << endl<< RESET;

                        e->data.usdbalance -= depositAmount;
                    }
            }
                else if (Op=='b'){
                    clearConsole();
                    cout << YELLOW << R"(                                                               Enter your deposit amount: )" << RESET;

                    cin >> depositAmount;
                    e->data.khbalance += depositAmount;
                    cout << YELLOW << R"(                                                               You deposited: )" << BLUE<< depositAmount <<"riel"<<RESET<< endl;

                    cout << YELLOW << R"(                                                               Please confirm the amount (Y/N): )" << RESET;

                    char confirm;
                    cin >> confirm;
                    if (confirm == 'Y' || confirm == 'y') {
                        cout << GREEN << R"(                                                               Deposit successful. )" << RESET;
                        cout <<endl;
                        cout << YELLOW << R"(                                                               Your balance now: )" <<BLUE<<e->data.khbalance << " (riel)" << endl<< RESET;

                        cout << endl;
                        logTransactionKH(ls, "Deposit", depositAmount, name);
                        saveCustomersToFile(ls);
                        return;
                    } else {
                        cout << RED << R"(                                                               Deposit cancelled. )" <<depositAmount<< " (riel)" << endl<< RESET;

                        e->data.khbalance -= depositAmount;
                    }
            return;
        }else {
            return;
        }
    }
        e = e->next;
    }

}

void withdraw(list* ls, string name, string password) {
    element* e = ls->head;
    while (e != nullptr) {
        if (e->data.name == name && e->data.password == password) {
            long long draw;
            char Op;
            cout << YELLOW << R"(
                                                                ***************************
                                                                * a. Withdraw in USD      *
                                                                * b. Withdraw in Riel     *
                                                                * c. Exit                 *
                                                                ***************************
                                                                Enter your choice: )" << RESET;
            cin >> Op;
            if (Op == 'a') {
                clearConsole();
                cout << YELLOW << R"(                                                           Enter the amount to withdraw: )" << RESET;
                cin >> draw;
                cout << YELLOW << R"(                                                           You withdraw: )" << RESET << BLUE << draw << "(USD)" << RESET << endl;

                if (draw > e->data.usdbalance) {
                    cout << RED << R"(                                                           Insufficient balance. Withdrawal failed. )" << RESET;
                    cout << endl;
                    cout << YELLOW << R"(                                                           You can withdraw up to )" << GREEN << e->data.usdbalance << " USD" << RESET;
                    cout << endl;
                } else {
                    cout << YELLOW << R"(                                                           Please confirm the amount (Y/N): )" << RESET;
                    char confirm;
                    cin >> confirm;
                    if (confirm == 'Y'  || confirm == 'y') {
                        e->data.usdbalance -= draw;
                        cout << YELLOW << R"(
                                                           Withdrawal successful. )" << endl << RESET;
                        cout << YELLOW << R"(
                                                           Your balance now: )" << BLUE << e->data.usdbalance << " USD" << RESET << endl;
                        logTransaction(ls, "Withdraw", draw, name);
                        saveCustomersToFile(ls);
                    } else {
                        cout << RED << R"(                                                           Withdrawal cancelled. )" << draw << " (USD)" << endl << RESET;
                    }
                }
            } else if (Op == 'b') {
                clearConsole();
                cout << YELLOW << R"(                                                                Enter the amount to withdraw: )" << RESET;
                cin >> draw;
                cout << YELLOW << R"(                                                                You withdraw: )" << BLUE << draw << " Riel" << RESET << endl;

                if (draw > e->data.khbalance) {
                    cout << RED << R"(                                                                Insufficient balance. Withdrawal failed. )" << RESET;
                    cout << endl;
                    cout << YELLOW << R"(                                                                You can withdraw up to )" << GREEN << e->data.khbalance << " Riel" << RESET;
                    cout << endl;
                } else {
                    cout << YELLOW << R"(                                                                Please confirm the amount (Y/N): )" << RESET;
                    char confirm;
                    cin >> confirm;
                    if (confirm == 'Y'  || confirm == 'y') {
                        e->data.khbalance -= draw;
                        cout << YELLOW << R"(
                                                                Withdrawal successful. )" << endl << RESET;
cout << YELLOW << R"(
                                                                Your balance now: )" << GREEN << e->data.khbalance << " Riel" << RESET << endl;
                        logTransactionKH(ls, "Withdraw", draw, name);
                        saveCustomersToFile(ls);
                    } else {
                        cout << RED << R"(                                                                Withdrawal cancelled. )" << draw << " Riel" << endl << RESET;
                    }
                }
            } else {
                return;
            }
            return;
        }
        e = e->next;
}

}
void displayTransaction(list* ls) {
    const char* folder = "BankManagment";
    string customerFile = string(folder) + "/" + "TransactionInformation.csv";
    ifstream accountFile(customerFile);

    if (accountFile.is_open()) {
        string line;
        getline(accountFile, line); 

        cout <<"\t\t\t\t"<< GREEN << setw(19) <<left<< "NAME" <<setw(30)<<left<<"TRANSECTION"<<setw(30)<<left<<"AMOUNT" << setw(30) <<left<< "DATE" << RESET << endl;

   
        while (getline(accountFile, line)) {
            inf account;
            string amount, currentDate;
            size_t pos = 0;

            // Parse name
            pos = line.find(',');
            account.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Parse transaction
            pos = line.find(',');
            account.transaction = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Parse amount
            pos = line.find(',');
            amount = line.substr(0, pos);
            line.erase(0, pos + 1);

            currentDate = line;

            // Print the account information with formatting
            cout <<"\t\t\t\t"<< BLUE << setw(20) <<left<< account.name << setw(31)<<left<< account.transaction<<setw(31)<<left<< amount << setw(31)<<left<< currentDate<< RESET << endl;
        }

        accountFile.close();
    } else {
        cout << YELLOW << "Unable to open file: " << customerFile << RESET << endl;
    }
}

void transfer(list* ls, string frompass) {
    string toname;
    string toemail;
    long long amount;
    int option;
    bool success = false;

    while (!success) {
        clearConsole();

        element* e = ls->head;

        while (e != nullptr) {
            if (e->data.password == frompass) {
                cout << YELLOW << R"(
                                                                *******************************
                                                                * 1. Transfer  in  USD        *
                                                                * 2. Transfer  in  RIEL       *
                                                                * 3. Exit                     *
                                                                *******************************
                                                                Enter your choice: )" << RESET;
                cin >> option;

                switch (option) {
                    case 1: {
                        clearConsole();
                        cout << GREEN << R"(
                                                                    Transfer to Account Gmail: )" << RESET;
                        cin >> toemail;
                        cout << GREEN << R"(
                                                                    Transfer to Account name: )" << RESET;
                        cin >> toname;
                        cout << GREEN << R"(
                                                                    Enter your USD amount: )" << RESET;
                        cin >> amount;

                        if (amount > e->data.usdbalance) {
                            cout << RED << R"(
                                                                    Insufficient balance. Transfer failed.)" << RESET << endl;
                        } else {
                            element* recipient = ls->head;
                            while (recipient != nullptr) {
                                if (recipient->data.name == toname && recipient->data.Gmail == toemail) {
                                    cout << YELLOW << "\t\t\t\t\t\t\tConfirm transfer of " << BLUE << amount << " USD to " << GREEN << toname << " (y/n): " << RESET;
                                    char confirm;
                                    cin >> confirm;
                                    if (confirm == 'y' || confirm == 'Y') {
                                        e->data.usdbalance -= amount;
                                        recipient->data.usdbalance += amount;
                                        cout << CYAN << "\t\t\t\t\t\t\tTransfer successful. Your balance now: " << BLUE << e->data.usdbalance << RESET << " USD." << endl;
                                        string trans = "Transfer to " + toname;
                                        logTransactionKH(ls, trans, amount, e->data.name);
                                        saveCustomersToFile(ls); // Save changes
                                        success = true;
                                         cout << "\t\t\t\t\t\t\t\tPress any key to return to menu...";
                                       _getch(); // Assumed to be defined elsewhere


                                    } else {
                                        cout << RED << "\t\t\t\t\t\t\tTransfer cancelled." << RESET << endl;
                                    }
                                    break;
                                }
                                recipient = recipient->next;
                            }
                            if (!success) {
                                cout << RED << "\t\t\t\t\t\t\tRecipient not found. Transfer failed." << RESET << endl;
                                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                                _getch();
                            }
                            
                        }
                        break;
                    }
                    case 2: {
                        clearConsole();
                        cout << GREEN << R"(
                                                                    Transfer to Account Gmail: )" << RESET;
                        cin >> toemail;
                        cout << GREEN << R"(
                                                                    Transfer to Account name: )" << RESET;
                        cin >> toname;
                        cout << GREEN << R"(
                                                                    Enter your Riel amount: )" << RESET;
                        cin >> amount;
                        if (amount > e->data.khbalance) {
                            cout << RED << R"(
                                                                    Insufficient balance. Transfer failed.)" << RESET << endl;
                        } else {
                            element* recipient = ls->head;
                            while (recipient != nullptr) {
                                if (recipient->data.name == toname && recipient->data.Gmail == toemail) {
                                    cout << YELLOW << "\t\t\t\t\t\t\tConfirm transfer of " << BLUE << amount << " RIEL to " << GREEN << toname << " (y/n): " << RESET;
                                    char confirm;
                                    cin >> confirm;
                                    if (confirm == 'y' || confirm == 'Y') {
                                        e->data.khbalance -= amount;
                                        recipient->data.khbalance += amount;
                                        cout << CYAN << "\t\t\t\t\t\t\tTransfer successful. Your balance now: " << BLUE << e->data.khbalance << RESET << " RIEL." << endl;
                                        string tran = "Transfer to " + toname;
                                        logTransactionKH(ls,tran, amount, e->data.name);
                                        saveCustomersToFile(ls); 
                                        success = true;
                                        cout << "\t\t\t\t\t\t\t\tPress any key to return to menu...";
                                    _getch(); 
                                    } else {
                                        cout << RED << "\t\t\t\t\t\t\tTransfer cancelled." << RESET << endl;
                                    }
                                    break;
                                }
                                recipient = recipient->next;
                            }
                            if (!success) {
                                cout << RED << "\t\t\t\t\t\t\tRecipient not found. Transfer failed." << RESET << endl;
                                cout << "\t\t\t\t\t\t\tPress any key to return to menu...";
                                _getch();
                            }

                            
                        }
                        break;
                    }
                    case 3:
                        return;
                    default:
                        cout << RED << "\t\t\t\t\t\t\tInvalid choice." << RESET << endl;
                        break;
                }
            }
            e = e->next;
        }
        if (!success) {
            cout << "Invalid password or account not found." << endl;
        }
    }
}
long long USDtoRiel(long long usd) {
    return usd * 4100.00;
}

long long RieltoUSD(long long riel) {
    return riel / 4100.00;
}

void exchange(list* ls, string password) {
    long long amount;
    int option;
    bool success = false;

    clearConsole(); // Assumed to be defined elsewhere

    if (!success) {
        element* e = ls->head;
        while (e != nullptr) {
            if (e->data.password == password) {
                cout << YELLOW << R"(
                                                                *******************************
                                                                * 1. Exchange USD to RIEL     *
                                                                * 2. Exchange RIEL to USD     *
                                                                * 3. Exit                     *
                                                                *******************************
                                                                Enter your choice: )" << RESET;
                cin >> option;

                switch (option) {
                    case 1: {
                        clearConsole();
                        cout << GREEN << R"(
                                                                    Enter your USD amount:)" << RESET;
                        cin >> amount;

                        if (amount > e->data.usdbalance) {
                            cout << RED << R"(
                                                                    Insufficient balance. Exchange failed.)" << RESET << endl;
                        } else {
                            e->data.usdbalance -= amount;
                            long long riel = USDtoRiel(amount); // Assumed to be defined elsewhere
                            e->data.khbalance += riel;
                            cout << GREEN << R"(
                                                                    Your balance now: )" <<e->data.usdbalance<<" USD and "<<e->data.khbalance<<" RIEL."<< RESET << endl;
                            saveCustomersToFile(ls);
                            logTransactionKH(ls, "Exchange to RIEL", amount, e->data.name);

                            //cout << "\t\t\t\t\t\t\t\tPress any key to return to menu...";
                            //_getch(); // Assumed to be defined elsewhere
                        }

                        break;
                    }
                    case 2: {
                        clearConsole();
                        cout << GREEN << R"(
                                                                    Enter your RIEL amount:)" << RESET;
                        cin >> amount;

                        if (amount > e->data.khbalance) {
                            cout << RED << R"(
                                                                    Insufficient balance. Exchange failed.)" << RESET << endl;
                        } else {
                            e->data.khbalance -= amount;
                            long long usd = RieltoUSD(amount); // Assumed to be defined elsewhere
                            e->data.usdbalance += usd;
                            cout << GREEN << R"(
                                                                    Your balance now: )" <<e->data.usdbalance << " USD and " << e->data.khbalance << " RIEL."<< RESET << endl;
                            saveCustomersToFile(ls);
                            logTransaction(ls, "Exchange to USD", amount, e->data.name); // Assumed to be defined elsewhere

                        }

                        break;
                    }
                    case 3:
                        return;
                    default:
                        cout << RED << "\t\t\t\t\t\t\tInvalid choice." << RESET << endl;
                        break;
                }
                return;
            }
            e = e->next;
        }
    }
}


void displayAllAccounts(list* ls) {
    element* e = ls->head;

    cout <<"\t\t\t\t"<< GREEN << setw(54) <<left<< "Account Name" << setw(43) <<left<< "Gmail" << RESET << endl;

    while (e != nullptr) {
        cout <<"\t\t\t\t"<< BLUE << setw(50) <<left<< e->data.name << setw(50) <<left<< e->data.Gmail << RESET << endl;
        e = e->next;
    }
}
void displayAccountBalance(list* ls, const string& accountName, const string& password) {

    element* current = ls->head;
    cout <<"\t\t\t\t"<<BLUE<< setw(50) <<left<< "Name"<<setw(50) <<left<<"Balance(USD)"<<setw(50) <<left<<"Balance(Riel) "<<endl;
    while (current != nullptr) {
        if (current->data.name == accountName && current->data.password == password) {
            
            cout <<"\t\t\t\t"<<GREEN<<setw(50) <<left<<current->data.name<<setw(50) <<left<<current->data.usdbalance<<setw(50) <<left<<current->data.khbalance<< RESET<<endl;
            break;
        }
        current = current->next;
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
    if (current->data.usdbalance != 0 && current->data.khbalance!=0) {
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
    cout << endl;

    saveCustomersToFile(ls);
}

