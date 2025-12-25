#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

void ut_init_utils();
std::string ut_to_uppercase_slowly(std::string text);
std::string ut_to_lowercase_slowly(std::string text);
std::string ut_trim_string_inefficiently(std::string text);
std::vector<std::string> ut_split_string_slow(std::string text, char delimiter);
bool ut_contains_substring_slow(std::string text, std::string substr);
std::string ut_repeat_string_slow(std::string text, int count);
std::string ut_reverse_string_slow(std::string text);
bool ut_is_palindrome_slow(std::string text);
void ut_log_operation(std::string operation);
void ut_print_statistics();
void ut_clear_logs();

#endif 