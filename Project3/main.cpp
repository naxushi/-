#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

class FileManager {
private:
    std::string currentDirectory;    // Текущая рабочая директория
    std::vector<std::string> files;  // Список файлов в текущей директории
    std::string currentEditFile;     // Имя текущего редактируемого файла
    std::string editor_buffer;       // Буфер редактора для текущего файла

    void printSeparator() {
        std::cout << "  ";
        for (int i = 0; i < 76; i++) std::cout << "-";
        std::cout << "\n";
    }

    void printBorder(const std::string& title = "") {
        std::cout << "  ";
        for (int i = 0; i < 76; i++) std::cout << "=";
        std::cout << "\n";

        if (!title.empty()) {
            int padding = (76 - static_cast<int>(title.length())) / 2;
            std::cout << "  |";
            for (int i = 0; i < padding; i++) std::cout << " ";
            std::cout << title;
            for (int i = padding + static_cast<int>(title.length()); i < 76; i++) std::cout << " ";
            std::cout << "|\n";
            std::cout << "  ";
            for (int i = 0; i < 76; i++) std::cout << "=";
            std::cout << "\n";
        }
    }

    void waitForEnter() {
        std::cout << "\n  Нажмите Enter для продолжения...";
        std::cin.get();
    }

public:
    //Конструктор класса
    FileManager() : currentDirectory("."), currentEditFile(""), editor_buffer("") {}

    void displayMainMenu() {
        printBorder("MAIN MENU");

        std::cout << "  1.  Read file\n";
        std::cout << "  2.  Edit file\n";
        std::cout << "  3.  Save file\n";
        std::cout << "  4.  Search in file\n";
        std::cout << "  5.  Delete file\n";
        std::cout << "  6.  Create new file\n";
        std::cout << "  7.  Go to folder\n";
        std::cout << "  8.  Copy file\n";
        std::cout << "  9.  Rename file\n";
        std::cout << "  10. File analysis\n";
        std::cout << "  11. Backup\n";
        printSeparator();
        std::cout << "  99. Exit\n";
        printBorder();
    }

     //Отображает содержимое текущей директории с сортировкой
    void listFilesWithQuickSort() {
        try {
            files.clear();
            // Собираем все файлы и папки в текущей директории
            for (const auto& entry : fs::directory_iterator(currentDirectory)) {
                files.push_back(entry.path().filename().string());
            }
            std::sort(files.begin(), files.end()); // Сортируем по алфавиту

            printBorder("SODERZHIMOE KATALOGA");
            std::cout << "  Path: " << currentDirectory << "\n";
            std::cout << "  Elements: " << files.size() << "\n";
            printSeparator();

            if (files.empty()) {
                std::cout << "  Folder is empty\n";
                printSeparator();
                return;
            }

            // Заголовок таблицы
            std::cout << "  " << std::left << std::setw(4) << "N";
            std::cout << std::left << std::setw(40) << "Name";
            std::cout << std::left << std::setw(15) << "Size";
            std::cout << "Type\n";
            printSeparator();

            // Вывод информации о каждом файле/папке
            for (size_t i = 0; i < files.size(); i++) {
                std::string full_path = currentDirectory + "/" + files[i];
                bool isDir = fs::is_directory(full_path);
                long long size = 0;

                if (!isDir) {
                    try {
                        size = fs::file_size(full_path);
                    }
                    catch (...) {
                        size = 0;
                    }
                }

                std::cout << "  " << std::left << std::setw(4) << static_cast<int>(i + 1);

                // Обрезаем длинные имена файлов
                std::string display_name = files[i];
                if (display_name.length() > 36) {
                    display_name = display_name.substr(0, 33) + "...";
                }
                std::cout << std::left << std::setw(40) << display_name;

                if (isDir) {
                    std::cout << std::left << std::setw(15) << "-";
                    std::cout << "Folder\n";
                }
                else {
                    // Форматируем размер файла
                    std::string size_str;
                    if (size < 1024) {
                        size_str = std::to_string(size) + " B";
                    }
                    else if (size < 1024 * 1024) {
                        size_str = std::to_string(size / 1024) + " KB";
                    }
                    else {
                        size_str = std::to_string(size / (1024 * 1024)) + " MB";
                    }
                    std::cout << std::left << std::setw(15) << size_str;
                    std::cout << "File\n";
                }
            }
            printSeparator();
        }
        catch (const std::exception& e) {
            std::cout << "\n  Error: " << e.what() << std::endl;
        }
    }

    //Читает выбранный файл в буфер редактора
    void readFile() {
        if (files.empty()) {
            std::cout << "\n  Folder is empty!";
            return;
        }
        std::cout << "\n  Choose file number: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "  Invalid choice!";
            return;
        }

        std::string filename = currentDirectory + "/" + files[choice - 1];

        if (fs::is_directory(filename)) {
            std::cout << "  This is a folder!";
            return;
        }

        try {
            std::ifstream file(filename);
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            currentEditFile = filename;
            editor_buffer = content;

            system("cls");
            printBorder("FILE CONTENT");
            std::cout << "  File: " << filename << "\n";
            std::cout << "  Size: " << content.length() << " bytes\n";
            printSeparator();

            std::cout << content << "\n";

            printSeparator();
            std::cout << "\n  File loaded successfully\n";
        }
        catch (const std::exception& e) {
            std::cout << "\n  Error: " << e.what() << "\n";
        }
    }

    // Редактирует текущий файл в буфере
    void editFile() {
        if (currentEditFile.empty()) {
            std::cout << "\n  Open file first!";
            waitForEnter();
            return;
        }

        system("cls");
        printBorder("EDIT FILE");
        std::cout << "  File: " << currentEditFile << "\n";
        std::cout << "  Size: " << editor_buffer.length() << " bytes\n";
        printSeparator();
        std::cout << "\n  Enter new content (EOF on new line to finish):\n";
        printSeparator();

        std::string new_content;
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "EOF") break; // Ключевое слово для завершения ввода
            new_content += line + "\n";
        }
        editor_buffer = new_content;

        std::cout << "\n  Content modified!\n";
        waitForEnter();
    }

     //Сохраняет содержимое буфера в файл
    void saveFile() {
        if (currentEditFile.empty()) {
            std::cout << "\n  No open file!";
            return;
        }

        system("cls");
        printBorder("SAVE FILE");
        std::cout << "  File: " << currentEditFile << "\n";
        std::cout << "  Size: " << editor_buffer.length() << " bytes\n";
        printSeparator();

        try {
            std::ofstream file(currentEditFile);
            file << editor_buffer;
            file.close();

            std::cout << "  File saved successfully!\n";
        }
        catch (const std::exception& e) {
            std::cout << "  Error: " << e.what() << "\n";
        }
    }

     //Выполняет поиск текста в текущем файле
    void searchInFile() {
        if (editor_buffer.empty()) {
            std::cout << "\n  Open file first!";
            return;
        }

        system("cls");
        printBorder("SEARCH");

        std::cout << "\n  Enter search query: ";
        std::string query;
        std::getline(std::cin, query);

        if (query.empty()) {
            std::cout << "\n  Empty query!";
            return;
        }

        // Поиск всех вхождений
        std::vector<std::string> search_results;
        size_t pos = 0;
        while ((pos = editor_buffer.find(query, pos)) != std::string::npos) {
            search_results.push_back(std::to_string(pos));
            pos += query.length();
        }

        system("chcp 1251");
        printBorder("SEARCH RESULTS");
        std::cout << "  Query: '" << query << "'\n";
        std::cout << "  Found: " << search_results.size() << "\n";
        printSeparator();

        if (search_results.empty()) {
            std::cout << "  Not found\n";
        }
        else {
            // Ограничиваем вывод до 20 результатов
            size_t max_display = std::min(search_results.size(), static_cast<size_t>(20));
            for (size_t i = 0; i < max_display; i++) {
                std::cout << "  " << i + 1 << ". Position " << search_results[i] << "\n";
            }

            if (search_results.size() > 20) {
                std::cout << "  ... and " << (search_results.size() - 20) << " more\n";
            }
        }
        printSeparator();
    }

    //Удаляет выбранный файл
    void deleteFile() {
        if (files.empty()) {
            std::cout << "\n  No files!";
            return;
        }

        std::cout << "\n  Choose file number: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "  Invalid choice!";
            return;
        }

        std::string filepath = currentDirectory + "/" + files[choice - 1];

        if (fs::is_directory(filepath)) {
            std::cout << "  This is a folder!";
            return;
        }

        try {
            fs::remove(filepath);
            std::cout << "\n  File deleted!\n";
        }
        catch (const std::exception& e) {
            std::cout << "\n  Error: " << e.what() << "\n";
        }
    }

     //Создает новый файл
    void createNewFile() {
        std::cout << "\n  Enter filename: ";
        std::string filename;
        std::getline(std::cin, filename);

        if (filename.empty()) {
            std::cout << "  Empty filename!";
            return;
        }

        std::string filepath = currentDirectory + "/" + filename;

        try {
            std::ofstream file(filepath);
            file << "";
            file.close();

            std::cout << "  File created!\n";
        }
        catch (const std::exception& e) {
            std::cout << "  Error: " << e.what() << "\n";
        }
    }

    //Изменяет текущую директорию
    void navigateDirectory() {
        std::cout << "\n  Enter path (.. for parent): ";
        std::string newdir;
        std::getline(std::cin, newdir);

        if (newdir == "..") {
            if (currentDirectory != ".") {
                currentDirectory = ".";
            }
        }
        else if (!newdir.empty()) {
            std::string test_path = currentDirectory + "/" + newdir;
            if (fs::exists(test_path) && fs::is_directory(test_path)) {
                currentDirectory = test_path;
                std::cout << "  Changed to: " << currentDirectory << "\n";
            }
            else {
                std::cout << "  Folder not found!";
            }
        }
    }

     //Копирует выбранный файл
    void copyFile() {
        if (files.empty()) {
            std::cout << "\n  No files!";
            return;
        }

        std::cout << "\n  Choose file number: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "  Invalid choice!";
            return;
        }

        std::string source = currentDirectory + "/" + files[choice - 1];
        std::string dest = source + ".copy";

        if (fs::is_directory(source)) {
            std::cout << "  This is a folder!";
            return;
        }

        try {
            std::ifstream src(source, std::ios::binary);
            std::ofstream dst(dest, std::ios::binary);
            dst << src.rdbuf();
            src.close();
            dst.close();
            std::cout << "\n  File copied!\n";
        }
        catch (const std::exception& e) {
            std::cout << "\n  Error: " << e.what() << "\n";
        }
    }
    //Переименовывает выбранный файл
    void renameFile() {
        if (files.empty()) {
            std::cout << "\n  No files!";
            return;
        }

        std::cout << "\n  Choose file number: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "  Invalid choice!";
            return;
        }

        std::cout << "  Enter new name: ";
        std::string new_name;
        std::getline(std::cin, new_name);

        if (new_name.empty()) {
            std::cout << "  Empty filename!";
            return;
        }

        std::string old_path = currentDirectory + "/" + files[choice - 1];
        std::string new_path = currentDirectory + "/" + new_name;

        try {
            fs::rename(old_path, new_path);
            std::cout << "  File renamed!\n";
        }
        catch (const std::exception& e) {
            std::cout << "  Error: " << e.what() << "\n";
        }
    }

     //Анализирует свойства выбранного файла
    void analyzeFileProperties() {
        if (files.empty()) {
            std::cout << "\n  No files!";
            return;
        }

        std::cout << "\n  Choose file number: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "  Invalid choice!";
            return;
        }

        std::string filepath = currentDirectory + "/" + files[choice - 1];

        if (fs::is_directory(filepath)) {
            std::cout << "  This is a folder!";
            return;
        }

        try {
            system("cls");
            printBorder("FILE ANALYSIS");

            auto size = fs::file_size(filepath);

            std::ifstream file(filepath);
            int lines = std::count(std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>(), '\n');
            file.close();

            std::cout << "  Name: " << files[choice - 1] << "\n";
            std::cout << "  Size: " << size << " bytes\n";
            std::cout << "  Lines: " << lines << "\n";
            printSeparator();
        }
        catch (const std::exception& e) {
            std::cout << "  Error: " << e.what() << "\n";
        }
    }

    //Создает резервную копию текущего файла
    void createBackup() {
        if (currentEditFile.empty()) {
            std::cout << "\n  No open file!";
            return;
        }

        system("cls");
        printBorder("CREATE BACKUP");
        std::cout << "  File: " << currentEditFile << "\n";
        printSeparator();

        try {
            std::string backup_name = currentEditFile + ".backup";
            std::ofstream backup(backup_name);
            backup << editor_buffer;
            backup.close();

            std::cout << "  Backup created: " << backup_name << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "  Error: " << e.what() << "\n";
        }
    }
    void run() {
        system("chcp 1251");
        std::system("chcp 65001 > nul");
        system("cls");

        int choice = 0;

        while (choice != 99) {
            system("chcp 1251");
            listFilesWithQuickSort();
            displayMainMenu();
            std::cout << "\n  Ваш выбор: ";
            std::cin >> choice;
            std::cin.ignore(10000, '\n');

            switch (choice) {
            case 1:
                readFile();
                waitForEnter();
                break;
            case 2:
                editFile();
                break;
            case 3:
                saveFile();
                waitForEnter();
                break;
            case 4:
                searchInFile();
                waitForEnter();
                break;
            case 5:
                deleteFile();
                waitForEnter();
                break;
            case 6:
                createNewFile();
                waitForEnter();
                break;
            case 7:
                navigateDirectory();
                break;
            case 8:
                copyFile();
                waitForEnter();
                break;
            case 9:
                renameFile();
                waitForEnter();
                break;
            case 10:
                analyzeFileProperties();
                waitForEnter();
                break;
            case 11:
                createBackup();
                waitForEnter();
                break;
            case 99:
                std::cout << "\n\n";
                printBorder("ВЫХОД");
                std::cout << "  Спасибо за использование Грязного Редактора!\n";
                std::cout << "  До свидания!\n";
                printBorder();
                std::cout << "\n\n";
                break;
            default:
                std::cout << "\n  ❌ Неверный выбор! Попробуйте снова.";
                waitForEnter();
            }
        }
    }
};
int main() {
    FileManager manager;
    manager.run();
    return 0;
}