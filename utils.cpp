#include "utils.h"

unordered_map<uint64_t, float> similarityCache;
data_smap filmAvgMap;

uint64_t makeCacheKey(const unsigned short id1, const unsigned short id2) {
    return (static_cast<uint64_t>(min(id1, id2)) << 32) | max(id1, id2);
}

// Compute average ratings for films
void computeFilmAverages(data_map &data) {
    for (auto & [filmId, userRatings] : data) {			//	for loop to iterate over each film
        float sum = 0.0f;
        int count = 0;

        for (auto & [userId, rating] : userRatings) {	//	iterate over each user rating for the film
            sum += rating;								//	(unfortunately this results in high time complexity, but this was the best solution we could come up with)
            count++;
        }
        const float avg = (count > 0) ? (sum / static_cast<float>(count)) : 0.0f;	//	calculate the average rating for the film
        filmAvgMap[filmId] = avg;													//	store the average rating for the film
    }
}

// Normalize ratings for films, by subtracting the average rating from each rating for that particular film
void normalizeFilmRatings(data_map &data) {
    for (auto & [filmId, userRatings] : data) {			//	iterate over the films
        const float avg = filmAvgMap[filmId];			//	get the average rating for the film
        for (auto & [userId, rating] : userRatings) {	//	iterate over the user ratings for the film
            rating -= avg;								//	normalize the rating
        }
    }
}