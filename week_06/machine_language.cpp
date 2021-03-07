#include "./assembler.h"

// add zeros as MSB's to complete n bits in "bvinary"
string binary_padding(string binary, int n) {
    int len;

    len = binary.length();
    if (n <= len) {
        return binary;
    }
    n -= len;
    for (int i = 0; i < n; i++) {
        binary = '0' + binary;
    }
    return binary;
}

// Convert A instruction and return Machine Code
string getInstructionA(string line, int *n) {
    string addr;
    string ml;

    addr = line.substr(1, line.length() - 1);
    if (ft_str_isnumber(addr)) {
        ml = to_binary(stoi(addr));
    } else if (g_symbols.find(addr) != g_symbols.end()) {
        ml = to_binary(g_symbols[addr]);
    } else {
        g_symbols[addr] = *n;
        ml = to_binary(*n);
        *n += 1;
    }
    return binary_padding(ml, 16);
}

// Convert C instruction and return Machine Code
string getInstructionC(string line) {
    string dest, comp, jump;
    int d_pos, j_pos, end_pos, len;
    string ml;

    ml = "111";
    len = line.length();
    d_pos = line.find('=');
    j_pos = line.find(';');

    end_pos = (j_pos == -1) ? len - d_pos : j_pos - d_pos - 1;
    comp = line.substr(d_pos + 1, end_pos);
    ml += g_truth_tables.comps[comp];
    if (d_pos != -1) {
        dest = line.substr(0, d_pos);
        ml += g_truth_tables.dests[dest];
    } else {
        ml += "000";
    }
    if (j_pos != -1) { //jump
        end_pos = len - j_pos;
        jump = line.substr(j_pos + 1, end_pos);
        ml += g_truth_tables.jumps[jump];
    } else {
        ml += "000";
    }
    return ml;
}

/* Convert Assembly instructions to machine Code and write it in "filename.hack" file */
void machine_language(string filename, vector<string> instructions) {
    ofstream f_ml;
    int n_addr;
    int len;
    string content;

    f_ml.open(filename + ".hack");
    n_addr = 16;
    len = instructions.size();
    for (int i = 0; i < len; i++) {
        if (instructions[i][0] == '@') { //instruction A
            content = getInstructionA(instructions[i], &n_addr);
            if (!content.empty()) {
                f_ml << content << endl;
            }
        }
        else { //instruction C
            f_ml << getInstructionC(instructions[i]) << endl;
        }
    }
    f_ml.close();
}