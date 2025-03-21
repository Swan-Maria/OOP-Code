#include <iostream>

template <class T> 
class Repository8
{
private:
    T m_array[8];
public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }

    const T& get(int index)
    {
        return m_array[index];
    }
};

template <>
class Repository8<bool>
{
private:
    unsigned char m_data;

public:
    Repository8() : m_data(0) {}

    void set(int index, bool value)
    {
        unsigned char bit = 1 << index;

        if (value) // якщо на вході у нас true, то біт потрібно "увімкнути"
            m_data |= bit; // використовуємо побітове АБО, щоб "увімкнути" біт
        else // якщо на вході у нас false, то біт потрібно "вимкнути" 
            m_data &= ~bit; // використовуємо побітове І, щоб "вимкнути" біт
    }

    bool get(int index)
    {
        unsigned char bit = 1 << index;

        // Використовуємо побітове І для отримання значення біта, 
        // а потім виконується його неявна конвертація в тип bool
        return (m_data & bit) != 0;
    }
};

int main()
{
    Repository8<int> intRepository;
    for (int count = 0; count < 8; ++count)
        intRepository.set(count, count);
    for (int count = 0; count < 8; ++count)
        std::cout << intRepository.get(count) << '\n';

    Repository8<bool> boolRepository;
    for (int count = 0; count < 8; ++count)
        boolRepository.set(count, count % 5);
    for (int count = 0; count < 8; ++count)
        std::cout << (boolRepository.get(count) ? "true" : "false") << '\n';

    return 0;
}