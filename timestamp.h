//
// Created by grimy on 25.05.2023.
//

#ifndef PASSWORDMANAGERPROJECT_TIMESTAMP_H
#define PASSWORDMANAGERPROJECT_TIMESTAMP_H
#include <string>

using namespace std;

class Timestamp {
public: int num_sec;


public:
    Timestamp();
    void writeTimestamp(const string& filepath) const;
    static string readTimestamp(const string& filepath);
};



#endif //PASSWORDMANAGERPROJECT_TIMESTAMP_H
