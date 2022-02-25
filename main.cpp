#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
//#include <libndls.h>

#include "path.hpp"

using namespace std;

string pathexample("/documents/nAssembler/clrscr.S.tns");

void print_vector(vector<string> vec) {
    cout << "{";
    while(!vec.empty()) {
        cout << vec.back() << "; ";
        vec.pop_back();
    }
    cout << "}" << endl;
}

int main(int argc, char *argv[])
{
    string path;

    if (argc > 1)
    {
        path = argv[1];
    }
    else
    {
        path = pathexample;
    }

    set_sourcepath(path);
    string sourcefolder = get_sourcefolder();
    string sourcefile = get_sourcepath();

    printf("_sourcefolder (length = %d): %s\n_sourcefile (length = %d): %s\n", sourcefolder.length(), sourcefolder.c_str(), sourcefile.length(), sourcefile.c_str());

    vector<string> sourcecode;
    sourcecode = get_sourcecode();
    print_vector(sourcecode);

    return EXIT_SUCCESS;
}