#include<cstdio>
#include<string.h>

int main()
{
    // Open input file
    FILE * input_file;
    input_file = fopen("input.txt", "r");

    int total_count = 0;

    char valid_chars [] = "abcdefghijklmnopqrstuvwxyz";
    char line [sizeof(valid_chars)];
    char group_str [254] = "\0";
    int group_str_end = 0;
    int group_head_count = 0;
    while (fgets(line, sizeof(valid_chars)+1, input_file))
    {
        // If this is a newline then we've reached the end of the group. Time to grok.
        if (strcmp(line, "\n") == 0)
        {
            int count_sum = 0;
            int i = 0;
            while (i < 26)
            {
                // Define and setup some vars
                int char_found;
                int str_len;
                int number_of_occurrences = 0;
                char search_char [1];
                strcpy(&search_char[0], &valid_chars[i]);
                search_char[1] = '\0';
                int start_pos = 0;

                // Find the index of the first search_char occurrence
                // Note: strcspn() returns the index of the last char if no match is found,
                // so we find the string length to compare against
                char_found = strcspn(&group_str[start_pos], &search_char[0]);
                str_len = strcspn(&group_str[start_pos], "\0");

                // Step through the group_str in chunks (divided live based on char_found)
                while (char_found != str_len)
                {
                    number_of_occurrences++;
                    start_pos += char_found+1;
                    str_len = strcspn(&group_str[start_pos], "\0");
                    char_found = strcspn(&group_str[start_pos], &search_char[0]);
                }

                // Did we find this letter a number of times equal to the number of members in the group?
                if (number_of_occurrences == group_head_count)
                {
                    count_sum++;
                }
                i++;
            }
            // Reset some vars for the next group
            group_str[0] = '\0';
            group_str_end = 0;
            group_head_count = 0;
            total_count += count_sum;
            continue;
        }
        // Find the end of the line
        int line_end = 0;
        line_end = strcspn(line, "\0");

        // Append the current line to the end of the group_str
        strcpy(&group_str[group_str_end], line);
        group_str[group_str_end+line_end] = '\0';
        group_str_end = strcspn(group_str, "\0");

        // Remove newline char from the group_str (Based on problem assumptions it only handles 1 newline)
        int newline_index;
        newline_index = strcspn(group_str, "\n");
        if (group_str[newline_index] == '\n')
        {
            group_head_count++;  // Update number of members in the group (newline == new group member)
            group_str[newline_index] = ' ';
        }
    }

    printf("Total count: %i\n", total_count);
    return 0;
}
