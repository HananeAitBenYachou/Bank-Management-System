#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsNormalDepositScreen : protected clsScreen
{
private:

	static float _ReadDepositAmount()
	{
		float Amount = 0; 
		cout << "\nEnter a positive Deposit Amount ? ";
		Amount = clsInputValidate::ReadFloatNumber(); 
		while (Amount <= 0)
		{
			cout << "\nInvalid Number ! Enter a positive Deposit Amount ? ";
			Amount = clsInputValidate::ReadFloatNumber();
		}

		return Amount; 
	}

public : 

	static void ShowNormalDepositScreen()
	{
		system("cls"); 
		_DrawScreenHeader("\t Deposit Screen", "", enSystemChoice::eAtmSystem);
		
		float DepositAmount = _ReadDepositAmount(); 

		char Answer = 'N';
		cout << "\nAre you sure you want to preform this transaction ? Y/N ?  ";
		cin >> Answer;


		if (toupper(Answer) == 'Y')
		{
			CurrentClient.Deposit(DepositAmount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is : " << CurrentClient.AccountBalance;

		}

		else
		{
			cout << "\nOperation was cancelled.\n";

		}

	}


};

