#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsQuickWithDrawScreen : protected clsScreen
{

public : 

	static void ShowQuickWithDrawScreen(short QuickWithdrawAmount)
	{

		char Answer = 'Y';
		cout << "\n\nAre you sure you want to perform this transaction ? Y/N ? ";
		cin >> Answer; 

        if (toupper(Answer) == 'Y')
        {
            if (CurrentClient.WithDraw(QuickWithdrawAmount))
            {
                cout << "\nAmount Withdrawd Successfully.\n";
                cout << "\nNew Balance Is : " << CurrentClient.AccountBalance;

            }

            else
            {
                cout << "\nCannot Withdeaw , Insufficient Balance !\n";
                cout << "\nAmount To Withdraw is " << QuickWithdrawAmount;
                cout << "\nYour Balance is " << CurrentClient.AccountBalance;
            }

        }

        else
        {
            cout << "\nOperation was cancelled.\n";

        }
	}


};

