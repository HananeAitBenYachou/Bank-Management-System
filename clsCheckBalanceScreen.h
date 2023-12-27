#pragma once
#include "clsScreen.h"
#include "Global.h"

class clsCheckBalanceScreen : protected clsScreen
{

private : 

	static void _PrintClientBalanceInfo(clsBankClient Client)
	{
		cout << "\n\n"; 
		cout << setw(37) << left << "" << "    Your Balance Is : \n";
		cout << setw(37) << left << "" << "+--------------------+\n";
		cout << setw(37) << left << "" << "|\t     " << Client.AccountBalance << " ($)     |\n";
		cout << setw(37) << left << "" << "+--------------------+\n\n\n";

	}

public :

	static void ShowCheckBalanceScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Check Balance Screen", "", enSystemChoice::eAtmSystem);
		
		_PrintClientBalanceInfo(CurrentClient);

	}

};

