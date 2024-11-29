#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Point {
    int x;
    int y;
};

double calculateEuclideanDistance(const Point& p1, const Point& p2) {
    return sqrt( pow(static_cast<double>(p2.x - p1.x), 2) + pow(static_cast<double>(p2.y - p1.y), 2) );
}

bool parseLineToPoint(const string& line, Point& point) {
    stringstream ss(line);
    string token;
    
    if (!getline(ss, token, ',')) { 
        ss.clear();
        ss.str(line);
        if (!getline(ss, token, ' ')) {
            return false;
        }
    }
    
    try {
        point.x = stoi(token);
    } catch (...) {
        return false;
    }
    
    if (!getline(ss, token, ',')) { 
        ss.clear();
        ss.str(line);

        if (!getline(ss, token, ' ')) {
            return false;
        }
        if (!getline(ss, token, ' ')) {
            return false;
        }
    }
    
    try {
        point.y = stoi(token);
    } catch (...) {
        return false;
    }
    
    return true;
}

int main() {
    vector<Point> positions;
    ifstream infile("centrals.txt");
    
    if (!infile) {
        cerr << "Error: Could not open 'centrals.txt'. Please ensure the file exists in the current directory." << endl;
        return 1;
    }
    
    string line;
    int line_number = 0;
    while (getline(infile, line)) {
        line_number++;

        if (line.empty()) continue;
        
        Point p;
        if (parseLineToPoint(line, p)) {
            positions.push_back(p);
        } else {
            cerr << "Warning: Invalid format in 'centrals.txt' at line " << line_number << ". Skipping this line." << endl;
        }
    }
    
    infile.close();
    
    if (positions.empty()) {
        cerr << "Error: No valid positions found in 'centrals.txt'." << endl;
        return 1;
    }
    

    cout << "Loaded Positions from 'centrals.txt':" << endl;
    for(const auto& pos : positions) {
        cout << "(" << pos.x << ", " << pos.y << ")" << endl;
    }
    cout << endl;
    
    Point destination;
    
    cout << "Insert destination position in x: ";
    while(!(cin >> destination.x)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input. Please enter an integer for x: ";
    }
    
    cout << "Insert destination position in y: ";
    while(!(cin >> destination.y)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer for y: ";
    }
    
    double shortest_distance = numeric_limits<double>::max();
    Point closest_position;
    bool first = true;
    cout << "\nCalculating distances to destination (" << destination.x << ", " << destination.y << "):" << endl;
    for(const auto& pos : positions) {
        Point current = pos;
        double distance = calculateEuclideanDistance(current, destination);
        cout << "Distance from (" << current.x << ", " << current.y << ") to ("
             << destination.x << ", " << destination.y << ") is " 
             << distance << endl;

        if(distance < shortest_distance || first) {
            shortest_distance = distance;
            closest_position = pos;
            first = false;
        }
    }
    
    cout << "\nThe closest position to (" << destination.x << ", " 
         << destination.y << ") is (" << closest_position.x 
         << ", " << closest_position.y << ") with a distance of " 
         << shortest_distance << endl;
    
    return 0;
}
