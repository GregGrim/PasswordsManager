//
// Created by grimy on 25.05.2023.
//

#include "password.h"
#include <iostream>
#include <utility>
Password:: Password(string name, string passwordText, string category, string website) {
        this->name = std::move(name);
        this->passwordText = passwordText;
        this->category = std::move(category);
        this->website = std::move(website);
        for (char i : passwordText) {
            check ^= i;
        }
    }
Password::Password() = default;
bool Password::isEncrypted() { // checks if the password is encrypted
        char check2 = 0;
        for (char i : passwordText) {
            check2 ^= i;
        }
        return check!=check2;
    }
void Password::encodePassword(const string& key) { // symmetric encodePassword and decoding function
    for (int i=0; i<name.length();i++) {
        name[i] ^= key[i % key.length()];
    }
    for (int i=0; i< passwordText.length(); i++) {
        passwordText[i] ^= key[i % key.length()];
    }
    for (int i=0; i<category.length();i++) {
        category[i] ^= key[i % key.length()];
    }
    for (int i=0; i<website.length();i++) {
        website[i] ^= key[i % key.length()];
    }
}
ostream& operator<=(ostream& os, Password arg) // operator to show info about password
{
    return os  << "name: "<< arg.name << "\tpassword: " << arg.passwordText
        << "\tcategory: " << arg.category << "\twebsite: " << arg.website << '\t' << (arg.isEncrypted()?"1":"0") << endl;
}
ostream& operator<<(ostream& os, Password const& arg) // operator to write password to file
{
    for(char c : arg.name) {
        os << (char) ('0' + ((c & 0xF0) >> 4));
        os << (char) ('0' + (c & 0xF));
    }
    os << ' ';
    for(char c : arg.passwordText) {
        os << (char) ('0' + ((c & 0xF0) >> 4));
        os << (char) ('0' + (c & 0xF));
    }
    os << ' ';
    for(char c : arg.category) {
        os << (char) ('0' + ((c & 0xF0) >> 4));
        os << (char) ('0' + (c & 0xF));
    }
    os << ' ';
    for(char c : arg.website) {
        os << (char) ('0' + ((c & 0xF0) >> 4));
        os << (char) ('0' + (c & 0xF));
    }
    os << ' ';
    os << (char) ('0' + ((arg.check & 0xF0) >> 4));
    os << (char) ('0' + (arg.check & 0xF));
    return os;
}
istream& operator>>(istream& is, Password &arg) // operator to read password from file
{
    string s ;
    arg.name="";
    arg.passwordText="";
    arg.category="";
    arg.website="";
    is >> s;
    for(int i=0;i<s.length();i+=2){
        arg.name+=(char)(((s[i] & 0xF) << 4) | (s[i+1]&0xF));
    }
    is >> s;
    for(int i=0;i<s.length();i+=2){
        arg.passwordText+=(char)(((s[i] & 0xF) << 4) | (s[i+1] & 0xF));
    }
    is >> s;
    for(int i=0;i<s.length();i+=2){
        arg.category+=(char)(((s[i] & 0xF) << 4) | (s[i+1] & 0xF));
    }
    is >> s;
    for(int i=0;i<s.length();i+=2){
        arg.website+=(char)(((s[i] & 0xF) << 4) | (s[i+1] & 0xF));
    }
    is >> s;
    arg.check=(char)(((s[0] & 0xF) << 4) | (s[1] & 0xF));
    return is;
}
string Password::getName() {
    return name;
}
string Password::getPasswordText() {
    return passwordText;
}
string Password::getCategory() {
    return category;
}
string Password::getWebsite() {
    return website;
}
void Password::setName(string newName) {
     name=std::move(newName);
}
void Password::setPasswordText(string newPasswordText) {
     passwordText = std::move(newPasswordText);
}
void Password::setCategory(string newCategory) {
     category = std::move(newCategory);
}
void Password::setWebsite(string newWebsite) {
     website = std::move(newWebsite);
}
void Password::setCheck(const string& newWord) {
    check = 0;
    for (char i : newWord) {
        check ^= i;
    }
}
