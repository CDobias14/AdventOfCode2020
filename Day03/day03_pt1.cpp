#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<tuple>
#include<algorithm>

using namespace std;
int main()
{
    cout << "We in this\n";
    fstream map_file;
    map_file.open("input.txt", ios::in);
    string clear_tile;
    string tree_tile;

    clear_tile = ".";
    tree_tile = "#";

    // Current x,y position
    int current_x;
    int current_y;
    // A slope represented as (x,y)
    int slope_x;
    int slope_y;

    current_x = 0;
    current_y = 0;
    slope_x = 3;  // 3 right
    slope_y = -1;  // 1 down

    vector <string> lines;
    string line;
    while (getline(map_file, line))
    {
        lines.push_back(line);
    }

    int map_length;
    map_length = lines[0].length() - 1;  // Subtract 1 so "length" starts at index 0

    int distance_to_bottom;
    distance_to_bottom = (lines.size() / abs(slope_y)) - 1;  // Subtract 1 so "distance" starts at index 0

    int trees_encountered = 0;
    int i = 0;
    while (i <= distance_to_bottom)
    {
        // Find value at current pos
        string current_tile;
        line = lines[current_y];
        current_tile = line[current_x];
        if (current_tile == tree_tile)
        {
            trees_encountered++;
        }

        // Debug
        //cout << line << " || " << (current_x + 1) << " || " << (current_y + 1) << " || " << current_tile << "\n";

        // Update pos based on slope
        current_x += slope_x;
        current_y -= slope_y;
        if (current_x > map_length)
        {
            int distance_past;
            distance_past = current_x - map_length;
            current_x = distance_past - 1;
        }
        // Account for end of map, update here if we need to loop back to the start
        i++;
    }

    cout << trees_encountered;
    map_file.close();
    return 0;
}
