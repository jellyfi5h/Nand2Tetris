#include "./assembler.h"
#include <fstream>

//Global Varibles
Assembler_TT g_truth_tables;
map<string, int> g_symbols;

void init_assembler() {
    g_truth_tables.dests = TT_destinations();
    g_truth_tables.comps = TT_ALU_comps();
    g_truth_tables.jumps = TT_jumps();
    g_symbols = predefined_symbols();
}

void Usage(){
    cerr << "Must enter a single assembly file\n\tex: assembler file_path.asm" << endl;
}

string get_filename(int ac, char **av) {
    string filename;
    int pos;
    int len;

    if (ac != 2) {
        return "";
    }
    filename = av[1];
    pos = filename.find_last_of("/\\");
    filename = filename.substr(pos + 1);
    pos = filename.find(".asm");
    len = filename.length();
    if (!(pos != -1 && (pos + 4) == len)) {
        return "";
    }
    filename = filename.substr(0, pos);
    return filename;
}


int main(int ac, char **av) {
    ifstream asm_file;
    vector<string> instructions;
    string error;
    string filename;

    // *Usage
    filename = get_filename(ac, av);
    if (filename.empty()) {
        Usage();
        return 1;
    }

    // *open file
    asm_file.open(av[1]);
    if (!asm_file) {
        cerr << "file doesn't exist" << endl;
        return 1;
    }

    // *construct predefined symbols
    init_assembler();

    // *read file content (store labels & instructions)
        // Return error if any detected, else an empty string
    error = read_asm(&asm_file, &instructions);
    asm_file.close();
    if (!error.empty()) {
        cerr << "Error: " + error << endl;
        return 1;
    }

    //convert assembly 
    machine_language(filename, instructions);
    return 0;
}