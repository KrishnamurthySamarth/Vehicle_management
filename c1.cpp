#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include<limits>
#include <iomanip>
#include <regex>

using namespace std;
int nor;

void printBox(const string& text, char borderChar = '.') 
{
    int boxWidth = 80; 
    int textLength = text.length();
    int padding = (boxWidth - textLength) / 2;

    string horizontalLine(boxWidth, borderChar);

    cout << borderChar << horizontalLine << borderChar << "\n";
    cout << borderChar << setw(padding) << right << "" << text;
    cout << setw(padding) << right << borderChar << "\n";
    cout << borderChar << horizontalLine << borderChar << "\n";
}

void clearScreen() 
	{
    	#ifdef _WIN32
       	 system("cls");
    	#else
      	system("clear");
		#endif
	}

void waitForKeypress()
{
	cout<<"\033[31m"<<"\n\n\n\n\n\n\n\n\n\nPress Enter to Continue..."<<"\033[0m";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void addUnderline(const string& text, char underlineChar = '-') {
    cout << text << "\n";
    for (int i = 0; i < text.length(); i++)
        cout << underlineChar;
    cout << "\n";
}

void printCentered(const std::string& text, char underlineChar = '-', int colorCode = 36)
 {
    int terminalWidth = 130;
    int textLength = text.length();

    int padding = (terminalWidth - textLength) / 2;
    int extraPadding = (terminalWidth - textLength) % 2;

    std::string underline(textLength, underlineChar);

    cout << "\033[" << colorCode << "m";
    cout << string(padding + extraPadding, ' ') << text << "\n";
    cout << string(padding, ' ') << underline << "\n";
    cout << "\033[0m";
}

class Member \
{
public:

    char memKey[20];
    char ownerName[20];
    char ownerAddr[20];
    char phoneNumber[20];
    int balance;
    int charge;
    char regNo[10];
    char type[20];
    time_t Intime;
    time_t Outtime;
};

class vehicle : public Member 
{
public:

    void Addmem(Member m[]);
    void del(Member m[]);
    void Search(Member m[]);
    void addEntry(Member m[]);
    void ExitVehicle(Member m[]);
    void UpdateMem(Member m[]);
    void ViewAll(Member m[]);
};

void vehicle::Addmem(Member m[])
 {

    printCentered("ADD NEW MEMBERSHIP",' ',36);

    cout << "Enter Details of the Member\n\n";
     while (true)
    {
        cout << "Membership ID -> ";
        cin >> m[nor].memKey;

        if (regex_match(m[nor].memKey, regex("[0-9]+")))
            break;

        printCentered("Invalid input. Membership ID must be a numerical value. Please enter again",' ',31);
    }
    cout << "Member Name -> ";
    cin >> m[nor].ownerName;
    cout << "Address: -> ";
    cin >> m[nor].ownerAddr;
    while (true)
    {
        cout << "Phone Number: -> ";
        cin >> m[nor].phoneNumber;

        if (regex_match(m[nor].phoneNumber, regex("[0-9]{10}")))
            break;

        printCentered("Invalid input. Phone number must be a 10-digit value. Please enter again",' ',31);
    }
    m[nor].balance = 500;

   printCentered("MEMBERSHIP ADDED SUCCESSFULLY\n",' ',32);

    addUnderline("DETAILS OF MEMEBRSHIP :\n");

    cout << "Member Key        : " << m[nor].memKey << "\n";
    cout << "Owner Name        : " << m[nor].ownerName << "\n";
    cout << "Owner Address     : " << m[nor].ownerAddr << "\n";
    cout << "Phone Number      : " << m[nor].phoneNumber << "\n";
    cout << "Minimum Balance   : " << m[nor].balance << "\n";


    ofstream f1("Membership.txt", ios::out | ios::app);
    f1 << "Member Key        : " << m[nor].memKey << "\n";
    f1 << "Owner Name        : " << m[nor].ownerName << "\n";
    f1 << "Owner Address     : " << m[nor].ownerAddr << "\n";
    f1 << "Phone Number      : " << m[nor].phoneNumber << "\n";
    f1 << "Minimum Balance   : " << m[nor].balance << "\n\n";

    f1.close();

    nor++;

    waitForKeypress();
    clearScreen();
}

void vehicle::del(Member m[])
{
    string membershipID;
    bool found = false;

    cout << "Enter the Membership ID to delete: ";
    cin >> membershipID;

    for (int i = 0; i < nor; i++)
    {
        if (m[i].memKey == membershipID)
        {
            found = true;
            for (int j = i; j < nor - 1; j++)
            {
                m[j] = m[j + 1];
            }
            nor--;

            printCentered("MEMBERSHIP DELETED SUCCESSFULLY\n", ' ', 32);

            break;
        }
    }

    if (!found)
    {
        printCentered("Membership ID not found. Deletion failed.\n", ' ', 31);
    }

    waitForKeypress();
    clearScreen();
}

void vehicle::Search(Member m[]) {
     printCentered("SEARCH FOR MEMBERSHIP",' ',36);

    ifstream f1("Membership.txt", ios::in|ios::app);
    char key[10];
    cout << "Enter Membership ID to be searched -> ";
    cin >> key;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int i, flag = 0;
    for (i = 0; i < nor; i++) {
        if (strcmp(key, m[i].memKey) == 0) {
            flag = 1;

            printCentered("RECORD EXIST!!", ' ', 32);

            addUnderline("MEMBERSHIP DETAILS : \n");

            cout << "Member Key       : " << m[i].memKey << "\n";
            cout << "Owner Name       : " << m[i].ownerName << "\n";
            cout << "Owner Address    : " << m[i].ownerAddr << "\n";
            cout << "Phone Number     : " << m[i].phoneNumber << "\n";
            cout << "Minimum Balance  : " << m[i].balance << "\n";
          
            break;
        }
    }

    if (!flag) 
        {
            printCentered("RECORD NOT FOUND", ' ', 31);
        }

    f1.close();
    waitForKeypress();
    clearScreen();
}

void vehicle::addEntry(Member m[]) 
{

    printCentered("ADD NEW VEHICLE ENTRY",' ',36);

    printCentered("\n\nPlease Make sure Membership exists before proceeding to add a vehicle.\n", ' ', 31);

    ifstream f1("Membership", ios::in);
    char key[10];
    cout << "\nEnter the Membership ID to which the vehicle should be added ->";
    cin >> key;

    int i, c,flag=0;
    for (i = 0; i < nor; i++) {
        if (strcmp(key, m[i].memKey) == 0) 
        {
            flag=1;

            addUnderline("Enter Vehicle Details : \n\n");

            int tp;
            cout << "Registration Number -> ";
            cin >> m[i].regNo;
            cout<<"Choose the type Of Vehicle -> \n";
            cout<<"1.Two-Wheeler\n2.Three-Wheeler\n3.Four-Wheeler\n4.Bicycle\n";
            cin>>tp;
           switch(tp)
           {
            case 1 :strcpy(m[i].type,"Two-Wheeler");
                    break;
            case 2 :strcpy(m[i].type,"Three-Wheeler");
                    break;
            case 3 :strcpy(m[i].type,"Four-Wheeler");
                    break;
            case 4 :strcpy(m[i].type,"Bicycle");
                    break;
           }       
            m[i].Intime = time(0);
            char* t = ctime(&(m[i].Intime));

            addUnderline("VEHICLE DETAILS : ");

            cout << "MEMBER KEY      : " << m[i].memKey << "\n";
            cout << "REG NO          : " << m[i].regNo << "\n";
            cout << "TYPE            : " << m[i].type << "\n";
            cout << "TIME-IN         : " << t << "\n";
           
            ofstream f2("Vehicle.txt", ios::out | ios::app);

            f2 << "MEMBER KEY   : " << m[i].memKey << "\n";
            f2 << "REG NO       : " << m[i].regNo << "\n";
            f2 << "TYPE         : " << m[i].type << "\n";
            f2 << "TIME-IN      : " << t << "\n";

            printCentered("SUCCESSFULLY ADDED", ' ', 36);

            f2.close();
        }  
    }
    if(!flag)
        {
            printCentered("NO RECORD EXIST", ' ', 31);
        }

    f1.close();
    waitForKeypress();
    clearScreen();
}

void vehicle::ExitVehicle(Member m[])
 {

    printCentered("REMOVE VEHICLE",' ',36);

    char key[10];
    cout << "Enter Membership ID to view the transaction -> ";
    cin >> key;
	int c;
    fstream f2("Vehicle.txt", ios::out | ios::app | ios::in);
    for (int i = 0; i < nor; i++) {
        if (strcmp(key, m[i].memKey) == 0) {
            cout << "\nMEMBER KEY: " << m[i].memKey << ", REG NO: " << m[i].regNo << "\n";
            cout << "\nPROCEED WITH ABOVE DETAILS?\n\n";
            cout << "1. Yes\t";
            cout << "2. No\n";
            cin >> c;
            if (c == 1) {
                m[i].Outtime = time(0);
                char* t = ctime(&(m[i].Outtime));
                f2<<"OUT-TIME     : "<<t<<"\n";
                int duration = difftime(m[i].Outtime, m[i].Intime);
                int hr = duration / 3600;
                if (strcmp(m[i].type, "Two-Wheeler") == 0) {
                    if (hr == 0)
                        m[i].charge = 20;
                    else
                        m[i].charge = 20 * hr;
                } else if (strcmp(m[i].type, "Three-Wheeler") == 0) {
                    if (hr == 0)
                        m[i].charge = 40;
                    else
                        m[i].charge = 40 * hr;
                } else if (strcmp(m[i].type, "Four-Wheeler") == 0) {
                    if (hr == 0)
                        m[i].charge = 50;
                    else
                        m[i].charge = 50 * hr;
                } else if (strcmp(m[i].type, "Bicycle") == 0) {
                    if (hr == 0)
                        m[i].charge = 10;
                    else
                        m[i].charge = 10 * hr;
                }

                printCentered("VEHICLE REMOVED SUCCESSFULLY", ' ', 32);

                addUnderline("VEHICLE DETAILS : \n");

                cout << "MEMBER KEY     : " << m[i].memKey << "\n";
                cout << "REG NO         : " << m[i].regNo << "\n";
                cout << "TYPE           : " << m[i].type << "\n";
                cout << "OUT_TIME       : " << t << "\n";
                cout << "Duration       : " << hr << " Hours"<< "\n";
                cout << "Charge Rupees  : " << m[i].charge << "\n";

            } 
        else
        {
            printCentered("TRANSACTION UNSUCCESSFULL - NO RECORD EXIST", ' ', 31);
            exit(0);
        }
        }
    }

    f2.close();
    waitForKeypress();
    clearScreen();
}

void vehicle::UpdateMem(Member m[]) {
    fstream f1("Membership.txt", ios::in | ios::out);

    char key[10];
    char tem1[200];

    for (int i = 0; i < nor; i++) {
        f1.getline(tem1, 200, '|');
        strcpy(key, m[i].memKey);

        for (int j = 0; j < nor; j++) {
            fstream f2("vehicle.txt", ios::in);

            if (strcmp(key, m[j].memKey) == 0) {
                m[i].balance = m[i].balance - m[j].charge;
            } else {
                j++;
            }

            f2.close();
        }

        i++;
    }
}

void vehicle::ViewAll(Member m[]) {
    fstream f1("Membership.txt", ios::in | ios::out);
    ofstream f3("Transaction.txt", ios::out|ios::app);

    char key[10];
    char tem1[200];

    for (int i = 0; i < nor; i++) 
    {
        f1.getline(tem1, 200, '|');
        strcpy(key, m[i].memKey);

                printCentered("ALL TRANSACTIONS IN THIS CENTER :\n",'-',36);

        for (int j = 0; j < nor; j++) {
            fstream f2("Vehicle.txt", ios::in);

            if (strcmp(key, m[j].memKey) == 0) {
                f3<<"MEMBER KEY      :"<< m[i].memKey<<"\n";
                f3<<"OWNER NAME      :"<< m[i].ownerName<<"\n";
                f3<<"oWNER ADDRESS   :"<<m[i].ownerAddr<<"\n";
                f3<<"VEHICLE TYPE    :"<< m[i].type<<"\n";
                f3<<"BALANCE         :"<<m[i].balance<<"\n";

                cout<<"Transaction "<<(i+1)<<":\n";
                cout<<"MEMBER KEY    :"<< m[i].memKey<<"\n" ;
                cout<<"OWNER NAME    :"<< m[i].ownerName<<"\n";
                cout<<"OWNER ADDRESS :"<<m[i].ownerAddr<<"\n";
                cout<<"VEHICLE TYPE  :"<< m[i].type<<"\n";
                cout<<"BALANCE       :"<<m[i].balance<<"\n";
                cout<<"\n";
            } else {
                j++;
            }

            f2.close();
        }
        f3.close();
        i++;
    }
    waitForKeypress();
    clearScreen();
}


int main() 
{
    Member m[100];
    vehicle V;
    int ch;

	clearScreen();

    printCentered("WELCOME  TO PARKING LOT SYSTEM", '-', 36);

    waitForKeypress();
    clearScreen();

    printBox("Our Price Board:");
    printBox("1. Two Wheeler: Rs.20 per hour");
    printBox("2. Three Wheeler: Rs.40 per hour");
    printBox("3. Four Wheeler: Rs.50 per hour");
    printBox("4. Bicycle: Rs.10 per hour");
    cout << "\n\n\nP.S: Each of the above is also the minimum charge when the vehicle is entered.\n";

    waitForKeypress();
    clearScreen();

    do {
        printBox("1.Add New Membership");
        printBox("2.Search Member");
        printBox("3.Add Vehicle");
        printBox("4.Exit Vehicle");
        printBox("5.Delete  Membership");
        printBox("6.View All Transactions");
        printBox("7.Exit");
        cout<<"\n\nChoose any option to continue ->  ";
        cin >> ch;

        switch (ch) {
            case 1:
				clearScreen();
                V.Addmem(m);
                break;
            case 2:
				clearScreen();
                V.Search(m);
                break;
            case 3:
				clearScreen();
                V.addEntry(m);
                break;
            case 4:
				clearScreen();
                V.ExitVehicle(m);
				V.UpdateMem(m);
                break;
            case 5:
                clearScreen();
                V.del(m);
            case 6:
				clearScreen();
                V.ViewAll(m);
                break;
            case 7:
                exit(0);
                break;
            default:
                cout << "Invalid Choice!!";
                break;
        }
    } while (ch != 6);

    return 0;
}
