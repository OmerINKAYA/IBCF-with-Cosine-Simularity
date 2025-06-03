/*
 BAHCESEHIR UNIVERSITY
 Faculty of Engineering and Natural Sciences
 Department of Computer Engineering

 CMP2003: Data Structures and Algorithms with C++
 2024-2025 - Fall Semester - Term Project

 Group Name:		Trailblazer
 Group Members:		Ömer İnkaya, Emir İsmail Genç
 Course Instructor:	Dr. Tevfik Aytekin
*/

#include "ibcf.h"           // for Item-Based Collaborative Filtering
#include "utils.h"          // for utility functions
#include <iostream>			// for standard input/output operations
#include <fstream>          // for file input/output operations
#include <sstream>			// for Istream string usage for parsing input

bool input_flag = false;    // Flag to determine input source


int main() {
    /*
     VARIABLE DECLARATIONS
     * The user ID, film ID and rating are stored as unsigned short and float for memory optimization.
    */
    data_map data;
    unsigned short user_id, film_id;
    float rating;
    string line;

    // Disable synchronization between C and C++ standard streams. This is for taking input from HackerRank.
    if (input_flag) {    // ...HackerRank input...
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        getline(cin, line);				    // read the first line
        if (line == "train dataset")			    // check if the first line is "train dataset"
            while (getline(cin,line)) { 		// while loop to read the "training" input only! line by line
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

    } else {             // ...public_training_data.txt / public_test_data.txt input...
        ifstream train_file("public_training_data.txt");
        ifstream test_file("public_test_data.txt");
        if (!train_file || !test_file) {
            cerr << "Error opening input files.\n";
            return 1;
        }

        // Read training data
        while (getline(train_file, line)) {
            istringstream iss(line);
            iss >> user_id >> film_id >> rating;
            data[film_id][user_id] = rating;
        }

        computeFilmAverages(data);
        normalizeFilmRatings(data);

        // Read test data and predict
        while (getline(test_file, line)) {
            int K = 40;
            istringstream iss(line);
            iss >> user_id >> film_id;

            float predictedRating = predictRatingIBCF(user_id, film_id, data, K);
            cout << predictedRating << "\n";
        }
    }

    return 0;
}





