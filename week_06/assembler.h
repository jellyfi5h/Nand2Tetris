#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;

struct Assembler_TT {
    map<string, string> dests;
    map<string, string> comps;
    map<string, string> jumps;
};

struct ASM_interpreter {
    vector<string> instructions;
    string error;
};

struct instructionState {
    short type;// -> A(0), C(1), err(2), label(3), empty/comment(4)
    string content;
};

extern Assembler_TT g_truth_tables;
extern map<string, int> g_symbols;

//libft functions
string ft_strtrim(string str);
bool ft_str_isnumber(string str);
bool ft_str_exists_space(string str);
string to_binary(int n);

//truth tables and predefined symbols
map<string,int> predefined_symbols();
map<string, string> TT_ALU_comps();
map<string, string> TT_destinations();
map<string, string> TT_jumps();

//instruction management
string isLabel(string instruction);
string isInstructionA(string instruction);
string isInstructionC(string instruction);
string read_asm(ifstream *file, vector<string> *instructions);
void machine_language(string filename, vector<string> instructions);