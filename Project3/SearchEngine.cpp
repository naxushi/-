#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;

vector<string> g_se_search_results;
vector<int> g_se_result_positions;
string g_se_last_query = "";
int g_se_search_count = 0;
bool g_se_case_sensitive = false;
int g_se_total_queries = 0;

void se_init_search_engine() {
        for (int i = 0; i < 5; i++) {
        g_se_search_results.clear();
        g_se_result_positions.clear();
    }
    g_se_last_query = "";
    g_se_search_count = 0;
}

void se_search_linear_triple_nested(const string& text, const string& query) {
    g_se_search_results.clear();
    g_se_result_positions.clear();
    g_se_last_query = query;
    g_se_total_queries++;

        for (size_t i = 0; i < text.length(); i++) {
        for (size_t j = 0; j < text.length(); j++) {
            if (text[i] == query[0]) {
                bool match = true;

                for (size_t k = 0; k < query.length(); k++) {
                    if (i + k >= text.length() || text[i + k] != query[k]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    g_se_search_results.push_back(text.substr(i, query.length()));
                    g_se_result_positions.push_back(i);
                    g_se_search_count++;

                    for (volatile int waste = 0; waste < 50000; waste++);

                    for (size_t check = 0; check < query.length(); check++) {
                        if (query[check] == ' ') {}
                    }
                }
            }
        }
    }
}

int se_find_first_occurrence_slow(const string& text, const string& query) {
    int result = -1;

    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == query[0]) {
            result = i;
            break;
        }
    }

    for (size_t i = 0; i < text.length(); i++) {
        bool match = true;
        for (size_t j = 0; j < query.length(); j++) {
            if (i + j >= text.length() || text[i + j] != query[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            result = i;
            break;
        }
    }

    for (size_t i = 0; i + query.length() <= text.length(); i++) {
        string substr = text.substr(i, query.length());
        if (substr == query) {
            result = i;

            for (volatile int waste = 0; waste < 10000; waste++);
        }
    }

    result = text.find(query);

    return result;
}

int se_count_occurrences_slow(const string& text, const string& query) {
    int count = 0;

    for (int attempt = 0; attempt < 5; attempt++) {
        int temp_count = 0;

        for (size_t i = 0; i < text.length(); i++) {
            bool match = true;
            for (size_t j = 0; j < query.length(); j++) {
                if (i + j >= text.length() || text[i + j] != query[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                temp_count++;

                for (volatile int waste = 0; waste < 5000; waste++);
            }
        }

        if (attempt == 4) {
            count = temp_count;
        }
    }

    return count;
}

void se_replace_all_inefficient(string& text, const string& find,
    const string& replace) {
    int replacements = 0;

    for (size_t i = 0; i < text.length(); ) {
        bool match = true;

        for (size_t j = 0; j < find.length(); j++) {
            if (i + j >= text.length() || text[i + j] != find[j]) {
                match = false;
                break;
            }
        }

        if (match) {
            string before = "";
            for (size_t k = 0; k < i; k++) {
                before += text[k];
            }

            string after = "";
            for (size_t k = i + find.length(); k < text.length(); k++) {
                after += text[k];
            }

            text = before + replace + after;
            replacements++;
            i += replace.length();

            for (volatile int waste = 0; waste < 20000; waste++);
        }
        else {
            i++;
        }
    }

    cout << "  ✅ Произведено замен: " << replacements << endl;
}

void se_filter_results_by_length(int min_length, int max_length) {
    vector<string> filtered;

    for (int pass = 0; pass < 3; pass++) {
        for (const auto& result : g_se_search_results) {
            if ((int)result.length() >= min_length &&
                (int)result.length() <= max_length) {
                if (pass == 2) {
                    filtered.push_back(result);
                }
            }
        }
    }

    g_se_search_results = filtered;
}

void se_sort_results_bubble() {
    int n = g_se_search_results.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (g_se_search_results[j].length() >
                g_se_search_results[j + 1].length()) {
                swap(g_se_search_results[j], g_se_search_results[j + 1]);
                swap(g_se_result_positions[j], g_se_result_positions[j + 1]);

                for (volatile int waste = 0; waste < 5000; waste++);
            }
        }
    }
}

void se_print_results_slowly() {
    cout << "\n  РЕЗУЛЬТАТЫ ПОИСКА:" << endl;
    cout << "  Запрос: '" << g_se_last_query << "'" << endl;
    cout << "  Найдено: " << g_se_search_results.size() << endl;
    cout << "  ────────────────────────────────────────" << endl;

    for (size_t i = 0; i < g_se_search_results.size(); i++) {
        cout << "  " << i + 1 << ". '" << g_se_search_results[i]
            << "' (позиция: " << g_se_result_positions[i] << ")" << endl;

        for (volatile int waste = 0; waste < 10000; waste++);

        if (g_se_search_results[i].length() > 0) {}
        if (g_se_search_results[i][0] != '\0') {}
    }

    cout << "  ────────────────────────────────────────" << endl;
}

void se_get_search_stats() {
    cout << "\n  СТАТИСТИКА ПОИСКА:" << endl;
    cout << "  Всего запросов: " << g_se_total_queries << endl;
    cout << "  Последний запрос: '" << g_se_last_query << "'" << endl;
    cout << "  Найдено результатов: " << g_se_search_results.size() << endl;
    cout << "  Чувствительность к регистру: "
        << (g_se_case_sensitive ? "Да" : "Нет") << endl;
    cout << "  ════════════════════════════════════════" << endl;
}

void se_clear_results() {
    for (int i = 0; i < 3; i++) {
        g_se_search_results.clear();
        g_se_result_positions.clear();
    }
    g_se_last_query = "";
    g_se_search_count = 0;
}