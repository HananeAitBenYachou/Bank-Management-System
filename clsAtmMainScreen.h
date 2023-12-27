#pragma once
#include "clsScreen.h"
#include "Global.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsQuickWithDrawMenueScreen.h"
#include "clsNormalWithDrawScreen.h"
#include "clsNormalDepositScreen.h"
#include "clsCheckBalanceScreen.h"
#include "clsAtmTransferScreen.h"
#include "clsAtmTransferLogListScreen.h"
#include "clsEmailsListScreen.h"

class clsAtmMainScreen : protected clsScreen
{
private:

    enum enAtmMenueOptions
    {
        eQuickWithDraw = 1,
        eNormalWithDraw = 2,
        eDeposit = 3,
        eTransfer = 4,
        eCheckBalance = 5,
        eTransferLogsList = 6,
        eShowEmails = 7,
        eLogout = 8,
    };

    static short _ReadAtmMenueOption()
    {
        short Choice;
        cout << left << setw(37) << "" << "Choose what do you want to do ? [1 to 8] ? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 8);
        return Choice;
    }

    static void _ShowQuickWithDrawScreen()
    {
        clsQuickWithDrawMenueScreen::ShowQuickWithDrawMenueScreen(); 
    }

    static void _ShowNormalWithDrawScreen()
    {
        clsNormalWithDrawScreen::ShowNormalWithDrawScreen(); 
    }

    static void _ShowDepositScreen()
    {
        clsNormalDepositScreen::ShowNormalDepositScreen();
    }

    static void _ShowCheckBalanceScreen()
    {
        clsCheckBalanceScreen::ShowCheckBalanceScreen(); 
    }

    static void _ShowTransferScreen()
    {
        clsAtmTransferScreen::ShowAtmTransferScreen();
    }

    static void _ShowTransferLogsListScreen()
    {
        clsAtmTransferLogListScreen::ShowAtmTransferLogListScreen();
    }

    static void _ShowEmailsListScreen()
    {
        clsEmailsListScreen::ShowClientEmailsMenue(); 
    }

    static void _Logout()
    {
        CurrentClient = clsBankClient::Find("", ""); 

    }

    static void _PerformAtmMenuOptions(enAtmMenueOptions AtmMenueOption)
    {
        switch (AtmMenueOption)
        {
        case enAtmMenueOptions::eQuickWithDraw:
            system("cls");
            _ShowQuickWithDrawScreen();
            _GoBackToAtmMenue(); 
            break;

        case enAtmMenueOptions::eNormalWithDraw:
            system("cls");
            _ShowNormalWithDrawScreen(); 
            _GoBackToAtmMenue();
            break;

        case enAtmMenueOptions::eDeposit:
            system("cls");
            _ShowDepositScreen(); 
            _GoBackToAtmMenue();
            break;

        case enAtmMenueOptions::eCheckBalance:
            system("cls");
            _ShowCheckBalanceScreen();
            _GoBackToAtmMenue();
            break;

        case enAtmMenueOptions::eTransfer:
            system("cls");
            _ShowTransferScreen(); 
            _GoBackToAtmMenue();
            break;

        case enAtmMenueOptions::eTransferLogsList:
            system("cls");
            _ShowTransferLogsListScreen(); 
            _GoBackToAtmMenue();
            break;

        case enAtmMenueOptions::eShowEmails:
            system("cls");
            _ShowEmailsListScreen();
            _GoBackToAtmMenue();
            break;

        case enAtmMenueOptions::eLogout:
            system("cls");
            _Logout(); 
            
        }
    }

    static void _GoBackToAtmMenue()
    {
        cout << "\n";
        cout << left << setw(37) << "" << "Press Any Key To Go Back To ATM Main Menue ... ";
        system("pause>0");
        ShowAtmMainScreen(); 
    }

public :

	static void ShowAtmMainScreen()
	{
        system("cls"); 
        _DrawScreenHeader("\t   ATM Main Menue","", enSystemChoice::eAtmSystem);

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tATM Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[1] Quick Withdraw.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[2] Normal WithDraw.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[3] Deposit.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[4] Transfer.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[5] Check Balance.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[6] Transactions Log.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[7] Emails Box.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;31m[8] Logout.\033[0m\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformAtmMenuOptions((enAtmMenueOptions)_ReadAtmMenueOption());
	}

};

