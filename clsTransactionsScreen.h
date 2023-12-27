#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogListScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{

private:

	enum enTransactionsMenueOptions
	{
		eDeposit = 1,
		eWithDraw = 2,
		eShowTotalBalances = 3,
		eTransfer = 4,
		eShowTransferLogList = 5,
		eShowMainMenue = 6,
	};

	static short _ReadTransactionsMenueOption()
	{
		short Choice;
		cout << left << setw(37) << "" << "Choose what do you want to do ? [1 to 6] ? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6 ? ");

		return Choice;
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
	{
		switch (TransactionsMenueOption)
		{
		case enTransactionsMenueOptions::eShowTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionsMenueOptions::eWithDraw:
			system("cls");
			_ShowWithDrawScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionsMenueOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
        
		case enTransactionsMenueOptions::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionsMenueOptions::eShowTransferLogList:
			system("cls");
			_ShowTransferLogListScreen(); 
			_GoBackToTransactionsMenue();
			break;

		case enTransactionsMenueOptions::eShowMainMenue:
			break;
			// do nothing here the main screen will handle it : -);
		}

	}
	
	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen(); 
	}

	static void _ShowWithDrawScreen()
	{
		clsWithDrawScreen::ShowWithDrawScreen(); 
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances(); 
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen(); 
	}

	static void _ShowTransferLogListScreen()
	{
		clsTransferLogListScreen::ShowTransferLogListScreen(); 
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n";
		cout << left << setw(37) << "" << "Press Any Key To Go Back To Transactions Menue ...";
		system("pause>0");
		ShowTransactionsMenue();

	}

public:

	static void ShowTransactionsMenue()
	{
		system("cls");

		if (!_CheckAccessRights(clsUser::enPermissions::pTransactions))
		{
			return; 
		}

		_DrawScreenHeader("\t    Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Show Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}

};

