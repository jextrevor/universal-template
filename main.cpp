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
string ExtractName(string);
void WriteOut(string, char*);

const regex TEMPLATE_REGEX("#(?!END#)(\\w)+#[^]+?#END#");
const regex TEMPLATE_INSTANCE_REGEX("@(\\w)+?:.*?,,@");
const regex TEMPLATE_NAME_REGEX("@(\\w)+?(?=:)");

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
    cout << "Reading input file " << argv[1] << "..." << endl;
    string output = ReadFile(argv[1]);
    smatch sm1;
    while(regex_search(output,sm1,TEMPLATE_REGEX)){
        output.replace(output.find(sm1[0]),sm1[0].length(),"");
    }
    smatch sm;
    while(regex_search(output,sm,TEMPLATE_INSTANCE_REGEX)){
        for(int i = 0; i < templates.size(); i++){
            if(ExtractName(sm[0]) == templates.at(i)->GetName()){
                cout << "Replacing instance of " << templates.at(i)->GetName() << "..." << endl;
                output.replace(output.find(sm[0]),sm[0].length(),templates.at(i)->Replace(sm[0]));
            }
        }
    }
    cout << "Writing to output file " << argv[argc-1] << "..." << endl;
    WriteOut(output,argv[argc-1]);
    //cout << output << endl;
    /*for(int i = 0; i < templates.size(); i++){
        templates.at(i)->Replace("@Test:test=1,,test2=2,,@");
    }*/
    return 0;
}
string ExtractName(string templateInstance){
    smatch sm;
    regex_search(templateInstance,sm,TEMPLATE_NAME_REGEX);
    string ret = sm[0];
    return ret.erase(0,1);
}
string ReadFile(char* filename){
    ifstream t;
    t.open(filename);
    string buffer;
    string line;
    while(t.good()){
        getline(t,line);
        buffer += line;
        buffer += "\n";
    }
    t.close();
    return buffer;
}
void WriteOut(string output, char* filename){
    ofstream out(filename);
    out << output;
    out.close();
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
    cout << "Created template " << name << "." << endl;
}