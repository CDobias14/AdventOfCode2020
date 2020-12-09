#include<cstdio>
#include<string.h>

struct BagEntry
{
    char bag_color [30];
    bool can_contain_gold = false;
};

static BagEntry bag_array [600];

void find_bag_usages(char bag_color[30], char file_name[30])
{
    FILE * input_file;
    input_file = fopen(file_name, "r");
    char line[256];
    int i = 0;
    while (fgets(line, 256, input_file))
    {
        char * bag_found;
        bag_found = strstr(line, bag_color);
        if (bag_found && bag_found != &line[0])
        {
            bag_array[i].can_contain_gold = true;
            char * next_bag_found;
            char * next_bag_color = bag_array[i].bag_color;

            // Begin recursion
            find_bag_usages(next_bag_color, file_name);
        }
        i++;
    }
    fclose(input_file);
    return;
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
        token = strtok(line, " ");
        int j = 0;
        while (j <= 1)
        {
            int str_end = 0;
            str_end = strcspn(current_color, "\0");
            strcpy(&current_color[str_end], token);
            str_end = strcspn(current_color, "\0");
            strcpy(&current_color[str_end], " \0");
            token = strtok(NULL, " ");
            j++;
        }

        strcpy(bag_array[i].bag_color, current_color);
        bag_array[i].can_contain_gold = false;

        i++;
    }
    fclose(input_file);

    char gold_bag[30] = "shiny gold";
    find_bag_usages(gold_bag, file_name);

    int total_count = 0;
    i = 0;
    while (i < 600)
    {
        bool contains_gold = false;
        contains_gold = bag_array[i].can_contain_gold;
        if (contains_gold)
        {
            total_count++;
        }
        i++;
    }

    printf("Total count = %i\n", total_count);
    return 0;
}
