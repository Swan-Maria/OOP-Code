// � ��� ���� �������, ����������� ����� �����. ����� �����.
// ��� ��� �� ����������, ���� ���������� ����� ��� ����� �������� ����� � ��������� ������?
// �������� � ��������� ������ ����������� � �������� (������ �����������������, ����������) �� ������ �����.
// ������ ��������� ���������� �������, �� ������ ��������� ������� �������������� �� ������������ �����.

#include <iostream>

void foo(int numberOfSeats) {
    std::cout << "Number of seats: " << numberOfSeats << '\n';
}

void foo(double) = delete;

int main() {
    foo(5);
    foo(5.6f);
}