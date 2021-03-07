#include "./assembler.h"

using namespace std;

string check_destination(string instruction, int e_pos);
string check_computation(string instruction, int b_pos, int e_pos);
string check_jump(string instruction, int b_pos, int e_pos);

//Check if instruction is a label or error
    //Return error specification in case found one, else empty
string isLabel(string instruction) {
    int last;
    string label;

    last = instruction.length() - 1;
    if (instruction[last] != ')') {
        return "Syntax Error: expected ')' at end of line";
    }
    label = instruction.substr(1, instruction.length() - 2);
    if (ft_str_exists_space(label)) {
        return "don't inlude whitespaces\nex: (Xxx)";
    }
    return "";
}

//Check if this instruction is type A
    //Return error specification in case found one, else empty
string isInstructionA(string instruction) {
    int ref;
    string addr;

    addr = instruction.substr(1, instruction.length() - 1);
    if (ft_str_exists_space(addr) || addr.empty()) {
        return "bad representation of memory address";
    }
    else if (ft_str_isnumber(addr)){
        ref = stoi(addr);
        if (ref < 0 || ref > 65534) {
            return "memory address selected must be between 0 and 65534 -> 16bit Computer";
        }
    }
    return "";
}

//Check if this instruction is type C
    //Return error specification in case found one, else empty
string isInstructionC(string instruction) {
    string error;
    int d_pos, j_pos, end_pos, len;

    len = instruction.length();
    d_pos = instruction.find('=');
    j_pos = instruction.find(';');
    if (d_pos == -1 && j_pos == -1) {
        return "Syntax Error: bad implementation of an instruction.";
    }
    if (d_pos != -1) {
        error = check_destination(instruction, d_pos);
        if (!error.empty()) {
            return error;  
        }
    }
    end_pos = (j_pos == -1) ? len - d_pos : j_pos - d_pos - 1;
    error = check_computation(instruction, d_pos + 1, end_pos);
    if (!error.empty()) {
        return error;
    }
    if (j_pos != -1) { //jump
        end_pos = len - j_pos;
        error = check_jump(instruction, j_pos + 1, end_pos);
        if (!error.empty()) {
            return error;
        }
    }
    return "";
}


/*      check errors in instruction C components (destination*, cpmoutation, jump)  */

string check_destination(string instruction, int e_pos) {
    string dest;

    dest = instruction.substr(0, e_pos);
    dest = ft_strtrim(dest);
    if (dest.empty()) {
        return "no destination has been specified.";
    }
    if (g_truth_tables.dests.find(dest) == g_truth_tables.dests.end()) {
         return "inexistent destination: \"" + dest + "\"";
    }
    return "";
}

string check_computation(string instruction, int b_pos, int e_pos) {
    string comp;

    comp = instruction.substr(b_pos, e_pos);
    comp = ft_strtrim(comp);
    if (comp.empty()) {
        return "no computation has been specified.";
    }
    if (g_truth_tables.comps.find(comp) == g_truth_tables.comps.end()) {
         return "inexistent computation: \"" + comp + "\"";
    }
    return "";
}


string check_jump(string instruction, int b_pos, int e_pos) {
    string jump;

    jump = instruction.substr(b_pos, e_pos);
    jump = ft_strtrim(jump);
    if (jump.empty()) {
        return "no jump has been specified.";
    }
    if (g_truth_tables.jumps.find(jump) == g_truth_tables.jumps.end()) {
         return "inexistent jump: \"" + jump + "\"";
    }
    return "";
}