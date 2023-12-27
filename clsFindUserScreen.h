#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iostream>
using namespace std; 

class clsFindUserScreen : protected clsScreen
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

	static string _ReadUserName()
	{
		cout << "\nPlease Enter UserName : ";
		string UserName = clsInputValidate::ReadString();
		return UserName;
	}

public : 

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t   Find User Screen");
	
		string UserName = _ReadUserName(); 

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser with Username : [" << UserName << "]  does not exist.\n";
			UserName = _ReadUserName();
		}

		clsUser User = clsUser::Find(UserName); 

		if (!User.IsEmpty())
		{
			cout << "\n\nUser Found :-) \n";
			_PrintUserCard(User);

		}
		
		else
		{
			cout << "\n\nUser Was Not Found :-( \n";
		}
		
	}
};

