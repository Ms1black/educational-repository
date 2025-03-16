#include "formatter_output.h"


char* textalign(const char* word, Alignment align, int size) {

    int length = strlen(word);
    char* aligned = new char[size + 1];

    switch (align) {
        
        case LEFT:

            strcpy(aligned, word);
            for (int i = length; i < size; i++){
                strcat(aligned, " ");
            }

            break;

        case CENTER:

            for (int i = 0; i < (size - length) / 2; i++){
                strcat(aligned, " ");
            }

            strcat(aligned, word);

            for (int i = 0; i < (size - length) / 2 + (size - length) % 2; i++){
                strcat(aligned, " ");
            }

            break;


        case RIGHT:

            for (int i = 0; i < (size - length); i++){
                strcat(aligned, " ");
            }

            strcat(aligned, word);

            break;

    }

    return aligned;

}