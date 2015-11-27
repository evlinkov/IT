#include <iostream>
#include "PreflowPush.h"
#include "DinicFlow.h"

<<<<<<< HEAD
int main()
{
    int a;
    std :: cout << "Введите значение :\n0 - PreflowPush\n1 - DinicFlow\n";
    std :: cin >> a;
    if (a != 0 && a != 1) {
        exit(0);
    }
    int vertices;
    std :: cin >> vertices;
    if (a == 0) {
        PreflowPush maxFlow(0, vertices - 1, vertices);
    }
    else {
        DinicFlow maxFlow(0, vertices - 1, vertices);
    }
    return 0;
}

=======
int main () {
    int a;
    std :: cout << "0 - выбор решения задачи предпотоками\n";
    std :: cout << "1 - выбор решения задачи алгоритмом Диница\n";
    std :: cin >> a;
    if (a == 0) {
        Solve_PushFlow();
    }
    else {
        Solve_DinicFlow();
    }
    return 0;
}
>>>>>>> e6708e8266077a9e9d130442267ea520cc1a848d
