/**
 * Keymatcher.
 *
 * It is a keyword matcher which can fastly identify whether a keyword is contained
 * in a keyword pool
 *
 * => This is a simplified version of Radix tree
 */
#ifndef __KEYMATCHER_H__
#define __KEYMATCHER_H__

#include <stdbool.h>

typedef struct keymatcher_ keymatcher;

keymatcher* new_keymatcher();

void addkey(keymatcher* km, const char* key);

bool is_match(keymatcher* km, const char* key);

void dump_km(keymatcher* km);

#endif