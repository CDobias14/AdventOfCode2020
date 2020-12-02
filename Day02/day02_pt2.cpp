#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<tuple>
#include<algorithm>

using namespace std;
tuple <int, int, char, string> dissect_password(string password_entry)
{
    // Get pos1 for target character
    string delimiter = "-";
    int pos1 = atoi(password_entry.substr(0, password_entry.find(delimiter)).c_str());
    pos1--; // Positional values start at 1, so -1 to account for us starting at index zero;
    password_entry.erase(0, password_entry.find(delimiter)+delimiter.length());

    // Get pos2 for target character
    delimiter = " ";
    int pos2 = atoi(password_entry.substr(0, password_entry.find(delimiter)).c_str());
    pos2--; // Positional values start at 1, so -1 to account for us starting at index zero;
    password_entry.erase(0, password_entry.find(delimiter)+delimiter.length());

    // Get target character
    delimiter = ": ";
    char target_character = password_entry.substr(0, password_entry.find(delimiter))[0];
    password_entry.erase(0, password_entry.find(delimiter)+delimiter.length());

    // Remaining string is thet password
    string password = password_entry;

    // Return! :D
    tuple <int, int, char, string> return_tuple;
    return_tuple = make_tuple(pos1, pos2, target_character, password);
    return return_tuple;
}

int check_passwords(string filename)
{
    fstream pass_file;
    pass_file.open(filename, ios::in);

    int valid_passwords = 0;
    string line;
    while (getline(pass_file, line))
    {
        // Dissect password entry
        tuple <int, int, char, string> password_tuple;
        password_tuple = dissect_password(line);

        // Parse values from return tuple
        int pos1 = get<0>(password_tuple);
        int pos2 = get<1>(password_tuple);
        char target_character = get<2>(password_tuple);
        string password = get<3>(password_tuple);

        // Check each position for a match to the target character
        bool pos1_match = false;
        bool pos2_match = false;
        if (target_character == password[pos1])
        {
            pos1_match = true;
        }
        if (target_character == password[pos2])
        {
            pos2_match = true;
        }

        // If exactly one match exists, the password is valid
        if (pos1_match != pos2_match)
        {
            valid_passwords++;  // Your password is valid! :D
        }
    }
    pass_file.close();
    return valid_passwords;
}

int main()
{
    cout << "Running main()" << "\n";
    string filename = "input.txt";
    int valid_passwords = check_passwords(filename);
    cout << "This many passwords successfully passed cert: " << valid_passwords;

    return 0;
}

