#ifndef _LIB_1_
#define _LIB_1_
#include <iostream>
#include <string>
using namespace std;

class Function{
    protected:
        string function;
        int val;
    public:
        //constructor
        //default
        Function(): function(" "), val(0) {}
        // for subtitute val in:
        Function(const string& function_, const int& val_): function(function_), val(val_) {}
        // for function only
        Function(const string& function_) : function(function_){}
};
class 



#endif