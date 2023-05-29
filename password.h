//
// Created by grimy on 25.05.2023.
//
#include <string>
#ifndef PASSWORDMANAGERPROJECT_PASSWORD_H
#define PASSWORDMANAGERPROJECT_PASSWORD_H
using namespace std;
/**
 * Class that contains all info associated with specific password
 */

class Password {
private:
    string name;
    string passwordText;
    string category;
    string website;
    char check = 0;
public: Password(string name, string passwordText, string category, string website);
    Password();
    /**
     * checks if the password was decrypted successfully
     * @return bool
     */
    bool isEncrypted();
    /**
     * encrypts the password fields using specific key
     * @param key
     */
    void encodePassword(const string& key);
    /**
     * operator to show info about password(fields)
     * @param os
     * @param arg
     * @return ostream
     */
    friend ostream& operator<=(ostream& os, Password arg);
    /**
     * operator to write password to file
     * @param os
     * @param arg
     * @return ostream
     */
    friend ostream& operator<<(ostream& os, Password const& arg);
    /**
     * operator to read password from file
     * @param is
     * @param arg
     * @return istream
     */
    friend istream& operator>>(istream& is, Password &arg);
    string getName();
    string getPasswordText();
    string getCategory();
    string getWebsite();

    void setName(string newName);

    void setWebsite(string newWebsite);

    void setCategory(string newCategory);

    void setPasswordText(string newPasswordText);

    void setCheck(const string& newWord);
};


#endif //PASSWORDMANAGERPROJECT_PASSWORD_H
