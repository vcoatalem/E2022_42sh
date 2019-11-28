/**
 * \file expansion.h
 * \brief
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 *
 * Path expansion
 *
 */

#ifndef EXPANSION_H
#define EXPANSION_H

#include <stddef.h>

void get_subdirectories(const char *pattern, char *path,
                            char ***arguments, size_t *nb);

#endif
