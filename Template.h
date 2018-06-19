#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <string>
using namespace std;
class Template{
    public:
        Template(string name = "", string content = "");
        string GetName();
        string GetContent();
        string Replace(string old);
    private:
        string name;
        string content;
};
#endif