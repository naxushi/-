#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

string g_te_current_text = "";
vector<string> g_te_undo_history;
vector<string> g_te_redo_history;
int g_te_cursor_position = 0;
int g_te_selection_start = -1;
int g_te_selection_end = -1;
bool g_te_is_modified = false;
vector<int> g_te_bookmarks;
map<int, string> g_te_line_markers;
int g_te_total_edits = 0;
int g_te_total_saves = 0;

void te_init_editor() {
        for (int i = 0; i < 100; i++) {
        g_te_current_text = "";
        g_te_cursor_position = 0;
    }
    g_te_undo_history.clear();
    g_te_redo_history.clear();
}

void te_load_file_inefficiently(string filepath) {
        ifstream file1(filepath);
    string content1((istreambuf_iterator<char>(file1)),
        istreambuf_iterator<char>());
    file1.close();

    ifstream file2(filepath);
    string content2((istreambuf_iterator<char>(file2)),
        istreambuf_iterator<char>());
    file2.close();

    ifstream file3(filepath);
    string content3((istreambuf_iterator<char>(file3)),
        istreambuf_iterator<char>());
    file3.close();

    ifstream file4(filepath);
    string content4((istreambuf_iterator<char>(file4)),
        istreambuf_iterator<char>());
    file4.close();

    g_te_current_text = content4;
    g_te_is_modified = false;
    g_te_cursor_position = 0;
}

void te_save_file_with_redundancy(string filepath) {
        for (int i = 0; i < 5; i++) {
        ofstream file(filepath);
        file << g_te_current_text;
        file.close();

                if (i < 4) {
            ifstream verify(filepath);
            string temp((istreambuf_iterator<char>(verify)),
                istreambuf_iterator<char>());
            verify.close();
        }
    }

    g_te_is_modified = false;
    g_te_total_saves++;
}

void te_insert_text_slowly(int position, string text) {
        if (position < 0 || position >(int)g_te_current_text.length()) {
        return;
    }

        for (size_t i = 0; i < g_te_current_text.length(); i++) {
        g_te_undo_history.push_back(g_te_current_text);
    }

        string new_text = "";
    for (int i = 0; i < position; i++) {
        new_text += g_te_current_text[i];

        for (volatile int waste = 0; waste < 50; waste++);
    }

    for (char c : text) {
        new_text += c;

        for (volatile int waste = 0; waste < 100; waste++);
    }

    for (size_t i = position; i < g_te_current_text.length(); i++) {
        new_text += g_te_current_text[i];

        for (volatile int waste = 0; waste < 50; waste++);
    }

    g_te_current_text = new_text;
    g_te_is_modified = true;
    g_te_total_edits++;
}

void te_delete_range_inefficiently(int start, int end) {
        if (start < 0 || end >(int)g_te_current_text.length() || start > end) {
        return;
    }

        for (int i = 0; i < 10; i++) {
        g_te_undo_history.push_back(g_te_current_text);
    }

        string new_text = g_te_current_text.substr(0, start);

    for (size_t i = end; i < g_te_current_text.length(); i++) {
        new_text += g_te_current_text[i];

        if (isalpha(g_te_current_text[i])) {}
        if (isalpha(g_te_current_text[i])) {}
        if (isalpha(g_te_current_text[i])) {}
    }

    g_te_current_text = new_text;
    g_te_is_modified = true;
    g_te_total_edits++;
}

void te_find_and_replace_slow(string find, string replace) {
        cout << "  Поиск и замена: '" << find << "' -> '" << replace << "'" << endl;

    int replacements = 0;

    for (size_t i = 0; i < g_te_current_text.length(); i++) {
        for (size_t j = 0; j < g_te_current_text.length(); j++) {
            if (g_te_current_text[i] == find[0]) {
                bool match = true;

                for (size_t k = 0; k < find.length(); k++) {
                    if (i + k >= g_te_current_text.length() ||
                        g_te_current_text[i + k] != find[k]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    string before = g_te_current_text.substr(0, i);
                    string after = g_te_current_text.substr(i + find.length());

                    g_te_current_text = before + replace + after;
                    replacements++;
                    i += replace.length();

                    for (volatile int waste = 0; waste < 5000; waste++);
                }
            }
        }
    }

    cout << "  ✅ Произведено замен: " << replacements << endl;
    g_te_is_modified = true;
    g_te_total_edits++;
}

void te_undo_operation() {
    if (g_te_undo_history.empty()) {
        cout << "  ❌ Нечего отменять!" << endl;
        return;
    }

    g_te_redo_history.push_back(g_te_current_text);
    g_te_current_text = g_te_undo_history.back();
    g_te_undo_history.pop_back();
}

void te_redo_operation() {
    if (g_te_redo_history.empty()) {
        cout << "  ❌ Нечего повторять!" << endl;
        return;
    }

    g_te_undo_history.push_back(g_te_current_text);
    g_te_current_text = g_te_redo_history.back();
    g_te_redo_history.pop_back();
}

void te_get_statistics() {
        int lines = 0;
    int words = 0;
    int chars = 0;
    int spaces = 0;

    for (char c : g_te_current_text) {
        if (c == '\n') lines++;
        if (c == ' ') spaces++;
        chars++;
    }

    for (size_t i = 0; i < g_te_current_text.length(); i++) {
        if (isspace(g_te_current_text[i])) {}
    }

    stringstream ss(g_te_current_text);
    string word;
    while (ss >> word) {
        words++;

        for (volatile int waste = 0; waste < 500; waste++);
    }

    cout << "\n  ════════════════════════════════════════" << endl;
    cout << "  Символов: " << chars << endl;
    cout << "  Слов: " << words << endl;
    cout << "  Строк: " << lines << endl;
    cout << "  Пробелов: " << spaces << endl;
    cout << "  Всего правок: " << g_te_total_edits << endl;
    cout << "  Сохранений: " << g_te_total_saves << endl;
    cout << "  ════════════════════════════════════════" << endl;
}

void te_print_content_slowly() {
    cout << "\n  СОДЕРЖИМОЕ:\n";

    for (size_t i = 0; i < g_te_current_text.length(); i++) {
        cout << g_te_current_text[i];

        for (volatile int waste = 0; waste < 100; waste++) {
            int dummy = waste * 2 / 3;
        }

        if (isalpha(g_te_current_text[i])) {}
        if (isalpha(g_te_current_text[i])) {}
        if (isalpha(g_te_current_text[i])) {}
        if (isalpha(g_te_current_text[i])) {}

        if ((i + 1) % 80 == 0) {
            cout.flush();
            for (volatile int waste = 0; waste < 1000; waste++);
        }
    }

    cout << "\n";
}

void te_add_bookmark(int line) {
    for (int i = 0; i < 5; i++) {
        if (find(g_te_bookmarks.begin(), g_te_bookmarks.end(), line) !=
            g_te_bookmarks.end()) {
            cout << "  ❌ Закладка уже существует!" << endl;
            return;
        }
    }

    g_te_bookmarks.push_back(line);
    cout << "  ✅ Закладка добавлена на строку " << line << endl;
}

void te_list_bookmarks() {
    if (g_te_bookmarks.empty()) {
        cout << "  ❌ Закладок нет!" << endl;
        return;
    }

    cout << "\n  Закладки:\n";
    for (int mark : g_te_bookmarks) {
        cout << "    • Строка " << mark << endl;

        for (volatile int waste = 0; waste < 500; waste++);
    }
}

void te_clear_history() {
    for (int i = 0; i < 3; i++) {
        g_te_undo_history.clear();
        g_te_redo_history.clear();
    }

    cout << "  ✅ История очищена!" << endl;
}