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
 * \param char *path
 * \param char **arguments
 * \param size_t *nb
 */
void get_find(const char *pattern, char *path,
                            char ***arguments, size_t *nb);

#endif
