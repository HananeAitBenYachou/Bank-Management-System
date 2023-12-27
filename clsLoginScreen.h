#pragma once
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"
#include <iostream>
using namespace std;

class clsLoginScreen : protected clsScreen
{
private :

	static bool _Login()
	{
		string UserName, Password; 
		bool LoginFailed = false; 
		short FailedLoginCount = 0; 

		do
		{
			system("cls"); 
			_DrawScreenHeader("\t Bank Login Screen");

			if (LoginFailed)
			{
				FailedLoginCount++; 

				cout << "\n" << "\033[1;31mInvalid Username/Password ! \033[0m" << endl;
				cout << "You have " << (3-FailedLoginCount) << " Trails to login.\n";
			}

			if (FailedLoginCount == 3)
			{
				cout << "\n\n" << "\033[1;32mYour are locked after 3 failed trails\033[0m" << endl;
				return false;	
			}


			cout << "\nEnter Username : ";
			UserName = clsInputValidate::ReadString(); 

			cout << "\nEnter Password : ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty() ; 

			system("cls");

		} while (LoginFailed);
	
		CurrentUser.RegisterLogIn();

		clsMainScreen::ShowMainMenue();
	}

public: 

	static bool ShowLoginScreen()
	{
		system("cls"); 
		return _Login(); 
		
	}

};
