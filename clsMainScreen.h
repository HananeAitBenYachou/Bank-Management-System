#pragma once
#include <iostream> 
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientsScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterListScreen.h"
#include "clsCurrencyExchangeScreen.h"
#include "clsLockSystemMenueScreen.h"



using namespace std; 

class clsMainScreen : protected clsScreen
{

private : 

    enum enMainMenueOptions
    {
        eListClients  = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eLockSystemMenue = 8,
        eLoginRegister = 9,
        eCurrencyExchangeMenue = 10,
        eExit = 11,
    };

    static short _ReadMainMenuOption()
    {
        short Choice; 
        cout << left << setw(37) << "" << "Choose what do you want to do ? [1 to 11] ? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 11);
        return Choice;
    }

    static void _ShowLockSystemMenueScreen()
    {
        clsLockSystemMenueScreen::ShowLockSystemMenue(); 
    }

    static void _ShowAllClientsScreen()
    {   
           clsClientsListScreen::ShowClientsList(); 
    }

    static void _ShowAddNewClientsScreen()
    {   
    
        clsAddNewClientsScreen::ShowAddNewClientScreen(); 

    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen(); 
    }

    static void _ShowUpdateClientScreen()
    {    
        clsUpdateClientScreen::ShowUpdateClientScreen(); 
    }

    static void _ShowFindClientScreen()
    {  
      
        clsFindClientScreen::ShowFindClientScreen(); 
    }

    static void _ShowManageUsersMenue()
    {
      
        clsManageUsersScreen::ShowManageUsersMenue(); 
    }

    static void _ShowTransactionsMenue()
    {
       
        clsTransactionsScreen::ShowTransactionsMenue(); 
    }

    static void _ShowCurrencyExchangeMenue()
    {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeMenue(); 
    }

    static void _ShowLoginRegisterListScreen()
    {
        clsLoginRegisterListScreen::ShowLoginRegisterListScreen();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");      
    }

    static void _PerformMainMenuOptions(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue(); 
            break; 

        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen(); 
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eLockSystemMenue:
            system("cls");
            _ShowLockSystemMenueScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue(); 
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegisterListScreen(); 
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eCurrencyExchangeMenue:
            system("cls");
            _ShowCurrencyExchangeMenue(); 
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            break;

        }
    }

    static void _GoBackToMainMenue()
    {    
        cout << "\n"; 
        cout << left << setw(37) << "" << "Press Any Key To Go Back To Main Menue ... "; 
        system("pause>0");
        ShowMainMenue(); 
    }

public : 
 
    static void ShowMainMenue()
    {
        system("cls"); 
        _DrawScreenHeader("\t      Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[1]  Show Client List.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[2]  Add New Client.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[3]  Delete Client.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[4]  Update Client Info.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[5]  Find Client.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[6]  Transactions.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[7]  Manage Users.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[8]  Lock Clients System.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[9]  Login Register.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[10] Currency Exchange.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;31m[11] Logout.\033[0m\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenuOptions((enMainMenueOptions)_ReadMainMenuOption()); 

    } 

};

