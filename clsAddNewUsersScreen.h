#pragma once
#include <iostream>
#include "iomanip"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std; 

class clsAddNewUsersScreen : protected clsScreen
{
private:

	static int _ReadPermissionsToSet()
	{
		int UserPermissions = 0;
		char Answer = 'n';
		
		cout << "\nDo you want to give Full Access ? Y/N ? ";
		cin >> Answer; 

		if (toupper(Answer) == 'Y')
		{
			UserPermissions = -1;
			return UserPermissions; 
		}

		else
		{
			cout << "\nDo you wan give access to : \n";

			cout << "\nShow Clients List ? Y/N ? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pListClients;

			cout << "\nAdd New Client ? Y/N ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pAddNewClient;


			cout << "\nDelete Client ? Y/N ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pDeleteClient;

			cout << "\nUpdate Client ? Y/N ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pUpdateClient;

			cout << "\nFind Client ? Y/N ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pFindClient;

			cout << "\nTransactions ? Y/N ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pTransactions;

			cout << "\nManage Users ? Y/N ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pManageUsers;

			cout << "\nShow Login Register List ? Y/N ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
				UserPermissions += clsUser::enPermissions::pShowLogInRegister;

		}

		return UserPermissions;
	}

	static void _ReadUserInfo(clsUser &User)
	{
		cout << "\nEnter FirstName : " << User.FirstName ;
		User.FirstName = clsInputValidate::ReadString(); 

		cout << "\nEnter LastName : " << User.LastName ;
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : " << User.Email ;
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : " << User.Phone ;
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password : " << User.Password ;
		User.Password = clsInputValidate::ReadString();

		cout << "\n~~~ Enter User Permissions ~~~\n";
		User.Permissions = _ReadPermissionsToSet(); 
		
	}

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

	static void ShowAddNewUsersScreen()
	{
		_DrawScreenHeader("\t Add New Users Screen");

		string Username; 
		cout << "\nPlease Enter Username : ";
		Username = clsInputValidate::ReadString(); 

		while (clsUser::IsUserExist(Username))
		{
			cout << "\nUsername Is Already Used , Choose another one : ";
			Username = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(Username); 

		_ReadUserInfo(NewUser); 

		clsUser::enSaveResults SaveResult; 
		SaveResult = NewUser.Save(); 

		switch (SaveResult)
		{
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nUser Added Successfully :-)\n";
			_PrintUserCard(NewUser);
			break;
			
		case clsUser::enSaveResults::svFailedEmptyObject: 
			cout << "\nError User was not saved , because it is Empty :-( \n";
			break; 

		case clsUser::enSaveResults::svFailedUserExists:
			cout << "\nError User was not saved , because it is already in the system :-(\n";
			break;
		}

	}

};


