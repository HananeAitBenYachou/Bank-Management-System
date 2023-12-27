#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsNormalWithDrawScreen : protected clsScreen
{
    
private : 

    static int _ReadNormalWithDrawAmount()
    {
        int Number = 0;
        cout << "\nEnter an amount multiple of 5's ? ";
        Number = clsInputValidate::ReadIntNumber(); 
        while (Number % 5 != 0)
        {
            cout << "\nInvalid Number , Enter an amount multiple of 5's ? ";
            Number = clsInputValidate::ReadIntNumber();

        }

        return Number;
    }

public :

    static void ShowNormalWithDrawScreen()
    {
        system("cls"); 
        _DrawScreenHeader("\t  Normal Withdraw Screen", "", enSystemChoice::eAtmSystem);

        int QuickWithdrawAmount = _ReadNormalWithDrawAmount(); 

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

