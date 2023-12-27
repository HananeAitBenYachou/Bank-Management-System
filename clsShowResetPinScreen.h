#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "Global.h"
#include <Windows.h>

class clsShowResetPinScreen : protected clsScreen
{
private:

	static void _ShowTimer(short NumberOfMinutes)
	{
		int Seconds = 0;

		while (NumberOfMinutes >= 0)
		{   
			system("cls");
			cout << "\n" << setw(33) << left << "" << "\033[1;31mYour are locked after choosing wrong answer :-(\033[0m" << endl;
			cout << "\n" << setw(45) << left << "" <<"\033[1;3;32mPlease wait a minute ... \033[0m\n\n";

			if (NumberOfMinutes >= 10)
			{
				if (Seconds >= 10)
				{
					cout << setw(50) << left << "" << "\033[1;91m" << char(201) << "\t      " << char(187) << "\n";
					cout << setw(50) << left << "" << "   \033[1;91m" << NumberOfMinutes << " : " << Seconds << "\033[0m\n";
					cout << setw(50) << left << "" << "\033[1;91m" << char(200) << "\t      " << char(188) << "\n";
				}


				else
				{
					cout << setw(50) << left << "" << "\033[1;91m" << char(201) << "\t      " << char(187) << "\n";
					cout << setw(50) << left << "" << "   \033[1;91m" << NumberOfMinutes << " : 0" << Seconds << "\033[0m\n";
					cout << setw(50) << left << "" << "\033[1;91m" << char(200) << "\t      " << char(188) << "\n";

				}

			}

			else
			{
				if (Seconds >= 10)
				{
					cout << setw(50) << left << "" << "\033[1;91m" << char(201) << "\t      " << char(187) << "\n";
					cout << setw(50) << left << "" << "   \033[1;91m" << "0" << NumberOfMinutes << " : " << Seconds << "\033[0m\n";
					cout << setw(50) << left << "" << "\033[1;91m" << char(200) << "\t      " << char(188) << "\n";
				}

				else
				{
					cout << setw(50) << left << "" << "\033[1;91m" << char(201) << "\t      " << char(187) << "\n";
					cout << setw(50) << left << "" << "   \033[1;91m" << "0" << NumberOfMinutes << " : 0" << Seconds << "\033[0m\n";
					cout << setw(50) << left << "" << "\033[1;91m" << char(200) << "\t      " << char(188) << "\n";
				}
			}


			if (Seconds == 0)
			{
				Seconds = 60;
				NumberOfMinutes--;
			}

			Seconds--;
			Sleep(1000);
	
		}
	}

	static string _ReadClientEmail()
	{
		string Email; 
		cout << "\nPlease Enter Your Email To Verify Your Identity ! "; 
		Email = clsInputValidate::ReadString(); 
		
		return Email; 
	}

	static void _ReadNewPinCode()
	{
		
		string PinCode = "";

		cout << "\nPlease Enter The New PinCode : ";
		PinCode = clsInputValidate::ReadString();

		while (PinCode.size() <= 2)
		{
			cout << "\nThe new password you provided is weak and can be easily guessed. Please choose a stronger password : ";
			PinCode = clsInputValidate::ReadString();
		}

		CurrentClient.PinCode = PinCode; 
		clsBankClient::enSaveResults SaveResult; 
		SaveResult = CurrentClient.Save();

			 
	}

	static void _AskAndVerifyAccountBalanceOption()
	{
		system("cls");
		_DrawScreenHeader("\t  Reset Pin Screen", "", enSystemChoice::eNone);

		clsUtil::Srand();

		double arr[4]; 
		arr[3] = CurrentClient.AccountBalance;

		clsUtil::FillArrayWithRandomNumbers(arr, 3, 1000, 10000);
		clsUtil::ShuffleArray(arr, 4);

		short RightAnswerPos = clsUtil::FindNumberPositionInArray(arr, 4, CurrentClient.AccountBalance);

		cout << "\n\nWhat Is Your Balance ? You have one chance to choose the correct answer otherwise you will be blocked ! \n\n";
		
		cout << "\033[1;3;32m~~~~ [Options] ~~~~\033[0m\n";
		cout << "\033[1;32m=======================\033[0m\n";
		cout << "\033[1;3;36m1) " << arr[0] << "\033[0m " << endl;
		cout << "\033[1;3;35m2) " << arr[1] << "\033[0m " << endl;
		cout << "\033[1;3;91m3) " << arr[2] << "\033[0m " << endl;
		cout << "\033[1;3;94m4) " << arr[3] << "\033[0m " << endl;
		cout << "\033[1;32m=======================\033[0m\n";

		cout << "\n\033[1;32mchoose [1 to 4] ==> \033[0m ";

		short Answer;
		cin >> Answer; 

		if ((Answer-1) == RightAnswerPos)
		{
			//Ask to enter new pin ;
			cout << "\n\n\033[1;32mCorrect Answer :-) \033[0m \n\n"; 
			_ReadNewPinCode(); 

			cout << "\n\n\033[1;32mYour PineCode Is Updated Successfully ! \033[0m\n"; 

			CurrentClient = clsBankClient::Find(""); 
			return; 

		}

		else
		{
			
			//Add it to blockedclients
			CurrentClient.Lock(); 
			//showtimer;
			_ShowTimer(1);
			return; 
		}

	}

	static void _ResetPinScreen()
	{
		string Email = "";

		bool EmailIsNotValid = false;
		short FailedTrails = 0;
		do
		{
			system("cls");
			_DrawScreenHeader("\t  Reset Pin Screen", "", enSystemChoice::eNone);

			if (EmailIsNotValid)
			{
				FailedTrails++;
				cout << "\n" << "\033[1;31mInvalid Email Addrress ! \033[0m" << endl;
				cout << "You have " << (3 - FailedTrails) << " Trails to login.\n";
			}

			if (FailedTrails == 3)
			{
				_ShowTimer(1); 
				return;
			}

			Email = _ReadClientEmail();

			CurrentClient = clsBankClient::FindByEmail(Email);
			EmailIsNotValid = CurrentClient.IsEmpty();

		} while (EmailIsNotValid);

		_AskAndVerifyAccountBalanceOption(); 
	}

public :

	static void ShowResetPinScreen()
	{

		char Answer = 'Y';
		cout << "\n\n" << setw(35) << left << "" << "\033[4;3;5;31m Forgot Your Password ? \033[0m  ";	
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			_ResetPinScreen(); 
			return; 
		}

		else
		{
			return; 
		}
	}

};

