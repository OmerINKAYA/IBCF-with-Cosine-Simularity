#ifndef IBCF_H
#define IBCF_H

#include "utils.h"          // for utility functions
#include <algorithm>		// for sorting and partial sorting functionality

float cosine_similarity_item(const unsigned short filmIdA, const data_smap &filmA, const unsigned short filmIdB, const data_smap &filmB);
float predictRatingIBCF(const unsigned short userId, const unsigned short targetFilmId, data_map &data, const int K);

#endif