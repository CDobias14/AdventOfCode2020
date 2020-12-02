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
    // Get min for target character
    string delimiter = "-";
    int min_count = atoi(password_entry.substr(0, password_entry.find(delimiter)).c_str());
    password_entry.erase(0, password_entry.find(delimiter)+delimiter.length());

    // Get max for target character
    delimiter = " ";
    int max_count = atoi(password_entry.substr(0, password_entry.find(delimiter)).c_str());
    password_entry.erase(0, password_entry.find(delimiter)+delimiter.length());

    // Get target character
    delimiter = ": ";
    char target_character = password_entry.substr(0, password_entry.find(delimiter))[0];
    password_entry.erase(0, password_entry.find(delimiter)+delimiter.length());

    // Remaining string is thet password
    string password = password_entry;

    // Return! :D
    tuple <int, int, char, string> return_tuple;
    return_tuple = make_tuple(min_count, max_count, target_character, password);
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
        int min_value = get<0>(password_tuple);
        int max_value = get<1>(password_tuple);
        char target_character = get<2>(password_tuple);
        string password = get<3>(password_tuple);

        // Count target_character usages in password and compare to min/max value
        int character_count = count(password.begin(), password.end(), target_character);
        if (min_value <= character_count && character_count <= max_value)
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

