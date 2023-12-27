#pragma once
#include "clsScreen.h"
#include "Global.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsAtmMainScreen.h"
#include <conio.h>
using namespace std;

class clsATMLoginScreen : protected clsScreen
{

private:


	static bool _Login()
	{
		string AccountNumber = "";
		string PinCode = "";
		bool LoginFailed = false;
		bool AccountLocked = false; 

		short FailedLoginCount = 0;

		do
		{
			system("cls");
			_DrawScreenHeader("\t    ATM Login Screen", "", enSystemChoice::eAtmSystem);

			if (LoginFailed)
			{
				FailedLoginCount++;
				cout << "\n" << "\033[1;31mInvalid AccountNumber/PinCode ! \033[0m" << endl;
				cout << "You have " << (3 - FailedLoginCount) << " Trails to login.\n";

			}

			if (AccountLocked)
			{
				cout << "\n" << "\033[1;31mThis Account Is Locked ! \033[0m" << endl;
			}

			if (FailedLoginCount == 3)
			{
				cout << "\n\n" << "\033[1;32mYour are locked after 3 failed trails :-(\033[0m" << endl;
				return false;
			}

			cout << "\nEnter Account Number : ";
			AccountNumber = clsInputValidate::ReadString();
			cout << "\nEnter Pin Code : ";
			PinCode = clsInputValidate::ReadString();
			
			CurrentClient = clsBankClient::Find(AccountNumber, PinCode);

			LoginFailed = CurrentClient.IsEmpty();
			AccountLocked = CurrentClient.GetMarkedForLocked(); 

		} while (LoginFailed || AccountLocked);

		clsAtmMainScreen::ShowAtmMainScreen();
	}

public:

	static bool ShowATMLoginScreen()
	{
		system("cls");
		return _Login();
	}


};

