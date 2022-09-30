#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Конкатенация строк
char *concatenation(char *str1, char *str2, char *result)
{
    int len_str1 = strlen(str1), len_str2 = strlen(str2), len_result = strlen(result);
    result[len_result] = '\0';

    for (int i = 0; i < len_str1; i++) {
        result[i] = str1[i];
    }

    for (int i = 0; i < len_str2; i++) {
        result[i + len_str1] = str2[i];
    }
    return result;
}
//Реверс строки
void reverse(char *str, int length)
{
    char *start = str, *finish = str + length - 1;

    while (start < finish) {
        char tmp = *start;
        *start = *finish;
        *finish = tmp;
        start += 1;
        finish -= 1;
    }    
}


int main(int argc, char *argv[])
{
    if (((argc == 3 && argv[2][1] != 'c') || (argc == 4 && argv[2][1] == 'c'))
        && (strlen(argv[2]) == 2)
        && (argv[2][0] == '-')
        && (argv[2][1] == 'l' || argv[2][1] == 'r' || argv[2][1] == 'u' || argv[2][1] == 'n' || argv[2][1] == 'c'))
    {
        int length = strlen(argv[1]);
        char state = argv[2][1];
        char *string = argv[1];

        /*char *string = (char*)malloc(sizeof(char) * length + 1);

        if (string == NULL) {
            printf("Out of memory!\n");
            return 0;
        }

        string[length] = '\0';

        for (int i = 0; i < length; i++) {
            string[i] = argv[1][i];
        }*/

        switch(state) {
            case 'l':
                printf("String length: %ld\n", strlen(string));
                break;
            case 'r':
                reverse(string, length);
                printf("Reverse string: %s\n", string);
                break;
            case 'u':
                printf("Toupper string: ");
                for (int i = 0; i < length; i++) {
                    if (i % 2 == 0)
                        printf("%c", toupper(string[i]));
                    else
                        printf("%c", string[i]);
                }
                printf("\n");
                break;
            case 'n':
                int count_digit = 0, count_letters = 0;

                for (int i = 0; i < length; i++) {
                    if (isdigit(string[i]))
                        count_digit++;
                    if (isalpha(string[i]))
                        count_letters++;
                }

                char *new_string = (char*)malloc(sizeof(char) * length + 1);

                if (new_string == NULL) {
                    printf("Out of memory!\n");
                    return 0;
                }

                new_string[length] = '\0';

                int count1 = 0, count2 = 0, count3 = 0;

                for (int i = 0; i < length; i++) {
                    if (isdigit(string[i])) {
                        new_string[count1++] = string[i];
                        //count1++;
                    }
                    if (isalpha(string[i])) {
                        new_string[count_digit + count2++] = string[i];
                        //count2++;
                    }
                    if (!isalpha(string[i]) && !isdigit(string[i])) {
                        new_string[count_letters + count_digit + count3++] = string[i];
                        //count3++;
                    }
                }
                printf("Transform string: %s\n", new_string);
                free(new_string);
                break;
            case 'c':
                char *second_string = argv[3];
                char *result_string = (char*)malloc(sizeof(char) * (strlen(string) + strlen(second_string)) + 1);
                printf("Cocatenation strings '%s' and '%s': %s\n",string, second_string, concatenation(string, second_string, result_string));
                free(result_string);
                break;
        }
    } else {
        printf("Incorrect input!\n");
    }
    return 0;
}