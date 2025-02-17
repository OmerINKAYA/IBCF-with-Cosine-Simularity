#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>	     // for unordered_map hash table data structure usage
#include <vector>			          // for vector data structure usage
#include <cmath>			           // for square root in cosine similarity calculation
#include <cstdint>            // for uint64_t data type usage

using namespace std;		// standard library namespace declaration for usage of standard library functions
using data_map		= 	unordered_map<unsigned short, unordered_map<unsigned short, float>>;	// unordered_map hash table special alias for storing user ratings for films
using data_smap		=	unordered_map<unsigned short, float>;									// unordered_map hash table special alias for storing user ratings for films

/*
 GLOBAL VARIABLES:
 * These are our global variables for film rating analysis.
 * "similarityCache" is the cache for storing "cosine similarities" between films.
 * "filmAvgMap" is the unordered_map data structure declaration for storing "average ratings" for films.
*/
extern unordered_map<uint64_t, float>	similarityCache;
extern data_smap		filmAvgMap;

/*
 * This is a function we made for creating a cache key for storing cosine similarities between films.
 * The cache key is created by the function by combining two film IDs.
*/
uint64_t makeCacheKey(const unsigned short id1, const unsigned short id2);

/*
 FUNCTION DECLARATIONS
 * These are our function declarations for film rating analysis.
*/
void	computeFilmAverages(data_map &data);
void	normalizeFilmRatings(data_map &data);

#endif
