#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include "BinaryTree.h"
#include "AVLTree.h"

using namespace std;
using namespace std::chrono;

//Sieve of Eratosthenes
vector<int> getPrimes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }
    vector<int> primeList;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) primeList.push_back(p);
    }
    return primeList;
}

//Temp function to test getPrimes before using it in the rest of the program
void testGetPrimes(int n) {
    vector<int> primes = getPrimes(n);
    cout << "Testing getPrimes(" << n << ")...\n";
    cout << "Number of primes found: " << primes.size() << endl;
    cout << "Primes found: ";
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl << endl;
}

/*BST Object with insert and search functions
Needs to alternate left and right nodes in order to self balance*/
BinaryTree binaryTree;

/*AVL Tree Object with insert and search functions
Needs to perform rotations to maintain balance after insertions*/
AVLTree avlTree;

int main() {

    //Get n from user
    int n;
    cout << "Enter a number n to generate primes from 1 to n: ";
    cin >> n;

    //TEMP Run a basic test of getPrimes before using the result in the rest of the program
    testGetPrimes(n);

    //Generate primes from 1 to n
    vector<int> primes = getPrimes(n);

    //Create balanced insertion order for BST by alternating low and high values
    vector<int> sortedPrimes = primes;
    sort(sortedPrimes.begin(), sortedPrimes.end());
    vector<int> balancedOrder;
    size_t left = 0, right = sortedPrimes.size() - 1;
    while (left <= right) {
        if (left <= right) balancedOrder.push_back(sortedPrimes[left++]);
        if (left <= right) balancedOrder.push_back(sortedPrimes[right--]);
    }

    //Insert primes into both trees, time the insertions, and track memory usage for each tree

    //AVL Tree insertions
    auto startAVLInsert = high_resolution_clock::now();
    for (int prime : primes) {
        avlTree.insert(prime);
    }
    auto endAVLInsert = high_resolution_clock::now();
    double durationAVLInsert = duration_cast<duration<double, milli>>(endAVLInsert - startAVLInsert).count();

    //BST Insertions (using balanced order)
    auto startBSTInsert = high_resolution_clock::now();
    for (int p : balancedOrder) {
        binaryTree.insert(p);
    }
    auto endBSTInsert = high_resolution_clock::now();
    double bstInsertDuration = duration_cast<duration<double, milli>>(endBSTInsert - startBSTInsert).count();

    //AVL Tree sorting
    auto startAVLSort = high_resolution_clock::now();
    sort(primes.begin(), primes.end());
    auto endAVLSort = high_resolution_clock::now();
    double durationAVLSort = duration_cast<duration<double, milli>>(endAVLSort - startAVLSort).count();

    //BST Sorting (in-order traversal to produce sorted values)
    auto startBSTSort = high_resolution_clock::now();
    binaryTree.sort();
    auto endBSTSort = high_resolution_clock::now();
    double bstSortDuration = duration_cast<duration<double, milli>>(endBSTSort - startBSTSort).count();

    //Search for all primes in both trees, time the searches, and track memory usage for each tree
    size_t foundAVL = 0;
    size_t foundBST = 0;

    //AVL Tree searches
    auto startAVLSearch = high_resolution_clock::now();
    for (int prime : primes) {
        if (avlTree.search(prime)) {
            foundAVL++;
        }
    }
    auto endAVLSearch = high_resolution_clock::now();
    double durationAVLSearch = duration_cast<duration<double, milli>>(endAVLSearch - startAVLSearch).count();

    //BST Searches
    auto startBSTSearch = high_resolution_clock::now();
    for (int p : primes) {
        if (binaryTree.find(p)) {
            foundBST++;
        }
    }
    auto endBSTSearch = high_resolution_clock::now();
    double bstSearchDuration = duration_cast<duration<double, milli>>(endBSTSearch - startBSTSearch).count();

    long long avlMemory = avlTree.getMemoryUsage();
    long long bstMemory = binaryTree.getMemoryUsage();
    size_t totalNodes = primes.size();

    //Output results in a table format
    cout << '\n';
    cout << left << setw(14) << "Tree" << setw(10) << "Nodes" << setw(14) << "Insert (ms)" << setw(14) << "Sort (ms)" << setw(14) << "Search (ms)" << setw(18) << "Memory (bytes)" << setw(10) << "Found" << '\n';
    cout << string(94, '-') << '\n';
    cout << left << setw(14) << "AVL Tree"
         << setw(10) << totalNodes
         << setw(14) << fixed << setprecision(3) << durationAVLInsert
         << setw(14) << durationAVLSort
         << setw(14) << durationAVLSearch
         << setw(18) << avlMemory
         << setw(10) << foundAVL << '\n';
    cout << left << setw(14) << "BST"
         << setw(10) << totalNodes
         << setw(14) << fixed << setprecision(3) << bstInsertDuration
         << setw(14) << bstSortDuration
         << setw(14) << bstSearchDuration
         << setw(18) << bstMemory
         << setw(10) << foundBST << '\n';



}