#include "ibcf.h"

/*
 * This is a function we made for calculating the cosine similarity between two films using IBCF (Item-Based Collaborative Filtering) method.
 * We found out that compared to the User-Based Collaborative Filtering method, the IBCF method is more efficient and accurate for our dataset.
 * We also tried the Pearson method with UBCF, but Cosine Similarity with IBCF turned out to be more efficient and accurate in our trial-and-error experiments.
 * The cosine similarity is calculated by iterating over the user ratings for the films, and the ratings are stored in the cache for future use.
*/
float cosine_similarity_item(const unsigned short filmIdA, const data_smap &filmA, const unsigned short filmIdB, const data_smap &filmB) {

    if (filmA.size() < 5 || filmB.size() < 5) return 0.0f;	//	if the number of ratings is less than 5, return 0.0

    const uint64_t cacheKey = makeCacheKey(filmIdA, filmIdB);		//	create a cache key for storing cosine similarities between films
    if (const auto it = similarityCache.find(cacheKey); it != similarityCache.end()) {	//	if the cosine similarity is already stored in the cache, return the cosine similarity value from there
        return it->second;
    }

    //	Define variables for cosine similarity calculation
    float numerator = 0.0f;
    float sumOfSquaresA = 0.0f;
    float sumOfSquaresB = 0.0f;
    unsigned short commonCount = 0;


	// iterate over the user ratings for the films
    if (filmA.size() <= filmB.size()) { // iterate over the user ratings for the film with the least number of ratings
        for (auto &[userId, ratingA] : filmA) {
            if (auto it = filmB.find(userId); it != filmB.end()) {	//	check if the user has rated the film
                const float ratingB = it->second;					//	get the rating for the film
                numerator      += ratingA * ratingB;				//	calculate the numerator for cosine similarity calculation
                sumOfSquaresA  += ratingA * ratingA;				//	calculate the sum of squares for film A
                sumOfSquaresB  += ratingB * ratingB;				//	calculate the sum of squares for film B
                commonCount++;										//	increment the common count
            }
        }
    } else {
        for (auto &[userId, ratingB] : filmB) {
            if (auto it = filmA.find(userId); it != filmA.end()) {
                const float ratingA = it->second;
                numerator      += ratingA * ratingB;
                sumOfSquaresA  += ratingA * ratingA;
                sumOfSquaresB  += ratingB * ratingB;
                commonCount++;
            }
        }
    }

    const float denominator = sqrt(sumOfSquaresA) * sqrt(sumOfSquaresB);	//	calculate the denominator for cosine similarity calculation

    // if the number of common ratings is less than 7 or the denominator is less than 1e-9, return 0.0
    if (commonCount < 7 || denominator < 1e-9f) {
        similarityCache[cacheKey] = 0.0f;	//	store the cosine similarity in the cache
        return 0.0f;
    }

    const float similarity = numerator / denominator;	//	calculate the cosine similarity
    similarityCache[cacheKey] = similarity;				//	store the cosine similarity in the cache
    return similarity;
}

// Predict the rating for the film using IBCF (Item-Based Collaborative Filtering) method, with K neighbors for the user ID and target film ID.
float predictRatingIBCF(const unsigned short userId, const unsigned short targetFilmId, data_map &data, const int K) {

    vector<pair<float, unsigned short>> similarities;		//	vector to store cosine similarities between films
    const auto & targetFilmRatings = data[targetFilmId];	//	get the user ratings for the target film

    for (auto & [otherFilmId, otherFilmRatings] : data) {						//	iterate over the films
        if (otherFilmId == targetFilmId) continue;								//	skip if the film is the target film
        if (otherFilmRatings.find(userId) == otherFilmRatings.end()) continue;	                    //	skip if the user has not rated the film

        //	calculate the cosine similarity between the target film and the other film
        if (float sim = cosine_similarity_item(targetFilmId, targetFilmRatings, otherFilmId, otherFilmRatings); sim > 1e-9f)
            similarities.emplace_back(sim, otherFilmId);	//	store the cosine similarity between the films
    }

    // sort the cosine similarities between the films
    sort(similarities.begin(),
            similarities.end(),
            [](auto &a, auto &b) {
                return a.first > b.first;
            });

    // define variables for weighted sum and similarity sum
    float weightedSum = 0.0f;
    float simSum = 0.0f;
    int count = 0;

    // calculate the weighted sum and similarity sum for the target film
    for (auto & [sim, filmId] : similarities) {					//	iterate over the cosine similarities between the films
        const float ratingNormalized = data[filmId][userId];	//	get the normalized rating for the film
        weightedSum += sim * ratingNormalized;					//	calculate the weighted sum
        simSum += sim;
        count++;
        if (count == K) break;	//	break if the count is equal to K
    }

    const float filmMean = filmAvgMap[targetFilmId];
    float predicted = 0.0f;

    if (simSum > 1e-9f)
        predicted = filmMean + (weightedSum / simSum);
    else
        predicted = filmMean;

    return predicted;
}
