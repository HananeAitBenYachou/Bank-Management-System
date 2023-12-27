#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsQuickWithDrawScreen.h"
#include <iomanip>

class clsQuickWithDrawMenueScreen : protected clsScreen
{
private:

    static short _ReadQuickWithDrawMenueOption()
    {
        short Choice;
        cout << left << setw(37) << "" << "Choose what do you want to do ? [1 to 9] ? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 9);
        return Choice;
    }

    static void _ShowQuickWithDrawScreen(short QuickWithdrawAmount)
    {
        clsQuickWithDrawScreen::ShowQuickWithDrawScreen(QuickWithdrawAmount);
    }

    static short GetQuickWithDrawAmount(short QuickWithdrawOption)
    {
        switch (QuickWithdrawOption)
        {
        case 1:
            return 20;
        case 2:
            return 50;
        case 3:
            return 100;
        case 4:
            return 200;
        case 5:
            return 400;
        case 6:
            return 600;
        case 7:
            return 800;
        case 8:
            return 1000;
        case 9:
            return 0;
        }
    }

    static void _PerformQuickWithDrawMenueOptions(short QuickWithdrawOption)
    {
        short QuickWithdrawAmount = GetQuickWithDrawAmount(QuickWithdrawOption);

        if (QuickWithdrawOption == 9)
            return; 
           
        else
        {
            system("cls");
            _ShowQuickWithDrawScreen(QuickWithdrawAmount);
            _GoBackToQuickWithDrawMenue();
            
        }

    }

    static void _GoBackToQuickWithDrawMenue()
    {
        cout << "\n";
        cout << left << setw(37) << "" << "Press Any Key To Go Back To Quick WithDraw Menue  ... ";
        system("pause>0");
        ShowQuickWithDrawMenueScreen(); 
      
    }

public :

    static void ShowQuickWithDrawMenueScreen()
    {
        system("cls");
        _DrawScreenHeader("Quick WithDraw Menue Screen","",enSystemChoice::eAtmSystem);

        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t\t\tQuick Withdraw Menue \n";
        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t [1] 20             [2] 50\n";
        cout << setw(37) << left << "" << "\t [3] 100            [4] 200\n";
        cout << setw(37) << left << "" << "\t [5] 400            [6] 600\n";
        cout << setw(37) << left << "" << "\t [7] 800            [8] 1000\n";
        cout << setw(37) << left << "" << "\t [9] Exit             \n";

        cout << setw(37) << left << "" << "=============================================\n\n";
        cout << setw(37) << left << "" << "Your Balance is : " << CurrentClient.AccountBalance;

        _PerformQuickWithDrawMenueOptions(_ReadQuickWithDrawMenueOption());
    }


};


