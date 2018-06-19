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
        smatch sm2;
        string hi = sm[0];
        regex_search(hi,sm2,VARIABLE_NAME_REGEX);
        string variablename = sm2[0];
        size_t index = newstr.find("{{"+variablename+"}}");
        size_t length = ("{{"+variablename+"}}").length();
        regex_search(hi,sm2,VARIABLE_VALUE_REGEX);
        string variablevalue = sm2[0];
        variablevalue.erase(0,1);
        while(index != string::npos){
            newstr.replace(index,length,variablevalue);
            index = newstr.find("{{"+variablename+"}}");
        }
        strr = sm.suffix();
    }
    return newstr;
}