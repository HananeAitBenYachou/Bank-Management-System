#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsTransferLogListScreen : protected clsScreen
{

private:

	static void _PrintTransferLogRecord(clsBankClient::stTransferLogRecord TransferLogRecord)
	{
		cout << setw(8) << left << "" << "| " << left << setw(20) << TransferLogRecord.DateTime;
		cout << "| " << left << setw(10) << TransferLogRecord.SourceAccountNumber;
		cout << "| " << left << setw(10) << TransferLogRecord.DestinationAccountNumber;
		cout << "| " << left << setw(12) << TransferLogRecord.Amount;
		cout << "| " << left << setw(15) << TransferLogRecord.SourceBalanceAfter;
		cout << "| " << left << setw(15) << TransferLogRecord.DestinationBalanceAfter;
		cout << "| " << left << setw(12) << TransferLogRecord.UserName;

	}

public : 

	static void ShowTransferLogListScreen()
	{
		vector<clsBankClient::stTransferLogRecord> vTransferLogRecors; 
		vTransferLogRecors = clsBankClient::GetTransferLogsList(); 

		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t   (" + to_string(vTransferLogRecors.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "_______________________________________________________\n\n";

		cout << setw(8) << left << "" << "| " << left << setw(20) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(12) << "Amount";
		cout << "| " << left << setw(15) << "s.Balance";
		cout << "| " << left << setw(15) << "d.Balance";
		cout << "| " << left << setw(12) << "UserName";

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "_______________________________________________________\n\n";

		if (vTransferLogRecors.size() == 0)
		{
			cout << "\n" << setw(8) << left << "" << "NO TRANSFER LOGS RECORDS ARE AVAILABLE IN THE SYSTME !\n\n";
		}

		else
			for (clsBankClient::stTransferLogRecord& TransferLogRecord : vTransferLogRecors)
			{
				_PrintTransferLogRecord(TransferLogRecord);
				cout << endl; 
			}

		cout << "\n" << setw(8) << left << "" << "________________________________________________________";
		cout << "_______________________________________________________\n\n";

	}

};

