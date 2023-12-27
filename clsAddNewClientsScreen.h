#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;


class clsAddNewClientsScreen : protected clsScreen
{
private : 

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter First Name : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Enter Email : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Enter Phone : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Enter PinCode : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter Account Balance : ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();

    }

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

    static void ShowAddNewClientScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }

        _DrawScreenHeader("\t Add New Client Screen");

        string AccountNumber = "";
        AccountNumber = clsBankClient::GetAutoAccountNumber();

        /*cout << "Please Enter Client Account Number ? ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nThis Account Number is already in the system, please try another one ? ";
            AccountNumber = clsInputValidate::ReadString();
        }*/

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();


        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:

            cout << "\nAccount Added Successfully :-)\n";
            _PrintClient(NewClient);
            break;

        case clsBankClient::enSaveResults::svFailedEmptyObject:
            cout << "\nError account was not saved because it's Empty :-(\n";
            break;

        case clsBankClient::enSaveResults::svFailedAccountExists:
            cout << "\nError ! this account is already in the file :-(\n";
            break;
        }
    }
   

};

