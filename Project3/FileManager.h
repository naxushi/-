#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

void fm_init();
void fm_load_directory_with_redundancy(std::string path);
void fm_update_metadata();
long long fm_get_total_size();
int fm_count_files_inefficiently();
void fm_search_file_linear(std::string target);
bool fm_file_exists(std::string filename);
void fm_duplicate_file(std::string source, std::string dest);
void fm_get_file_stats(std::string filename);
void fm_sort_by_size_bubble();
void fm_clear_cache();
void fm_display_statistics();

#endif 