#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsLockClientScreen : protected clsScreen
{
private:

    static clsBankClient _ReadClientToLock()
    {
        string AccountNumber = "";
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        bool ClientNotFound = false;
        bool ClientIsAlreadyBlocked = false;
   
        cout << "\nPlease Enter Account Number To Lock ? ";
        AccountNumber = clsInputValidate::ReadString();

        Client = clsBankClient::Find(AccountNumber);

        do
        {
            
            ClientNotFound = Client.IsEmpty();
            ClientIsAlreadyBlocked = Client.GetMarkedForLocked();

                
            if (ClientNotFound)
            {
                cout << "\nThis Account Number is not found , please try a valid one ? ";
                AccountNumber = clsInputValidate::ReadString();
            }

            else if (ClientIsAlreadyBlocked)
            {
                cout << "\nThis Account Number is already Locked  , please try an unlocked one ? ";
                AccountNumber = clsInputValidate::ReadString();
            }

            Client = clsBankClient::Find(AccountNumber);

        } while (ClientNotFound || ClientIsAlreadyBlocked);

        return Client; 

    }


public: 

	static void ShowLockClientScreen()
	{
        _DrawScreenHeader("\t  Lock Client Screen");


        clsBankClient Client = clsBankClient::Find("");
        Client = _ReadClientToLock();

        char Answer = 'N';
        cout << "\nAre you sure you want to Lock this client ? Y/N ? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {

            if (Client.Lock())
            {
                cout << "\n\nClient Locked Successfully :-) \n";
                cout << "Date of Lock is : [ " << Client.GetLockDate() << " ] \n";

                string MessageBody = "Dear Sir/Madam Your account have been locked , please contact the bank to unlock it !";
                Client.SendEmail(CurrentUser.UserName, "Hi", MessageBody);

            }

            else
            {
                cout << "\n\nError Client Was Not Locked :-( \n";
            }

        }
	}

};

