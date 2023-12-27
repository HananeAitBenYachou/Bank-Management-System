#pragma once
#include "clsScreen.h"
#include <iomanip>
class clsAtmTransferLogListScreen : protected clsScreen
{
private:

	static void _PrintAtmTransferLogRecord(clsBankClient::stAtmTransactionLogRecord AtmTransferLogRecord)
	{
		string Amount = "";
		cout  << setw(8) << left << "" << "| " << left << setw(25) << AtmTransferLogRecord.DateTime;
		cout  << "| " << left << setw(20) << AtmTransferLogRecord.TransactionType;
		cout  << "| " << left << setw(10) << AtmTransferLogRecord.SourceAccountNumber;
		cout  << "| " << left << setw(10) << AtmTransferLogRecord.DestinationAccountNumber;
		
		if (AtmTransferLogRecord.TransactionType == "Withdraw" )
		{
			Amount = "\33[0;31m -" + to_string(AtmTransferLogRecord.Amount) + "\33[0m";
		}

		else if (AtmTransferLogRecord.TransactionType == "Transfer")
		{
			if (AtmTransferLogRecord.SourceAccountNumber == CurrentClient.GetAccountNumber())
			{
				Amount = "\33[0;31m -" + to_string(AtmTransferLogRecord.Amount) + "\33[0m";
			}

			else
			{
				Amount = "\33[0;32m +" + to_string(AtmTransferLogRecord.Amount) + "\33[0m";
			}
		}

		else 
		{
			Amount = "\33[0;32m +" + to_string(AtmTransferLogRecord.Amount) + "\33[0m";
		}

		cout  << "| " << left << setw(15) << Amount;
	}

public: 

	static void ShowAtmTransferLogListScreen()
	{
		vector<clsBankClient::stAtmTransactionLogRecord> vAtmTransferLogRecors;
		vAtmTransferLogRecors = clsBankClient::GetAtmTransactionLogsList(CurrentClient);

		string Title = "   ATM Transaction Log List Screen";
		string SubTitle = "\t   (" + to_string(vAtmTransferLogRecors.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle,enSystemChoice::eAtmSystem);

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "______________________________________________\n\n";

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(20) << "Transaction Type";
		cout << "| " << left << setw(10) << "From";
		cout << "| " << left << setw(10) << "To";
		cout << "| " << left << setw(15) << "Amount";
		
		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "______________________________________________\n\n";

		if (vAtmTransferLogRecors.size() == 0)
		{
			cout << "\n" << setw(8) << left << "" << "NO TRANSFER LOGS RECORDS ARE AVAILABLE IN THE SYSTME !\n\n";
		}

		else
			for (clsBankClient::stAtmTransactionLogRecord AtmTransferLogRecord : vAtmTransferLogRecors)
			{
				_PrintAtmTransferLogRecord(AtmTransferLogRecord);
				cout << endl;
			}

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "______________________________________________\n\n";

	}

};

