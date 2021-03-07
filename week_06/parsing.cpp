#include "./assembler.h"

//get rid of comments and whitespaces
string clean_line(string line) {
    string instruction;
    int comment_index;

    comment_index = line.find("//");
    if (comment_index != -1) {
        line = line.substr(0, comment_index);
    }
    instruction = ft_strtrim(line);
    return instruction;
}

//get instruction State (error, comment, instructionA, instructionC, label)
string parsing(string line, int *state) {
    string instruction;
    string error;

    instruction = clean_line(line);
    if (instruction.empty()) {
        *state = 4; //empty line or comment
        return "";
    }
    if (instruction[0] == '(') { //isLabel
        error = isLabel(instruction);
        if (!error.empty()) {
            *state = 2;
            return error;
        }
        *state = 3;
        return instruction.substr(1, instruction.length() - 2);;
    }
    else if (instruction[0] == '@') { //isInstructionA
        error = isInstructionA(instruction);
        if (!error.empty()) {
            *state = 2;
            return error;
        }
        *state = 0;
        return instruction;
    } else { //isInstructionC
        error = isInstructionC(instruction);
        if (!error.empty()) {
            *state = 2;
            return error;
        }
        *state = 1;
        return instruction;
    }
    return 0;
}

//Assembler first pass: detect errors, store labels in symbols
string read_asm(ifstream *file, vector<string> *instructions) {
    string line;
    int state;
    int counter;
    int i;
    string content;

    counter = i = 1;
    while(getline(*file, line)) {
        content = parsing(line, &state);
        switch (state) {
            case 0://instruction A
            case 1://instruction C
                instructions->push_back(content);
                counter++;
                break;
            case 2://error
                return "line " + to_string(i) + ": " + content;
            case 3://label
                g_symbols[content] = counter - 1;
                break;
        }
        i++;
    }
    return "";
}