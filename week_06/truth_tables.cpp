#include <iostream>
#include <map>

using namespace std;

/***  this file contains creation of truth tables used to interpret C instruction (destinations, ALU computations, jumps)  ***/
map<string,int> predefined_symbols() {
    map<string, int> symbols;
    symbols["SP"] = 0;
    symbols["LCL"] = 1;
    symbols["ARG"] = 2;
    symbols["THIS"] = 3;
    symbols["THAT"] = 4;
    symbols["SCREEN"] = 16384;
    symbols["KBD"] = 24576;

    for (int i=0; i < 16; i++) {
        symbols["R"+to_string(i)] = i;
    }
    return symbols;
}

map<string, string> TT_ALU_comps() {
    map<string, string> comps;
    // when a=0
    comps["0"] = "0101010";
    comps["1"] = "0111111";
    comps["-1"] = "0111010";
    comps["D"] = "0001100";
    comps["A"] = "0110000";
    comps["!D"] = "0001101";
    comps["!A"] = "0110001";
    comps["-D"] = "0001111";
    comps["-A"] = "0110011";
    comps["D+1"] = "0011111";
    comps["A+1"] = "0110111";
    comps["D-1"] = "0001110";
    comps["A-1"] = "0110010";
    comps["D+A"] = "0000010";
    comps["D-A"] = "0010011";
    comps["A-D"] = "0000111";
    comps["D&A"] = "0000000";
    comps["D|A"] = "0010101";
    //when a=1
    comps["M"] = "1110000";
    comps["!M"] = "1110001";
    comps["-M"] = "1110011";
    comps["M+1"] = "1110111";
    comps["M-1"] = "1110010";
    comps["D+M"] = "1000010";
    comps["D-M"] = "1010011";
    comps["M-D"] = "1000111";
    comps["D&M"] = "1000000";
    comps["D|M"] = "1010101";
    return comps;
}

map<string, string> TT_destinations() {
    map<string, string> dests;
    dests["M"] = "001";
    dests["D"] = "010";
    dests["MD"] = "011";
    dests["A"] = "100";
    dests["AM"] = "101";
    dests["AD"] = "110";
    dests["AMD"] = "111";
    return dests;
}

map<string, string> TT_jumps() {
    map<string, string> jumps;
    jumps["JGT"] = "001";
    jumps["JEQ"] = "010";
    jumps["JGE"] = "011";
    jumps["JLT"] = "100";
    jumps["JNE"] = "101";
    jumps["JLE"] = "110";
    jumps["JMP"] = "111";
    return jumps;
}

