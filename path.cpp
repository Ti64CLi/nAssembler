#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

#include "path.hpp"

using namespace std;

string _sourcefolder;
string _sourcefile;
map<string, string> _files;

/*void force_quit(string error)
{
    printf(error.c_str());
    exit(EXIT_FAILURE);
}*/

void set_sourcepath(string path)
{
    _sourcefile = path;
    size_t bs = path.rfind("/");
    _sourcefolder = path.substr(0, bs);
}

string get_sourcepath(void)
{
    return _sourcefile;
}

string get_sourcefolder(void)
{
    return _sourcefolder;
}

void change_sourcepath(string path)
{
    string abspath = _abspath(_sourcefolder, path);
    _sourcefile = abspath;
    size_t bs = abspath.rfind("/");
    _sourcefolder = abspath.substr(0, bs);
}

string _abspath(string curpath, string path)
{
    if(path.substr(0, 2) == "./") {
        return _abspath(curpath, path.substr(2, path.length() - 2));
    } else if(curpath.empty()) {
        return path;
    } else if(path.substr(0, 3) == "../") {
        string parpath = curpath.substr(0, curpath.rfind("/") + 1);
        return _abspath(parpath, path.substr(3, path.length() - 3));
    } else if(path[0] == '/') {
        return path;
    } else {
        return curpath + path;
    }
}

file_t add_file(string path) {
    string abspath = _abspath(_sourcefolder, path);
    if(_files.count(abspath)) {
        return (file_t){.size = _files[abspath].length(), .abspath = abspath};
    }

    size_t size = 0;

    ifstream f(abspath, ios::ate | ios::binary);
    if(!f.is_open()) {
        printf("Couldn't open file '%s' in add_file()\n", abspath.c_str());
        size = -1;
    } else {
        streampos size = f.tellg();
        char *s = new char [size];

        f.seekg(0, ios::beg);
        f.read(s, size);
        f.close();

        string str = s;
        delete[] s;

        if(str.empty()) {
            printf("Couldn't read file '%s' in add_file()\n", abspath.c_str());
        } else {
            _files[abspath] = str;
            size = str.length();
        }
    }

    return (file_t){.size = size, .abspath = abspath};
}

string filecontents(string path) {
    string abspath = _abspath(_sourcefolder, path);
    return _files[abspath];
}

size_t filesize(string path) {
    string abspath = _abspath(_sourcefolder, path);
    if(_files.count(abspath))
        return _files[abspath].length();
    
    printf("Error in filesize()\nHint : add_file needs to be called on the same file before using this function !\n");
    return -1;
}

vector<string> split(string str, string separator) { // split a string according to separator
    vector<string> splitstring;
    size_t lastoffset = 0;
    size_t newoffset = 0;

    while((newoffset = str.find(separator, lastoffset)) != string::npos) {
        if(newoffset - lastoffset > 0)
            splitstring.push_back(str.substr(lastoffset, newoffset - lastoffset));
        lastoffset = newoffset + 1;
    }

    return splitstring;
}

vector<string> get_sourcecode(void) { //return an empty vector<string> instead of None
    vector<string> s;
    if(_sourcefile.empty())
        return s;
    
    ifstream f(_sourcefile, ios::ate);
    if(f.is_open()) {
        streampos size = f.tellg(); //get the size of the file
        char *cstr = new char [size];

        f.seekg(0, ios::beg); //go back to the beginning
        f.read(cstr, size);
        f.close();

        string str = cstr;
        delete[] cstr;

        if(str.empty()) {
            printf("Couldn't read file '%s' in get_sourcecode()\n", _sourcefile.c_str());
        } else {
            s = split(str, "\n"); //split str according to '\n'
        }
    }

    printf("Couldn't open file '%s' in get_sourcecode()\n", _sourcefile.c_str());
    return s;
}