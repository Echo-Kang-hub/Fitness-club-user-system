#pragma once
#include <iostream>
#include <string>

using namespace std;


//��ʾ�����������Ϣ
class Event 
{
public:
    string name;
    string type;
    string location;
    string time;  

    Event(string& n, string& t, const string& loc=" ", const string& eventTime=" ") : name(n), type(t), location(loc), time(eventTime) {}
};

