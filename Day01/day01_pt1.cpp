#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>


using namespace std;
int main(){
    cout << "Action! \n";
    //open("D:\Main Storage\Coding\Advent of Code 2020\Day01\input.txt")
    fstream my_file;
    my_file.open("input.txt", ios::in);

    if (!my_file) {
        cout << "RIP, no file :( \n";
    }
    else {
        cout << "Woot, file! :D \n";
        vector <int> lines;
        string line;

        while (getline(my_file, line)) {
            int line_as_int = atoi(line.c_str());
            
            lines.push_back(line_as_int);
            //cout << lines << "\n";
        }

        int i = 0;
        while ( i < lines.size() ) {
            int value_one;
            value_one = lines[i];
            //cout << value_one << "\n";
            i++;
            int j = 0;
            while ( j < lines.size() ) {
                int value_two;
                value_two = lines[j];
                if (value_one != value_two && value_one + value_two == 2020) {
                    int solution;
                    solution = value_one * value_two;
                    cout << "Fucking gottem" << "\n";
                    cout << solution;
                    return solution;
                }
                j++;
            }
        }
    }
    return 0;
}
