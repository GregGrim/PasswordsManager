//
// Created by grimy on 25.05.2023.
//

#ifndef PASSWORDMANAGERPROJECT_TIMESTAMP_H
#define PASSWORDMANAGERPROJECT_TIMESTAMP_H
#include <string>

using namespace std;
/**
 * Class that contains timestamp as number of seconds
 */
class Timestamp {
public: int num_sec;


public:
    Timestamp();
    /**
     * writes time to first 17 chars in file inside first 2 bits of each char
     * @param filepath
     */
    void writeTimestamp(const string& filepath) const;
    /**
     * reads last written timestamp from file
     * @param filepath
     * @return time
     */
    static string readTimestamp(const string& filepath);
};



#endif //PASSWORDMANAGERPROJECT_TIMESTAMP_H
