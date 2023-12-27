#pragma once
#include "Global.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsLoginScreen.h"
#include "clsATMLoginScreen.h"
#include "clsShowResetPinScreen.h"

using namespace std;

class clsStartScreen 
{

private : 

    enum enStartMenueOptions
    {
        eBankSystem = 1,
        eAtmSystem = 2,       
    };

    static short _ReadStartMenueOption()
    {
        short Choice;
        cout << left << setw(35) << "" << "\033[3;33m Choose what do you want to do ? [1 to 2] ? \033[0m";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 2);
        return Choice;
    }

    static void _ShowAtmSystemScreen()
    {
        /* while (true)
         {
             if (!clsATMLoginScreen::ShowATMLoginScreen())
             {
                 break;
             }
         }*/

        if (!clsATMLoginScreen::ShowATMLoginScreen())
        {     
            clsShowResetPinScreen::ShowResetPinScreen(); 

            cout << "\n\n" << setw(35) << left << "" << "Press Any Key To Go Back To Start Menue ! ";
            system("pause>0"); 
            return;
        }

    }

    static void _ShowBankSystemScreen()
    {
        /*while (true)
        {
            if (!clsLoginScreen::ShowLoginScreen())
            {
                break;
            }
        }*/

        if (!clsLoginScreen::ShowLoginScreen())
        {
            cout << "\n\n" << setw(35) << left << "" << "Press Any Key To Go Back To Start Menue ! ";
            system("pause>0");
            return;
        }
    }

    static void _PerformStartMenuOptions(enStartMenueOptions StartMenueOption)
    {
        switch (StartMenueOption)
        {
        case enStartMenueOptions::eBankSystem:
            system("cls");
            _ShowBankSystemScreen();
            _GoBackToStartMenue(); 
            break;

        case enStartMenueOptions::eAtmSystem:
            system("cls");
            _ShowAtmSystemScreen();          
            _GoBackToStartMenue(); 
            break;

        }
    }

    static void _GoBackToStartMenue()
    {      
        ShowStartMenue();
    }

public :


    static void ShowStartMenue()
    {
        system("cls");
     
        string S = "\t\t _______ _______ _______ ______   _______    __   __ _______ __    _ __   __ _______ \n"
            "\t\t|       |       |       |    _ | |       |  |  |_|  |       |  |  | |  | |  |       |\n"
            "\t\t|  _____|_     _|   _   |   | || |_     _|  |       |    ___|   |_| |  | |  |    ___|\n"
            "\t\t| |_____  |   | |  |_|  |   |_||_  |   |    |       |   |___|       |  |_|  |   |___ \n"
            "\t\t|_____  | |   | |       |    __  | |   |    |       |    ___|  _    |       |    ___|\n"
            "\t\t _____| | |   | |   _   |   |  | | |   |    | ||_|| |   |___| | |   |       |   |___ \n"
            "\t\t|_______| |___| |__| |__|___|  |_| |___|    |_|   |_|_______|_|  |__|_______|_______|";
        cout <<"\033[5;33m" << S << "\033[0m\n\n\n";

        string Menue1 = "\n"
            "\t\t\t\t ^ ^                 \n"
            "\t\t\t\t(O,O)                \n"
            "\t\t\t[1]     (   ) BANK SYSTEM\n"
            "\t\t\t\t-\"-\"-----------------";

        string Menue2 = "\n"
            "\t\t\t\t ^ ^                 \n"
            "\t\t\t\t(O,O)                \n"
            "\t\t\t[2]     (   ) ATM SYSTEM\n"
            "\t\t\t\t-\"-\"-----------------";

        cout << setw(22) << left << "" << "\033[1;95m<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:><:>:<:>:<:>:<:>\033[0m";
        cout << setw(37) << left << "" << "\033[1;95m" << Menue1 << "\033[0m\n";
        cout << setw(37) << left << "" << "\033[1;95m" << Menue2 << "\033[0m\n\n";
        cout << setw(22) << left << "" << "\033[1;95m<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:><:>:<:>:<:>:<:>\033[0m\n\n";

        _PerformStartMenuOptions((enStartMenueOptions)_ReadStartMenueOption());

    }

};

