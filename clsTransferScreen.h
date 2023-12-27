#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std; 

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\n\t~~~ Client Card ~~~ ";
		cout << "\n======================================\n";
		cout << "\nFull Name      : " << Client.FullName();
		cout << "\nAccount Number : " << Client.GetAccountNumber();
		cout << "\nAccount Balance: " << Client.AccountBalance;
		cout << "\n\n======================================\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber;

		cout << "\nPlease Enter Account Number to Transfer From : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();

		}

		return AccountNumber; 
	}

	static double _ReadTransferAmount(clsBankClient ClientSender)
	{
		double TransferAmount = 0;
		cout << "\n\nEnter Transfer Amount : ";
		TransferAmount = clsInputValidate::ReadDblNumber();

		while (TransferAmount > ClientSender.AccountBalance)
		{
			cout << "\n\nAmount Exceeds the available Balance , Enter another Amount ? ";
			TransferAmount = clsInputValidate::ReadDblNumber();
		}

		return TransferAmount;
	}

public : 

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t Transfer Screen");

		clsBankClient ClientSender = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientCard(ClientSender);

		clsBankClient ClientReceiver = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientCard(ClientReceiver);

		double TransferAmount = _ReadTransferAmount(ClientSender); 

		char Answer = 'Y'; 
		cout << "\n\nAre you sure you want to perform this operation ? Y/N ? ";
		cin >> Answer; 

		if (toupper(Answer) == 'Y')
		{
			if (ClientSender.Transfer(ClientReceiver, TransferAmount,CurrentUser.UserName))
			{
				cout << "\n\nTransfer done successfully. :-)\n"; 
				_PrintClientCard(ClientSender);
				_PrintClientCard(ClientReceiver);
			}

			else
			{
				cout << "\nCannot Transfer , Insufficient Balance !\n";
				cout << "\nAmount To Transfer is " << TransferAmount;
				cout << "\nClient [" << ClientSender.GetAccountNumber() << "] Balance is " << ClientSender.AccountBalance;
			}

		}

		else
		{
			cout << "\n\nThis Operation was cancelled ! "; 
		}

	}
};

