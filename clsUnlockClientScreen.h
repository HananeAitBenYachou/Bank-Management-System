#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsUnlockClientScreen : protected clsScreen
{
    static clsBankClient _ReadClientToUnlock()
    {
        string AccountNumber = "";
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        bool ClientNotFound = false;
        bool ClientNotLocked = false;

        cout << "\nPlease Enter Account Number To Unlock ? ";
        AccountNumber = clsInputValidate::ReadString();

        Client = clsBankClient::Find(AccountNumber);

        do
        {

            ClientNotFound = Client.IsEmpty();
            ClientNotLocked = !Client.GetMarkedForLocked();

            if (ClientNotFound)
            {
                cout << "\nThis Account Number is not found , please try a valid one ? ";
                AccountNumber = clsInputValidate::ReadString();
            }

            else if (ClientNotLocked)
            {
                cout << "\nThis Account Number is not Locked  , please try a locked one ? ";
                AccountNumber = clsInputValidate::ReadString();
            }

            Client = clsBankClient::Find(AccountNumber);

        } while (ClientNotFound || ClientNotLocked);

        return Client;

    }


public:

    static void ShowUnlockClientScreen()
    {
        _DrawScreenHeader("\t  Unlock Client Screen");


        clsBankClient Client = clsBankClient::Find("");
        Client = _ReadClientToUnlock();

        char Answer = 'N';
        cout << "\nAre you sure you want to Unlock this client ? Y/N ? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {

            if (Client.Unlock())
            {
                cout << "\n\nClient Unlocked Successfully :-) \n";
                cout << "Date of Unlock is : [ " << clsDate::GetSystemDateTimeString() << " ] \n";

                string MessageBody = "Dear Sir/Madam Your account have been unlocked now !";
                Client.SendEmail(CurrentUser.UserName, "Hi", MessageBody);
            }

            else
            {
                cout << "\n\nError Client Was Not Unlocked :-( \n";
            }

        }

    }
};

