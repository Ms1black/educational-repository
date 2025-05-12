#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
#include <cstring>

#include "formatter_output.h"


char* textalign(const char* word, Alignment align, int size) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wword = converter.from_bytes(word);

    int length = wword.length(); 
    if (length >= size) return strdup(word); 

    std::wstring aligned;
    
    switch (align) {

        case LEFT:
            aligned = wword + std::wstring(size - length, L' ');
            break;

        case CENTER: {
            
            int left_pad = (size - length) / 2;
            int right_pad = size - length - left_pad;
            aligned = std::wstring(left_pad, L' ') + wword + std::wstring(right_pad, L' ');
            break;
        }

        case RIGHT:

            aligned = std::wstring(size - length, L' ') + wword;
            break;
    }

    std::string result = converter.to_bytes(aligned); 

    char* res = new char[result.length() + 1];
    std::strcpy(res, result.c_str()); 
    return res;
}