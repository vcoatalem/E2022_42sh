/**
 * \file expansion.h
 * \brief
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 *
 *
 */

#ifndef EXPANSION_H
#define EXPANSION_H

#include <stddef.h>

#define EXPANSION_SUCCESS 0
#define EXPANSION_FAILURE 1
#define EXPANSION_ERROR 2

void clean_pattern(char *pattern);

int check_star(char *path, size_t *index, size_t size, char next);

int check_question_mark(size_t *index, size_t size);

int check_brackets(char *path, size_t *index, size_t size, char *brackets);

#endif
