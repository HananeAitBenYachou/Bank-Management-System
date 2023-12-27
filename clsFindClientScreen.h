#pragma once
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
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

public :

	static void ShowFindClientScreen()
	{   
		if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}
		_DrawScreenHeader("\t Find Client Screen"); 

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber); 

		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :-) \n";
		}
		else
		{
			cout << "\nClient Was not Found :-( \n";
		}

		_PrintClient(Client); 
	}

};

