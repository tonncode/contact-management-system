#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include "contactbst.h"
#include "myvector.h"
#include "contact.h"

using namespace std;

//constructor of Node class
Node::Node(string key, MyVector<Contact>* contactVector)
{
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
    this->contactVector = contactVector;
}

//constructor
ContactBST::ContactBST()
{
    this->root=nullptr;
    this->size = 0;
}

//destructor
ContactBST::~ContactBST()
{
    while(root != nullptr)
    {
        root = del(root,root->key);//removing all nodes
    }
}

//before moving to inserting process, this function collects contact attributes
void ContactBST::insert_collection()
{
    string fname, lname, email, primaryPhone, city, country;
    char isfavourite;
    bool phone_error = false, email_error = false, fname_error = false, lname_error = false, city_error = false, country_error = false;
    bool isFav;
    string check = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout<<"Please enter the details of the contact"<<endl;
    
    //cheking firstname entered
    do
    {
        cout<<"First Name: ";
        cin>>fname;
        fname_error = false;
        if (fname.length() <= 1)
        {
            cout<<"Firstname cannot be only 1 character"<<endl;
            fname_error = true;
        }
        for(int i=0; i<fname.length(); ++i)
        {
            if(isalpha(fname[i]) == false)
            {
                cout<<"Name consists only letters"<<endl;
                fname_error = true;
                break;
            }
        }
    }
    while(fname_error);

    do
    {
        cout<<"Last Name: ";
        cin>>lname;
        lname_error = false;
        if (lname.length() <= 1)
        {
            cout<<"Lastname cannot be only 1 character"<<endl;
            lname_error = true;
        }
        for(int i=0; i<lname.length(); ++i)
        {
            if(isalpha(lname[i]) == false)
            {
                cout<<"Name consists only letters"<<endl;
                lname_error = true;
                break;
            }
        }
        
    }
    while(lname_error);
    
    do
    {
        cout<<"Email: ";
        cin>>email;
        email_error = true;
        int sign = -1;
        for (int i=0; i<email.length(); ++i)
        {
            if (i != email.length() - 1 && i != 0 && email[i] == '@')
            {
                sign = i;
                email_error = false;
            }
            if (i != email.length() - 1 && i != 0 && email[i] == '.')
            {
                email_error = false;
            }
            if (i != email.length() - 1) {
                if (email[i] == '@' && email[i+1] == '.')
                {
                    email_error = true;
                }
                if (email[i] == '.' && email[i+1] == '@')
                {
                    email_error = true;
                }
            }
        }
        email_error = true;
        for (int i=0; i<email.length(); ++i)
        {
            if (i != email.length() - 1 && i != 0 && email[i] == '.')
            {
                if (i > sign) {
                    email_error = false;
                }
            }
        }
        if (email.length() <= 4 || email_error == true)
        {
            cout<<"Invalid email. Example: qwerty@gmail.com"<<endl;
            email_error = true;
        }
    }
    while(email_error);
    
    do
    {
        cout<<"Phone#: ";
        cin>>primaryPhone;
        phone_error = false;
        for (int i=0; i<primaryPhone.length(); ++i)
        {
            if (!isdigit(primaryPhone[i]))
            {
                phone_error = true;
                cout<<"Phone number cantains only digits"<<endl;
                break;
            }
        }
        if (primaryPhone.length() <= 4)
        {
            phone_error = true;
            cout<<"Phone number cannot be only 4 digits"<<endl;
        }
    }
    while(phone_error);
    
    do
    {
        cout<<"City: ";
        cin>>city;
        city_error = false;
        if (city.length() <= 2)
        {
            cout<<"City name cannot be only 2 characters"<<endl;
            city_error = true;
        }
        for(int i=0; i<city.length(); ++i)
        {
            if(isalpha(city[i]) == false)
            {
                cout<<"City Name consists only letters"<<endl;
                city_error = true;
                break;
            }
        }
        
    }
    while(city_error);
    
    do
    {
        cout<<"Country: ";
        cin>>country;
        country_error = false;
        if (country.length() <= 2)
        {
            cout<<"Country name cannot be only 2 characters"<<endl;
            country_error = true;
        }
        for(int i=0; i<country.length(); ++i)
        {
            if(isalpha(country[i]) == false)
            {
                cout<<"Country Name consists only letters"<<endl;
                country_error = true;
                break;
            }
        }
    }
    while(country_error);
    
    do
    {
        cout<<"Do you want to add the contact in your favourites (y/n): ";
        cin>>isfavourite;
        if (isfavourite == 'y')
        {
            isfavourite = true;
            break;
        }
        else if(isfavourite == 'n')
        {
            isfavourite = false;
            break;
        }
        else
        {
            cout<<"Error: Invalid input"<<endl;
        }
    }
    while(true);
    
    if(isfavourite)
    {
        isFav = true;
    }
    else
    {
        isFav = false;
    }
    
    string key = fname + " " + lname;
    Contact* data = new Contact(fname,lname,email,primaryPhone,city,country,isFav);
    insert_helper(key, data);
}

// update root when adding new contacts
void ContactBST::insert_helper(string key, Contact *data)
{
    root = add(root, key, data);
    size = size + 1;
}

//adding a new contact by passing the contact's key and attributes as arguments
Node* ContactBST::add(Node *ptr, string key, Contact *data)
{
    if(ptr == nullptr)
    {
        MyVector<Contact>* contactVector = new MyVector<Contact>;
        contactVector->push_back(data);
        cout<<"Contact "<<key<<" has successfully been added!"<<endl;
        return new Node(key, contactVector);
    }
    
    int c = key.compare(ptr->key);
    
    if (key == ptr->key)
    {
        ptr->contactVector->push_back(data);
        cout<<"Contact "<<ptr->key<<" has successfully been added!"<<endl;
        return ptr;
    }
    else if (c < 0)
    {
        if(ptr->left == nullptr)
        {
            MyVector<Contact>* contactVector = new MyVector<Contact>;
            contactVector->push_back(data);
            ptr->left = new Node(key, contactVector);
            cout<<"Contact "<<ptr->left->key<<" has successfully been added!"<<endl;
            return ptr;
        }
        else
        {
            ptr->left = add(ptr->left, key, data);
        }
    }
    else
    {
        if(ptr->right == nullptr)
        {
            MyVector<Contact>* contactVector = new MyVector<Contact>;
            contactVector->push_back(data);
            ptr->right = new Node(key, contactVector);
            cout<<"Contact "<<ptr->right->key<<" has successfully been added!"<<endl;
            return ptr;
        }
        else
        {
            ptr->right = add(ptr->right, key, data);
        }
    }
    return ptr;
}

// update root when removing contacts
void ContactBST::remove_helper(string key)
{
    root = del(root, key);
}

//deleting a contact by its key, if there are several contacts with the same key, the user himself will choose which contact to delete
Node* ContactBST::del(Node *ptr, string key)
{
    if(!findKey(root, key))
    {
        cout<<"No contact found with a key "<<key<<endl;
        return root;
    }
    
    int c = key.compare(ptr->key);
    
    if(c != 0)
    {
        if(c < 0)
        {
            ptr->left = del(ptr->left, key);
        }
        else
        {
            ptr->right = del(ptr->right, key);
        }
    }
    else if(ptr->contactVector->size() > 1)
    {
        cout<<ptr->contactVector->size()<<" record(s) found:"<<endl;
        for (int i=0; i<ptr->contactVector->size(); ++i)
        {
            char isfavourite = '0';
            if(ptr->contactVector->at(i)->isFav)
            {
                isfavourite = '1';
            }
            cout<<i+1<<". " + ptr->contactVector->at(i)->fname + ", "+ptr->contactVector->at(i)->lname+", "+ptr->contactVector->at(i)->email+", "+ptr->contactVector->at(i)->primaryPhone+", "+ptr->contactVector->at(i)->city+", "+ptr->contactVector->at(i)->country<<endl;
        }
        string recordnumber;
        cout<<"Please select the record you want to delete: ";
        cin>>recordnumber;
        for (int i=0; i<recordnumber.length(); ++i)
        {
            if (!isdigit(recordnumber[i]))
            {
                cout<<"Invalid input. Try again..."<<endl;
                return ptr;
            }
        }
        int record = stoi(recordnumber);
        ptr->contactVector->erase(record - 1);
        cout<<"The contact record has successfully been deleted!"<<endl;
    }
    else
    {
        cout<<ptr->contactVector->size()<<" record found:"<<endl;
        char isfavourite = '0';
        if(ptr->contactVector->at(0)->isFav)
        {
            isfavourite = '1';
        }
        cout<<"1. " + ptr->contactVector->at(0)->fname + ", "+ptr->contactVector->at(0)->lname+", "+ptr->contactVector->at(0)->email+", "+ptr->contactVector->at(0)->primaryPhone+", "+ptr->contactVector->at(0)->city+", "+ptr->contactVector->at(0)->country<<endl;
        
        if(ptr->left == NULL && ptr->right == NULL)
        {
            ptr = nullptr;
            cout<<endl<<"The contact record has successfully been deleted!"<<endl;
        }
        else if(ptr->left != NULL && ptr->right == NULL)
        {
            ptr = ptr->left;
            cout<<endl<<"The contact record has successfully been deleted!"<<endl;
        }
        else if(ptr->left == NULL && ptr->right != NULL)
        {
            ptr = ptr->right;
            cout<<endl<<"The contact record has successfully been deleted!"<<endl;
        }
        else if(ptr->left != NULL && ptr->right != NULL)
        {
            string min = ptr->right->key;
            Node* minptr = findMinRight(ptr->right);
            string minkey = minptr->key;
            MyVector<Contact>* mincontactVector = minptr->contactVector;
            ptr->right = del(ptr->right, minkey);
            ptr->key = minkey;
            ptr->contactVector = mincontactVector;
            cout<<endl<<"The contact record has successfully been deleted!"<<endl;
        }
    }
    
    return ptr;
}

//when a node has two children (left and right), it will be removed by replacing it with the minimum node on the right side (according to the key)
Node* ContactBST::findMinRight(Node* ptr)
{
    if(ptr->left != NULL)
    {
        ptr = findMinRight(ptr->left);
    }
    return ptr;
}

// check for the existence of the key
bool ContactBST::findKey(Node *ptr,string key)
{
    bool result1 = false, result2 = false;
    if(ptr == nullptr)
    {
        return false;
    }
    int c = key.compare(ptr->key);
    if(c == 0)
    {
        return true;
    }
    else
    {
        if(c < 0)
        {
            result1 = findKey(ptr->left, key);
            if (result1) {
                return true;
            }
        }
        else if(c > 0)
        {
            result2 = findKey(ptr->right, key);
            if (result2) {
                return true;
            }
        }
    }
    return false;
}


Node* ContactBST::search(Node *ptr, string key)
{
    if(ptr == nullptr)
    {
        cout<<"No contacts found..."<<endl;
        return ptr;
    }
    if(!findKey(root, key))
    {
        cout<<"No contact found with a key "<<key<<endl;
        return root;
    }
    int c = key.compare(ptr->key);
    if(c == 0)
    {
            cout<<ptr->contactVector->size()<<" record(s) found:"<<endl;
            for (int i=0; i<ptr->contactVector->size(); ++i)
            {
                char isfavourite = '0';
                if(ptr->contactVector->at(i)->isFav)
                {
                    isfavourite = '1';
                }
                cout<<" "<<i+1<<". First Name:" + ptr->contactVector->at(i)->fname<<endl;
                cout<<"    Last Name: " +ptr->contactVector->at(i)->lname<<endl;
                cout<<"    Email: " + ptr->contactVector->at(i)->email<<endl;
                cout<<"    Phone#: " + ptr->contactVector->at(i)->primaryPhone<<endl;
                cout<<"    City: " + ptr->contactVector->at(i)->city<<endl;
                cout<<"    Country: " + ptr->contactVector->at(i)->country<<endl;
            }
    }
    else
    {
        if(c < 0)
        {
            ptr->left = search(ptr->left, key);
        }
        else if(c > 0)
        {
            ptr->right = search(ptr->right, key);
        }
    }
    return ptr;
}



bool ContactBST::markFav(Node *ptr, string key)
{
    if(!findKey(root, key))
    {
        cout<<endl;
        cout<<"No contact found with a key "<<key<<endl;
        return false;
    }
    
    while (true)
    {
        int c = key.compare(ptr->key);
        
        if(c != 0)
        {
            if(c < 0)
            {
                ptr = ptr->left;
            }
            else
            {
                ptr = ptr->right;
            }
        }
        else if(ptr->contactVector->size() > 1)
        {
            cout<<ptr->contactVector->size()<<" record(s) found:"<<endl;
            for (int i=0; i<ptr->contactVector->size(); ++i)
            {
                char isfavourite = '0';
                if(ptr->contactVector->at(i)->isFav)
                {
                    isfavourite = '1';
                }
                cout<<i+1<<". " + ptr->contactVector->at(i)->fname + ", "+ptr->contactVector->at(i)->lname+", "+ptr->contactVector->at(i)->email+", "+ptr->contactVector->at(i)->primaryPhone+", "+ptr->contactVector->at(i)->city+", "+ptr->contactVector->at(i)->country+", "+isfavourite<<endl;
            }
            string recordnumber;
            int record;
            if (ptr->contactVector->size() > 1)
            {
                cout<<"Please select the record you want to mark as favorite: ";
                cin>>recordnumber;
                for (int i=0; i<recordnumber.length(); ++i)
                {
                    if (!isdigit(recordnumber[i]))
                    {
                        cout<<"Invalid input. Try again..."<<endl;
                        return ptr;
                    }
                }
                record = stoi(recordnumber);
            }
            else
            {
                recordnumber = "0";
                record = stoi(recordnumber);
            }
            cout<<endl;
            ptr->contactVector->at(record)->isFav = true;
            cout<<ptr->key + " ("<<ptr->contactVector->at(record)->email<<") has successfully been marked as favorite!"<<endl;
            return true;
        }
        else
        {
            cout<<endl;
            ptr->contactVector->at(0)->isFav = true;
            cout<<ptr->key + " ("<<ptr->contactVector->at(0)->email<<") has successfully been marked as favorite!"<<endl;
            return true;
        }
    }
}

bool ContactBST::unmarkFav(Node *ptr, string key)
{
    if(!findKey(root, key))
    {
        cout<<endl;
        cout<<"No contact found with a key "<<key<<endl;
        return false;
    }
    
    while (true)
    {
        int c = key.compare(ptr->key);
        
        if(c != 0)
        {
            if(c < 0)
            {
                ptr = ptr->left;
            }
            else
            {
                ptr = ptr->right;
            }
        }
        else if(ptr->contactVector->size() > 1)
        {
            cout<<ptr->contactVector->size()<<" record(s) found:"<<endl;
            for (int i=0; i<ptr->contactVector->size(); ++i)
            {
                char isfavourite = '0';
                if(ptr->contactVector->at(i)->isFav)
                {
                    isfavourite = '1';
                }
                cout<<i+1<<". " + ptr->contactVector->at(i)->fname + ", "+ptr->contactVector->at(i)->lname+", "+ptr->contactVector->at(i)->email+", "+ptr->contactVector->at(i)->primaryPhone+", "+ptr->contactVector->at(i)->city+", "+ptr->contactVector->at(i)->country+", "+isfavourite<<endl;
            }
            string recordnumber;
            int record;
            if (ptr->contactVector->size() > 1)
            {
                cout<<"Please select the record you want to mark as favorite: ";
                cin>>recordnumber;
                for (int i=0; i<recordnumber.length(); ++i)
                {
                    if (!isdigit(recordnumber[i]))
                    {
                        cout<<"Invalid input. Try again..."<<endl;
                        return ptr;
                    }
                }
                record = stoi(recordnumber);
            }
            else
            {
                recordnumber = "0";
                record = stoi(recordnumber);
            }
            cout<<endl;
            ptr->contactVector->at(record)->isFav = false;
            cout<<ptr->key + " ("<<ptr->contactVector->at(record)->email<<") has successfully been unmarked as favorite!"<<endl;
            return true;
        }
        else
        {
            cout<<endl;
            ptr->contactVector->at(0)->isFav = false;
            cout<<ptr->key + " ("<<ptr->contactVector->at(0)->email<<") has successfully been unmarked as favorite!"<<endl;
            return true;
        }
    }
}


Node* ContactBST::update(Node *ptr, string key)
{
    string newkey;
    if(!findKey(root, key))
    {
        cout<<endl;
        cout<<"No contact found with a key "<<key<<endl;
        return ptr;
    }
    
    while (true)
    {
        int c = key.compare(ptr->key);
        
        if(c != 0)
        {
            if(c < 0)
            {
                ptr = ptr->left;
            }
            else
            {
                ptr = ptr->right;
            }
        }
        else
        {
            cout<<ptr->contactVector->size()<<" record(s) found:"<<endl;
            for (int i=0; i<ptr->contactVector->size(); ++i)
            {
                char isfavourite = '0';
                if(ptr->contactVector->at(i)->isFav)
                {
                    isfavourite = '1';
                }
                cout<<i+1<<". " + ptr->contactVector->at(i)->fname + ", "+ptr->contactVector->at(i)->lname+", "+ptr->contactVector->at(i)->email+", "+ptr->contactVector->at(i)->primaryPhone+", "+ptr->contactVector->at(i)->city+", "+ptr->contactVector->at(i)->country+", "+isfavourite<<endl;
            }
            string recordnumber, field, newdata, another;
            int record;
            bool dataerror = false;
            cout<<endl;
            if (ptr->contactVector->size() > 1) {
                cout<<"Please select the record you want to edit: ";
                cin>>recordnumber;
                for (int i=0; i<recordnumber.length(); ++i)
                {
                    if (!isdigit(recordnumber[i]))
                    {
                        cout<<"Invalid input. Try again..."<<endl;
                        return ptr;
                    }
                }
                record = stoi(recordnumber);
            }
            else
            {
                recordnumber = "0";
                record = stoi(recordnumber);
            }
            
            while(true)
            {
                bool changefl = false;
                cout<<"Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, 6) Country: ";
                cin>>field;
                string check = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
                if (field == "1")
                {
                    do
                    {
                        cout<<"Please enter a new first name: ";
                        cin>>newdata;
                        dataerror = false;
                        if (newdata.length() <= 1)
                        {
                            cout<<"First Name cannot be only 1 character"<<endl;
                            dataerror = true;
                        }
                        for(int i=0; i<newdata.length(); ++i)
                        {
                            if(isalpha(newdata[i]) == false)
                            {
                                cout<<"Name consists only letters"<<endl;
                                dataerror = true;
                                break;
                            }
                        }
                    }
                    while(dataerror);
                    ptr->contactVector->at(record)->fname = newdata;
                    newkey = newdata + " " + ptr->contactVector->at(record)->lname;
                    Contact* data = ptr->contactVector->at(record);
                    if(ptr->contactVector->size() == 1)
                    {
                        remove_helper(ptr->key);
                    }
                    insert_helper(newkey, data);
                    changefl = true;
                }
                else if (field == "2")
                {
                    do
                    {
                        cout<<"Please enter a new last name: ";
                        cin>>newdata;
                        dataerror = false;
                        if (newdata.length() <= 1)
                        {
                            cout<<"Last Name cannot be only 1 character"<<endl;
                            dataerror = true;
                        }
                        for(int i=0; i<newdata.length(); ++i)
                        {
                            if(isalpha(newdata[i]) == false)
                            {
                                cout<<"Name consists only letters"<<endl;
                                dataerror = true;
                                break;
                            }
                        }
                    }
                    while(dataerror);
                    ptr->contactVector->at(record)->lname = newdata;
                    newkey = ptr->contactVector->at(record)->fname + " " + newdata;
                    Contact* data = ptr->contactVector->at(record);
                    if(ptr->contactVector->size() == 1)
                    {
                        remove_helper(ptr->key);
                    }
                    insert_helper(newkey, data);
                    changefl = true;
                }
                else if (field == "3")
                {
                    do
                    {
                        cout<<"Please enter the new email: ";
                        cin>>newdata;
                        dataerror = true;
                        for (int i=0; i<newdata.length(); ++i)
                        {
                            if (i != 0 && newdata[i] == '@')
                            {
                                dataerror = false;
                                break;
                            }
                        }
                        dataerror = true;
                        for (int i=0; i<newdata.length(); ++i)
                        {
                            if (i != 0 && newdata[i] == '.')
                            {
                                dataerror = false;
                                break;
                            }
                        }
                        if (newdata.length() <= 3 || dataerror == true)
                        {
                            cout<<"Invalid email. Example: qwerty@gmail.com"<<endl;
                            dataerror = true;
                        }
                    }
                    while(dataerror);
                    ptr->contactVector->at(record)->email = newdata;
                }
                else if (field == "4")
                {
                    do
                    {
                        cout<<"Please enter the new phone#: ";
                        cin>>newdata;
                        dataerror = false;
                        for (int i=0; i<newdata.length(); ++i)
                        {
                            if (!isdigit(newdata[i]))
                            {
                                dataerror = true;
                                cout<<"Phone number cantains only digits"<<endl;
                                break;
                            }
                        }
                        if (newdata.length() <= 4)
                        {
                            dataerror = true;
                            cout<<"Phone number cannot be only 4 digits"<<endl;
                        }
                    }
                    while(dataerror);
                    ptr->contactVector->at(record)->primaryPhone = newdata;
                }
                else if (field == "5")
                {
                    do
                    {
                        cout<<"Please enter the new city: ";
                        cin>>newdata;
                        dataerror = false;
                        if (newdata.length() <= 2)
                        {
                            cout<<"City name cannot be only 2 characters"<<endl;
                            dataerror = true;
                        }
                        for(int i=0; i<newdata.length(); ++i)
                        {
                            if(isalpha(newdata[i]) == false)
                            {
                                cout<<"City Name consists only letters"<<endl;
                                dataerror = true;
                                break;
                            }
                        }
                    }
                    while(dataerror);
                    ptr->contactVector->at(record)->city = newdata;
                }
                else if (field == "6")
                {
                    do
                    {
                        cout<<"Please enter the new country: ";
                        cin>>newdata;
                        dataerror = false;
                        if (newdata.length() <= 2)
                        {
                            cout<<"Country name cannot be only 2 characters"<<endl;
                            dataerror = true;
                        }
                        for(int i=0; i<newdata.length(); ++i)
                        {
                            if(isalpha(newdata[i]) == false)
                            {
                                cout<<"Country consists only letters"<<endl;
                                dataerror = true;
                                break;
                            }
                        }
                    }
                    while(dataerror);
                    ptr->contactVector->at(record)->country = newdata;
                }
                cout<<"The contact record has successfully been updated!"<<endl<<endl;
                while (true) {
                    cout<<"Do you want to edit another field (y/n)? ";
                    cin>>another;
                    if(another == "n")
                    {
                        break;
                    }
                    else if(another != "y")
                    {
                        cout<<"Invalid input (y/n)"<<endl;
                    }
                    else if(another == "y")
                    {
                        break;
                    }
                }
                if (another == "n") {
                    break;
                }
                else if(changefl)
                {
                    update(root, newkey);
                    break;
                }
            }
            return ptr;
        }
    }
}


int ContactBST::importCSV(Node *ptr, string path)
{
    ifstream fin(path);
    int n = 0;
    while (!fin.eof())
    {
        n = n + 1;
        string v, d;
        string fname,lname, email, primaryPhone, city, country;
        int isfavourite = 0;
        int number = 1;
        getline(fin, v);
        
        v = v + ",,";
        for (int i = 0; i < v.length(); ++i)
        {
            if (v[i] != ',')
            {
                d = d + v[i];
            }
            else
            {
                if (number == 1)
                {
                    fname = d;
                    number = number + 1;
                    d = "";
                    i = i + 1;
                }
                else if (number == 2)
                {
                    lname = d;
                    number = number + 1;
                    d = "";
                    i = i + 1;
                }
                else if (number == 3)
                {
                    email = d;
                    number = number + 1;
                    d = "";
                    i = i + 1;
                }
                else if (number == 4)
                {
                    primaryPhone = d;
                    number = number + 1;
                    d = "";
                    i = i + 1;
                }
                else if (number == 5)
                {
                    city = d;
                    number = number + 1;
                    d = "";
                    i = i + 1;
                }
                else if (number == 6)
                {
                    country = d;
                    number = number + 1;
                    d = "";
                    i = i + 1;
                }
                else if (number == 7)
                {
                    isfavourite = stoi(d);
                    number = number + 1;
                    d = "";
                }
                else if (number == 8)
                {
                    bool isFav = false;
                    if (isfavourite == 1)
                    {
                        isFav = true;
                    }
                    else
                    {
                        isFav = false;
                    }
                    Contact* data = new Contact(fname, lname, email, primaryPhone, city, country, isFav);
                    string key = fname + ' ' + lname;
                    insert_helper(key, data);
                    number = 1;
                    d = "";
                }
            }
        }
    }
    fin.close();
    return n - 1;
}

int ContactBST::exportCSV(Node *ptr, string path)
{
    if(root != nullptr)
    {
        inorder(root);
        ofstream fout(path);
        int n = 0;
        if (fout.is_open())
        {
            for (int i=0; i<contactsinorder->size(); ++i)
            {
                char isfavourite = '0';
                if(contactsinorder->at(i)->isFav)
                {
                    isfavourite = '1';
                }
                fout<<contactsinorder->at(i)->fname + ", " + contactsinorder->at(i)->lname + ", " + contactsinorder->at(i)->email + ", " + contactsinorder->at(i)->primaryPhone + ", " + contactsinorder->at(i)->city + ", " + contactsinorder->at(i)->country + ", " + isfavourite<<endl;
                n = n + 1;
            }
        }
        fout.close();
        return n;
    }
    else
    {
        cout<<"No contacts..."<<endl;
        return 0;
    }
}

void ContactBST::inorder(Node* ptr)
{
    if(root == ptr)
    {
        contactsinorder = new MyVector<Contact>;
    }
    if(root != nullptr)
    {
        if(ptr->left != nullptr)
        {
            inorder(ptr->left);
        }
        for (int i=0; i<ptr->contactVector->size(); ++i)
        {
            Contact* contactnode = new Contact(ptr->contactVector->at(i)->fname,ptr->contactVector->at(i)->lname,ptr->contactVector->at(i)->email,ptr->contactVector->at(i)->primaryPhone,ptr->contactVector->at(i)->city,ptr->contactVector->at(i)->country,ptr->contactVector->at(i)->isFav);
            contactsinorder->push_back(contactnode);
        }
        if (ptr->right != nullptr)
        {
            inorder(ptr->right);
        }
    }
    else
    {
        cout<<"No contacts..."<<endl;
    }
}

void ContactBST::printASC(Node *ptr)
{
    if(root != nullptr)
    {
        inorder(root);
        for (int i=0; i<contactsinorder->size(); ++i)
        {
            char isfavourite = '0';
            if(contactsinorder->at(i)->isFav)
            {
                isfavourite = '1';
            }
            cout<<contactsinorder->at(i)->fname + ", " + contactsinorder->at(i)->lname + ", " + contactsinorder->at(i)->email + ", " + contactsinorder->at(i)->primaryPhone + ", " + contactsinorder->at(i)->city + ", " + contactsinorder->at(i)->country + ", " + isfavourite<<endl;
        }
    }
    else
    {
        cout<<"No contacts..."<<endl;
    }
}

void ContactBST::printDES(Node *ptr)
{
    if(root != nullptr)
    {
        inorder(root);
        for (int i=contactsinorder->size()-1; i>=0; --i)
        {
            char isfavourite = '0';
            if(contactsinorder->at(i)->isFav)
            {
                isfavourite = '1';
            }
            cout<<contactsinorder->at(i)->fname + ", " + contactsinorder->at(i)->lname + ", " + contactsinorder->at(i)->email + ", " + contactsinorder->at(i)->primaryPhone + ", " + contactsinorder->at(i)->city + ", " + contactsinorder->at(i)->country + ", " + isfavourite<<endl;
        }
    }
    else
    {
        cout<<"No contacts..."<<endl;
    }
}

void ContactBST::printFav(Node *ptr)
{
    bool r=true;
    if(root != nullptr)
    {
        inorder(root);
        for (int i=0; i<contactsinorder->size(); ++i)
        {
            if(contactsinorder->at(i)->isFav)
            {
                cout<<contactsinorder->at(i)->fname + ", " + contactsinorder->at(i)->lname + ", " + contactsinorder->at(i)->email + ", " + contactsinorder->at(i)->primaryPhone + ", " + contactsinorder->at(i)->city + ", " + contactsinorder->at(i)->country + ", "<<contactsinorder->at(i)->isFav<<endl;
                r = false;
            }
        }
    }
    else
    {
        cout<<"No contacts..."<<endl;
    }
    if(r)
    {
        cout<<"No favourite contacts..."<<endl;
    }
}
