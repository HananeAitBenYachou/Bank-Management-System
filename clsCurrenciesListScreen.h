#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include <iostream>

using namespace std; 

class clsCurrenciesListScreen :protected clsScreen
{ 
private:

	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << setw(5) << left << "" << "| " << setw(30) << left << Currency.GetCountry();
		cout << "| " << setw(10) << left << Currency.GetCurrencyCode(); 
		cout << "| " << setw(40) << left << Currency.GetCurrencyName();
		cout << "| " << setw(15) << left << Currency.GetRate() << "|";
	}

public: 

	static void ShowCurrenciesListScreen()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList(); 

		string Title = "\t Currencies List Screen";
		string SubTitle = "\t  (" + to_string(vCurrencies.size()) + ") Currency.";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(5) << left << "" << "_______________________________________________________";
		cout << "________________________________________________\n\n";

		cout << setw(5) << left << "" << "| " << setw(30) << left << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(40) << left << "Name";
		cout << "| " << setw(15) << left << "Rate/(1$)" << "|";
		
		cout << endl; 
		cout << setw(5) << left << "" << "_______________________________________________________";
		cout << "________________________________________________\n\n";

		if (vCurrencies.size() == 0)
		{
			cout << setw(37) << left << "" << "NO CURRENCIES AVAILABLE IN THE SYSTEM !\n\n";

		}

		else
			for (clsCurrency& C : vCurrencies)
			{
				_PrintCurrencyRecordLine(C);
				cout << endl; 
			}

		cout << setw(5) << left << "" << "_______________________________________________________";
		cout << "________________________________________________\n\n";

 	}

};

