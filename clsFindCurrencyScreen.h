#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsCurrency.h"
class clsFindCurrencyScreen : protected clsScreen
{
private : 

	enum enFindByChoices {eByCode = 1, eByCountry = 2};

	static enFindByChoices _ReadFindByChoice()
	{
		short Choice;
		cout << "\nFind By : [1] Code or [2] Country ? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 2);

		return (enFindByChoices) Choice;
	}

	static string _ReadCurrencyCode()
	{
		cout << "\n\nPlease Enter Currency Code : ";
	   
		string Code = clsInputValidate::ReadString();

		return Code; 
	}

	static string _ReadCountry()
	{
		cout << "\n\nPlease Enter Country Name : ";

		string CountryName = clsInputValidate::ReadString();

		return CountryName;
	}

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

	static void _ShowResults(clsCurrency Currency)
	{

		if (!Currency.IsEmpty())
		{
			cout << "\n\nCurrency Found :-)\n";
			_PrintCurrencyCard(Currency);
		}

		else
		{
			cout << "\n\nCurrency Was Not Found :-(\n";
		}
	}

public : 

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");

		enFindByChoices Choice = _ReadFindByChoice(); 

		switch (Choice)
		{
		case enFindByChoices::eByCode:
		{
			string CurrencyCode = _ReadCurrencyCode();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);		
			_ShowResults(Currency); 
			break; 
		}

		case enFindByChoices::eByCountry:
		{
			string Country = _ReadCountry(); 
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
			break;
		}
		}
	}
};

