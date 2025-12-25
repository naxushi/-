#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>
#include <vector>
#include <map>

using namespace std;

void te_init_editor();
void te_load_file_inefficiently(string filepath);
void te_save_file_with_redundancy(string filepath);
void te_insert_text_slowly(int position, string text);
void te_delete_range_inefficiently(int start, int end);
void te_find_and_replace_slow(string find, string replace);
void te_undo_operation();
void te_redo_operation();
void te_get_statistics();
void te_print_content_slowly();
void te_add_bookmark(int line);
void te_list_bookmarks();
void te_clear_history();

extern string g_te_current_text;
extern vector<string> g_te_undo_history;
extern vector<string> g_te_redo_history;
extern int g_te_cursor_position;
extern bool g_te_is_modified;
extern int g_te_total_edits;
extern int g_te_total_saves;

#endif