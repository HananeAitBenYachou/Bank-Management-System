#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 2, AddNewMode = 3 };
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	static clsUser _ConvertDataLineToUserObject(string DataLine, string Seperator = "#//#")
	{
		vector<string> vUserData = clsString::Split(DataLine, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

	}

	static string _ConvertUserObjectToDataLine(clsUser User, string Seperator = "#//#")
	{
		string stUserData;

		stUserData += User.FirstName + Seperator;
		stUserData += User.LastName + Seperator;
		stUserData += User.Email + Seperator;
		stUserData += User.Phone + Seperator;
		stUserData += User.UserName + Seperator;
		stUserData += clsUtil::EncryptText(User.Password) + Seperator;
		stUserData += to_string(User.Permissions);

		return stUserData;
	}

	static vector<clsUser> _LoadUsersDataFromFile(string Seperator = "#//#")
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		vector<clsUser> vUsers;

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertDataLineToUserObject(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;

			for (clsUser& User : vUsers)
			{
				if (!User.MarkedForDeleted())
				{
					Line = _ConvertUserObjectToDataLine(User);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User._UserName == _UserName)
			{
				User = *this;
				_SaveUsersDataToFile(vUsers);
				break;
			}
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToDataLine(*this));

	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector<string> vLoginRegisterData = clsString::Split(Line, Seperator);

		LoginRegisterRecord.DateTime = vLoginRegisterData[0];
		LoginRegisterRecord.UserName = vLoginRegisterData[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterData[2]);
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterData[3]);

		return LoginRegisterRecord;
	}

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string stLoginRecord = "";

		stLoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		stLoginRecord += UserName + Seperator;
		stLoginRecord += clsUtil::EncryptText(Password) + Seperator;
		stLoginRecord += to_string(Permissions);

		return stLoginRecord;
	}

public:

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		short Permissions;
	};

	enum enPermissions
	{
		eAll = -1, pListClients = 1, pAddNewClient = 2,
		pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16,
		pTransactions = 32, pManageUsers = 64 , pShowLogInRegister = 128
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsUser Find(string UserName)
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				return User;

			}
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName && User.Password == Password)
			{
				return User;
			}
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResults { svFailedEmptyObject = 1, svSucceeded = 2, svFailedUserExists = 3 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode():
		{
			if (IsEmpty())
			{
				return enSaveResults::svFailedEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}

		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFailedUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}

		}
	}

	static clsUser GetAddNewUserObject(string Username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool Delete()
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == _UserName)
			{
				User._MarkedForDelete = true;
				_SaveUsersDataToFile(vUsers);
				*this = _GetEmptyUserObject();

				return true;
			}
		}

		return false;
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		else if ((this->Permissions & Permission) == Permission)
			return true;

		else
			return false;
	}

	void RegisterLogIn()
	{
		fstream MyFile;
		string DataLine = _PrepareLogInRecord();

		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord> vLoginRegisterRecord;
		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			MyFile.close(); 
		}

		return vLoginRegisterRecord;
	}

};

