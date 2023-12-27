#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

using namespace std;

class clsWithDrawScreen : protected clsScreen
{
private :

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\n\t~~~ Client Card ~~~ ";
        cout << "\n======================================\n";
        cout << "\nFirst Name     : " << Client.FirstName;
        cout << "\nLast Name      : " << Client.LastName;
        cout << "\nFull Name      : " << Client.FullName();
        cout << "\nEmail          : " << Client.Email;
        cout << "\nPhone          : " << Client.Phone;
        cout << "\nAccount Number : " << Client.GetAccountNumber();
        cout << "\nPinCode        : " << Client.PinCode;
        cout << "\nAccount Balance: " << Client.AccountBalance;
        cout << "\n\n======================================\n";
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        return AccountNumber;
    }

public : 

    static void ShowWithDrawScreen()
    {
        _DrawScreenHeader("\t   WithDraw Screen");

        string AccountNumber = ""; 
        AccountNumber = _ReadAccountNumber(); 

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber(); 
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber); 

        _PrintClient(Client); 

        double Amount = 0;
        cout << "\nPlease enter withdraw amount ? ";
        Amount = clsInputValidate::ReadDblNumber(); 

        char Answer = 'N'; 
        cout << "\nAre you sure you want to perform this operation ? Y/N ? ";
        cin >> Answer; 

        if(toupper(Answer)== 'Y')
        { 
            if (Client.WithDraw(Amount))
            {
                cout << "\nAmount Withdrawd Successfully.\n";
                cout << "\nNew Balance Is : " << Client.AccountBalance;

            }
           
            else
            {
                cout << "\nCannot Withdeaw , Insufficient Balance !\n";
                cout << "\nAmount To Withdraw is " << Amount;
                cout << "\nYour Balance is " << Client.AccountBalance;
            }
           
        }

        else
        {
            cout << "\nOperation was cancelled.\n";
           
        }

    }
};

