#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std; 

class clsClientsListScreen : protected clsScreen
{

private : 

    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << setw(8) << left << "" << "| "<< left << setw(15) << Client.GetAccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(20) << Client.Email;
        cout << "| " << left << setw(12) << Client.PinCode;
        cout << "| " << left << setw(12) << Client.AccountBalance;
    }

public : 

   static void ShowClientsList()
   {
       if (!_CheckAccessRights(clsUser::enPermissions::pListClients))
       {
           return;
       }

       vector<clsBankClient> vClients = clsBankClient::GetClientsList();

       string Title = "\t  Clients List Screen"; 
       string Subtitle = "\t   (" + to_string(vClients.size()) + ") Client (s).";

       _DrawScreenHeader(Title, Subtitle); 

       cout << setw(8) << left << "" << "\n\t_______________________________________________________________";
       cout << "_________________________________________\n\n";

      cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
      cout << "| " << left << setw(20) << "Client Name";
      cout << "| " << left << setw(12) << "Phone";
      cout << "| " << left << setw(20) << "Email";
      cout << "| " << left << setw(12) << "Pin Code";
      cout << "| " << left << setw(12) << "Balance";

      cout << setw(8) << left << "" << "\n\t_______________________________________________________________";
      cout << "_________________________________________\n\n";

      if (vClients.size() == 0)
      {
          cout << setw(8) << "";
          cout <<"" << "\t\t\t\t\tNo Clients Available In The System !!!\n";

      }

      else 
        for (clsBankClient& C : vClients)
        {
            _PrintClientRecordLine(C);
            cout << endl;
        }

      
      cout << setw(8) << left << "" << "\n\t_______________________________________________________________";
      cout << "_________________________________________\n\n";

   }

};

