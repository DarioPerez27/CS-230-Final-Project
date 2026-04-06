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

int main() {

    //Get n from user

    //Generate primes from 1 to n

    //Insert primes into both trees, time the insertions, and track memory usage for each tree

    //Search for all primes in both trees, time the searches, and track memory usage for each tree

    //Output results in a table format

}