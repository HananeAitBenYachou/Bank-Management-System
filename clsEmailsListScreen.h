#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"

class clsEmailsListScreen : protected clsScreen
{
private:

	enum enEmailsMenueOptions {eShowMessages = 1 , eExit = 2};

	static void _PrintClientMessageRecord(clsBankClient::stClientMessageBox ClientMessage)
	{	
		cout << setw(8) << left << "" << "| " << ClientMessage.NumberOfMessage << "] " << left << setw(40) << ClientMessage.DateTime;
		cout << "| " << left << setw(20) << ClientMessage.Sender;
		cout << "| " << left << setw(20) << ClientMessage.Title;

		if (!ClientMessage.MarkedForRead)
		{
			cout << "\033[1;5;31m " << char(259) << "\033[0m";
		}

		else
		{
			cout << "\033[1;5;32m " << char(259) << "\033[0m";
		}
	}
	
	static short _ReadEmailsMenueOption()
	{
		short Choice;
		cout << "\n\nChoose what do you want to do : [1] Show Messages / [2] Exit : ";
		Choice = clsInputValidate::ReadIntNumberBetween(1, 2);
		return Choice;
	}

	static void _PrintDetailedMessage(clsBankClient::stClientMessageBox ClientMessage)
	{
		system("cls"); 

		cout << "\n\n\n" << setw(8) << left << "" << "\033[1;5;31m___________________________________"
			<< char(259) << " " << char(174) << " ... Title ... " << char(175) << " " << char(259)
			<< "___________________________________\033[0m\n\n";

		cout << setw(50) << left << "" << ClientMessage.Title;


		cout << "\n\n\n" << setw(8) << left << "" << "\033[1;5;31m___________________________________"
			<< char(259) << " " << char(174) << " ... Body ... " << char(175) << " " << char(259)
			<< "___________________________________\033[0m\n\n";

		cout << setw(20) << left << "" << ClientMessage.Body << "\n\n";

	
	}

	static short _ReadMessageNumber(vector <clsBankClient::stClientMessageBox> vMessages)
	{
		short MessageNumber;
		cout << "\n\nEnter Message Number : ";
		MessageNumber = clsInputValidate::ReadIntNumberBetween(1, vMessages.size());

		return MessageNumber; 
	}

	static void _ShowDetailedMessage(vector <clsBankClient::stClientMessageBox> &vMessages)
	{
		if (vMessages.size() == 0)
		{
			cout << "\nNo Available Messages In the moment ! \n\n";
			return; 
		}

		short MessageNumber = _ReadMessageNumber(vMessages);

		for (clsBankClient::stClientMessageBox& Message : vMessages)
		{
			if (Message.NumberOfMessage == MessageNumber)
			{
				_PrintDetailedMessage(Message);
				
				clsBankClient::SaveClientsEmailsListToFile(Message);	
			}	
		}

	}

    static void _PerformEmailsMenueOptions(enEmailsMenueOptions EmailsMenueOption , vector <clsBankClient::stClientMessageBox> &vMessages)
    {
        switch (EmailsMenueOption)
        {
		case enEmailsMenueOptions::eShowMessages:
			_ShowDetailedMessage(vMessages); 
            _GoBackToEmailsMenue();
            break;

		case enEmailsMenueOptions::eExit:
		{

		}

        }
    }

	static void _GoBackToEmailsMenue()
	{
		cout << "\n";
		cout << left << setw(37) << "" << "Press Any Key To Go Back To Emails Menue ... ";
		system("pause>0");
		ShowClientEmailsMenue();
	}

public:

	
	static void ShowClientEmailsMenue()
	{
		system("cls");
		vector <clsBankClient::stClientMessageBox> vMessages = clsBankClient::GetClientEmailsList(CurrentClient);


		string Title = "\t   Messages List Screen";
		string Substitle = "\t     (" + to_string(vMessages.size()) + ") Message (s).";

		_DrawScreenHeader(Title, Substitle, enSystemChoice::eAtmSystem);

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "___________________________________________________\n\n";

		cout << setw(8) << left << "" << "| " << "   " << left << setw(40) << "Date/Time";
		cout << "| " << left << setw(20) << "From";
		cout << "| " << left << setw(20) << "Title";


		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "___________________________________________________\n\n";

		if (vMessages.size() == 0)
		{
			cout << setw(10) << left << "" << "No Available Messages In The System !\n\n";

			return;
		}

		else
		{
			short NumberOfMessage = 0;
			for (clsBankClient::stClientMessageBox& Message : vMessages)
			{
				NumberOfMessage++;
				Message.NumberOfMessage = NumberOfMessage;
				_PrintClientMessageRecord(Message);
				cout << endl;
			}
		}


		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "___________________________________________________\n\n";

		_PerformEmailsMenueOptions(enEmailsMenueOptions(_ReadEmailsMenueOption()), vMessages);

	}

};

