#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <atomic>

const std::string filename = "D:\\Visual Studio Repos\\Messager\\x64\\Debug\\chat.txt";

// !!! ПЕРЕД ЗАПУСКОМ каждый пользователь меняет эти строки на своё имя
const std::string username = "user2";
const std::string peername = "user1";

std::atomic<bool> running(true);

void read_messages_loop(std::streampos& position)
{
    while (running)
    {
        std::ifstream chatRead(filename, std::ios::in);
        if (chatRead.is_open())
        {
            chatRead.seekg(position);
            std::string line;
            bool updated = false;

            while (std::getline(chatRead, line))
            {
                // Разбираем строку: username|time|message
                size_t delim1 = line.find('|');
                size_t delim2 = line.find('|', delim1 + 1);

                if (delim1 != std::string::npos && delim2 != std::string::npos)
                {
                    std::string author = line.substr(0, delim1);
                    std::string timestamp = line.substr(delim1 + 1, delim2 - delim1 - 1);
                    std::string message = line.substr(delim2 + 1);

                    // Показываем любое сообщение (и своё, и чужое)
                    std::cout << "\n" << author << " [" << timestamp << "]: " << message << "\n> ";
                    std::cout.flush();

                    updated = true;
                }

                position = chatRead.tellg();
            }
            chatRead.close();

            // Сохраняем позицию только если было новое сообщение
            if (updated) {
                std::ofstream savePosFile("position_" + username + ".txt");
                if (savePosFile.is_open()) {
                    savePosFile << static_cast<std::streamoff>(position);
                    savePosFile.close();
                }
            }
        }

        Sleep(200); // Проверяем каждые 200 мс
    }
}

int main()
{
    std::cout << "Welcome to the Messager with " << peername << "!\n"
        << "Enter /exit to exit the program.\n";

    std::streampos position = 0;
    std::ifstream posFile("position_" + username + ".txt");
    if (posFile.is_open())
    {
        std::streamoff posValue;
        posFile >> posValue;
        position = static_cast<std::streampos>(posValue);
        posFile.close();
    }

    // Стартуем поток чтения
    std::thread readerThread(read_messages_loop, std::ref(position));

    // Основной цикл для ввода сообщений
    while (true)
    {
        std::cout << "> ";
        std::string message;
        std::getline(std::cin, message);

        if (message == "/exit")
            break;

        std::ofstream chatWrite(filename, std::ios::app);
        if (!chatWrite.is_open())
        {
            std::cerr << "Error opening file for writing\n";
            break;
        }

        time_t sec = time(nullptr);
        struct tm timeinfo;
        localtime_s(&timeinfo, &sec);

        char timeStr[26];
        asctime_s(timeStr, sizeof(timeStr), &timeinfo);
        timeStr[strcspn(timeStr, "\n")] = '\0';

        chatWrite << username << "|" << timeStr << "|" << message << '\n';
        chatWrite.flush(); // Принудительно сбрасываем буфер на диск
        chatWrite.close();

        // После записи сразу обновляем позицию (на всякий случай)
        std::ifstream tmp(filename, std::ios::ate);
        if (tmp.is_open()) {
            position = tmp.tellg();
            tmp.close();

            std::ofstream savePosFile("position_" + username + ".txt");
            if (savePosFile.is_open()) {
                savePosFile << static_cast<std::streamoff>(position);
                savePosFile.close();
            }
        }
    }

    running = false;
    readerThread.join();

    std::cout << "Exiting chat.\n";
    return 0;
}
