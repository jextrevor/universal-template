#include "Template.h"
#include <regex>
#include <iostream>

const regex VARIABLE_REGEX("(?!:)\\w+=.+?,,");
const regex VARIABLE_NAME_REGEX("\\w+(?==)");
const regex VARIABLE_VALUE_REGEX("=.+?(?=,,)");

Template::Template(string name, string content){
    this->name = name;
    this->content = content;
}
string Template::GetName(){
    return this->name;
}
string Template::GetContent(){
    return this->content;
}
string Template::Replace(string old){
    //@TemplateName:var1=Test,,var2=Testtt,,@
    string newstr = this->content;
    smatch sm;
    string strr = old;
    while(regex_search(strr,sm,VARIABLE_REGEX)){
        cout << sm[0] << endl;
        smatch sm2;
        string hi = sm[0];
        regex_search(hi,sm2,VARIABLE_NAME_REGEX);
        cout << sm2[0] << endl;
        regex_search(hi,sm2,VARIABLE_VALUE_REGEX);
        cout << sm2[0] << endl;
        strr = sm.suffix();
    }
    return old;
}