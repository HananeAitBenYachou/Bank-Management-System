#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsLockClientScreen.h"
#include "clsUnlockClientScreen.h"
#include "clsLockedClientsListScreen.h"


class clsLockSystemMenueScreen : protected clsScreen
{

private:

    enum enLockSystemMenueOptions
    {
        eLockClient = 1,
        eUnlockClient = 2,
        eListLockedClients = 3,
        eMainMenue = 4
        
    };

    static short _ReadLockSystemMenueOption()
    {
        short Choice;
        cout << left << setw(37) << "" << "Choose what do you want to do ? [1 to 4] ? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 4);
        return Choice;
    }

    static void _ShowLockClientScreen()
    {
        clsLockClientScreen::ShowLockClientScreen();    
    }

    static void _ShowUnlockClientScreen()
    {
        clsUnlockClientScreen::ShowUnlockClientScreen(); 
    }

    static void _ShowLockedClientsListScreen()
    {
        clsLockedClientsListScreen::ShowClientsList(); 
    }

    static void _PerformLockSystemMenueOptions(enLockSystemMenueOptions LockSystemMenueOption)
    {
        switch (LockSystemMenueOption)
        {
        case enLockSystemMenueOptions::eLockClient:
            system("cls");
            _ShowLockClientScreen(); 
            _GoBackToLockSystemMenue(); 
            break; 

        case enLockSystemMenueOptions::eUnlockClient:
            system("cls");
            _ShowUnlockClientScreen(); 
            _GoBackToLockSystemMenue();
            break;

        case enLockSystemMenueOptions::eListLockedClients:
            system("cls");
            _ShowLockedClientsListScreen(); 
            _GoBackToLockSystemMenue();
            break;

        case enLockSystemMenueOptions::eMainMenue:
        {

        }

        }
    }

    static void _GoBackToLockSystemMenue()
    {
        cout << "\n";
        cout << left << setw(37) << "" << "Press Any Key To Go Back To Lock System Menue ... ";
        system("pause>0");
        ShowLockSystemMenue();
    }

public:

    static void ShowLockSystemMenue()
    {
        system("cls");
        _DrawScreenHeader("\t  Lock System Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[1]  Lock Client.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[2]  UnLock Client.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[3]  Show Locked Clients List.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;31m[4]  Main Menue.\033[0m\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformLockSystemMenueOptions((enLockSystemMenueOptions)_ReadLockSystemMenueOption());

    }

};

