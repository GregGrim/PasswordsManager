#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <regex>
#include <random>
#include <iomanip>
#include "password.h"
#include "timestamp.h"

using namespace std;

/**
 * function reads passwords from file using specific key to decrypt
 * @param key
 * @param filepath
 * @return vector of Passwords
 */
vector<Password> readPasswords(const string& key,const string& filepath) {
    Timestamp time = Timestamp();
    time.writeTimestamp(filepath);

    ifstream file(filepath);

    vector<Password> passwords = vector<Password>();
    Password p;
    while (!file.eof()) {
            file >> p;
            if(!p.getName().empty()) {
                p.encodePassword(key);
                passwords.push_back(p);
            }
    }
    file.close();
    return passwords;
}
/**
 * function rewrites file with passwords using key to encrypt
 * @param passwords
 * @param key
 * @param filepath
 */
void writePasswords(const vector<Password>& passwords, const string& key,const string& filepath){
    char name[1000];
    strcpy(name, filepath.c_str());
    ofstream tempFile("temp.txt", ios_base::app); // Create a temporary output file
    vector<Password> ps = passwords;
    for (Password& password: ps) {
        password.encodePassword(key);
        tempFile << password << endl;
    }
    tempFile.close();
    remove(name);
    rename("temp.txt", name);
}
/**
 * function checks if the provided key is valid for this file
 * @param key
 * @param filepath
 * @return bool
 */
bool checkKey(const string& key,const string& filepath) {
    vector<Password> existingPasswords = readPasswords(key,filepath);
    bool flag = false;
    for (Password pas: existingPasswords) {
        if(pas.isEncrypted()) flag=true;
    }
    return !flag;
}
/**
 * function checks if the provided file exists
 * @param filepath
 * @return bool
 */
bool checkFile(const string& filepath) {
    fstream file (filepath);
    if (!file) {
        return false;
    } else return true;
}
/**
 * function searches for all Passwords which match given string
 * @param parameter
 * @param passwords
 * @return vector of matched Passwords
 */
vector<Password> searchFunc(const string& parameter,const vector<Password>& passwords) {
    vector<Password> filteredPasswords;
    copy_if(passwords.begin(), passwords.end(), back_inserter(filteredPasswords),
            [&parameter](Password p) {
                return (p.getName().find(parameter) != string::npos)||
                       (p.getPasswordText().find(parameter) != string::npos)||
                       (p.getCategory().find(parameter) != string::npos)||
                       (p.getWebsite().find(parameter) != string::npos);
            });
    return filteredPasswords;
}
/**
 * function sorts all Passwords according to provided parameter (can sort by name, category or name and category)
 * @param parameter
 * @param passwords
 * @return vector of sorted Passwords
 */
vector<Password> sortPasswords(const string& parameter,const vector<Password>& passwords) {
    vector<Password> sortedPasswords = passwords;
    if(parameter=="name") {
        sort(sortedPasswords.begin(), sortedPasswords.end(),
                  [](Password& password1, Password& password2){
            return password1.getName()<password2.getName();
        });
    } else if (parameter=="cat"){
        sort(sortedPasswords.begin(), sortedPasswords.end(),
                  [](Password& password1, Password& password2){
            return password1.getCategory()<password2.getCategory();
        });
    } else if(parameter=="namecat") {
        sort(sortedPasswords.begin(), sortedPasswords.end(),
                  [](Password& password1,Password& password2) {
                      if (password1.getName() == password2.getName()) {
                          return password1.getCategory() < password2.getCategory();
                      }
                      return password1.getName() < password2.getName();
                  });
    } else cout << "Parameter is invalid.\n";
    return sortedPasswords;
}
/**
 * function edits field of given Password according to given field and new word for it
 * @param name
 * @param field field to change
 * @param newWord word to put
 * @param passwords
 */
void editPassword(const string& name,const string& field, const string& newWord,vector<Password>& passwords) {
    bool flag = false;
    for (Password& p: passwords) {
        if(p.getName()==name) {
            if(field=="name") {
                p.setName(newWord);
            } else if(field=="passwordText") {
                p.setPasswordText(newWord);
                p.setCheck(newWord);
            } else if(field=="category") {
                p.setCategory(newWord);
            } else if(field=="website") {
                p.setWebsite(newWord);
            }
            flag = true;
        }
    }
    if(!flag) cerr << "No such password name!\n";
}
/**
 * function deletes given Password from list of all passwords
 * @param passwords
 * @param name
 */
void deletePassword(vector<Password> *passwords, const string& name) {
    erase_if(*passwords, [&name](Password& pas) {
        return pas.getName() == name;
    });
}
/**
 * function analyzes if the given Password is strong or has been used before
 * @param passwords
 * @param passwordText
 */
void analyzePassword(vector<Password>& passwords,string& passwordText) {
    for (Password& password: passwords) {
       if(password.getPasswordText()==passwordText) cout<<"Password has been used before!\n";
    }
    if (regex_search(passwordText, regex("[a-zA-Z]"))) {
        if (regex_search(passwordText, regex("\\d"))&&passwordText.length()>7) {
            if (regex_search(passwordText, regex("[^A-Za-z0-9]"))) {
                cout << "Password is strong\n";
            } else cout << "Password is medium\n";
        } else cout << "Password is weak\n";
    } else cout << "Password is weak\n";
}
/**
 * function reads categories from file
 * @return vector of strings representing categories
 */
vector<string> readCategories () {
    vector<string> categories;
    ifstream file;
    file.open("Categories.txt");
    string cat;
    while(file>>cat) {
   //     cout<<cat;
        categories.push_back(cat);
    }
    file.close();
    return categories;
}
/**
 * function writes categories to the file
 * @param categories
 */
void writeCategories(const vector<string>& categories) {
    char name[1000];
    strcpy(name, "Categories.txt");
    ofstream tempFile("temp.txt", ios_base::app); // Create a temporary output file
    for (const string& category: categories) {
        tempFile << category << " ";
    }
    tempFile.close();
    remove(name);
    rename("temp.txt", name);
}
/**
 * function deletes given Category from list of all categories
 * @param categories
 * @param name
 * @param passwords
 */
void deleteCategory(vector<string> *categories, const string& name, vector<Password>& passwords) {
    erase_if(*categories, [&name](string& category) {
        return category == name;
    });
    for (Password& p: passwords) {
        if(p.getCategory()==name){
            p.setCategory("-");
        }
    }
}
/**
 * function creates random string in uuid4 format
 * @return random string in uuid4 format
 */
string generateUUIDv4() {
    // Generate random bytes
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint8_t> dis(0, 255);
    stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << setw(2) << setfill('0') << hex << static_cast<int>(dis(gen));
    }
    // Format the random bytes as a UUID v4 string
    string uuid = ss.str();
    uuid.insert(8, "-");
    uuid.insert(13, "-");
    uuid.insert(18, "-");
    uuid.insert(23, "-");

    // Set the version and variant bits for UUID v4
    uuid[14] = '4';  // Set the version bits (bits 12-15) to "0100"
    uuid[19] = (uuid[19] & 0x0F) | 0x40;  // Set the variant bits (bits 16-17) to "10"

    return uuid;
}

/**
 * main method with CLI implemented with intuitive navigation commands
 * @return
 */
int main() {
//    cout << Timestamp::readTimestamp(path) << endl; //command to read last timestamp
    string filepath;
    cout << "Welcome to password Manager!\nWrite a name of file or path to file with passwords:\n";
    cin >> filepath;
    if(!checkFile(filepath)){
        cerr << "Error opening file.\n";
    } else {
        cout << "Type key to access file:\n";
        string your_key;
        cin >> your_key;
        if(!checkKey(your_key, filepath)) {
            cerr << "Key is incorrect!\n";
        } else {
            cout << "Key is correct\n";
            string command;
            cout << "Type your command(add, search, sort, edit, delete or quit):\n";
            cin >> command;
            while(command!="quit") {
                vector<Password> passwords = readPasswords(your_key,filepath);
                vector<string> categories = readCategories();
                if(command=="search") { // done
                    string parameter;
                    cout << "Provide specific word to search:\n";
                    cin >> parameter;
                    vector<Password> filteredPasswords = searchFunc(parameter,passwords);
                    if(filteredPasswords.empty()) cout << "No passwords found.\n";
                    else {
                        for (const Password &pas: filteredPasswords) {
                            cout <= pas;
                        }
                    }
                } else if(command=="sort") {
                    string parameter;
                    cout <<"Provide specific parameter to sort(cat, name, namecat):\n";
                    cin >> parameter;
                    vector<Password> sortedPasswords = sortPasswords(parameter,passwords);
                    for (const Password& pas: sortedPasswords) {
                        cout <= pas;
                    }
                } else if(command=="edit") { // done
                    cout << "Write name of password you want to change:\n";
                    string name;
                    cin >> name;
                    cout << "Write a field you want to change and new word for this field:\n";
                    string newWord;
                    string field;
                    cin >> field >> newWord;
                    editPassword(name, field, newWord, passwords);
                } else if(command=="delete") { // done
                    cout<<"What do you want to delete?(password or category):\n";
                    cin>>command;
                    if(command=="password") {
                        cout << "Write name of password you want to delete:\n";
                        string name;
                        cin >> name;
                        deletePassword(&passwords, name);
                        cout << "Password deleted.\n";
                    } else if(command=="category"){
                        cout << "Write name of category you want to delete:\n";
                        string name;
                        cin >> name;
                        deleteCategory(&categories,name,passwords);
                        cout << "Category deleted.\n";
                    }
                } else if(command=="add") {
                    cout<<"What do you want to add?(password or category):\n";
                    cin>>command;
                    if(command=="password") {
                        string password;
                        string name;
                        string category;
                        string website;
                        cout<< "Enter your name for password, password, category and website('-' if it doesnt exist)\n";
                        cin >> name >> password >> category >> website;
                        while(!count(categories.begin(), categories.end(), category)) {
                            cout<<"Such category does not exist! Write available category:\n";
                            for (const string& cat: categories) {
                                cout<<cat<<"\t";
                            }
                            cout<<endl;
                            cin>>category;
                        }
                        analyzePassword(passwords, password);
                        char dec = '-';
                        string msg = "Want to proceed[p] or change password[c], generate random[g]?:\n";
                        cout << msg;
                        cin >> dec;
                        while (dec!='p') {
                            if(dec=='g') {
                                password = generateUUIDv4();
                                cout << "Your generated password is: " << password << endl;
                            } else {
                                cout << "Enter another password:\n";
                                cin >> password;
                                analyzePassword(passwords, password);
                            }
                            cout << msg;
                            cin >> dec;
                        }
                        Password p = Password(name,password,category,website);
                        passwords.push_back(p);
                        cout<<name<<" "<< password<<" "<<category <<" "<< website << endl;
                        cout<<"Password added.\n";
                    } else if(command=="category"){ //done
                        string category;
                        cout << "Enter new category name:\n";
                        cin>>category;
                        if(count(categories.begin(), categories.end(), category)){
                            cout<<"Such category already exists!\n";
                        } else {
                            categories.push_back(category);
                            cout<<"category added.\n";
                        }
                    }
                }
                writePasswords(passwords,your_key,filepath);
                writeCategories(categories);
                Timestamp time = Timestamp();
                time.writeTimestamp(filepath);
                cout << "Type your new command([quit] to end working with file):\n";
                cin >> command;
            }
        }
    }
}
