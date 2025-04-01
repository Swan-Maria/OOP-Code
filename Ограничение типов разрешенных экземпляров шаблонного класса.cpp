// При помощи =delete можно запретить создание экземпляров шаблонной функции с определенными типами

#include <iostream>

template <typename T>
void bar(T param) { /*..*/ }

template <>
void bar<int>(int) = delete;

int main() {
    bar<int>(5);
}