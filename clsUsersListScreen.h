#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std; 

class clsUsersListScreen : protected clsScreen
{
private : 

	static void _PrintUserRecord(clsUser User)
	{

		cout << setw(8) << left << "" << "| " << left << setw(15) << User.UserName;
		cout << "| " << left << setw(25) << User.FullName();
		cout << "| " << left << setw(20) << User.Email;
		cout << "| " << left << setw(12) << User.Phone;
		cout << "| " << left << setw(10) << User.Password;
		cout << "| " << left << setw(12) << User.Permissions;
	}

public : 

	static void ShowUsersList()
	{
		vector <clsUser> vUsers = clsUser::GetUsersList(); 

		string Title = "\t   Users List Screen";
		string Substitle = "\t     (" + to_string(vUsers.size()) + ") User(s).";

		_DrawScreenHeader(Title, Substitle); 

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "___________________________________________________\n\n";

		cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "___________________________________________________\n\n";

		if (vUsers.size() == 0)
		{
			cout << setw(8) << left << "" << "No Users Available In The System !";
		}


		else
		    
			for (clsUser& User : vUsers)
			{
				_PrintUserRecord(User);
				cout << endl; 
			}


		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "___________________________________________________\n\n";

	}

};

