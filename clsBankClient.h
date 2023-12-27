#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsDate.h"

using namespace std; 

class clsBankClient : public clsPerson
{
private :

	string _AccountNumber; 
	string _PinCode;
	double _AccountBalance; 
	bool _MarkedForDeleted = false; 
	int _MarkedForLocked = 0;
	string _LockDate = "Not Locked";

	enum enMode {EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2 }; 
	enMode _Mode; 

	enum enAddToTransactionsLog { eAdd = 1, eNotAdd = 2 };

	static clsBankClient _ConvertDataLineToClientObject(string DataLine, string Seperator = "#//#")
	{
		vector<string> vClientData; 
		vClientData = clsString::Split(DataLine,Seperator) ;

		return clsBankClient(enMode::UpdateMode,vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]), stoi(vClientData[7]) , vClientData[8]);
	}

	static string _ConvertClientObjectToDataLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.GetAccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance) +Seperator;
		stClientRecord += to_string(Client._MarkedForLocked) + Seperator;
		stClientRecord += Client.GetLockDate();

		return stClientRecord; 
	}

	static vector<clsBankClient> _LoadClientsDataFromFile(string Seperator = "#//#")
	{
		vector<clsBankClient> vClients; 
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsBankClient Client = _ConvertDataLineToClientObject(DataLine);
				vClients.push_back(Client);

			}

			MyFile.close(); 

		}
		
		return vClients; 
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile; 
		MyFile.open("Clients.txt", ios::out); 

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (C.GetMarkedForDeleted() != true)
				{
					MyFile << _ConvertClientObjectToDataLine(C) << endl;
				}
			}

			MyFile.close(); 
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0,0,"");
	}

	static string _LoadAutoAccountNumberFromFile()
	{
		fstream MyFile;
		static short AutoNumber;

		MyFile.open("AutoAccountNumber.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				AutoNumber = stoi(Line);
				AutoNumber++;
				_SaveNewAutoAccountNumberToFile(AutoNumber);

				return Line;
				MyFile.close();
			}
		}
	}

	static void _SaveNewAutoAccountNumberToFile(short NewAutoNumber)
	{
		fstream MyFile;
		MyFile.open("AutoAccountNumber.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line = to_string(NewAutoNumber);
			MyFile << Line << endl;
			MyFile.close();

		}
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);

		if (MyFile.is_open())
		{		
			MyFile << stDataLine<< endl;
			MyFile.close();
		}

	}

	void _AddNewClient()
	{

		_AddDataLineToFile(_ConvertClientObjectToDataLine(*this)); 
	}

	bool _Update()
	{
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile(); 

		for (clsBankClient& C : _vClients)
		{
			if (C.GetAccountNumber() == _AccountNumber)
			{
				C = *this; 
				_SaveClientsDataToFile(_vClients); 
				return true; 
					
			}
		}

		return false; 
	}

	string _PrepareTransferLogRecord(clsBankClient ClientReceiver, double Amount, string UserName, string Seperator = "#//#")
	{
		string stTransferRecord = "";
		stTransferRecord += clsDate::GetSystemDateTimeString()+ Seperator;
		stTransferRecord += _AccountNumber + Seperator;
		stTransferRecord += ClientReceiver.GetAccountNumber() + Seperator;
		stTransferRecord += to_string(Amount) + Seperator;
		stTransferRecord += to_string(_AccountBalance) + Seperator;
		stTransferRecord += to_string(ClientReceiver.AccountBalance) + Seperator;
		stTransferRecord += UserName;

		return stTransferRecord;
	}

	void _RegisterTransferLog(clsBankClient ClientReceiver, double Amount, string UserName)
	{
		fstream MyFile;
		string DataLine = _PrepareTransferLogRecord(ClientReceiver, Amount, UserName);
		MyFile.open("TransferLog.txt", ios::app | ios::out);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}

	}

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string DataLine, string Seperator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;
		vector<string> vTransferLogData = clsString::Split(DataLine, Seperator);
		TransferLogRecord.DateTime = vTransferLogData[0];
		TransferLogRecord.SourceAccountNumber = vTransferLogData[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLogData[2];
		TransferLogRecord.Amount = stoi(vTransferLogData[3]);
		TransferLogRecord.SourceBalanceAfter = stoi(vTransferLogData[4]);
		TransferLogRecord.DestinationBalanceAfter = stoi(vTransferLogData[5]);
		TransferLogRecord.UserName = vTransferLogData[6];

		return TransferLogRecord;
	}
	
	enum enTransactionType;
	string _GetTransactionTypeName(enTransactionType TransactionType)
	{
		string arr[] = { "Deposit", "Withdraw","Transfer" };
		return arr[TransactionType - 1];
	}

	string _PrepareAtmTransactionLogRecord(clsBankClient ClientReceiver, enTransactionType TransactionType ,double Amount,string Seperator = "#//#")
	{
		string stAtmTransferLogRecord = ""; 
		stAtmTransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		stAtmTransferLogRecord += _GetTransactionTypeName(TransactionType) + Seperator;
		stAtmTransferLogRecord += _AccountNumber + Seperator;
		stAtmTransferLogRecord += ClientReceiver.GetAccountNumber() + Seperator;
		stAtmTransferLogRecord += to_string(Amount); 

		return stAtmTransferLogRecord;
	}

	void _RegisterAtmTransactionLog(clsBankClient ClientReceiver, enTransactionType TransactionType, double Amount)
	{
		fstream MyFile;
		MyFile.open("AtmTransactionLog.txt", ios::app | ios::out);

		string DataLine = _PrepareAtmTransactionLogRecord(ClientReceiver, TransactionType, Amount);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl; 
			MyFile.close(); 
		}
	}

	struct stAtmTransactionLogRecord;
	static stAtmTransactionLogRecord _ConvertAtmTransactionLogLineToRecord(string DataLine , string Seperator = "#//#")
	{
		stAtmTransactionLogRecord AtmTransferLogRecord;
		vector<string> vAtmTransferRecordData = clsString::Split(DataLine, Seperator);

		AtmTransferLogRecord.DateTime = vAtmTransferRecordData[0];
		AtmTransferLogRecord.TransactionType = vAtmTransferRecordData[1];
		AtmTransferLogRecord.SourceAccountNumber = vAtmTransferRecordData[2];
		AtmTransferLogRecord.DestinationAccountNumber = vAtmTransferRecordData[3];
		AtmTransferLogRecord.Amount = stof(vAtmTransferRecordData[4]);

		return AtmTransferLogRecord;
	}

	/*****************************************************/

	struct stClientMessageBox;
	string _PrepareClientMessageRecord(string SenderName , string MessageTitle , string MessageBody, string Seperator = "#//#")
	{
		string stMessageDataLine = "";
		stMessageDataLine += GetAccountNumber() + Seperator;
		stMessageDataLine += to_string(0) + Seperator; 
		stMessageDataLine += MessageTitle + Seperator;
		stMessageDataLine += MessageBody + Seperator;
		stMessageDataLine += SenderName + Seperator;
		stMessageDataLine += clsDate::GetSystemDateTimeString() + Seperator;
		stMessageDataLine += to_string(0); 
		return stMessageDataLine;
	}

	void _RegisterClientMessageLog(string SenderName, string MessageTitle, string MessageBody)
	{
		fstream MyFile;
		string DataLine = _PrepareClientMessageRecord(SenderName,MessageTitle,MessageBody);

		MyFile.open("ClientsEmails.txt", ios::app | ios::out);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}

	}

	static stClientMessageBox _ConvertClientMessageToRecord(string DataLine, string Seperator = "#//#")
	{
		stClientMessageBox ClientMessageBoxRecord;

		vector<string> vClientMessageData = clsString::Split(DataLine, Seperator);
		ClientMessageBoxRecord.ReceiverAccountNumber = vClientMessageData[0];
		ClientMessageBoxRecord.NumberOfMessage = stoi(vClientMessageData[1]);
		ClientMessageBoxRecord.Title = vClientMessageData[2];
		ClientMessageBoxRecord.Body = vClientMessageData[3];
		ClientMessageBoxRecord.Sender = vClientMessageData[4];
		ClientMessageBoxRecord.DateTime = vClientMessageData[5];
		ClientMessageBoxRecord.MarkedForRead = stoi(vClientMessageData[6]);

		return ClientMessageBoxRecord;
	}

	static string _ConvertClientMessageRecordToLine(stClientMessageBox MessageRecord , string Seperator = "#//#")
	{
		string stMessageDataLine = "";

		stMessageDataLine += MessageRecord.ReceiverAccountNumber + Seperator; 
		stMessageDataLine += to_string(MessageRecord.NumberOfMessage) + Seperator;
		stMessageDataLine += MessageRecord.Title + Seperator;
		stMessageDataLine += MessageRecord.Body + Seperator;
		stMessageDataLine += MessageRecord.Sender + Seperator;
		stMessageDataLine += MessageRecord.DateTime + Seperator;
		stMessageDataLine += to_string(MessageRecord.MarkedForRead) ;

		return stMessageDataLine;
	}

	static vector<stClientMessageBox> _LoadClientsEmailsListFromFile()
	{
		fstream MyFile;
		MyFile.open("ClientsEmails.txt", ios::in);

		vector<stClientMessageBox> vClientMessageRecords;

		if (MyFile.is_open())
		{
			string Line;
			stClientMessageBox ClientMessageRecord;

			while (getline(MyFile, Line))
			{
				if (Line.empty())
				{
					MyFile.close();
					return vClientMessageRecords;
				}

				ClientMessageRecord = _ConvertClientMessageToRecord(Line);	
				vClientMessageRecords.push_back(ClientMessageRecord);
			}

			MyFile.close();
		}

		return vClientMessageRecords;
	}



public : 

	enum enTransactionType
	{
		eDeposit = 1,
		eWithdraw = 2,
		eTransfer = 3,
	};

	struct stTransferLogRecord
	{
		string DateTime; 
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount = 0;
		double SourceBalanceAfter = 0;
		double DestinationBalanceAfter = 0;
		string UserName;

	};

	struct stAtmTransactionLogRecord
	{
		string DateTime;
		string TransactionType;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount = 0;
		
	};

	struct stClientMessageBox
	{
		string ReceiverAccountNumber;
	    short NumberOfMessage = 0; 
		string Title; 
		string Body;
		string Sender; 
		string DateTime;
		bool MarkedForRead = false;
	};

	clsBankClient(enMode Mode , string FirstName, string LastName, string Email, string Phone ,string AccountNumber , string PinCode , double AccountBalance , bool MarkedForLocked , string LockDate)
		: clsPerson(FirstName , LastName , Email ,Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber; 
		_PinCode = PinCode; 
		_AccountBalance = AccountBalance;
		_MarkedForLocked = MarkedForLocked; 
		_LockDate = LockDate; 
	}

	string GetAccountNumber()
	{
		return _AccountNumber; 
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode; 
	}

	__declspec(property ( get = GetPinCode , put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _AccountBalance; 
	}

	__declspec(property (get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	bool GetMarkedForDeleted()
	{
		return _MarkedForDeleted; 
	}

	int GetMarkedForLocked()
	{
		return _MarkedForLocked; 
	}

	string GetLockDate()
	{
		return _LockDate; 
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClientsData = _LoadClientsDataFromFile(); 
		fstream MyFile;

		for (clsBankClient& Client : vClientsData)
		{
			if (Client.GetAccountNumber() == AccountNumber)
			{
				return Client; 
			}
		}
		
		return _GetEmptyClientObject();

	}
	
	static clsBankClient Find(string AccountNumber , string PinCode)
	{
		vector<clsBankClient> vClientsData = _LoadClientsDataFromFile();
		fstream MyFile;

		for (clsBankClient& Client : vClientsData)
		{
			if (Client.GetAccountNumber() == AccountNumber && Client.PinCode == PinCode)
			{	
				return Client;
			}
		}

		return _GetEmptyClientObject();

	}

	static clsBankClient FindByEmail(string Email)
	{
		vector<clsBankClient> vClientsData = _LoadClientsDataFromFile();
		fstream MyFile;

		for (clsBankClient& Client : vClientsData)
		{
			if (Client.Email == Email)
			{
				return Client;
			}
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty()); 

	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0,0,"");
	}

	static string GetAutoAccountNumber()
	{
		string AccountNumber = "A";
	
		AccountNumber += _LoadAutoAccountNumberFromFile(); 
		
		return AccountNumber; 
	}

	enum enSaveResults {svFailedEmptyObject = 0  , svSucceeded = 1 , svFailedAccountExists = 2};

	 enSaveResults Save()
	 {

		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			return enSaveResults::svFailedEmptyObject;
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database 
			if (IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFailedAccountExists; 
			}

			else
			{
				_AddNewClient(); 
				//we need to set the mode to update after add new client
				_Mode = enMode::UpdateMode; 
				return enSaveResults::svSucceeded; 
			}
		}

		}		
	 }

	 bool Delete()
	 {
		 vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

		 for (clsBankClient& C : _vClients)
		 {
			 if (C.GetAccountNumber() == _AccountNumber)
			 {
				 C._MarkedForDeleted = true;
				 _SaveClientsDataToFile(_vClients);
				 *this = _GetEmptyClientObject();
				 return true;

			 }
		 }

		 return false;
	 }

	 static vector<clsBankClient> GetClientsList()
	 {
		 return _LoadClientsDataFromFile(); 
	 }

	 static double GetTotalBalances()
	 {
		 vector<clsBankClient> vClients = GetClientsList(); 

		 double TotalBalances = 0; 

		 for (clsBankClient& C : vClients)
		 {
			 TotalBalances += C.AccountBalance; 

		 }

		 return TotalBalances;

	 }

	 void Deposit(double Amount , enAddToTransactionsLog Action = enAddToTransactionsLog::eAdd )
	 {
		 _AccountBalance += Amount;	
		 Save();

		 if(Action == enAddToTransactionsLog::eAdd)
		     _RegisterAtmTransactionLog(*this, enTransactionType::eDeposit, Amount);	
	 }

	 bool WithDraw(double Amount , enAddToTransactionsLog Action = enAddToTransactionsLog::eAdd)
	 {
		 if (Amount > _AccountBalance)
			 return false;
		 else
		 {
			 _AccountBalance -= Amount;	
			 Save();

			 if (Action == enAddToTransactionsLog::eAdd)
			   _RegisterAtmTransactionLog(*this, enTransactionType::eWithdraw, Amount);
			 
		 }

	 }

	 bool Transfer(clsBankClient &ClientReceiver , double Amount , string UserName = "")
	 {
		 if (Amount > AccountBalance)
		 {
			 return false;
		 }
			
		 WithDraw(Amount , enAddToTransactionsLog::eNotAdd);
		 ClientReceiver.Deposit(Amount, enAddToTransactionsLog::eNotAdd);

		  Save();
		 _RegisterTransferLog(ClientReceiver, Amount, UserName);

		 _RegisterAtmTransactionLog(ClientReceiver, enTransactionType::eTransfer, Amount);

		 return true; 
	 }

	 static vector<stTransferLogRecord> GetTransferLogsList()
	 {
		 fstream MyFile; 
		 MyFile.open("TransferLog.txt", ios::in);

		 vector<stTransferLogRecord> vTransferLogRecords;

		 if (MyFile.is_open())
		 {
			 string Line; 
			 stTransferLogRecord TransferLogRecord; 

			 while (getline(MyFile, Line))
			 {
				 TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				 vTransferLogRecords.push_back(TransferLogRecord);
			 }

			 MyFile.close(); 
		 }

		 return vTransferLogRecords; 
	 }

	 static vector<stAtmTransactionLogRecord> GetAtmTransactionLogsList(clsBankClient Client)
	 {
		 fstream MyFile;
		 MyFile.open("AtmTransactionLog.txt", ios::in);

		 vector<stAtmTransactionLogRecord> vAtmTransferLogRecords;

		 if (MyFile.is_open())
		 {
			 string Line;
			 stAtmTransactionLogRecord TransferLogRecord;

			 while (getline(MyFile, Line))
			 {
				 TransferLogRecord = _ConvertAtmTransactionLogLineToRecord(Line);
				 if(TransferLogRecord.DestinationAccountNumber ==  Client.GetAccountNumber() || TransferLogRecord.SourceAccountNumber == Client.GetAccountNumber())
				     vAtmTransferLogRecords.push_back(TransferLogRecord);
			 }

			 MyFile.close();
		 }

		 return vAtmTransferLogRecords;
	 }

	 bool Lock()
	 {
		 if (GetMarkedForLocked())
		 {
			 return false; 
		 }

		 _MarkedForLocked = 1; 
		 _LockDate = clsDate::GetSystemDateTimeString(); 
		 Save();

		 return true; 
	 }

	 bool Unlock()
	 {
		 if (!GetMarkedForLocked())
		 {
			 return false;
		 }

		 _MarkedForLocked = 0;
		 _LockDate = "Not Locked"; 
		 Save();

		 return true;
	 }

	 static vector<clsBankClient> GetLockedClientsList()
	 {
		 vector<clsBankClient> vClients;
		 fstream MyFile;

		 MyFile.open("Clients.txt", ios::in);

		 if (MyFile.is_open())
		 {
			 string DataLine;

			 while (getline(MyFile, DataLine))
			 {
				 clsBankClient Client = _ConvertDataLineToClientObject(DataLine);

				 if (Client.GetMarkedForLocked())
				 {
					 vClients.push_back(Client);
				 }
				 
			 }

			 MyFile.close();

		 }

		 return vClients;
	 }

	 static vector<stClientMessageBox> GetClientEmailsList(clsBankClient Client)
	 {
		 fstream MyFile;
		 MyFile.open("ClientsEmails.txt", ios::in);

		 vector<stClientMessageBox> vClientMessageRecords;

		 if (MyFile.is_open())
		 {
			 string Line;
			 stClientMessageBox ClientMessageRecord;

			 while (getline(MyFile, Line))
			 {   
				 if (Line.empty())
				 {
					 MyFile.close();
					 return vClientMessageRecords;
				 }
				 
				 ClientMessageRecord = _ConvertClientMessageToRecord(Line);

				if (ClientMessageRecord.ReceiverAccountNumber == Client.GetAccountNumber())
					vClientMessageRecords.push_back(ClientMessageRecord);			
			 }

			 MyFile.close();
		 }

		 return vClientMessageRecords;
	 }


	 void SendEmail(string SenderName, string MessageTitle, string MessageBody)
	 {
		 _RegisterClientMessageLog(SenderName, MessageTitle, MessageBody);
	 }

	 static void SaveClientsEmailsListToFile(stClientMessageBox ClientMessageRecord)
	 {
		 fstream MyFile;
		 vector<stClientMessageBox> vClientsEmails = _LoadClientsEmailsListFromFile(); 

		 MyFile.open("ClientsEmails.txt", ios::out);

			 if (MyFile.is_open())
			 {
				 string Line;
				 stClientMessageBox ClientMessageRecord1;

				 for (stClientMessageBox& Message : vClientsEmails)
				 {

					 if (Message.DateTime == ClientMessageRecord.DateTime && Message.ReceiverAccountNumber == ClientMessageRecord.ReceiverAccountNumber)
					 {
						 Message.MarkedForRead = true;
					 }

					 Line = _ConvertClientMessageRecordToLine(Message);
					 MyFile << Line << endl;
				 }

				 MyFile.close();
			 }
	 }


};
