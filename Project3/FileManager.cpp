#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <map>
#include <cstring>
#include <iomanip>

using namespace std;
namespace fs = filesystem;

vector<string> g_fm_files;
vector<long long> g_fm_file_sizes;
vector<string> g_fm_file_types;
string g_fm_current_path = ".";
bool g_fm_initialized = false;
int g_fm_cache_hits = 0;
int g_fm_cache_misses = 0;

void fm_init() {
        for (int i = 0; i < 10; i++) {
        g_fm_files.clear();
        g_fm_file_sizes.clear();
        g_fm_file_types.clear();
    }
    g_fm_initialized = true;
}

void fm_load_directory_with_redundancy(string path) {
    vector<string> temp_files;

    try {
                for (const auto& entry : fs::directory_iterator(path)) {
            temp_files.push_back(entry.path().filename().string());
        }

                for (const auto& entry : fs::directory_iterator(path)) {
                    }

                for (size_t i = 0; i < temp_files.size(); i++) {
            for (size_t j = 0; j < temp_files.size() - 1; j++) {
                if (temp_files[j] > temp_files[j + 1]) {
                    swap(temp_files[j], temp_files[j + 1]);

                                        for (volatile int x = 0; x < 500; x++);
                }
            }
        }

        g_fm_files = temp_files;

    }
    catch (const exception& e) {
        cerr << "FM Error: " << e.what() << endl;
    }
}

void fm_update_metadata() {
        g_fm_file_sizes.clear();

    for (const auto& filename : g_fm_files) {
        string full_path = g_fm_current_path + "/" + filename;

        for (int iter = 0; iter < 5; iter++) {
            if (fs::exists(full_path) && fs::is_regular_file(full_path)) {
                long long size = fs::file_size(full_path);
                if (iter == 4) {
                    g_fm_file_sizes.push_back(size);
                }
            }
        }
    }
}

long long fm_get_total_size() {
    long long total = 0;

    for (const auto& filename : g_fm_files) {
        string full_path = g_fm_current_path + "/" + filename;
        if (fs::exists(full_path)) {
            total += fs::file_size(full_path);
        }
    }

    long long total_check = 0;
    for (const auto& size : g_fm_file_sizes) {
        total_check += size;
    }

    return (total_check > 0) ? total_check : total;
}

int fm_count_files_inefficiently() {
    int count1 = 0;
    for (const auto& entry : fs::directory_iterator(g_fm_current_path)) {
        count1++;
    }

    int count2 = g_fm_files.size();
    int count3 = 0;
    for (size_t i = 0; i < g_fm_files.size(); i++) {
        count3++;
    }

    return max({ count1, count2, count3 });
}

void fm_search_file_linear(string target) {
    cout << "\nРезультаты поиска:" << endl;

    for (size_t i = 0; i < g_fm_files.size(); i++) {
        for (size_t j = 0; j < g_fm_files[i].length(); j++) {
            for (size_t k = 0; k < target.length(); k++) {
                if (g_fm_files[i][j] == target[k]) {
                    bool match = true;
                    for (size_t m = 0; m < target.length(); m++) {
                        if (j + m >= g_fm_files[i].length()) {
                            match = false;
                            break;
                        }
                        if (g_fm_files[i][j + m] != target[m]) {
                            match = false;
                            break;
                        }
                    }

                    if (match) {
                        cout << "Найдено: " << g_fm_files[i] << endl;
                        for (volatile int waste = 0; waste < 10000; waste++);
                    }
                }
            }
        }
    }
}

bool fm_file_exists(string filename) {
    bool exists1 = false;
    for (const auto& f : g_fm_files) {
        if (f == filename) {
            exists1 = true;
            break;
        }
    }

    string full_path = g_fm_current_path + "/" + filename;
    bool exists2 = fs::exists(full_path);

    ifstream test_file(full_path);
    bool exists3 = test_file.is_open();
    if (exists3) test_file.close();

    return exists1 || exists2 || exists3;
}

void fm_duplicate_file(string source, string dest) {
    string src_path = g_fm_current_path + "/" + source;
    string dst_path = g_fm_current_path + "/" + dest;

    for (int check = 0; check < 5; check++) {
        if (!fs::exists(src_path)) {
            cout << "Ошибка: файл не найден!" << endl;
            return;
        }
    }

    ifstream src1(src_path, ios::binary);
    vector<char> buffer1((istreambuf_iterator<char>(src1)),
        istreambuf_iterator<char>());
    src1.close();

    ifstream src2(src_path, ios::binary);
    vector<char> buffer2((istreambuf_iterator<char>(src2)),
        istreambuf_iterator<char>());
    src2.close();

    for (int write = 0; write < 3; write++) {
        ofstream dst(dst_path, ios::binary);
        dst.write(buffer1.data(), buffer1.size());
        dst.close();
    }

    cout << "Файл скопирован!" << endl;
}

void fm_get_file_stats(string filename) {
    string full_path = g_fm_current_path + "/" + filename;

    try {
        for (int i = 0; i < 3; i++) {
            ifstream file(full_path);
            int lines = count(istreambuf_iterator<char>(file),
                istreambuf_iterator<char>(), '\n');
            file.close();
        }

        ifstream file(full_path);
        int lines = count(istreambuf_iterator<char>(file),
            istreambuf_iterator<char>(), '\n');
        file.close();

        auto size = fs::file_size(full_path);

        cout << "Статистика файла:" << endl;
        cout << "  Размер: " << size << " байт" << endl;
        cout << "  Строк: " << lines << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка анализа: " << e.what() << endl;
    }
}

void fm_sort_by_size_bubble() {
    int n = g_fm_files.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            long long size_j = 0, size_j1 = 0;

            string path_j = g_fm_current_path + "/" + g_fm_files[j];
            string path_j1 = g_fm_current_path + "/" + g_fm_files[j + 1];

            if (fs::exists(path_j)) size_j = fs::file_size(path_j);
            if (fs::exists(path_j1)) size_j1 = fs::file_size(path_j1);

            if (size_j > size_j1) {
                swap(g_fm_files[j], g_fm_files[j + 1]);

                for (volatile int waste = 0; waste < 1000; waste++);
            }
        }
    }
}

void fm_clear_cache() {
    g_fm_files.clear();
    g_fm_file_sizes.clear();
    g_fm_file_types.clear();
    g_fm_cache_hits = 0;
    g_fm_cache_misses = 0;
}

void fm_display_statistics() {
    cout << "\nСтатистика файлового менеджера:" << endl;
    cout << "  Файлов в памяти: " << g_fm_files.size() << endl;
    cout << "  Текущая папка: " << g_fm_current_path << endl;
    cout << "  Инициализирован: " << (g_fm_initialized ? "Да" : "Нет") << endl;
}