/*Created By J. Cox 12/18/2020*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void createMenu(); //Function Prototype
void createNoAccountMenu();

class bankAccount{
private:
    int accountNumber;
    int pin;
    double balanceChecking;
    double balanceSavings;
    string lastName;
    

public:
string firstName;
    bankAccount(){
        accountNumber = 0;
        balanceChecking = 0.00;
        balanceSavings = 0.00;
        firstName = "";
        lastName = "";
    };

    void createAccount(int &counter){
        cout << "What is your first name?" << endl;
            cin >> firstName;
        cout << "What is your last name?" << endl;
            cin >> lastName;
        cout << "Enter unique PIN (XXXX Digits 1-9): " << endl;
            cin >> pin;

        accountNumber = counter;
        balanceChecking = 0.00; //Initialize Balances
        balanceSavings = 0.00;

        cout << "Account Successfully Created!" << endl;
        cout << "Your account number is: " << counter << endl;

        counter++;
    }

    void showBalance(){
        cout << "Hello " << firstName << ", your balances are: " << '\n';
        cout << "Checking: $" << balanceChecking << '\n';
        cout << "Savings: $" << balanceSavings << '\n';
    }

    void deposit(){
        string account;
        double amount;

        cout << "Which account would you like to deposit to? (Checking/Savings)" << '\n'; //User determines account
            cin >> account;

        while(account != "Checking" && account != "Savings"){ //User Input Error Check
            cout << "Invalid account name." << endl;
            cout << "Which account would you like to deposit to? (Checking/Savings)" << endl;
                cin >> account;
        }

        cout << "How much would you like to deposit?" << endl; //User determines deposit
        cin >> amount;

        while(!cin){//User input error check
            cin.clear();
            cin.ignore(100,'\n');
            cout << "Invalid Amount" << endl;
            cout << endl;
            cout << "How much would you like to deposit?" << endl;
                cin >> amount;
        }
    //Balance Updates
        if(account == "Checking"){
            balanceChecking = balanceChecking + amount;
        }
        if(account == "Savings"){
            balanceSavings = balanceSavings + amount;
        }
    }

    void withdrawl(){
        int amount;
        string account;

        cout << "Withdraw from which account?" << endl;
            cin >> account;
        
        while(account != "Checking" && account != "Savings"){ //User Input Error Check
            cout << "Invalid account name." << endl;
            cout << "Which account would you like to deposit to? (Checking/Savings)" << endl;
                cin >> account;
        }
        
        if(account == "Checking"){
            cout << "Current Balance: $" << balanceChecking << '\n';
            cout << "How much would you like to withdrawal?" << endl;
            cin >> amount;

            while(balanceChecking - amount < 0){ //Prevents "overdraft"
                cout << "Insufficient Funds!" << endl;
                cout << "Current Balance: $" << balanceChecking << endl;
                cout << "How much would you like to withdrawal?" << endl;
                cin >> amount;
        }
            balanceChecking = balanceChecking - amount;

            cout << "Withdrawl Successful!" << endl;
            cout << "New Balance: $" << balanceChecking << endl;
        }

        if(account == "Savings"){
            cout << "Current Balance: $" << balanceSavings << '\n';
            cout << "How much would you like to withdrawal?" << endl;
            cin >> amount;

            while(balanceSavings - amount < 0){ //Prevents "overdraft"
                cout << "Insufficient Funds!" << endl;
                cout << "Current Balance: $" << balanceSavings << endl;
                cout << "How much would you like to withdrawal?" << endl;
                cin >> amount;
            }

            balanceSavings = balanceSavings - amount;

            cout << "Withdrawl Successful!" << endl;
            cout << "New Balance: $" << balanceSavings << endl;
        }
    }

    void balanceTransfer(){

            string account;
            double amount;

            cout << "What account would you like to transfer to? (Checking/Savings)" << endl;
                cin >> account;
            
            while(account != "Checking" && account != "Savings"){
                cout << "Invalid Account Choice!" << '\n';
                cout << "What account would you like to transfer to? (Checking/Savings)" << endl;
                cin >> account;
            }
            if(account == "Checking"){
            cout << "Current Balance is: $" << balanceSavings << '\n';
            cout << "How much would you like to transfer?" << '\n';
                cin >> amount;

            while(balanceSavings - amount < 0){
                cout << "Insufficient Funds!" << '\n';
                cout << "Current Balance is: $" << balanceSavings << '\n';
                cout << "How much would you like to transfer?" << '\n';
                cin >> amount;
            }
            cout << "Transfer successful!" << '\n';
            balanceSavings = balanceSavings - amount;
            balanceChecking = balanceChecking + amount;
            }

            if(account == "Savings"){
            cout << "Current Balance is: $" << balanceChecking << '\n';
            cout << "How much would you like to transfer?" << '\n';
                cin >> amount;

            while(balanceChecking  - amount < 0){
                cout << "Insufficient Funds!" << '\n';
                cout << "Current Balance is: $" << balanceChecking  << '\n';
                cout << "How much would you like to transfer?" << '\n';
                cin >> amount;
            }
            cout << "Transfer successful!" << '\n';
            balanceSavings = balanceSavings + amount;
            balanceChecking = balanceChecking - amount;
            }
        }

    void deleteAccount(){
            firstName = "DELETED";
            lastName = "DELETED";
            balanceChecking = 0;
            balanceSavings = 0;
            pin = 0;
                cout << "Account successfully deleted!" << '\n';
        }

    //Friend Functions
    friend void writeToFile(ofstream &outData, vector<bankAccount> &Accounts);
    friend void readFromFile(ifstream &inData, vector<bankAccount> &Accounts);
    friend int verification(vector<bankAccount> &Accounts, int &accountNumberHolder, bankAccount &activeAccount);
};

int main(){

    vector<bankAccount> Accounts;
    bankAccount activeAccount;

    int accountNumberHolder;
    int counter = 0;
    int security;

    string query;
    string anotherQuery;

    ofstream outData;
    ifstream inData;

//Import existing accounts for external ledger
    inData.open("BankingData.txt");
    readFromFile(inData, Accounts);
    inData.close();

//Find current account number
    counter = Accounts.size();

    do{
        if(counter == 0){ //No accounts case
        createNoAccountMenu();
        cout << "What would you like to do today?" << endl;
            cin >> query;
            while(query != "C"){
                cout << "Error: NO ACCOUNTS EXIST. Create account for more options." << endl;
                cout << "What would you like to do today?" << endl;
                cin >> query;
            }
        }

    createMenu();

    cout << "What would you like to do today?" << endl;
    cin >> query;

    if(query == "C"){
        activeAccount.createAccount(counter);
        Accounts.push_back(activeAccount);
        cout << "Another Transaction? (Y/N)" << endl;
            cin >> anotherQuery;
        }
    
    if(query == "X"){
        security = verification(Accounts, accountNumberHolder, activeAccount);
        if(security == 1){
            activeAccount.deleteAccount();
            Accounts[accountNumberHolder] = activeAccount;
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 2){
            cout << "Incorrect Pin!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 3){
            cout << "Account doesn't exist!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
    }
    
    if(query == "D"){
        security = verification(Accounts, accountNumberHolder, activeAccount);
        if(security == 1){
            activeAccount.deposit();
            Accounts[accountNumberHolder] = activeAccount;
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 2){
            cout << "Incorrect Pin!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 3){
            cout << "Account doesn't exist!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
    }

    if(query == "W"){
        security = verification(Accounts, accountNumberHolder, activeAccount);
        if(security == 1){
            activeAccount.withdrawl();
            Accounts[accountNumberHolder] = activeAccount;
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 2){
            cout << "Incorrect Pin!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 3){
            cout << "Account doesn't exist!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
    }
    
    if(query == "B"){
        security = verification(Accounts, accountNumberHolder, activeAccount);
        if(security == 1){
            activeAccount.showBalance();
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 2){
            cout << "Incorrect Pin!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 3){
            cout << "Account doesn't exist!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
    }

    if(query == "T"){
        security = verification(Accounts, accountNumberHolder, activeAccount);
        if(security == 1){
            activeAccount.balanceTransfer();
            Accounts[accountNumberHolder] = activeAccount;
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 2){
            cout << "Incorrect Pin!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
        if(security == 3){
            cout << "Account doesn't exist!" << '\n';
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }
    }

    while(anotherQuery != "Y" && anotherQuery != "N"){
            cout << "Error: Invalid Input" << endl;
            cout << "Another Transaction? (Y/N)" << endl;
                cin >> anotherQuery;
        }

    if(anotherQuery == "N"){
            cout << "Thanks! Have a great day!" << endl;
            break;
        }



    }while(anotherQuery == "Y");

    outData.open("BankingData.txt");
    writeToFile(outData, Accounts);
    outData.close();

    return 0;
}


//Additional Functions

void createNoAccountMenu(){
    cout << "Bank of C++" << endl;
    cout << "-------------------" << endl;
    cout << "'>>'Create Account (C)" << endl;
}

void createMenu(){
    cout << "Bank of C++" << endl;
    cout << "-------------------" << endl;
    cout << ">>Create Account (C)" << endl;
    cout << ">>Delete Account (X)" << endl;
    cout << ">>Deposit (D)" << endl;
    cout << ">>Withdrawl (W)" << endl;
    cout << ">>Show Balance (B)" << endl;
    cout << ">>Balance Transfer (T)" << endl;

    cout << "-------------------" << endl;
}

void writeToFile(ofstream &outData, vector<bankAccount> &Accounts){
    for(int i = 0; i < Accounts.size(); i++){
        outData << Accounts[i].accountNumber << " " << Accounts[i].pin << " " << Accounts[i].firstName << " " << Accounts[i].lastName << " " << Accounts[i].balanceChecking << " " << Accounts[i].balanceSavings << endl;
    } 
}

void readFromFile(ifstream &inData, vector<bankAccount> &Accounts){
    bankAccount temp;
    while(!(inData.eof())){
        inData >> temp.accountNumber;
        if(inData.eof()){
            return;
        }
        inData >> temp.pin;
        inData >> temp.firstName;
        inData >> temp.lastName;
        inData >> temp.balanceChecking;
        inData >> temp.balanceSavings;

        Accounts.push_back(temp);
    }
}

int verification(vector<bankAccount> &Accounts, int &accountNumberHolder, bankAccount &activeAccount){

    int pinInput;
    int pinHolder = 0;
    int accNum;
    cout << "What is the account number?" << endl;
        cin >> accNum;

    for(vector<bankAccount>::iterator it = Accounts.begin(); it != Accounts.end(); it++){
                bankAccount temp = *it;
                if(temp.accountNumber == accNum){
                    pinHolder = temp.pin;
                    activeAccount = temp;
                } 
    }

    if(pinHolder == 0){ //Account doesn't exist
        return 3;
    }

    cout << "What is the PIN on the account?" << endl;
        cin >> pinInput;

    if(pinInput == pinHolder){
        accountNumberHolder = accNum;

        return 1;
    } 
    else{
        return 2;
    }
}