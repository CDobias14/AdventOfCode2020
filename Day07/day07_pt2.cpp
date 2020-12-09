// Incorrect answers: 8
#include<cstdio>
#include<string.h>

struct BagEntry
{
    char bag_color [30];
    bool can_contain_gold = false;
    char contained_bags [10][30];  // [Bag entry][Color of bag]
    int number_contained [10];     //            [How many bags fit]
};

static BagEntry bag_array [600];

int find_bag_usages(char bag_color[30], char file_name[30])
{
    FILE * input_file;
    input_file = fopen(file_name, "r");
    int bag_usages = 0;
    char line[256];
    int i = 0;
    while (fgets(line, 256, input_file))
    {
        char * bag_found;
        bag_found = strstr(line, bag_color);
        if (bag_found && bag_found == &line[0])
        {
            int number_contained = 0;
            int j = 0;
            while (j < 10)
            {
                char contained_bag[30] = "\0";
                strcpy(&contained_bag[0], &bag_array[i].contained_bags[j][0]);
                int number_contained = bag_array[i].number_contained[j];
                int additional_bags = 0;
                // Begin Recursion
                if (contained_bag[0] != '\0')
                {
                    additional_bags += number_contained;
                    additional_bags *= find_bag_usages(contained_bag, file_name);
                    number_contained += additional_bags;
                    bag_usages += number_contained;
                }
                j++;
            }
        }
        i++;
    }
    fclose(input_file);
    return bag_usages;
}

int main()
{
    // Open input file
    FILE * input_file;
    char file_name [30] = "input.txt";
    input_file = fopen(file_name, "r");

    char can_contain_gold_bag [20][30];

    char line[256];
    int gold_bag_indices [25];
    int i = 0;
    while (fgets(line, 256, input_file))
    {
        char current_color[30] = "\0";
        char * token;
        token = strtok(line, " ,.");
        int j = 1;
        int k = 1;
        int total_count_contained_bags = 0;  // Used as index for appending to a BagEntry's 2d arrays
        char bag_color[30] = "\0";
        int bag_count = 0;
        while (token != NULL)
        {
            if (j <= 2)  // The top level bag at the start of the list
            {
                int str_end = 0;
                str_end = strcspn(current_color, "\0");
                strcpy(&current_color[str_end], token);
                str_end = strcspn(current_color, "\0");
                strcpy(&current_color[str_end], " \0");
            }
            else if (strstr(token, "no"))  // This bag contains no other bags
            {
                break;
            }
            else if (j >= 5)  // The bags contained within the top level bag
            {
                if (k == 1)  // The first entry is always the number of bags
                {
                    sscanf(token, "%i", &bag_count);
                }
                else if (k == 2 || k == 3)  // The next two are always the color of the bag
                {
                    int str_end_2 = 0;
                    str_end_2 = strcspn(bag_color, "\0");
                    strcpy(&bag_color[str_end_2], token);
                    str_end_2 = strcspn(bag_color, "\0");
                    strcpy(&bag_color[str_end_2], " \0");
                }
                else if (k == 4) // 4th is always "bag" / "bags", which means it's the end of this sub-bag
                {
                    strcpy(&bag_array[i].contained_bags[total_count_contained_bags][0], bag_color);
                    bag_array[i].number_contained[total_count_contained_bags] = bag_count;
                    total_count_contained_bags++;
                    bag_color[0] = '\0';
                    k = 0;
                }
                k++;
            }
            token = strtok(NULL, " ,.");
            j++;
        }

        strcpy(bag_array[i].bag_color, current_color);
        bag_array[i].can_contain_gold = false;

        i++;
    }
    fclose(input_file);

    char gold_bag[30] = "shiny gold ";
    int total_count = 0;
    total_count = find_bag_usages(gold_bag, file_name);

    printf("Total count = %i\n", total_count);
    return 0;
}
