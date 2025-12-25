#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <vector>

void se_init_search_engine();
void se_search_linear_triple_nested(const std::string& text, const std::string& query);
int se_find_first_occurrence_slow(const std::string& text, const std::string& query);
int se_count_occurrences_slow(const std::string& text, const std::string& query);
void se_replace_all_inefficient(std::string& text, const std::string& find,
    const std::string& replace);
void se_filter_results_by_length(int min_length, int max_length);
void se_sort_results_bubble();
void se_print_results_slowly();
void se_get_search_stats();
void se_clear_results();

#endif 