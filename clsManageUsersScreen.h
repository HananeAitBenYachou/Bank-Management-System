#pragma once
#include <iostream>
#include "iomanip"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUsersScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private : 

	enum enManageUsersMenueOptions
	{
		eListUsers = 1,
		eAddNewUser = 2,
		eDeleteUser = 3,
		eUpdateUser = 4,
		eFindUser = 5,
		eShowMainMenue = 6
	};

	static void _ShowAllUsersScreen()
	{
		clsUsersListScreen::ShowUsersList(); 
	}

	static void _ShowAddNewUsersScreen()
	{
		clsAddNewUsersScreen::ShowAddNewUsersScreen(); 
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen(); 
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen(); 
	}

	static short _ReadManageUsersMenueOption()
	{
		short Choice = 0; 
		cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 6] ? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6 ? ");
 		
		return Choice; 
	}

	static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
	{
		switch (ManageUsersMenueOption)
		{
		case enManageUsersMenueOptions::eListUsers:
			system("cls");
			_ShowAllUsersScreen();
			_GoBackToManageUsersMenue(); 
			break;

		case enManageUsersMenueOptions::eAddNewUser:
			system("cls");
			_ShowAddNewUsersScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break; 

		case enManageUsersMenueOptions::eShowMainMenue:
		{

		}
						
		}
	}

	static void _GoBackToManageUsersMenue()
	{
		cout << setw(37) << left << "" << "Press Any Key To Go Back To Manage Users Menue ...";
		system("pause>0");

		ShowManageUsersMenue(); 
	}

public : 

	static void ShowManageUsersMenue()
	{
		system("cls"); 

		if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}

		_DrawScreenHeader("\t Manage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tManage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Users List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
        
		_PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
	}


};

