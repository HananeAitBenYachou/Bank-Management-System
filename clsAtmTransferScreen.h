#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAtmTransferScreen : protected clsScreen
{
private:

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

	static clsBankClient _ReadDestinationAccountNumber()
	{
		string AccountNumber = ""; 
		cout << "\nPlease Enter Account Number to Transfer To : "; 
		AccountNumber = clsInputValidate::ReadString(); 

        while (AccountNumber == CurrentClient.GetAccountNumber())
        {
            cout << "\nYou cannot Transfer to your own Account, choose another one to Transfer To : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber); 

        
        return Client; 
	}

    static float _ReadTransferAmount()
    {
        double Amount; 

        cout << "\nEnter Transfer Amount : "; 
        Amount = clsInputValidate::ReadFloatNumber(); 

        while (Amount > CurrentClient.AccountBalance)
        {
            cout << "\n\nAmount Exceeds the available Balance , Enter another Amount : ";
            Amount = clsInputValidate::ReadFloatNumber();
        }

        return Amount; 
    }

public : 

    static void ShowAtmTransferScreen()
    {
        _DrawScreenHeader("\t Transfer Screen ", "", enSystemChoice::eAtmSystem);

        clsBankClient ClientDestination = _ReadDestinationAccountNumber(); 
        _PrintClient(ClientDestination); 

        float Amount = _ReadTransferAmount(); 

        char Answer = 'Y'; 
        cout << "\n\nAre you sure you want to perform this operation ? Y/N ? "; 
        cin >> Answer; 

        if (toupper(Answer) == 'Y')
        {
            if (CurrentClient.Transfer(ClientDestination, Amount))
            {
                cout << "\nTransfer Done successfully ! \n"; 
                _PrintClient(CurrentClient);
                _PrintClient(ClientDestination); 
            }

            else
            {
                cout << "\n\nTransfer Failed :-(\n";
            }
        }
        else
        {
            cout << "\nOperation was cancelled ! \n"; 
        }

    }



};

