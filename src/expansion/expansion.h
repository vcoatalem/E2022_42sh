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

/**
 * \brief add all files and directories that match the shell wildcard in arguments
 *
 * \param const char *pattern
 */

char **expand_file_pattern(char *pattern, void *bundle_ptr);

#endif
