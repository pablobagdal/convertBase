#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
            // i сейчас фактически является индексом расположения точки
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
        // помним, что i является индексом расположения точки
        for (int j = i+1; j < length; ++j) {
            int digit;
            if (num[j] >= '0' && num[j] <= '9') {
                digit = num[j] - '0';
            } else if (num[j] >= 'A' && num[j] <= 'Z') {
                digit = num[j] - 'A' + 10;
            } else if (num[j] >= 'a' && num[j] <= 'z') {
                digit = num[j] - 'a' + 10;
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

        fractionPart = (double)fraction / pow(fromBase, length - 1 - i);
    }

    // while(fractionPart >= 1) {
    //     fractionPart /= (double)10;
    // }


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

void printDecConvertedToBase(double num) {

}

void printWelcome() {
    printf("Добро пожаловать в программу для выполнения операция и расчётов с числами в различных системах счисления.\n");
}
void printMenu() {
    printf("Выберите пункт меню:\n");
    printf("1. Перевести число из одной системы в другую\n");
    printf("2. Выполнить арифметическую операцию между двумя числами\n");
    printf("Выберите пункт меню:\n");
}

void scenario1() {
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

    printf("Введите основание желаемой системы счисления: ");
    scanf("%d", &toBase);

    printDecConvertedToBase(numInDec);
}

void scenario2() {
    char num1[100];
    char num2[100];

    int fromBase1;
    int fromBase2;

    int toBase;

    double numInDec1;
    double numInDec2;

    double result;

    char oper[256];

    printf("Введите первое число: ");
    scanf("%s", num1);

    printf("Введите основание системы счисления первого числа: ");
    scanf("%d", &fromBase1);

    printf("Введите второе число: ");
    scanf("%s", num2);

    printf("Введите основание системы счисления второго числа: ");
    scanf("%d", &fromBase2);

    printf("Введите основание желаемой системы счисления: ");
    scanf("%d", &toBase);

    printf("Введите желаемую операцию ('+', '-', '*', '/'): ");
    scanf("%s", oper);

    // вычисления
    numInDec1 = convertBaseToDec(num1, fromBase1);
    numInDec2 = convertBaseToDec(num2, fromBase2);

    switch (oper[0])
    {
    case '+':
        result = numInDec1 + numInDec2;
        break;
    case '-':
        result = numInDec1 - numInDec2;
        break;
    case '*':
        result = numInDec1 * numInDec2;
        break;
    case '/':
        if(numInDec2 == 0) {
            printf("Деление на ноль запрещено\n");
            return;
        }
        result = numInDec1 / numInDec2;
        break;
    default:
        printf("Недопустимая операция\n");
        return;
        break;
    }

    printf("%s(%d) %c %s(%d) = ", num1, fromBase1, oper[0], num2, fromBase2);
    printDecConvertedToBase(result);
    printf("(%d)\n", toBase);

}

int scenario(char choice) {
    if(choice == 1) {
        scenario1();
        return 1;
    } else if(choice == 2) {
        scenario2();
        return 2;
    } else if(choice == 3) {
        return 0;
    } else {
        printf("Некорректный пункт меню\n");
        return -1;
    }
}

int main() {
   printf("Result: %s = %lf\n", "3a.23d7", convertBaseToDec("3a.23d7", 16));
   
    return 0;
}
// int main() {
//     char userInput[256];
//     printWelcome();

//     while(1) {
//         printMenu();

//         scanf("%s", userInput);
        
//         if (scenario(userInput[0]) == 0) {
//             break;
//         }

//         // system("pause");
//         scanf("%s", userInput);
//         // system("pause");
//         system("clear");
//     }
//     return 0;
// }