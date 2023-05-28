//
// Created by grimy on 25.05.2023.
//
#include <string>
#ifndef PASSWORDMANAGERPROJECT_PASSWORD_H
#define PASSWORDMANAGERPROJECT_PASSWORD_H
using namespace std;


class Password {
private:
    string name;
    string passwordText;
    string category;
    string website;
    char check = 0;
public: Password(string name, string passwordText, string category, string website);
    Password();
    bool isEncrypted();
    static string encodeString(string s,const string& key);
    void encodePassword(const string& key);
    friend ostream& operator<=(ostream& os, Password arg); // operator to show info about password
    friend ostream& operator<<(ostream& os, Password const& arg); // operator to write password to file
    friend istream& operator>>(istream& is, Password &arg); // operator to read password from file
    string getName();
    string getPasswordText();
    string getCategory();
    string getWebsite();

    void setName(string newName);

    void setWebsite(string newWebsite);

    void setCategory(string newCategory);

    void setPasswordText(string newPasswordText);

    void setCheck(const string& newWord);

    char getCheck();
};


#endif //PASSWORDMANAGERPROJECT_PASSWORD_H
