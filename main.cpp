/*
 BAHCESEHIR UNIVERSITY
 Faculty of Engineering and Natural Sciences
 Department of Computer Engineering

 CMP2003: Data Structures and Algorithms with C++
 2024-2025 - Fall Semester - Term Project

 Group Name:		Trailblazer
 Group Members:		Ömer İnkaya (2103353), Emir İsmail Genç (2202780), Berkay Şahin (2203066)
 Course Instructor:	Dr. Tevfik Aytekin
*/

#include "ibcf.h"           // for Item-Based Collaborative Filtering
#include "utils.h"          // for utility functions
#include <iostream>			// for standard input/output operations
#include <sstream>			// for Istream string usage for parsing input


int main() {
    // Disable synchronization between C and C++ standard streams. This is for taking input from HackerRank.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	/*
	 VARIABLE DECLARATIONS
	 * The user ID, film ID and rating are stored as unsigned short and float for memory optimization.
	*/
    data_map data;
    unsigned short user_id, film_id;
    float rating;
    string line;

    getline(cin, line);							// read the first line
    if (line == "train dataset")				// check if the first line is "train dataset"
        while (getline(cin,line)) { 			// while loop to read the "training" input only! line by line
            if (line == "test dataset") break;	// exit if the line is "test dataset"

            // parse the input line
            istringstream iss(line);
            iss >> user_id >> film_id >> rating;

			// store the user rating for the film in the map
            data[film_id][user_id] = rating;
        }

    computeFilmAverages(data);	// compute average ratings for films (line 121)
    normalizeFilmRatings(data);	// normalize ratings for films (line 129)

    while (getline(cin,line)) { 	// while loop to read the "testing" input only! line by line
        int K = 40; 				// set the number of neighbors to consider for IBCF

		// parse the input line
        istringstream iss(line);
        iss >> user_id >> film_id;

        float predictedRating = predictRatingIBCF(user_id, film_id, data, K);	// predict the rating for the film using IBCF (line 142)
        cout << predictedRating << "\n"; 										// print the predicted rating
    }

    return 0;
}





