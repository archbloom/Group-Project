#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H
#include <QDate>
#include <string.h>
#include <iostream>
using namespace std;
class log_entry
{
    public:
    string ip_address,date,time,method,status,size,object,url,agent;
   log_entry(string ip,string d,string t,string m,string st,string sz,string o,string u,string a)
   {
    ip_address = ip;
    date = d;
    time = t;
    method = m;
    status = st;
    size = sz;
    object = o;
    url = u;
    agent = a;
   }
    log_entry();
};

#endif // LOG_ENTRY_H
