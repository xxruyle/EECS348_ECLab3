#include <iostream>
#include <string> 

#include <iostream> 

class Account 
{
    public: 
        std::string accountNumber;  
        std::string accountHolder;  
        float balance;  

        Account(const  std::string& num, const  std::string& holder, float bal) : accountNumber(num), accountHolder(holder), balance(bal) {}; 

        void displayDetails() {}; 

        void deposit(int amount) 
        {
            balance += amount;
        }; 

        float withdraw(int amount) 
        {
            if (amount <= balance) 
            {
                balance -= amount; 
            } else {
                std::cout << "Insufficient balance for withdrawal " << std::endl;  
            }
            return amount;
        }; 

        friend Account operator+(const Account& self, Account& other)        
        {
            Account res = self; 
            res.balance += 300;
            other.balance -= 300;  
            return res;  
        }

        Account& operator=(const Account& other) {
            if (this != &other) {
                accountNumber = other.accountNumber;
                accountHolder = other.accountHolder;
                balance = other.balance;
            }
            return *this;
        }


        friend std::ostream& operator<<(std::ostream& outputStream, const Account& account) 
        {  
            outputStream << "Account Details for Account (ID: " << account.accountNumber << "):\n"
                << "   Holder: " << account.accountHolder << "\n"
                << "   Balance: $" << account.balance << "\n" << std::endl; 
            return outputStream; 
        }

}; 

class SavingsAccount : public Account 
{

    public: 
        float interestRate; 

        SavingsAccount(const  std::string& num, const  std::string& holder, float bal, float rate) 
        : Account(num, holder, bal), interestRate(rate) {};

        void displayDetails()
        {
            std::cout << "Account Details for Savings Account (ID:  " << accountNumber << "):\n";
            std::cout << "Holder: " << accountHolder << std::endl; 
            std::cout << "Balance: $" << balance << std::endl;  
            std::cout << "Interest Rate: " << interestRate * 100 << ".00%" << std::endl;  
            std::cout << std::endl;
        };


        float withdraw(int amount)  
        {
            if (amount <= balance - minBal) {  // Minimum balance of $100 for savings account   
                balance -= amount;
            } else {
                std::cout << "Insufficient balance for withdrawal from savings account.\n";   
            }

            return amount; 

        };
 

    private: 
        int minBal = 50;
}; 

class CurrentAccount : public Account 
{
    public: 
        float overdraftlimit;

        CurrentAccount(const std::string& num, const std::string& holder, float bal, float limit)   
        : Account(num, holder, bal), overdraftlimit(limit) {};  




        void displayDetails()
        {
            std::cout << "Account Details for Current Account (ID:  " << accountNumber << "):\n"; 
            std::cout << "Holder: " << accountHolder << std::endl; 
            std::cout << "Balance: $" << balance << std::endl;  
            std::cout << "Overdraft Limit: $" << overdraftlimit << ".00" << std::endl;  
            std::cout << std::endl;
        };


        float withdraw(int amount)   
        {
            if (amount < overdraftlimit + balance)  
            {
                balance -= amount; 
            } else {
                std::cout << "Insufficient balance for withdrawal from current account" << std::endl;
            }

            return amount; 
        };

        CurrentAccount& operator=(const Account& other) {
                if (this != &other) {
                    accountNumber = other.accountNumber;
                    accountHolder = other.accountHolder;
                    balance = other.balance;
                    overdraftlimit = overdraftlimit;   
                }
                return *this;
            }



};

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);
    
    std::cout << "Account details after deposit and withdrawal: " << std::endl;  
    savings.displayDetails();
    current.displayDetails();

    std::cout << "Display the details of all accounts after each transaction using the << operator" << std::endl;
    std::cout << savings; 
    std::cout << current; 


    // Transfer 300 from savings to current
    current = current + savings;

    std::cout << "Account details after transfer: " << std::endl; 
    savings.displayDetails();
    current.displayDetails();

    std::cout << "Display the details of all accounts after each transaction using the << operator" << std::endl; 
    std::cout << savings; 
    std::cout << current; 

    std::cout << "Ensure proper validation for withdrawal operations based on account type." << std::endl; 
    savings.withdraw(2000);  
    current.withdraw(2000);



    return 0;
}