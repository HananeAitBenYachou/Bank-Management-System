#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

using namespace std;

class clsDepositScreen : protected clsScreen
{
private : 

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\n\t~~~ Client Card ~~~ ";
        cout << "\n======================================\n";
        cout << "\nFirst Name     : " << Client.FirstName;
        cout << "\nLast Name      : " << Client.LastName;
        cout << "\nFull Name      : " << Client.FullName();
        cout << "\nEmail          : " << Client.Email;
        cout << "\nPhone          : " << Client.Phone;
        cout << "\nAccount Number : " << Client.GetAccountNumber();
        cout << "\nPinCode        : " << Client.PinCode;
        cout << "\nAccount Balance: " << Client.AccountBalance;
        cout << "\n\n======================================\n";
    }

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

public: 

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t    Deposit Screen ");

		string AccountNumber = _ReadAccountNumber(); 

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with ["<< AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber(); 

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client); 

		double DepositAmount = 0;
		cout << "\nPlease enter deposit amount ? ";
	    DepositAmount = clsInputValidate::ReadDblNumber();

		char Answer = 'N';
		cout << "\nAre you sure you want to preform this transaction ? Y/N ?  ";
		cin >> Answer; 


		if (toupper(Answer) == 'Y')
		{
			Client.Deposit(DepositAmount);
			cout << "\nAmount Deposited Successfully.\n"; 
			cout << "\nNew Balance Is : " << Client.AccountBalance; 

		}

		else
		{
			cout << "\nOperation was cancelled.\n";

		}
	}

};

