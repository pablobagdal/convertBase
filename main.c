#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FLOATING_PRECISION 1000000.0

#ifdef _WIN32
void clearScreen() {
    system("cls");
}
#else
void clearScreen() {
    system("clear");
}
#endif

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

    total = wholePart + fractionPart;

    if(isNegative) {
        total *= -1;
    }

    return total;
}

void printDecConvertedToBase(double decimal, int toBase) {
    // Переводим из десятичной системы в заданную
    char result[100];
    int index = 0;
    int hasFraction = 0;

    int wholePart = decimal;
    int fractionPart = 0;

    // double toFraction = 0;

    double onlyFraction = 0;

    if ((double)(int)decimal != decimal) {
        hasFraction = 1;
    }

    if (hasFraction) {
        // toFraction = decimal - wholePart;
        onlyFraction = decimal - wholePart;

        // вроде это уже не нужно
        // while(round(toFraction * FLOATING_PRECISION)/FLOATING_PRECISION != 0) {
        //     fractionPart = 10*fractionPart + (int)(toFraction*10);
        //     toFraction = toFraction*10 - (int)(toFraction*10);
        // }
    }

    wholePart = decimal;

    while (wholePart > 0) {
        int remainder = wholePart % toBase;
        char digit;

        if (remainder < 10) {
            digit = remainder + '0';
        } else {
            digit = remainder - 10 + 'A';
        }

        result[index++] = digit;
        wholePart /= toBase;
    }

    // теперь разложим все символы в правильном порядке, то есть в обратном
    for(int j = 0; j < index-1; j++) {
        char temp = result[j];
        result[j] = result[index-1-j];
        result[index-1-j] = temp;
    }


    if(hasFraction) {
        result[index++] = '.';

        onlyFraction *= toBase;
        while ((int)onlyFraction != 0) {
            int remainder = (int)onlyFraction;
            char digit;

            if (remainder < 10) {
                digit = remainder + '0';
            } else {
                digit = remainder - 10 + 'A';
            }

            result[index++] = digit;
            onlyFraction = onlyFraction - (int)onlyFraction;
            onlyFraction *= toBase;
        }
    }

    // Выводим результат
    for (int i = 0; i < index; i++) {
        printf("%c", result[i]);
    }

}

void printWelcome() {
    clearScreen();
    printf("Добро пожаловать в программу для выполнения операция и расчётов с числами в различных системах счисления.\n");
}
void printMenu() {
    printf("Выберите пункт меню:\n");
    printf("1. Перевести число из одной системы в другую\n");
    printf("2. Выполнить арифметическую операцию между двумя числами\n");
    printf("3. Выход\n");
    printf("Выберите пункт меню:\n");
}

void scenario1() {
    char num[100];
    int fromBase, toBase;
    double numInDec;

    clearScreen();

    // Вводим число и основание системы счисления
    printf("Введите число: ");
    scanf("%s", num);

    printf("Введите основание текущей системы счисления: ");
    scanf("%d", &fromBase);

    numInDec = convertBaseToDec(num, fromBase);

    printf("Ваше число в десятичной системе будет равняется %lf\n", numInDec);

    printf("Введите основание желаемой системы счисления: ");
    scanf("%d", &toBase);

    printDecConvertedToBase(numInDec, toBase);
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

    clearScreen();

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
    printDecConvertedToBase(result, toBase);
    printf("(%d)\n", toBase);

}

int scenario(char choice) {
    if(choice == '1') {
        scenario1();
        return 1;
    } else if(choice == '2') {
        scenario2();
        return 2;
    } else if(choice == '3') {
        return 0;
    } else {
        printf("Некорректный пункт меню\n");
        return -1;
    }
}
int main() {
    char userInput[256];

    printWelcome();

    while(1) {
        printMenu();

        scanf("%s", userInput);
        
        if (scenario(userInput[0]) == 0) {
            break;
        }


        scanf("%s", userInput);
        // system("pause");
        clearScreen();
    }
    return 0;
}