#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iostream> 
#include <iomanip>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
    enum enCurrencyExchangeMenueOptions
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4,
        eShowMainMenue = 5,
    };
    
    static short _ReadCurrencyExchangeMenueOption()
    {
        short Choice;

        cout << setw(37) << left << "" << "choose what do you want to do ? [1 to 5] ? ";
        Choice = clsInputValidate::ReadShortNumberBetween(1, 5,"Enter a number [1 to 5] : ");

        return Choice;
    }

    static void _ShowCurrenciesListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();

    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen(); 
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen(); 
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen(); 
    }

    static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeMenueOptions CurrencyExchangeMenueOption)
    {
        switch (CurrencyExchangeMenueOption)
        {
        case enCurrencyExchangeMenueOptions::eListCurrencies:
            system("cls");
            _ShowCurrenciesListScreen(); 
            _GoBackToCurrencyExchangeMenue();
            break; 

        case enCurrencyExchangeMenueOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen(); 
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOptions::eUpdateCurrencyRate:
            system("cls");
            _ShowUpdateCurrencyRateScreen(); 
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen(); 
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOptions::eShowMainMenue:
        {

        }

        }
    }

    static void _GoBackToCurrencyExchangeMenue()
    {
        cout << setw(37) << left << "" << "Press Any Key To Go Back To Currency Exchange Main Menue ... ";
        system("pause>0");
        ShowCurrencyExchangeMenue(); 
    }

public : 

	static void ShowCurrencyExchangeMenue()
	{
		system("cls");
		_DrawScreenHeader("    Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t        Currency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[1] List Currencies.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[2] Find Currency.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[3] Update Currency.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[4] Currency Calculator.\033[0m\n";
        cout << setw(37) << left << "" << "\t\033[1;32m[5] Main Menue.\033[0m\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyExchangeMenueOption((enCurrencyExchangeMenueOptions)_ReadCurrencyExchangeMenueOption());
	}

};

