#include <iostream> 
#include <windows.h>
#include <fstream> 
#include <string>
#include <thread>

const std::string chat_file_name = "chat.txt";
const std::string user_name = "User2";
const std::string peer_name = "User1";
std::string pos_file_name = "position_user2.txt";
int unread_count = 0;
bool running(true);

void count_unread_messages(std::streampos& position)
{
    std::ifstream chat_file(chat_file_name, std::ios::in);
    if (chat_file)
    {
        chat_file.seekg(position);
        std::string line;

        while (std::getline(chat_file, line))
        {
            unread_count++;
        }
        chat_file.close();

        if (unread_count > 0)
        {
            std::cout << "\nYou have " << unread_count << " unread messages from " << peer_name << "!\n";
        }
    }
}

void reading_messages(std::streampos & position)
{
    while (running)
    {
        std::ifstream Reading(chat_file_name, std::ios::in);
        if (Reading)
        {
            Reading.seekg(position);
            std::string line;
            bool updated = false;

            while (std::getline(Reading, line))
            {
                size_t delim = line.find('|');
                if (delim != std::string::npos)
                {
                    std::string author = line.substr(0, delim);
                    std::string message = line.substr(delim + 1);
                    std::cout << "\n" << author << ": " << message;
					std::cout.flush(); // Обновляем вывод
                    updated = true;
                }
                position = Reading.tellg();
            }
            Reading.close();
            if (updated)
            {
                std::ofstream save_position(pos_file_name);
                if (save_position)
                {
                    save_position << static_cast<std::streamoff>(position);
                    save_position.close();
                }
                std::cout << "\n>> ";
            }
        }
        Sleep(200);
    }
}


int main()
{
    std::cout << "Welcome to the Messenger with " << peer_name << "!\n"
        << "Enter '/exit' to exit the program.\n";

    // Определяем начальную позицию чтения из файла
    std::streampos position = 0;
    std::ifstream position_file(pos_file_name);
    if (position_file.is_open())
    {
        std::streamoff position_value;
        position_file >> position_value;
        position = static_cast<std::streampos>(position_value);
        position_file.close();
    }

    count_unread_messages(position);

    std::thread readerThread(reading_messages, std::ref(position));

    // Основной цикл для отправки сообщений
    while (true)
    {
        std::cout << ">> ";
        std::string message;
        std::getline(std::cin, message);
        if (message == "/exit")
        {
            break;
        }

        std::ofstream chatWrite(chat_file_name, std::ios::app);
        if (!chatWrite)
        {
            std::cerr << "Error opening file for writing\n";
            break;
        }

        chatWrite << user_name << "|" << message << '\n';
		chatWrite.flush();
        chatWrite.close();

        std::ifstream tmp(chat_file_name, std::ios::ate);
        if (tmp.is_open()) {
            position = tmp.tellg();
            tmp.close();

            // Сохраняем новую позицию в отдельный файл
            std::ofstream save_position(pos_file_name);
            if (save_position) {
                save_position << static_cast<std::streamoff>(position);
                save_position.close();
            }
        }
    }

    running = false;
    readerThread.join();

    return 0;
}