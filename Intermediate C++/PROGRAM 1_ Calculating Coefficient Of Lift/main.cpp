#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <string>  
#include <vector>
#include <algorithm>

using namespace std; 

void readData(const string &s, vector<double> &a, vector<double> &c) {
    ifstream fin; 

    fin.open (s);

    if (!fin.is_open()) {
        cout << "Error opening " << s << endl; 
        exit(1); 
    }

    double num;  

    while (fin >> num) {
        a.push_back(num);
        fin >> num; 
        c.push_back(num);
    }

    fin.close(); 
}

double interpolation(double num, const vector<double> &a, const vector<double> &c) {
    double low; 
    double cLow; 
    double high; 
    double cHigh; 
    double interpolation; 
    for (unsigned int i = 0; i < a.size(); ++i) {
        if (num == a.at(i)) {
            return c.at(i); 
        }
    }

    for (unsigned int i = 0; i < a.size(); ++i) {
        if (a.at(i) < num) {
            low = a.at(i); 
            cLow = c.at(i); 
        }
    }

    for (unsigned int i = 0; i < a.size(); ++i) {
        if (a.at(i) > num) {
            high = a.at(i); 
            cHigh = c.at(i);
            break; 
        }
    }

    interpolation = cLow + ((num - low) / (high - low)) * (cHigh - cLow); 

    return interpolation; 
}

bool isOrdered(const vector<double> &a) {
    vector<double> v; 
    for (unsigned int i = 0; i < a.size(); ++i) {
        v.push_back(a.at(i));
    }

    sort(v.begin(), v.end());

    if (v == a) {
        return true; 
    }

    else {
        return false; 
    }
}

void reorder(vector<double> &a, vector<double> &c) {
    vector<pair<double, double>> v1; 

    for (unsigned int i = 0; i < a.size(); ++i) {
        v1.emplace_back(a.at(i), c.at(i));
    }

    sort(v1.begin(), v1.end());
    sort(a.begin(), a.end());

    for (unsigned int i = 0; i < a.size(); ++i) {
        if (v1[i].second != c.at(i)) {
            c.at(i) = v1[i].second;
        }
    }
}

int main (int argc, char *argv[]) {
    vector<double> angle; 
    vector<double> coefficient;
    string file; 
    string userAnswer; 
    double userNum;


    file = argv[1];

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " fileName" << endl; 
        return 1; 
    } 

    readData (file, angle, coefficient);

    if (!isOrdered(angle)) {
        reorder (angle, coefficient);
    }

    do {
        cout << "Enter a flight-path angle: "; 
        cin >> userNum;

        if ((userNum >= angle.front()) && (userNum <= angle.back())) {
            cout << "Corresponding coefficient: " << interpolation(userNum, angle, coefficient) << endl; 
        }

        else {
            break; 
        }

        cout << "Do you want to enter another flight-path angle? " << endl; 
        cout << "Please enter Yes or No. " << endl;
        cin >> userAnswer;  
    } while (userAnswer == "Yes"); 

    return 0; 
}