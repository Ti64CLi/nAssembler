#ifndef __PATH_HPP__
#define __PATH_HPP__

#include <string>

using namespace std;

//void force_quit(string error);

typedef struct {
    size_t size;
    string abspath;
} file_t;

void set_sourcepath(string path);
string get_sourcepath(void);
string get_sourcefolder(void);
void change_sourcepath(string path);
string _abspath(string curpath, string path);

file_t add_file(string path);
string filecontents(string path);
size_t filesize(string path);
vector<string> split(string str, string separator);
vector<string> get_sourcecode(void);

#endif