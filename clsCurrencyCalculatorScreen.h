#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

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

	static clsCurrency _GetCurrency(string Message)
	{
		
		string CurrencyCode = clsInputValidate::ReadString(); 

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Code is not found , choose a valid one : ";
			CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;
	}

	static float _ReadExchangeAmount()
	{
		cout << "\nEnter Amount to Exchange : ";
		float Amount; 
		Amount = clsInputValidate::ReadFloatNumber(); 

		return Amount;
	}

	static void _PrintCurrencyCalculatorResults(float Amount , clsCurrency C1 , clsCurrency C2)
	{
		cout << "\nConvert From : \n\n";
		_PrintCurrencyCard(C1);
		
		float ResultInUSD = C1.ConvertToUSD(Amount);
		cout << Amount << " " << C1.GetCurrencyCode() << " = " << ResultInUSD << " " << C2.GetCurrencyCode();


		if (C2.GetCurrencyCode() == "USD")
		{	
			return; 
		}

		else
		{   
			cout << "\n\nConverting from USD to  : \n\n";
			cout << "To : ";
			_PrintCurrencyCard(C2);

			float ResultInCurrency2 = C1.ConvertToOtherCurrency(Amount,C2);
			cout << Amount << " " << C1.GetCurrencyCode() << " = " << ResultInCurrency2 << " " << C2.GetCurrencyCode();
		}

	}

public:

	static void ShowCurrencyCalculatorScreen()
	{	
		char Continue = 'Y';	
		do
		{   
			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code : ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code : ");
			float Amount = _ReadExchangeAmount();

			_PrintCurrencyCalculatorResults(Amount,CurrencyFrom,CurrencyTo); 

			cout << "\n\n\nDo you want to perform another calculation ? Y/N ? ";
			cin >> Continue; 

		} while (toupper(Continue) == 'Y');


	}


};

