#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

public : 

    static void ShowDeleteClientScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("\t  Delete Client Screen");

        string AccountNumber = "";

        cout << "Please Enter Account Number ? ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "This Account Number is not found , please try a valid one ? ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClient(Client);

        char Answer = 'N';
        cout << "\nAre you sure you want to delete this client ? Y/N ? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {

            if (Client.Delete())
            {
                cout << "\n\nClient Deleted Successfully :-) \n";
                _PrintClient(Client);
            }

            else
            {
                cout << "\n\nError Client Was Not Deleted :-( \n";
            }

        }

    }


};

