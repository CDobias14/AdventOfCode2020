#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<tuple>
#include<algorithm>

using namespace std;
int find_encountered_trees(string file_name, int slope_x, int slope_y)
{
    fstream map_file;
    map_file.open(file_name, ios::in);

    string clear_tile;
    string tree_tile;

    clear_tile = ".";
    tree_tile = "#";

    // Current x,y position
    int current_x;
    int current_y;
    // A slope represented as (x,y)
    current_x = 0;
    current_y = 0;

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

    map_file.close();
    return trees_encountered;
}

int main()
{
    string file_name;
    file_name = "input.txt";
    int total_product;
    total_product = find_encountered_trees(file_name, 1, -1);
    total_product *= find_encountered_trees(file_name, 3, -1);
    total_product *= find_encountered_trees(file_name, 5, -1);
    total_product *= find_encountered_trees(file_name, 7, -1);
    total_product *= find_encountered_trees(file_name, 1, -2);
    cout << total_product;
    return 0;
}
