#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

const int MAX_YR = 9999;
const int MIN_YR = 1800;

class Rent
{
    string VehcileName;

public:
    void rent()
    {
        cout << "Choose a Vehcile" << endl;
        ShowVehicles(); //
        cout << "Enter Vehicle Name:";
        cin >> VehcileName;
        string content, match, temp;
        stringstream ss;
        int price;
        fstream Vehicle;
        Vehicle.open("vehicle.txt");
        while (Vehicle)
        {
            getline(Vehicle, content); // loop file lines till it end;
            if (content.find(VehcileName) != content.npos)
            {
                cout << "VEHICLE IS AVAILABLLE!!\n";
                match = content;
                ss << match;
                while (!ss.eof())
                {
                    ss >> temp;
                    if (stringstream(temp) >> price)
                    {
                        cout << "Per Day Price is:" << price << endl;
                        RentProcess(price, VehcileName); // doing next process.
                        temp = "";
                    }
                }
            }
        }
    }
    void ShowVehicles()
    {
        string content;
        fstream Vehicle;
        Vehicle.open("vehicle.txt");
        while (getline(Vehicle, content))
        {
            cout << content << endl;
        }
    }
    void RentProcess(int price, string vehicle)
    {
        int d, m, y;
        int pdate, rdate, tday, totalRent;
        cout << "Enter Pickup Date(DD MM YYYY):";
        cin >> d >> m >> y;
        pdate = checkDate(d, m, y);
        cout << "Enter Return Date(DD MM YYYY):";
        cin >> d >> m >> y;
        rdate = checkDate(d, m, y);
        if (rdate == -1 || pdate == -1)
        {
            cout << "Make sure you have entered a valid date please try again by a valid date." << endl;
        }
        else
        {
            tday = rdate - pdate;
            totalRent = price * tday;
            cout << "Total Rent Price: " << totalRent;
            fstream Rent;
            Rent.open("Rent&Ride.txt");
            Rent << vehicle << endl;   // vehicle name
            Rent << totalRent << endl; //  total rent
            Rent << pdate << endl;     // pickup date
            Rent << rdate;             // return date
            // so here we stored this data to file.
            Rent.close(); // closing file
        }
    }
    bool LeapYear(int year)
    {
        return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
    }
    int checkDate(int d, int m, int y)
    {
        if (y > MAX_YR || y < MIN_YR)
            return -1;
        if (m > 12 || m < 1)
            return -1;
        if (d > 31 || d < 1)
            return -1;
        // heandling february month
        if (m == 2)
        {
            if (LeapYear(y))
                return (d <= 29);
            else
                return (d <= 28);
        }
        if (m == 4 || m == 6 || m == 9 || m == 11)
            return (d <= 30);
        return d;
    }
};

class Main : public Rent
{
private:
    char c2;

public:
    void Welcome()
    {

        cout << "Welcome to Rent & Ride" << endl;
        cout << "Lets Start With Login Or Registration Process" << endl;
        cout << "would you like to register or login?(answer with y or n)" << endl;
        cin >> c2;
        switch (c2)
        {
        case 'y':

            Register();
            break;
        case 'n':
            Login();
            break;
        default:
            cout << "Please answer with correct options!";
            break;
        }
    }
    void Register()
    {
        int age, choice, ch;
        char name[50], gender[15];
        cout << "Enter Your Name:";
        cin >> name;
        cout << "Enter Your Age:";
        cin >> age;
        cout << "Enter Your Gender:";
        cin >> gender;
        fstream Customer;
        Customer.open("customers.txt", ios::out | ios::in);
        Customer << name << endl;
        Customer << age << endl;
        Customer << gender;
        Customer.close();

        cout << "would you like to rent a vehicle?(answer with 0 for yes or 1 for no )" << endl;
        cin >> ch;
        switch (ch)
        {
        case 0:
            rent();
            break;
        case 1:
            cout << "Thanks for using rent & ride.";
            break;
        default:
            cout << "Please answer with correct options!";
            break;
        }
    }
    void Login()
    {
        string name, loginName, gender, age;
        int choice;
        cout << "Enter Your Name:";
        cin >> name;
        loginName = GetName();
        if (name == loginName)
        {
            fstream Cs;
            Cs.open("customers.txt", ios::in);
            Cs.seekg(0, ios::beg);
            getline(Cs, name);
            getline(Cs, age);
            getline(Cs, gender);
            cout << "Name = " << name << "\nAge = " << age << "\nGender = " << gender << endl;
            cout << "Your Now logged In To System!" << endl;
            cout << "Would you like to return your vehicle or want to rent another vehicle? (answer with 1 for return or 0 for renting a vehicle):";
            cin >> choice;
            switch (choice)
            {
            case 1:
                ReturnVehicle();
                // return vehicle process
                break;
            case 0:
                rent(); // loop rent process again
                break;
            default:
                cout << "Please pick a correct option!";
            }
        }
        else
            cout << "Sorry We couldn't Find Your Data in Our system! Try Registering.";
    }
    void ReturnVehicle()
    {
        int d, m, y, pdate, rdate;
        string VehicleName;
        int PICK, RETURN, TOTALRENT;
        cout << "Enter Pickup Date(DD MM YYYY):";
        cin >> d >> m >> y;
        PICK = checkDate(d, m, y);
        cout << "Enter Return Date(DD MM YYYY):";
        cin >> d >> m >> y;
        RETURN = checkDate(d, m, y);
        fstream Rent;
        Rent.open("Rent&Ride.txt");
        Rent >> VehicleName;
        Rent >> TOTALRENT;
        Rent >> pdate;
        Rent >> rdate;
        int panelty_amount = 0;
        if(rdate == -1 || pdate == -1){
            cout << "Please Enter a Correct Date" << endl;
            _Exit(0); //Terminating program here.
        };

        if (RETURN - PICK > rdate - pdate || RETURN - PICK < rdate - pdate) // checking pick and return date is same
        {
            panelty_amount = TOTALRENT / 2;
            cout << "You are returning Vehicle after the date your Panelty is = " << panelty_amount << endl;
            TOTALRENT = TOTALRENT + panelty_amount;
            }


                cout << "Your Total Rent Amount = " << TOTALRENT << endl;
                cout << "Thanks for using Rent & Ride.";
                Rent.close();
            
    }
    string GetName()
    {
        string line;
        fstream Customer;
        Customer.open("customers.txt", ios::in);
        Customer.seekg(0, ios::beg);
        Customer >> line;
        return line;
    }
};

int main()
{
    Main m;
    m.Welcome();

    return 0;
}
