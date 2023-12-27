#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsCurrency.h"
class clsUpdateCurrencyRateScreen :protected clsScreen
{
private :

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n\t~~~ Currency Card ~~~ ";
		cout << "\n======================================\n";
		cout << "\nCountry      : " << Currency.GetCountry();
		cout << "\nCode         : " << Currency.GetCurrencyCode();
		cout << "\nName         : " << Currency.GetCurrencyName();
		cout << "\nRate(1$) =   : " << Currency.GetRate();
		cout << "\n\n======================================\n\n";
	}

	static float _ReadNewRate()
	{
		float NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

public : 

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t Update Currency Screen");

		string CurrencyCode = ""; 
		cout << "\nPlease Enter Currency Code : "; 
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Code is not found , choose a valid one : ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		char Answer = 'Y';
		cout << "\nAre you sure you want to update the rate of this Currancy ? Y/N ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\n\n<~~~ Update Currency Rate : ~~~>\n";
			cout << "\nEnter New Rate : ";
					 
			Currency.UpdateRate(_ReadNewRate());
			
			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrencyCard(Currency);
			
		}

		else
			cout << "\nOperation was cancelled ! ";

	}
};

