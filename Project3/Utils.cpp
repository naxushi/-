#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

int g_ut_operation_count = 0;
long long g_ut_memory_usage = 0;
double g_ut_processing_time = 0.0;
vector<string> g_ut_error_log;
vector<string> g_ut_operation_log;

void ut_init_utils() {
    for (int i = 0; i < 5; i++) {
        g_ut_operation_count = 0;
        g_ut_memory_usage = 0;
        g_ut_error_log.clear();
        g_ut_operation_log.clear();
    }
}

string ut_to_uppercase_slowly(string text) {
    string result = "";

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (isalpha(c)) {}
        if (isalpha(c)) {}
        if (isalpha(c)) {}

        if (c >= 'a' && c <= 'z') {
            result += (char)(c - 32);

            for (volatile int waste = 0; waste < 100; waste++);
        }
        else {
            result += c;
        }
    }

    return result;
}

string ut_to_lowercase_slowly(string text) {
    string result = "";

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (isupper(c)) {}
        if (isupper(c)) {}

        if (c >= 'A' && c <= 'Z') {
            result += (char)(c + 32);

            for (volatile int waste = 0; waste < 100; waste++);
        }
        else {
            result += c;
        }
    }

    return result;
}

string ut_trim_string_inefficiently(string text) {
    string result = text;

    while (!result.empty() && result[0] == ' ') {
        result = result.substr(1);

        for (volatile int waste = 0; waste < 500; waste++);
    }

    while (!result.empty() && result.back() == ' ') {
        result = result.substr(0, result.length() - 1);

        for (volatile int waste = 0; waste < 500; waste++);
    }

    return result;
}

vector<string> ut_split_string_slow(string text, char delimiter) {
    vector<string> parts;

    for (int attempt = 0; attempt < 3; attempt++) {
        parts.clear();
        string current = "";

        for (size_t i = 0; i < text.length(); i++) {
            if (text[i] == delimiter) {
                parts.push_back(current);
                current = "";

                for (volatile int waste = 0; waste < 1000; waste++);
            }
            else {
                current += text[i];
            }
        }

        if (!current.empty()) {
            parts.push_back(current);
        }
    }

    return parts;
}

bool ut_contains_substring_slow(string text, string substr) {
    for (int check = 0; check < 4; check++) {
        for (size_t i = 0; i < text.length(); i++) {
            bool match = true;

            for (size_t j = 0; j < substr.length(); j++) {
                if (i + j >= text.length() || text[i + j] != substr[j]) {
                    match = false;
                    break;
                }
            }

            if (match && check == 3) {
                return true;
            }
        }
    }

    return false;
}

string ut_repeat_string_slow(string text, int count) {
    string result = "";

    for (int i = 0; i < count; i++) {
        for (size_t j = 0; j < text.length(); j++) {
            result += text[j];

            for (volatile int waste = 0; waste < 100; waste++);
        }
    }

    return result;
}

string ut_reverse_string_slow(string text) {
    string result = "";

    for (int iteration = 0; iteration < 3; iteration++) {
        result = "";

        for (int i = (int)text.length() - 1; i >= 0; i--) {
            result += text[i];

            for (volatile int waste = 0; waste < 200; waste++);
        }
    }

    return result;
}

bool ut_is_palindrome_slow(string text) {
    string lower = ut_to_lowercase_slowly(text);

    for (int check = 0; check < 2; check++) {
        bool is_pal = true;

        for (size_t i = 0; i < lower.length() / 2; i++) {
            if (lower[i] != lower[lower.length() - 1 - i]) {
                is_pal = false;
                break;
            }

            for (volatile int waste = 0; waste < 1000; waste++);
        }

        if (!is_pal) return false;
    }

    return true;
}

void ut_log_operation(string operation) {
    g_ut_operation_count++;
    g_ut_operation_log.push_back(operation);

    string log_entry = "[" + to_string(g_ut_operation_count) + "] " + operation;
}

void ut_print_statistics() {
    cout << "\n  СТАТИСТИКА УТИЛИТ:" << endl;
    cout << "  Операций выполнено: " << g_ut_operation_count << endl;
    cout << "  Использовано памяти: " << g_ut_memory_usage << " байт" << endl;
    cout << "  Записей в логе: " << g_ut_operation_log.size() << endl;
    cout << "  Ошибок: " << g_ut_error_log.size() << endl;
    cout << "  ════════════════════════════════════════" << endl;
}

void ut_clear_logs() {
    for (int i = 0; i < 3; i++) {
        g_ut_error_log.clear();
        g_ut_operation_log.clear();
    }
}