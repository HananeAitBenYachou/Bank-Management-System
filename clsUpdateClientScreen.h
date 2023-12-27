#pragma once
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;


class clsUpdateClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "Enter Email : ";
		Client.Email = clsInputValidate::ReadString();

		cout << "Enter Phone : ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "Enter PinCode : ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "Enter Account Balance : ";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();

	}

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

public:

	static void ShowUpdateClientScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClient))
		{
			return;
		}

		_DrawScreenHeader("\t Update Client Screen");

		string AccountNumber = "";
		cout << "Please Enter Client Account Number ? ";

		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "This Account Number is not found , please try a valid one ? ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		char Answer = 'N'; 

		cout << "\n\nAre you sure you want to update this client ? Y/N ? ";
		cin >> Answer; 

		if (toupper(Answer) == 'Y')
		{
			cout << "\n\t~~~ Update Client Info ~~~\n";
			cout << "\n======================================\n";

			_ReadClientInfo(Client);

			clsBankClient::enSaveResults SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResults::svSucceeded:

				cout << "\nClient Updated Successfully :-)\n";
				_PrintClient(Client);
				break;

			case clsBankClient::enSaveResults::svFailedEmptyObject:
				cout << "\nError account was not saved because it's Empty\n";
				break;
			}
		}


	}

};

