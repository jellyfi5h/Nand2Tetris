#include <iostream>
#include <string>

using namespace std;
/*** string manipulation functions ***/

// Delete whitespaces from the begining and end of a string
string ft_strtrim(string str) {
    int bg, end;

    end = str.length();
    bg = 0;
    while (bg < end && isspace(str[bg])) {
        bg++;
    }
    if (bg == end) {
        return "";
    }
    end -= 1;
    while (end >= bg && isspace(str[end])) {
        end--;
    }
    return str.substr(bg, end - bg + 1);
}

// Return true if string passed in parameter is a number, else return false
bool ft_str_isnumber(string str) {
    int len;

    len = str.length();
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// Return true if the string given contain whitespace
bool ft_str_exists_space(string str) {
    int i, len;

    len = str.length();
    i = 0;
    while (i < len) {
        if (isspace(str[i])) {
            return true;
        }
        i++;
    }
    return false;
}


string to_binary(int n) {
    string binary;
    char bit;

    for(int i = 0; n > 0; i++)
    {
        bit = (n % 2) ? '1' : '0';
        binary = bit + binary;
        n = n / 2;
    }
    return binary;
}