#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

class Database
{
protected:
    Database() { }
public:
    static Database& get()
    {
        // thread-safe since C++11
        static Database database;
        return database;
    }
    void setName(const std::string& n) {name = n;}
    const std::string& getName() {return name;}
    Database(Database const&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database const&) = delete;
    Database& operator=(Database &&) = delete;
private:
    std::string name="Jef";
};
#endif // DATABASE_H
