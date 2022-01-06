//
//  Table.hpp
//  Project4
//
//  Created by Laura Lu on 2021-05-30.
//  Copyright © 2021 Laura Lu. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <array>
#include <string>


const int DEFAULT_BUCKETS = 997;
//template<typename KeyType, typename ValueType>

class Table
{
public:
    Table (std::string keyColumn, const std::vector<std::string>& columns);
    ~Table();
    bool good() const;
    bool insert(const std::string& recordString);
    void find(std::string key, std::vector<std::vector<std::string>>& records) const;
    int select(std::string query, std::vector<std::vector<std::string>>& records) const;
    
    // We prevent a Table object from being copied or assigned by
    // making the copy constructor and assignment operator unavailable.
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;
    
private:
    std::vector<std::vector <std::vector<std::string>>> m_array; //make a vector that holds vectors which holds array of strings 
    std::string key;

    int keyindex;
    std::vector<std::string> hold;

    bool stringToDouble(std::string s, double& d) const;
    int hashFunc(std::string name) const
    {
        std::size_t h = std::hash<std::string>{}(name);
        unsigned int bucketNumber = h % DEFAULT_BUCKETS;
        return bucketNumber;
    }
};

class StringParser
{
public:
    StringParser(std::string text = "")
    {
        setString(text);
    }
    
    void setString(std::string text)
    {
        m_text = text;
        m_start = 0;
    }
    
    bool getNextField(std::string& field);
    
private:
    std::string m_text;
    size_t m_start;
};


#endif /* Table_hpp */
