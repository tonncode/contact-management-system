#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include "contact.h"

using namespace std;

//Constructor
Contact::Contact(string fname1, string lname1, string email1, string primaryPhone1, string city1, string country1, bool isFav1)
{
    fname = fname1;
    lname = lname1;
    email = email1;
    primaryPhone = primaryPhone1;
    city = city1;
    country = country1;
    isFav = isFav1;
}
