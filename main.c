#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для перевода числа из некоторой системы счисления в десятичную
double convertBaseToDec(char num[], int fromBase) {
    double total = 0;

    int wholePart = 0;
    double fractionPart = 0;
    int length = strlen(num);
    int isNegative = 0;
    int i = 0;
    int hasFraction = 0;
    int fraction = 0;

    // Переводим в десятичную систему
    if(num[0] == '-') {
        isNegative = 1;
        i++;
    }

    for (; i < length; i++) {
        int digit;
        if (num[i] >= '0' && num[i] <= '9') {
            digit = num[i] - '0';
        } else if (num[i] >= 'A' && num[i] <= 'Z') {
            digit = num[i] - 'A' + 10;
        } else if (num[i] >= 'a' && num[i] <= 'z') {
            digit = num[i] - 'a' + 10;
        } else if (num[i] == '.') {
            // переходим к дробной части
            hasFraction = 1;
            i+=2;
            break;
        } else {
            printf("Ошибка: некорректный символ в числе\n");
            return 0;
        }

        if (digit >= fromBase) {
            printf("Ошибка: цифра в числе превышает основание системы счисления\n");
            return 0;
        }

        wholePart = wholePart * fromBase + digit;
    }

    if(hasFraction) {
        for (; i < length; i++) {
            int digit;
            if (num[i] >= '0' && num[i] <= '9') {
                digit = num[i] - '0';
            } else if (num[i] >= 'A' && num[i] <= 'Z') {
                digit = num[i] - 'A' + 10;
            } else if (num[i] >= 'a' && num[i] <= 'z') {
                digit = num[i] - 'a' + 10;
            } else {
                printf("Ошибка: некорректный символ в числе\n");
                return 0;
            }

            if (digit >= fromBase) {
                printf("Ошибка: цифра в числе превышает основание системы счисления\n");
                return 0;
            }

            fraction = fraction * fromBase + digit;
        }
    }
    fractionPart = fraction;

    while(fractionPart >= 1) {
        fractionPart /= (double)10;
    }


    total = wholePart + fractionPart;

    if(isNegative) {
        total *= -1;
    }

    return total;
}

// void convertBaseFromDec(double decimal, int toBase) {
//     // Переводим из десятичной системы в заданную
//     char result[100];
//     int index = 0;
//     int hasFraction = 0;

//     if ((double)(int)decimal != decimal) {
//         hasFraction = 1;
//     }

//     int wholePart;
//     int fractionPart;

//     if (hasFraction) {
//         wholePart = decimal;
//         fractionPart = decimal - wholePart;
//     }

//     wholePart = decimal;

//     while (wholePart > 0) {
//         int remainder = wholePart % toBase;
//         char digit;

//         if (remainder < 10) {
//             digit = remainder + '0';
//         } else {
//             digit = remainder - 10 + 'A';
//         }

//         result[index++] = digit;
//         wholePart /= toBase;
//     }
//     if(hasFraction) {
//         result[index++] = '.';

//         while (fractionPart > 0) {
//             int remainder = fractionPart % toBase;
//             char digit;

//             if (remainder < 10) {
//                 digit = remainder + '0';
//             } else {
//                 digit = remainder - 10 + 'A';
//             }

//             result[index++] = digit;
//             fractionPart /= toBase;
//         }
//     }
    

//     // Выводим результат в обратном порядке
//     printf("Результат: ");
//     for (int i = index - 1; i >= 0; i--) {
//         printf("%c", result[i]);
//     }

//     printf("\n");
// }

int main() {
    char num[100];
    int fromBase, toBase;
    double numInDec;

    // Вводим число и основание системы счисления
    printf("Введите число: ");
    scanf("%s", num);

    printf("Введите основание текущей системы счисления: ");
    scanf("%d", &fromBase);

    numInDec = convertBaseToDec(num, fromBase);

    printf("Ваше число в десятичной системе будет равняется %lf\n", numInDec);

    // printf("Введите основание новой системы счисления: ");
    // scanf("%d", &toBase);

    // // Переводим и выводим результат
    // convertBaseFromDec(12378.123, toBase);
    // convertBaseToDec("123aef.aa", fromBase);

    return 0;
}