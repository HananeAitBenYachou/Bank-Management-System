#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std; 

class clsCurrency : protected clsScreen
{

private : 

	static clsCurrency _ConvertDataLineToCurrencyObject(string DataLine , string Seperator = "#//#")
	{
		vector<string> vCurrencyData; 
		vCurrencyData = clsString::Split(DataLine, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyRecordToDataLine(clsCurrency Currency , string Seperator = "#//#")
	{
		string stCurrencyDataLine = ""; 
		
		stCurrencyDataLine += Currency.GetCountry() + Seperator;
		stCurrencyDataLine += Currency.GetCurrencyCode() + Seperator;
		stCurrencyDataLine += Currency.GetCurrencyName() + Seperator;
		stCurrencyDataLine += to_string(Currency.Rate);

		return stCurrencyDataLine;
	
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile()
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		vector<clsCurrency> vCurrencies; 

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertDataLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}

			MyFile.close(); 
		}
		return vCurrencies; 
	}

	static void _SaveCurrenciesDataToFile(vector<clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt",ios::out);

		if (MyFile.is_open())
		{
			string Line;
			for (clsCurrency& Currency : vCurrencies)
			{
				MyFile << _ConvertCurrencyRecordToDataLine(Currency) << endl; 
			}

			MyFile.close();
		}

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : vCurrencies)
		{
			if (C.GetCurrencyCode() == clsString::UpperAllString(_CurrencyCode))
			{
				C = *this;
				_SaveCurrenciesDataToFile(vCurrencies);

			}
		}
	}


	enum enMode {EmptyMode = 1, UpdateMode = 2};

	string _Country; 
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate; 
	enMode _Mode; 

public : 

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string GetCountry()
	{
		return _Country;
	}

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	string GetCurrencyName()
	{
		return _CurrencyName; 
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		 _Update(); 
	}

	float GetRate()
	{
		return _Rate;
	}
	
	__declspec(property (get = GetRate,  put = SetRate)) float Rate;

	static clsCurrency FindByCountry(string CurrencyCountry)
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile(); 

		CurrencyCountry = clsString::UpperAllString(CurrencyCountry);

		for (clsCurrency& C : vCurrencies)
		{
			if (clsString::UpperAllString(C.GetCountry()) == CurrencyCountry)
			{
				return C;
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		for (clsCurrency& C : vCurrencies)
		{
			if (C.GetCurrencyCode() == CurrencyCode)
			{
				return C;
			}
		}

		return _GetEmptyCurrencyObject();
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);

		return !Currency.IsEmpty(); 
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile(); 
	}

	float ConvertToUSD(float Amount)
	{
		return float(Amount / _Rate);
	}

	float ConvertToOtherCurrency(float Amount , clsCurrency C2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (C2.GetCurrencyCode() == "USD")
		{
			return AmountInUSD; 
		}

		return float(AmountInUSD * C2.Rate);
	}


};

