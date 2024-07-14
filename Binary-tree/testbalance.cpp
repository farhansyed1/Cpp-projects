
// To compile: g++ -o testbalance.exe testbalance.cpp 
// Running valgrind: valgrind --leak-check=full --show-leak-kinds=all ./testbalance.exe

#include "bintree.cpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <ctime>
#include <iomanip>

using namespace std;

void basicTest(){
    cout << "Basic test" << endl;
    
    vector<int> randomNumbers(9000);
    iota(randomNumbers.begin(), randomNumbers.end(), 1);  // 1 to 9000

    // Fixed seed
    shuffle(randomNumbers.begin(), randomNumbers.end(), default_random_engine(020416));

    vector<int> maxHeightResults(800);
    vector<int> minHeightResults(800);

    for (int i = 0; i < 800; i++) {
        Node* t = nullptr;
        for (int num : randomNumbers) {
            insert(t, num, num);
        }
        maxHeightResults[i] = max_height(t);
        minHeightResults[i] = min_height(t);

        delete_tree(t);

        next_permutation(randomNumbers.begin(), randomNumbers.end());
    }

    // MAX
    double avgMaxHeight = accumulate(maxHeightResults.begin(), maxHeightResults.end(), 0.0) / 800;    
    int highestMaxHeight = *max_element(begin(maxHeightResults), end(maxHeightResults));

    // MIN
    double avgMinHeight = accumulate(minHeightResults.begin(), minHeightResults.end(), 0.0) / 800;
    int lowestMinHeight = *min_element(begin(minHeightResults), end(minHeightResults));

    // DIFFERENCE
    vector<int> heightDifferences(800);
    for (int i = 0; i < maxHeightResults.size(); i++) {
        heightDifferences[i] = abs(maxHeightResults[i] - minHeightResults[i]);
    }

    int greatestDifference = *max_element(begin(heightDifferences), end(heightDifferences));
    int lowestDifference = *min_element(begin(heightDifferences), end(heightDifferences));

    double avgHeightDifference = accumulate(heightDifferences.begin(), heightDifferences.end(), 0.0) / 800;

    // Output results
    cout << setprecision(2);
    cout << "Average maximum height: " << avgMaxHeight << endl;
    cout << "Highest maximum height: " << highestMaxHeight << endl;
    
    cout << "Average minimum height: " << avgMinHeight << endl;
    cout << "Lowest minimum height: " << lowestMinHeight << endl;
    
    cout << "Average height difference: " << avgHeightDifference << endl;
    cout << "Greatest height difference: " << greatestDifference << endl;
    cout << "Lowest height difference: " << lowestDifference << endl;
}

void improvedTest(){
    cout << "Improved test" << endl;
    
    srand(020416);

    vector<int> maxHeightResults(800);
    vector<int> minHeightResults(800);

    for (int i = 0; i < 800; i++) {
        int sizeOfVec = rand() % 9000;
            
        vector<int> randomNumbers(sizeOfVec);
        iota(randomNumbers.begin(), randomNumbers.end(), 1); 

        shuffle(randomNumbers.begin(), randomNumbers.end(), default_random_engine(020416));
        
        Node* t = nullptr;
        for (int num : randomNumbers) {
            insert(t, num, num);
        }
        maxHeightResults[i] = max_height(t);
        minHeightResults[i] = min_height(t);

        delete_tree(t);
    }

    // MAX
    double avgMaxHeight = accumulate(maxHeightResults.begin(), maxHeightResults.end(), 0.0) / 800;    
    int highestMaxHeight = *max_element(begin(maxHeightResults), end(maxHeightResults));

    // MIN
    double avgMinHeight = accumulate(minHeightResults.begin(), minHeightResults.end(), 0.0) / 800;
    int lowestMinHeight = *min_element(begin(minHeightResults), end(minHeightResults));

    // DIFFERENCE
    vector<int> heightDifferences(800);
    for (int i = 0; i < maxHeightResults.size(); i++) {
        heightDifferences[i] = abs(maxHeightResults[i] - minHeightResults[i]);
    }

    int greatestDifference = *max_element(begin(heightDifferences), end(heightDifferences));
    int lowestDifference = *min_element(begin(heightDifferences), end(heightDifferences));

    double avgHeightDifference = accumulate(heightDifferences.begin(), heightDifferences.end(), 0.0) / 800;

    // Output results
    cout << setprecision(2);
    cout << "Average maximum height: " << avgMaxHeight << endl;
    cout << "Highest maximum height: " << highestMaxHeight << endl;
    
    cout << "Average minimum height: " << avgMinHeight << endl;
    cout << "Lowest minimum height: " << lowestMinHeight << endl;
    
    cout << "Average height difference: " << avgHeightDifference << endl;
    cout << "Greatest height difference: " << greatestDifference << endl;
    cout << "Lowest height difference: " << lowestDifference << endl;
}

int main(){
    basicTest();
    cout << "\n";
    improvedTest();
}