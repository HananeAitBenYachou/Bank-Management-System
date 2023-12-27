#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsScreen.h"

class clsLockedClientsListScreen : protected clsScreen
{

private:

    static void _PrintLockedClientRecordLine(clsBankClient Client)
    {
        
        cout << setw(5) << left << "" << "| " << left << setw(15) << Client.GetAccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(15) << Client.Email;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(15) << Client.AccountBalance;
        cout << "| " << left << setw(15) << Client.GetLockDate();
    }

public:

    static void ShowClientsList()
    {
       
        vector<clsBankClient> vLockedClients = clsBankClient::GetLockedClientsList();

        string Title = "\tLocked Clients List Screen";
        string Subtitle = "\t (" + to_string(vLockedClients.size()) + ") Locked Client (s).";

        _DrawScreenHeader(Title, Subtitle);

       
        cout << "\n" << setw(5) << left << "" << "_______________________________________________________________";
        cout << "__________________________________________________________\n\n";

        cout << setw(5) << left << "" << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(15) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(15) << "Balance";
        cout << "| " << left << setw(15) << "Lock Date";

        cout << "\n" << setw(5) << left << "" << "_______________________________________________________________";
        cout << "__________________________________________________________\n\n";

        if (vLockedClients.size() == 0)
        {
            cout << setw(8) << "";
            cout << "" << "\t\t\t\t\tNo Clients Locked Available In The System !!!\n";

        }

        else
            for (clsBankClient& C : vLockedClients)
            {
                _PrintLockedClientRecordLine(C);
                cout << endl;
            }


        cout << "\n" << setw(5) << left << "" << "_______________________________________________________________";
        cout << "__________________________________________________________\n\n";

    }

};

