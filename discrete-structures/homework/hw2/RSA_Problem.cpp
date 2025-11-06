#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <sstream>

using namespace std;

// Function to compute (a * b) % n safely for large numbers
long long multiply_mod(long long a, long long b, long long n) {
    return (long long)(((__int128)a * b) % n);
}

// Function for Modular Exponentiation (a^b % n)
long long power_mod(long long a, long long b, long long n) {
    long long res = 1;
    a %= n;
    while (b > 0) {
        if (b & 1) {
            res = multiply_mod(res, a, n);
        }
        b >>= 1;
        a = multiply_mod(a, a, n);
    }
    return res;
}

// Extended Euclidean Algorithm
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

// Function to compute GCD
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the Modular Inverse
long long mod_inverse(long long a, long long m) {
    long long x, y;
    long long g = extended_gcd(a, m, x, y);
    if (g != 1) {
        return -1;
    } else {
        return (x % m + m) % m;
    }
}

// Check if a number is prime
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to factor n = p * q
bool factor_n(long long n, long long &p, long long &q) {
    // Check if n is prime (invalid for RSA)
    if (is_prime(n)) {
        return false;
    }
    
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            
            // Check if both factors are prime and distinct
            if (p != q && is_prime(p) && is_prime(q)) {
                return true;
            }
        }
    }
    return false;
}

// Function to map a number to a character
char map_to_char(long long num) {
    if (num >= 5 && num <= 30) {
        return (char)('A' + (num - 5));
    }
    switch (num) {
        case 31: return ' ';
        case 32: return '"';
        case 33: return ',';
        case 34: return '.';
        case 35: return '\'';
        default: return '?';
    }
}

// Main function to solve the RSA problem
void solve_rsa() {
    // Read e and n from input
    long long e, n;
    cin >> e >> n;

    int m;
    cin >> m;

    vector<long long> ciphertext(m);
    for (int i = 0; i < m; ++i) {
        cin >> ciphertext[i];
    }
    
    // Step 1: Try to factor n
    long long p = 0, q = 0;
    bool valid_factors = factor_n(n, p, q);

    // Check if factoring failed or produced invalid factors
    if (!valid_factors) {
        cout << "Public key is not valid!" << endl;
        return;
    }

    // Ensure p < q for consistency
    if (p > q) swap(p, q);

    // Step 2: Compute phi(n)
    long long phi_n = (p - 1) * (q - 1);

    // Step 3: Check if gcd(e, phi_n) = 1
    if (gcd(e, phi_n) != 1) {
        cout << "Public key is not valid!" << endl;
        return;
    }

    // Step 4: Find private key d
    long long d = mod_inverse(e, phi_n);
    if (d == -1) {
        cout << "Public key is not valid!" << endl;
        return;
    }

    // Step 5: Decrypt the message
    vector<long long> plaintext_integers;
    string plaintext_message = "";

    for (long long C : ciphertext) {
        long long M = power_mod(C, d, n);
        plaintext_integers.push_back(M);
        plaintext_message += map_to_char(M);
    }
    
    // Output results
    cout << p << " " << q << " " << phi_n << " " << d << endl;

    for (size_t i = 0; i < plaintext_integers.size(); ++i) {
        cout << plaintext_integers[i];
        if (i < plaintext_integers.size() - 1) cout << " ";
    }
    cout << endl;

    cout << plaintext_message << endl;
}

int main() {
    solve_rsa();
    return 0;
}