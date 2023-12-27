#pragma once
#include <iostream> 
#include "clsUser.h"
#include "clsDate.h"
#include "Global.h"
#include <cstdlib>

using namespace std;

class clsScreen
{
protected : 

    enum enSystemChoice {eBankSystem = 1 , eAtmSystem = 2 ,eNone = 3};

    static void _DrawScreenHeader(string Title, string SubTitle = "" , enSystemChoice SystemChoice = enSystemChoice::eBankSystem)
    {
        cout << "\t\t\t\t\t\033[1;35m______________________________________\033[0m";
        cout << "\n\n\t\t\t\t\t " << "\033[1;35m" << Title << "\033[0m";

        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  "<<"\033[1;35m" << SubTitle << "\033[0m\n";
        }
        cout << "\n\t\t\t\t\t\033[1;35m______________________________________\033[0m\n\n";

        if (SystemChoice == enSystemChoice::eBankSystem)
        {
            cout << "\t\t\t\t\t\033[1;34mUser : \033[0m" << "\033[3;42;30m" << CurrentUser.UserName << "\033[0m\n";
            cout << "\t\t\t\t\t\033[1;34mDate : \033[0m" << "\033[3;43;30m" << clsDate::GetSystemDateTimeString() << "\033[0m\n\n";

        }

        else if(SystemChoice == enSystemChoice::eAtmSystem)
        {
            cout << "\t\t\t\t\t\033[1;34mClient : \033[0m" << "\033[3;42;30m" << CurrentClient.GetAccountNumber() << "\033[0m\n";
            cout << "\t\t\t\t\t\033[1;34mDate   : \033[0m" << "\033[3;43;30m" << clsDate::GetSystemDateTimeString() << "\033[0m\n\n";

        }

        if (SystemChoice == enSystemChoice::eNone)
        {
            cout << "\t\t\t\t\t\033[1;34mDate   : \033[0m" << "\033[3;43;30m" << clsDate::GetSystemDateTimeString() << "\033[0m\n\n";

        }
 
    }

    static bool _CheckAccessRights(clsUser::enPermissions Permissions)
    {
        if (!CurrentUser.CheckAccessPermission(Permissions))
        {
            cout << "\t\t\t\t\t________________________________________";
            cout << "\n\n\t\t\t\t\t   Access Denied ! Contact Your Admin.";
            cout << "\n\t\t\t\t\t________________________________________\n\n";

            return false;
        }

        else
            return true; 
    }

};

