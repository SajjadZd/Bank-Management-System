// This is a Bank Management System developed by Sajjad(f2024266540) and Abdullah(f2024266508).
//This project is based on OOP and it contains all four pillars of oop.

#include<iostream> // for basic input output
#include<string> // to use string data type
#include<vector> // for storing different trnasaction records etc.
#include<fstream> // for file handeling
#include <ctime> // for getting date and time.
#include <cstdlib>  // For rand() and srand()

using namespace std;

vector<string> randomIds;

// user defined structure for UserData
struct UserData{
int age;
string id;
string name;
string address;
string phoneNumber;
};

// function for generating random Id.
string generateRandomID(vector<string> &randomIds) {
again:
string id = "";
bool found = false;

srand(time(0)); 

for (int i = 0; i < 6; i++) {
    int digit = rand() % 10;
    id += ('0' + digit);  // convert int to char and append
}

for (int i = 0; i < randomIds.size(); i++) {
    
    if(id == randomIds[i] ){
    	found = true;
    	break;
	}
}

if(!found){
	randomIds.push_back(id);
	return id;
}else{
	goto again;
}

}

// funtion for taking UserInput
UserData inputInfo()
{
UserData user;		

user.id = generateRandomID(randomIds);

cout << "Enter name: ";
getline(cin, user.name);

cout << "Enter Address: ";
getline(cin, user.address);

cout << "Enter PhoneNumber : ";
getline(cin,user.phoneNumber);

while (true) {
    cout << "Enter age: ";
    cin >> user.age;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Age! Please Enter correct age only." << endl;
    } else {
    	cin.ignore();
        break;
    }
}
return user;
}

//funtion for taking Amount as an input.
float inputAmount( )
{
float amount;
while (true) {
    cout << "Enter Amount : ";
    cin >> amount;
    
	 if (cin.fail()) {
        cin.clear(); 
        cin.ignore(1000, '\n'); 
        cout << "Invalid amount! Please enter correct value." << endl;
    }
    else if (amount < 0) {
        cout << "Amount cannot be negative. Try again." << endl;
    }
    else 
	{
        cin.ignore(); 
        break; 
    }
}

return amount;

}

// function for converting choices to lower.
void convertToLower(string &word)
{
for(int i = 0 ; i < word.length(); i++)
{
	word[i] = tolower(word[i]);
}
}

// function for getting Date and Time.
string getDateAndTime() {
time_t timestamp;
time(&timestamp);

string time = ctime(&timestamp);

if (!time.empty() && time[time.length() - 1] == '\n') {
    time.erase(time.length() - 1); // remove trailing newline
}

return time;
}

//abstract Person class
class Person{
public:
	int age;
	string name;
	string phoneNumber;
	string address;
	
	// Pure virtual Function for achieving runtime polymorphism.
	virtual void displayInfo() = 0;
};

// Account class.
class Account{
public:
	string id;
	double balance;
	
	void displayAccountInfo()
	{
		cout << "Account Id : " << id << endl
		     << "Balance : " << balance << endl;
	}
};

//Transaction class.
class Transaction{
public:
	string id;
	double amount;
	string dateAndTime;
	string doneBy;
	
	void displayTransactionHistory()
	{
		cout << "Transaction Id : " << id << endl
			 << "Transaction Amount : " << amount << endl
			 << "Transaction Date and Time : " << dateAndTime << endl
			 << "Done by " << doneBy << endl;
	}		
};

// Loan class
class Loan{
public:
	string id;
	string idofUser;
	double amount;
	bool isApproved;
	string dateAndTime;
	string requestedBy;
	
	// Default constructor.
	Loan() {}
	// Parameterized constructor.
	Loan(string id, string idofUser, float amount, bool isApproved, string dateAndTime, string requestedBy)
	{
		this->id = id;
		this->idofUser = idofUser;
		this->amount = amount;
		this->isApproved = isApproved;
		this->dateAndTime = dateAndTime;
		this->requestedBy = requestedBy;
	}
	void displayLoanInfo()
	{
		cout << "Loan Id : " << id << endl
			 << "Loan Amount : " << amount << endl
			 << "Request Date and Time : " << dateAndTime << endl
			 << "Requested By : " << requestedBy << endl
			 << "Status : " << (isApproved? "Request Approved." : "Request not Aprroved.") 
			 << endl;
	}
};

// Function for Generating transaction Report
Transaction generateTransactionReport(float Amount, string user)
{
Transaction T;
T.id = generateRandomID(randomIds); 
T.amount = Amount;
T.dateAndTime = getDateAndTime();
T.doneBy = user;

return T;
}

// Function for Generating Loan Report
Loan generateLoanReport(float amount, string user, string userId)
{
Loan loan;
loan.amount = amount;
loan.dateAndTime = getDateAndTime();
loan.id = generateRandomID(randomIds);
loan.isApproved = false;
loan.requestedBy = user;
loan.idofUser = userId;

return loan;
}

// Function for saving Transaction histories in file.
void saveTransactionToFile(Transaction transaction, string type, string id)
{
ofstream file("transactions.txt" , ios::app);

if(file.is_open()){
	file << id << endl
     << "Transaction Id : " << transaction.id << endl
	 << "Transaction Amount : " << transaction.amount << endl
	 << "Transaction Date and Time : " << transaction.dateAndTime << endl
	 << "Done by " << transaction.doneBy << endl
	 << "Transaction type : " << type << endl
	 << id << endl;
}else{
	cout << "Error: file is not opened!" << endl;
}	 
file.close();
}

// Function for saving Loan histories in file.
void saveLoanHistoryToFile(vector<Loan> loan)
{
ofstream file("Loans.txt");

if(file.is_open()){
	for(int i = 0; i < loan.size(); i++)
	{
		file << loan[i].idofUser << "\t" << loan[i].requestedBy << "\t" << loan[i].id << "\t" 
	     << loan[i].amount << "\t" << loan[i].isApproved << "\t" << loan[i].dateAndTime << "\t" << endl;
	}
}else{
	cout <<"Error: file is not opened" << endl;
}
file.close();
}

// function for loading loans from file to program.
void LoadLoansFromFile(vector<Loan> &loans)
{
    Loan LoAn;
    ifstream file("Loans.txt");

    if(file.is_open()){
    	while (file >> LoAn.idofUser >> LoAn.requestedBy >> LoAn.id >> LoAn.amount >> LoAn.isApproved)
	    {
	        file.ignore();
	        getline(file, LoAn.dateAndTime); 
	        loans.push_back(LoAn);
	    }
	}else{
	cout <<"Error: file is not opened" << endl;
	}

    file.close();
}

// Customer class inherited from Person class
class Customer : public Person{
public:
	string customerId;
	float amount;
	Account account;
	Transaction transaction;
	Loan loan;
	
	
	// Parameterized Constructor.
	Customer(int age, string name, string phoneNum, string address, string id, string Password, float bal = 0 ,string accId = generateRandomID(randomIds))
	{
		this->age = age;
		this->name =  name;
		this->phoneNumber = phoneNum;
		this->address = address;
		this->customerId = id;
		this->password = Password;
		account.balance = bal;
		account.id = accId;
	}
	
	// Default constructor
	Customer(){	}
	
	void displayInfo()
	{
		cout << "Customer Id : " << customerId << endl
			 << "Customer Name : " << name << endl
			 << "Customer Age : " << age << endl
			 << "Customer Phone: " << phoneNumber << endl
			 << "Customer Address : " << address << endl << endl
			 << "Account Information : " << endl;
			 account.displayAccountInfo();
	}
	
	void transferFunds(Customer &customer)
	{
		 amount = inputAmount();
		 if(amount > account.balance)
		 {
		 	cout << "Insuficient Balance in your account." << endl;
		 }
		 else
		 {
		 	account.balance -= amount;
		 	customer.account.balance += amount;
		 	cout << "Transaction has been done successfully!" << endl;
		    transaction = generateTransactionReport(amount, name);
		 	transaction.displayTransactionHistory();
		 	saveTransactionToFile(transaction, "FundsTransfer", customerId);
		 	
		 }
		 
	}
	
	void depositeMoney()
	{
		amount = inputAmount();
		account.balance += amount;
		cout << "Deposite has been done successfully!" << endl;
		transaction = generateTransactionReport(amount, name);
	 	transaction.displayTransactionHistory();
	 	saveTransactionToFile(transaction, "Money Deposit", customerId);
	}
	
	void withdrawMoney()
	{
	     amount = inputAmount();
	     if(amount > account.balance)
		 {
		 	cout << "Insuficient Balance in your account." << endl;
		 }
		 else
		 {
		 	account.balance -= amount;
		 	cout << "Withdrawl has been done successfully!" << endl;
		 	transaction = generateTransactionReport(amount, name);
		 	transaction.displayTransactionHistory();
		 	saveTransactionToFile(transaction,"Withdraw", customerId);
		 }
	}
	
	void requestForLoan(vector<Loan> &loans)
	{
		amount = inputAmount();
		cout << "Your Request for Loan has been sent please wait for Approval." << endl;
		loan = generateLoanReport(amount, name, customerId);
//			saveLoanHistoryToFile(loan);
		loans.push_back(Loan(loan.id, loan.idofUser, loan.amount, loan.isApproved, loan.dateAndTime, loan.requestedBy));
	}
	
	void checkLoanApproval(vector<Loan> &loans)
	{
		
		bool found = false;
		
		for(int i = 0 ; i < loans.size(); i++)
		{
			if(customerId == loans[i].idofUser)
			{
				loans[i].displayLoanInfo();
				cout << endl;
				found = true;
			}
			
		}
		
		if(!found)
		{
			cout << "There is no request for loan with this Id." << endl;
		}
	}
	
	void viewTransactionsHistory()
	{
		string line;
		bool found = false;
		ifstream Ifile("transactions.txt");
		while(getline(Ifile,line))
		{
			if(line == customerId)
			{
				found = true;
				while(getline(Ifile,line))
				{
					if(line == customerId)
					{
						break;
					}
					cout << line << endl;
					
				}
				cout << endl;
			}
		}
		if(!found)
		{
			cout << "There is no Transaction History with this Id." << endl;
		}
		Ifile.close();
	}
	//getter for password.
	string getPassword()
	{
		return password;
	}
	
	//setter for password.
	void setPassword(string newpass)
	{
		password = newpass;
	}
	
private:
	string password;
};

// Manager class
class Manager : public Person{
public:
	string id;
	Manager(string name, int age, string phoneNumber, string Address, string id , string Password)
	{
		this->name = name;
		this->age = age;
		this->phoneNumber = phoneNumber;
		this->address = Address;
		this->id = id;
		this->password = Password;
	}
	void displayInfo()
	{
	    cout << "Manager Id : " << id << endl
			 << "Manager Name : " << name << endl
			 << "Manager Age : " << age << endl
			 << "Manager Address : " << address << endl << endl;
	}
	
	void viewAllCustomers(vector<Customer> customers)
	{
		for(int i = 0 ; i < customers.size(); i++)
		{
			customers[i].displayInfo();
		}
	}
	
	void deleteCustomer(vector<Customer> &customers, string choice)
	{
		
		int j;
		string id;
		bool isFound = false;
		Customer customerToBeDelete;
		cout << "Enter Id of customer : ";
		getline(cin, id);
		
		for(int i = 0 ; i < customers.size(); i++)
		{
			if(customers[i].customerId == id)
			{
				isFound = true;
				j = i;
				customerToBeDelete = customers[i];
				cout << "Current Information is:" << endl;
				customers[i].displayInfo();
				cout << endl;
				break;
			}
		}
		
		if(isFound)
		{
			while(true)
			{
				cout << "Are you sure you want to delete this Customer?[yes/no] : ";
				getline(cin, choice);
				convertToLower(choice);
				if(choice == "yes")
				{
					customers.erase(customers.begin() + j);
					cout << "Customer deleted successfully!" << endl;
					break;
				}
				else if(choice == "no")
				{
					break;
				}
				else
				{
					cout << "Invalid choice . try again" << endl;
				}
			}
		}
		
		else
		{
			cout << "Customer not found." << endl;
		}
	}
	
	void viewAllLoanRequests(vector<Loan> loans)
	{
		for(int i = 0 ; i < loans.size(); i++)
		{
			loans[i].displayLoanInfo();
			cout << endl;
		}
		
		if(loans.size() == 0){
			cout << "There is no Loan Request." << endl;
		}
	} 
	
	void approveLoanRequest(vector<Loan> &loans, vector<Customer> &customers, string choice)
	{
		string id;
		int j;
		bool found = false;
		bool isAlreadApproved = true;
		double balance;
		cout << "Enter Loan Id to approve : ";
		getline(cin, id);
		
		for(int i = 0; i < loans.size(); i++)
		{
			if(id == loans[i].id && !loans[i].isApproved)
			{
				id = loans[i].idofUser;
				found = true;
				isAlreadApproved = false;
				j= i;
			}
		}
		
		if(isAlreadApproved){
			cout << "Loan Is Already Approved with this Id or Not found!" << endl;
		}
		else{
			if(found)
				{
					while (true)
					{
						cout << "Do you want to Approve this Loan[yes/no]? ";
						cin >> choice;
						convertToLower(choice);
						if(choice == "yes")
						{
							cin.ignore();
							loans[j].isApproved = true;
							cout << "Loan is Approved!." << endl;
							balance = loans[j].amount;
							for(int i = 0; i < customers.size(); i++)
							{
								if(id == customers[i].customerId)
								{
									customers[i].account.balance += balance;
								}
							}
							break;
						}
						else if (choice == "no")
						{
							break;
						}
						else
						{
							cout << "Invalid choice . try again" << endl;
						}
					}
		      	}
		      	else
		      	{
		      		cout << "There is no request for loan with this Id." << endl;
				 }
		}
}

	void viewTransactionsHistoryofCustoomer(string customerId)
	{
		string line;
		bool found = false;
		ifstream Ifile("transactions.txt");
		while(getline(Ifile,line))
		{
			if(line == customerId)
			{
				found = true;
				while(getline(Ifile,line))
				{
					if(line == customerId)
					{
						break;
					}
					cout << line << endl;
					
				}
				cout << endl;
			}
		}
		if(!found)
		{
			cout << "There is no Transaction History with this Id." << endl;
		}
		Ifile.close();
	}
	//getter for password.
	string getPassword()
	{
		return password;
	}
	
	//setter for password.
	void setPassword(string newpass)
	{
		password = newpass;
	}
	
private:
	string password;
};

// function for showing banner.
void showBanner()
{
cout << " ______________________________________________________________________________________________________________________ " << endl
	 << "|                                           Welcome to Bank!!                                                          |" << endl
	 << "|______________________________________________________________________________________________________________________|" << endl << endl;
}

// Function for Validating Password.
bool passwordIsValid(string password)
{
bool isSpecialsymbol = false;
bool isUpperletter = false;
bool isDigit = false;

//checking password length.
if(password.length() > 16 || password.length() < 8)
{
	cout <<"Invalid, Length of password must from 8 to 16" << endl;
	return false;
}
//checking if password starts with special symbol then it is invalid.
if (password[0] == '@' || password[0] == '$' || password[0] == '%' ||
    password[0] == '&' || password[0] == '*')
{
    cout << "Invalid, Password cannot start with special symbol." << endl;
    return false;
}
//using loop to get each character of password.
for (int i = 0 ; i < password.length(); i++)
{
	//checking if our charachter contains upper letter
	for (char j = 65 ; j <= 90; j++)
	{
		if(password[i] == j)
		{
			isUpperletter = true;
			break;
		}
	
	}
	//checking if our charachter contains digit.	
	for (char k = 48 ; k <= 57; k++)
	{
		if(password[i] == k)
		{
			isDigit = true;
			break;
		}
    }
    //checking if our charachter contains special symbols.
  	if( password[i] == '@' 
    ||  password[i] == '$' 
	||  password[i] == '%'
    ||  password[i] == '&' 
	||  password[i] == '*'
	||  password[i] == '_')
  	{
      isSpecialsymbol = true;  		
	}
}
//checking if our password contains upper letter,digit and special symbol then prints valid.
if (isSpecialsymbol && isUpperletter && isDigit )
{
	cout << "Valid Password.";
	return true;
}
else
{
   cout << "Not Valid Password," ;
   	//if not contains upper letter then display this message.
	if(!isUpperletter)
	{
		cout << "Must have one upper case.";
	}
	//if not contains special symbol then display this message.
	if(!isSpecialsymbol)
	{
		cout << "Must contain a special symbol.";
	}
	//if not contains digit then display this message.
	if(!isDigit)
	{
		cout << "Must conatains one digit.";
	}
	return false;
}
}

// function that check customers in array for authentication that if the customer is already a customer.
bool customerFound(vector<Customer> customers, string id, string userPassword, Customer &currentMember)
{
bool isFound = false;
for(int i = 0 ; i < customers.size(); i++)
{
	if(customers[i].getPassword() == userPassword && (customers[i].customerId == id || customers[i].name == id ) )
	{
		isFound = true;
		currentMember = customers[i];
		break;
	}
}

if(isFound)
{
	return true;
}
else
{
	return false; 
}

}

// function for displaying customer menu.
void showCustomerMenu()
{
cout << " ______________________________________________________________________________________________________________________ " << endl
	 << "|                                           Welcome to Bank as a Customer                                              |" << endl
	 << "|______________________________________________________________________________________________________________________|" << endl << endl
	 
	 << "                                            1.  Deposite Money.                                                          " << endl
	 << "                                            2.  Withdraw Money.                                                          " << endl
	 << "                                            3.  Transfer Funds.                                                          " << endl
	 << "                                            4.  View Transaction History.                                                " << endl
	 << "                                            5.  View Your Details.                                                       " << endl
	 << "                                            6.  Apply for Loan.                                                          " << endl
	 << "                                            7.  Check Loan Approval.                                                     " << endl
	 << "                                            8.  Change Password.                                                         " << endl
   	 << "                                            9.  LogOut.                                                                  " << endl
	 << "                                            10. Exit Program.                                                           " << endl;
}


// funtion for checking user choice to  continue to program.
bool Continue(string choice)
{
while(true)
{
	cout << "Press M or m to continue to the program : ";
	getline(cin, choice);
	if (choice == "m" || choice == "M")
	{
		return true;
	}
	else
	{
		cout << "Invalid choice . try again" << endl;
	}
}
}

// function for displaying Manger menu.
void showManagerMenu()
{
cout << " ______________________________________________________________________________________________________________________ " << endl
	 << "|                                           Welcome to Bank as a Manager                                               |" << endl
	 << "|______________________________________________________________________________________________________________________|" << endl << endl
	 
	 << "                                            1. View All customers.                                                     " << endl
	 << "                                            2. view User Transactions History.                                         " << endl
	 << "                                            3. delete User.                                                            " << endl
	 << "                                            4. Approve Loan.                                                           " << endl
	 << "                                            5. View Your Details.                                                      " << endl
	 << "                                            6. View All loan requests.                                                 " << endl
   	 << "                                            7. LogOut.                                                                 " << endl
	 << "                                            8. Exit Program.                                                           " << endl;	
}

// Function for saving customers in file.
void saveCustomersToFile(vector<Customer> customers)
{
ofstream file("customers.txt");

if(file.is_open()){
	for(int i = 0; i < customers.size(); i++)
	{
		file << customers[i].customerId << endl
			 << customers[i].age << endl
			 << customers[i].name << endl
			 << customers[i].phoneNumber << endl
			 << customers[i].address << endl
			 << customers[i].getPassword() << endl
			 << customers[i].account.balance << endl
			 << customers[i].account.id << endl;
		
	}
}else{
	cout <<"Error: file is not opened" << endl;
}
file.close();
}

// function that loads customers from file to program.
void LoadCustomersFromFile(vector<Customer> &customers)
{
    Customer customer;
    string pass;
    ifstream file("customers.txt");

   
	if(file.is_open()){
		 while (getline(file, customer.customerId))
	    {
	        file >> customer.age;
	        file.ignore();
	        getline(file, customer.name);
	        getline(file, customer.phoneNumber);
	        getline(file, customer.address);
	        getline(file, pass);
	        file >> customer.account.balance;
	        file.ignore();
	        getline(file, customer.account.id);
	        customer.setPassword(pass);
	        customers.push_back(customer);
	    }	
	}else{
		cout <<"Error: file is not opened" << endl;
	}
    file.close();
}

// Main function(driver program)
int main()
{
	
vector<Customer> customers;
vector<Loan> loans;
LoadLoansFromFile(loans);
LoadCustomersFromFile(customers);

Manager manager("Sajjad", 19, "0334-9873212", "Angoori Scheme", "0110" ,"OKOK4" );


Customer currentCustomer;
Person *personptr;
string choice, customerPassword, nameOrId, managerPassword;

showBanner();
while(true)
{
	start:
	cout << "Are you a Customer or Manager? ";
	getline(cin, choice);
	convertToLower(choice);
	if(choice == "customer")
	{
		system("cls");
		showBanner();
		while(true)
		{
			cout << "Are you already a customer?[yes/no]";
			getline(cin, choice);
			convertToLower(choice);
			if(choice == "yes")
			{
				CustomerCredentials:
				cout << "Enter Your Name or Id :";
				getline(cin, nameOrId);
				cout << "Enter your Password: ";
				getline(cin, customerPassword);
				if(customerFound(customers,nameOrId,customerPassword,currentCustomer))
				{
					customerPannel:
						system("cls");
						showBanner();
						showCustomerMenu();
						while(true)
						{
							cout << "Enter Your choice: ";
						    getline(cin, choice);
						    if(choice == "1")
						    {
						    	system("cls");
							    showBanner();
							    currentCustomer.depositeMoney();
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if (choice == "2")
							{
								system("cls");
							    showBanner();
							    currentCustomer.withdrawMoney();
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if (choice == "3")
							{
								system("cls");
							    showBanner();
							   	bool found = false;
							   	cout << "Enter Id of user to transfer funds:";
								getline(cin, nameOrId);
								for(int i = 0; i < customers.size(); i++)
								{
									if(nameOrId == customers[i].customerId)
									{
										found = true;
										currentCustomer.transferFunds(customers[i]);
									}
								}										
								if(!found)
								{
									cout << "Customer not exists with this ID." << endl;
						     	}
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if (choice == "4")
							{
								system("cls");
							    showBanner();
							    currentCustomer.viewTransactionsHistory();
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if (choice == "5")
							{
								system("cls");
							    showBanner();
							    personptr = &currentCustomer;
							    personptr->displayInfo();
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if (choice == "6")
							{
								system("cls");
							    showBanner();
							    currentCustomer.requestForLoan(loans);
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if (choice == "7")
							{
								system("cls");
							    showBanner();
							    currentCustomer.checkLoanApproval(loans);
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if (choice == "8")
							{
								system("cls");
							    showBanner();
							    while(true)
							    {
							    	cout << "Enter New Password: ";
								    getline(cin,customerPassword);
								    if(passwordIsValid(customerPassword))
								    {
								    	for(int i = 0; i < customers.size(); i++)
										{
											if(customers[i].customerId == currentCustomer.customerId)
											{
												customers[i].setPassword(customerPassword);
											}
										}
								    	cout << "Password Updated Succuessfully!" << endl;
								    	break;
									}
									else
									{
										cout << ".. ReEnter your Password" << endl;
									}
								}
							    if(Continue(choice))
								{
									goto customerPannel;
								}
							}
							else if(choice == "9")
							{
								system("cls");
								showBanner();
								goto start;
							}
							else if(choice == "10")
							{
								break;
							}
							else
							{
								cout << "Invalid Choice .. Try again" << endl;
							}
						}
					break;
					
				}
				else
				{
					cout << "Credentials of Customer are inncorrect or Not found. " << endl;
					while(true)
					{
						cout << "Press 1 to ReEnter credentials and 0 to close the program : ";
						getline(cin, choice);
						if(choice == "1")
						{
							goto CustomerCredentials;
						}
						else if (choice == "0")
						{
							return 0;
						}
						else
						{
							cout << "Invalid Choice .. Try again" << endl;
						}
					}
				}
				break;
			}
			else if( choice == "no" )
			{
				cout << "Ok no prob.. let's create your account" << endl;
				UserData user;
				user = inputInfo();
				while(true)
				{
					cout << "Enter Your Password (must contain 1 speacial symbol, 1 Digit, UpperCase letter, lowerCase letter and length is must of 8-16 Characters long): ";
					getline(cin, customerPassword);
					if(passwordIsValid(customerPassword))
					{
						customers.push_back(Customer(user.age, user.name, user.phoneNumber, user.address, user.id, customerPassword));
						cout << "Your Account Created successfully!!" << endl
							 << "Now Go to login Page and SignUp with your credentials" << endl;
					    while(true)
						{
						   	 cout << "Press R or r to go to Login page : ";
							 getline(cin, choice);
							 if (choice == "r" || choice == "R")
							 {
							 	system("cls");
							 	showBanner();
						 		cout << "************************************************************************************************************************" << endl
									 << "*                                                      LOGIN PAGE                                                      *" << endl
     								 << "************************************************************************************************************************" << endl;
							 	goto start;
							 }
							 else
							 {
							 	cout << "Invalid choice . try again" << endl;	
							 }
						}
					}
					else
					{
						cout << ".. ReEnter your Password" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "Invalid choice, Try Again!!" << endl;
			}
		}
		break;
	}
	else if(choice == "manager")
	{
		managerCredentials:
		cout << "Enter Manager name or Id: ";
		getline(cin, nameOrId);
		cout << "Enter Manager Password: ";
		getline(cin, managerPassword);
		if((manager.name == nameOrId || manager.id == nameOrId) && manager.getPassword() == managerPassword)
		{
			managerPannel:
			system("cls");
			showBanner();
			showManagerMenu();
			while(true)
			{
				cout << "Enter Your choice: ";
				getline(cin, choice);
				if(choice == "1")
				{
					system("cls");
					showBanner();
					manager.viewAllCustomers(customers);
					if(Continue(choice))
					{
						goto managerPannel;
					}
					
				}
				else if(choice == "2")
				{
					system("cls");
					showBanner();
					cout << "Enter Id: ";
					getline(cin, nameOrId);
					manager.viewTransactionsHistoryofCustoomer(nameOrId);
					if(Continue(choice))
					{
						goto managerPannel;
					}
					
				}
				else if(choice == "3")
				{
					system("cls");
					showBanner();
					manager.deleteCustomer(customers, choice);
					if(Continue(choice))
					{
						goto managerPannel;
					}
					
				}
				else if(choice == "4")
				{
					system("cls");
					showBanner();
					manager.approveLoanRequest(loans,customers, choice);
					if(Continue(choice))
					{
						goto managerPannel;
					}
					
				}
				else if (choice == "5")
				{
					system("cls");
				    showBanner();
				    personptr = &manager;
				    personptr->displayInfo();
				    if(Continue(choice))
					{
						goto managerPannel;
					}
				}
				else if (choice == "6")
				{
					system("cls");
				    showBanner();
				    manager.viewAllLoanRequests(loans);
				    if(Continue(choice))
					{
						goto managerPannel;
					}
				}
				else if(choice == "7")
				{
					system("cls");
					showBanner();
					goto start;
				}
				else if(choice == "8")
				{
					break;
				}
				else
				{
					cout << "Invalid Choice!! .. Please try again" << endl;
				}
			}
		}
		else
		{
			cout << "Credentials of Manager are inncorrect. " << endl;
			while(true)
			{
				cout << "Press 1 to ReEnter credentials and 0 to close the program : ";
				getline(cin, choice);
				if(choice == "1")
				{
					goto managerCredentials;
				}
				else if (choice == "0")
				{
					return 0;
				}
				else
				{
					cout << "Invalid Choice .. Try again" << endl;
				}
			}
		}
		break;
	}
	else
	{
		cout << "Invalid choice, Try Again!!" << endl;
	}
}

saveCustomersToFile(customers);
saveLoanHistoryToFile(loans);
cout << "END" << endl;

return 0;
}
