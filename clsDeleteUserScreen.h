#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include <iostream>
using namespace std; 

class clsDeleteUserScreen : protected clsScreen
{
private : 

	static void _PrintUserCard(clsUser User)
	{
		cout << "\n\t~~~ User Card ~~~ ";
		cout << "\n======================================\n";
		cout << "\nFirst Name     : " << User.FirstName;
		cout << "\nLast Name      : " << User.LastName;
		cout << "\nFull Name      : " << User.FullName();
		cout << "\nUser Name      : " << User.UserName;
		cout << "\nEmail          : " << User.Email;
		cout << "\nPhone          : " << User.Phone;
		cout << "\nPassword       : " << User.Password;
		cout << "\nPermissions    : " << User.Permissions;
		cout << "\n\n======================================\n\n";
	}

public : 

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t  Delete User Screen");

		string UserName = ""; 
		cout << "\nPlease Enter Username : ";
		UserName = clsInputValidate::ReadString(); 

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser does not exist in the system , Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUserCard(User); 

		char Answer = 'N'; 
		cout << "\nAre you sure you want to delete this user ? Y/N ? ";
		cin >> Answer; 

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\n\nUser Has Been Deleted Successfully :-)\n";
				_PrintUserCard(User); 
			}

			else
			{
				cout << "\n\nError Client Was Not Deleted :-( \n";
			}
			
		}
		
	}

};
