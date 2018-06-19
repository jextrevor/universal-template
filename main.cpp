#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

#include "Template.h"

using namespace std;

string ReadFile(char*);
string trim(string const&);
void BuildTemplates(char*, vector<Template*>&);
void CreateTemplate(string, vector<Template*>&);

const regex TEMPLATE_REGEX("#(?!END#)(\\w)+#[^]+?#END#");

int main(int argc, char* argv[]){
    cout << "UNIVERSAL TEMPLATE ENGINE 1.0" << endl;
    vector<Template*> templates = vector<Template*>();
    if(argc < 3){
        cerr << "Usage: " << argv[0] << " input [templates] output" << endl;
        return 1;
    }
    cout << "Reading templates..." << endl;
    for(int i = 1; i < argc-1; i++){
        cout << "Reading " << argv[i] << "..." << endl;
        BuildTemplates(argv[i],templates);
    }
    for(int i = 0; i < templates.size(); i++){
        templates.at(i)->Replace("@Test:test=1,,test2=2,,@");
    }
    return 0;
}
string ReadFile(char* filename){
    ifstream t;
    t.open(filename);
    string buffer;
    string line;
    while(t){
        getline(t,line);
        buffer += line;
        buffer += "\n";
    }
    t.close();
    return buffer;
}
void BuildTemplates(char* filename, vector<Template*>& templates){
    string buffer = ReadFile(filename);
    smatch sm;
    string strr = buffer;
    while(regex_search(strr,sm,TEMPLATE_REGEX)){
        CreateTemplate(sm[0],templates);
        strr = sm.suffix();
    }
}
void CreateTemplate(string str, vector<Template*>& templates){
    string name = str.substr(str.find('#')+1,str.find('#',1)-str.find('#')-1);
    string content = str.substr(str.find('#',1)+1,str.find("#END#")-str.find('#',1)-1);
    templates.push_back(new Template(name,content));
}