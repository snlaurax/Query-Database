//
//  Table.cpp
//  Project4
//
//  Created by Laura Lu on 2021-05-30.
//  Copyright © 2021 Laura Lu. All rights reserved.
// location name
//locatoin name school

#include "Table.h"

Table::Table (std::string keyColumn, const std::vector<std::string>& columns)
{
    m_array.resize(DEFAULT_BUCKETS);
    
    //make a vector that holds the array of column names
    hold = columns;
    key = keyColumn; //key column that we are looking for
    
    //find the index where the key is
    for (int i =0; i<columns.size();i++)
    {
        if (columns[i] == key)
        {
            keyindex = i;  //key is in columns vector
            break;
        }
    }
}

Table::~Table()
{
    std::cerr << "deleted"; //no pointers or dyanmically allocated
}


bool Table::good() const
{
    bool check = false;
    
    for (int i =0; i<hold.size();i++)
    {
        if (hold[i] == key)
        {
            check = true;     //key is in columns vector
            break;
        }
        
        else
            check = false; //key isnt in columns vector
    }
    
    for (int i =0; i<hold.size();i++)
    {
        if (hold[i].empty()) //if a column is empty, just exit because we can't create an empty name one
        {
            return false;
        }
    }
    
    if (!check)
        return false; //exit the program if the key field is not inside
    
    //check for duplicates in columns vector
    for (int i = 0; i < hold.size(); ++i)
    {
        for (int j = i + 1; j < hold.size(); ++j)
        {
            if (hold[i] == hold[j]) //if they are equal then exit
                return false;
        }
    }
    return true;
}


bool Table::insert(const std::string& recordString)
{
    //check if the table is constructed correctly
    if (!good())
        return false;
    
    std::vector<std::vector<std::string>> indexvec;
    std::string temp;
    std::vector <std::string> colnames;
    std::string stringhold = recordString;
    int bucket;
    
    //create a stringparser object
    StringParser s;
    s.setString (recordString); 
    
    while (s.getNextField (stringhold))//if its true
    {
        colnames.push_back (stringhold); //use stringparser to parse through the different names and add
        //std::cerr << stringhold << std::endl; 
    }

    //if the number of inputted values is less than/more than the number of columns then return false and don't do anything
    if (colnames.size()!= hold.size())
    {
        return false;
    }
    
    else
    {
        bucket = hashFunc(colnames [keyindex]); //bucket is equal to the hashfunction of the keyfield
        m_array [bucket].push_back (colnames);
    }
        
    return true;
}

void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const
{
    //check if the table is constructed correctly
    if (!good())
        return;
    
    records.clear(); 
    std::vector<std::string> indexvec;
    
    //check to see whether they sent in something that matches 

    int bucket = hashFunc(key); //find the bucket number

    if (m_array[bucket].empty()) //do nothing if that area is empty
    {
        std::cerr << "the bucket was empty";
        return;
    }

    for (int i = 0; i<m_array[bucket].size(); i++)
    {
        indexvec = m_array[bucket][i]; //check that bucket and that column
        records.push_back (indexvec); //push it to records
    }
     
}

int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const
{
    records.clear(); //make sure the vector of vectors is empty
    //check if the table is constructed correctly
    if (!good())
        return -1;
    
    //create a stringparser object
    StringParser s;
    s.setString (query);
    std::vector<std::string> index;
    std::vector<std::string> kfcheck;

    std::string oper [31] = {"<", "<=", ">", ">=", "!=", "==", "=", "LT","Lt", "lt", "lT", "LE", "Le", "le", "lE", "GT", "Gt", "gt", "gT", "GE", "Ge", "ge", "gE", "NE", "Ne", "ne", "nE", "EQ", "Eq", "eq", "eQ" };
    
    while (s.getNextField (query))//if its true
    {
        index.push_back (query); //use stringparser to parse through the different names and add
        std::cerr <<query << std::endl; 
    }
    
    if (index.size() != 3) //make sure we don't go into bonus select
    {
        return -1;
    }
    
    //************************check if the FIRST token is equal to a column name****************************
    
    bool check = false;
    
    for (int i =0; i< hold.size(); i++)
    {
        if (index[0] == hold [i])
        {
            check = true;
            break;
        }
    }
    
    if (check == false) //if the first index is not equal to any column names
    {
        std::cerr << "keyfield not passed";
        records.clear(); //make the vector empty
        return -1;
    }
    
//************************check if the SECOND token is equal to an operator ****************************
    std::string compare = index [1];
    bool opercheck = false;
    
    for (int i = 0; i<31; i++)
    {
        if (compare == oper [i])
        {
            opercheck = true;
            break;
        }
    }
    
    if (!opercheck)
    {
        std::cerr << "operator not passed";
        records.clear();
        return -1; //stop here!
    }
    
//*****************everything is okay in the query, now we can try to do the operators!***************
    
    //find the index of the query
    int qindex = 0;
    std::string keyfield;
    
    for (int i =0; i<hold.size();i++)
    {
        if (hold[i] == index[0])
        {
            qindex = i;  //this is the new index
            break;
        }
    }
    
    int count = 0;
    
    for (int i = 0; i<DEFAULT_BUCKETS; i++)
    {
        if (!m_array [i].empty()) //if the bucket isn't empty, there will be vectors inside
        {
            std::cerr << "M_ARRAYSIZE" << m_array [i].size()<<std::endl;
            
            for (int j = 0; j < m_array[i].size(); j++)
            {
                //we want to compare each queryindex value
                
                //find the value by finding the queryindex value within each vector
                kfcheck = m_array [i][j];
                keyfield = kfcheck [qindex];
                std::cerr << "KFCHECK" << keyfield <<std::endl;

              //std::cerr<< "keyfield" << keyfield <<std::endl;
                
                //then we want to use the find function to find the
                
                if (index[1] == "<")
                {
                    if (keyfield < index[2]) //check whethr it is less than, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "<=")
                {
                    if (keyfield <= index[2]) //check whethr it is less than equal the value we want to compare with, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "==" || index[1] == "=")
                {
                    if (keyfield == index[2]) //check whethr it is equal the value we want to compare with, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == ">")
                {
                    if (keyfield > index[2]) //check whethr it is more than the value we want to compare with, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == ">=")
                {
                    if (keyfield >= index[2]) //check whethr it is more than  = the value we want to compare with, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "!=")
                {
                    if (keyfield != index[2]) //check whethr it is != than the value we want to compare with, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                //NUMERICAL COMPARISONS
                //convert the third index to a double
                //convert the keyfield to a double
                
                //only keep comparing if both are doubles
                double a = 0;
                double b = 0;

                if (index[1] == "LT" || index[1] == "Lt"  || index[1] == "lt" || index[1] == "lT")
                {
                    if (!stringToDouble (index[2], b)) //ex. price LT H;
                    {
                        return -1;
                    }
                        
                    if (!stringToDouble (keyfield, a))
                    {
                        count++;
                    }
                    
                    else if (a<b && stringToDouble (keyfield, a))
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "LE" || index[1] == "Le"  || index[1] == "le" || index[1] == "lE")
                {
                    if (!stringToDouble (index[2], b)) //ex. price LT H;
                    {
                        return -1;
                    }
                    
                    if (!stringToDouble (keyfield, a))
                    {
                        count++;
                    }
                    
                    else if (a <= b && stringToDouble (keyfield, a)) //check whethr it is less than, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "EQ" || index[1] == "Eq"  || index[1] == "eq" || index[1] == "eQ")
                {
                    if (!stringToDouble (index[2], b)) //ex. price LT H;
                    {
                        return -1;
                    }
                    
                    if (!stringToDouble (keyfield, a))
                    {
                        count++;
                    }
                    
                    else if (a == b && stringToDouble (keyfield, a)) //check whethr it is equal to, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "GT" || index[1] == "Gt"  || index[1] == "gt" || index[1] == "gT")
                {
                    if (!stringToDouble (index[2], b)) //ex. price LT H;
                    {
                        return -1;
                    }
                    
                    if (!stringToDouble (keyfield, a))
                    {
                        count++;
                    }
                    
                    else if (a > b && stringToDouble (keyfield, a)) //check whethr it is more than, if it is then we can add it to records
                    {
                        records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "GE" || index[1] == "Ge"  || index[1] == "ge" || index[1] == "gE")
                {
                    if (!stringToDouble (index[2], b)) //ex. price LT H;
                    {
                        return -1;
                    }
                    
                    if (!stringToDouble (keyfield, a))
                    {
                        count++;
                    }
                    
                    else if (a >= b && stringToDouble (keyfield, a)) //check whethr it is more than or equal, if it is then we can add it to records
                    {
                            records.push_back (kfcheck);
                    }
                }
                
                if (index[1] == "NE" || index[1] == "Ne"  || index[1] == "ne" || index[1] == "nE")
                {
                    if (!stringToDouble (index[2], b)) //ex. price LT H;
                    {
                        return -1;
                    }
                    
                    if (!stringToDouble (keyfield, a))
                    {
                        count++;
                    }
                    
                    else if (a != b && stringToDouble (keyfield, a)) //check whethr it is nt equal to it, if it it isnt and can be converted to a number then we can add it to records
                    {
                            records.push_back (kfcheck);
                    }
                }
            }
        }
    }
    return count;
}

bool Table::stringToDouble(std::string s, double& d) const
{
    char* end;
    d = std::strtof(s.c_str(), &end);
    return end == s.c_str() + s.size()  &&  !s.empty();
}


bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1);
        fieldText = m_text.substr(m_start, end-m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}


