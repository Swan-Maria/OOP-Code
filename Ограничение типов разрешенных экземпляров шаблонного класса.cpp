// ��� ������ =delete ����� ��������� �������� ����������� ��������� ������� � ������������� ������

#include <iostream>

template <typename T>
void bar(T param) { /*..*/ }

template <>
void bar<int>(int) = delete;

int main() {
    bar<int>(5);
}