#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std; 

class clsTotalBalancesScreen : protected clsScreen
{

private:

	static void _PrintClientBalanceRecordLine(clsBankClient Client)
	{
		cout << setw(20) << left << "" << "| " << left << setw(15) << Client.GetAccountNumber();
		cout << "| " << left << setw(40) << Client.FullName();
		cout << "| " << left << setw(12) << Client.AccountBalance;

	}


public:

	static void ShowTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();


		string Title = "\t  Balance List Screen";
		string Subtitle = "\t   (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, Subtitle); 

		//cout << "\n\n\t\t\t\t\tBalance List (" << vClients.size() << ") Client(s).\n";

		cout << "\n" << setw(20) << left << "" << "___________________________________________________";
		cout << "_____________________________\n\n";

		cout << setw(20) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";

		cout << "\n" << setw(20) << left << "" << "___________________________________________________";
		cout << "_____________________________\n\n";

		if (vClients.size() == 0)
		{
			cout << setw(20) << left << "" << "No Clients Available In The System !!!";

		}
		else

			for (clsBankClient& C : vClients)
			{
				_PrintClientBalanceRecordLine(C);
				cout << endl;
			}
		cout << "\n" << setw(20) << left << "" << "___________________________________________________";
		cout << "_____________________________\n\n";

		double TotalBalances = clsBankClient::GetTotalBalances();

		cout << setw(20) << left << "" << "\t\t\tTotal Balances = " << TotalBalances;
		cout << setw(20) << left << "" << "\n\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ").\n\n";



	}



};

