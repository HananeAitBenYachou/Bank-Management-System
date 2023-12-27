#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsLoginRegisterListScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterRecord(clsUser::stLoginRegisterRecord LoginRegisterRecord)
	{

		cout << setw(8) << left << "" << "| " << left << setw(30) << LoginRegisterRecord.DateTime;
		cout << "| " << left << setw(20) << LoginRegisterRecord.UserName;
		cout << "| " << left << setw(20) << LoginRegisterRecord.Password;
		cout << "| " << left << setw(10) << LoginRegisterRecord.Permissions;
		
	}

public:

	static void ShowLoginRegisterListScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pShowLogInRegister))
		{
			return; 
		}

		vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecords = clsUser::GetLoginRegisterList();

		string Title = "\tLogin Register List Screen";
		string Substitle = "\t     (" + to_string(vLoginRegisterRecords.size()) + ") Record(s).";

		_DrawScreenHeader(Title, Substitle);

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "__________________________________________\n\n";

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "__________________________________________\n\n";

		if (vLoginRegisterRecords.size() == 0)
		{
			cout << setw(8) << left << "" << "NO LOGIN REGISTER RECORD AVAILBALE IN THE SYSTEM!";
		}


		else

			for (clsUser::stLoginRegisterRecord & Record : vLoginRegisterRecords)
			{
				_PrintLoginRegisterRecord(Record);
				cout << endl;
			}


		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "__________________________________________\n\n";

	}

};

