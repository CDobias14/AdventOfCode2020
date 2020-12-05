#include<cstdio>
#include<string.h>

static const char* entry_names[8] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

struct PassportData
{
    char entry_values [8][30];
};

bool validate_passport(PassportData passport_data)
{
    // Birth Year
    if (!passport_data.entry_values[0][0])  // "byr"
    {
        return false;
    }
    else
    {
        int birth_year;  // byr
        sscanf(&passport_data.entry_values[0][0], "%d", &birth_year);
        if (birth_year < 1920 || 2002 < birth_year)
        {
            return false;
        }
    }
    //printf("Birth year valid.\n");

    // Issue Year
    if (!passport_data.entry_values[1][0])  // "iyr"
    {
        return false;
    }
    else
    {
        char str_catch_1 [4];
        char str_catch_2 [4];
        int issue_year;  // iyr
        sscanf(&passport_data.entry_values[1][0], "%d", &issue_year);
        //printf("STR CATCH 1: %s\n", str_catch_1);
        //printf("ISSUE YEAR 1: %d\n", issue_year);
        //printf("STR CATCH 2: %s\n", str_catch_2);
        if (issue_year < 2010 || 2020 < issue_year)
        {
            return false;
        }
    }
    //printf("Issue year valid.\n");

    // Expiration Year
    if (!passport_data.entry_values[2][0])  // "eyr"
    {
        return false;
    }
    else
    {
        int expiration_year;  // eyr
        sscanf(&passport_data.entry_values[2][0], "%d", &expiration_year);
        if (expiration_year < 2020 || 2030 < expiration_year)
        {
            return false;
        }
    }
    //printf("Expiration year valid.\n");

    // Height
    if (!passport_data.entry_values[3][0])  // "hgt"
    {
        return false;
    }
    else
    {
        int height;  // hgt
        char height_token [5];
        if (strstr(&passport_data.entry_values[3][0], "cm"))  // We've got cenimeters
        {
            sscanf(&passport_data.entry_values[3][0], "%i", &height);
            if (height < 150 || 193 < height)
            {
                printf("cm Height INVALID: %i\n", height);
                return false;
            }
        }
        else if (strstr(&passport_data.entry_values[3][0], "in"))  // We've got inches
        {
            sscanf(&passport_data.entry_values[3][0], "%i", &height);
            if (height < 59 || 76 < height)
            {
                printf("in Height INVALID: %i\n", height);
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    //printf("Height valid.\n");

    // Hair Color
    if (!passport_data.entry_values[4][0])  // "hcl"
    {
        return false;
    }
    else
    {
        char starting_value[] = {'#'};
        int dist_to_pound_sign;
        dist_to_pound_sign = strspn(&passport_data.entry_values[4][0], starting_value);

        char valid_values[] = "0123456789abcdef";
        int entry_length;
        entry_length = strspn(&passport_data.entry_values[4][1], valid_values);
        if (dist_to_pound_sign != 1 && entry_length != 6)
        {
            return false;
        }
    }
    //printf("Hair color valid.\n");

    // Eye Color
    if (!passport_data.entry_values[5][0])  // "ecl"
    {
        return false;
    }
    else
    {
        bool valid_color = false;
        char valid_ecl_values[7][4] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        int i = 0;
        while (i < 7)
        {
            char color_entry[4];
            strncpy(color_entry, &passport_data.entry_values[5][0], 3);
            color_entry[3] = '\0';
            int cmp_result;
            cmp_result = strcmp(valid_ecl_values[i], color_entry);
            if (cmp_result == 0)
            {
                valid_color = true;
                break;
            }
            else
            {
                ;
                //printf("ECL Value: %s\n", &valid_ecl_values[i][0]);
                //printf("Entry Value: %s\n", &passport_data.entry_values[5][0]);
                //printf("strcmp result: %i\n", cmp_result);
                //cmp_result = strcmp("amb\n", &passport_data.entry_values[5][0]);
                //printf("strcmp result: %i\n", cmp_result);
                //printf("str length: %i\n", strlen(&passport_data.entry_values[5][0]));
            }
            i++;
        }
        if (!valid_color)
        {
            return false;
        }
    }
    //printf("Eye color valid.\n");

    // Passport ID
    if (!passport_data.entry_values[6][0])  // "pid"
    {
        return false;
    }
    else
    {
        char valid_values[] = "0123456789";
        int entry_length;
        entry_length = strspn(&passport_data.entry_values[6][0], valid_values);
        if (entry_length != 9)
        {
            return false;
        }
    }
    //printf("Passport ID valid.\n");

    //printf("byr = %s\n", &passport_data.entry_values[0][0]);
    //printf("iyr = %s\n", &passport_data.entry_values[1][0]);
    //printf("eyr = %s\n", &passport_data.entry_values[2][0]);
    //printf("hgt = %s\n", &passport_data.entry_values[3][0]);
    //printf("hcl = %s\n", &passport_data.entry_values[4][0]);
    //printf("ecl = %s\n", &passport_data.entry_values[5][0]);
    printf("pid = %s\n", &passport_data.entry_values[6][0]);

    return true;
}

int main()
{
    // Open batch file of passports
    FILE * batch_file;
    batch_file = fopen("input.txt", "r");

    // Variables for the loop
    int valid_passport_count = 0;
    bool valid_passport = false;
    char line [100];  // Char array to store each line. Int value == max char length of line
    PassportData passport_data;  // Initialize and zero out 2d array for passport data storage
    int z = 0;
    while (z < sizeof(*entry_names))
    {
        passport_data.entry_values[z][0] = '\0';
        z++;
    }
    
    // File processing loop
    while (fgets(line, 100, batch_file))
    {
        //printf(line);
        // Check if we've reached the end of the current passport entry
        if (line[0] == '\n' || feof(batch_file) == EOF)
        {
            // Parse passport_data
            valid_passport = validate_passport(passport_data);

            // If our passport is valid, increment count
            if (valid_passport == true)
            {
                valid_passport_count++;
                printf("VALID passport.\n");
            }
            else
            {
                ;
                printf("Invalid passport.\n");
            }


            // Reset passport_data and valid_passport
            valid_passport = false;
            int i = 0;
            while (i < sizeof(*entry_names))
            {
                //printf("%s:%s\n", entry_names[i], &passport_data.entry_values[i]);
                passport_data.entry_values[i][0] = '\0';
                i++;
            }
            printf("Entry complete. Proceeding to next passport.\n\n\n");
            continue;  // Continue to the next line (i.e. next passport entry)
        }

        // Tokenize, parse, and enter data to passport_data.entry_values
        char *tokenized;
        tokenized = strtok(line, " ");
        while (tokenized != NULL)  // Iterate over each token
        {
            //printf("%s\n", tokenized);
            int j = 0;
            while (j < sizeof(*entry_names))  // Iterate over entry_names for comparison
            {
                if (strstr(tokenized, entry_names[j]))
                {
                    strcpy(&passport_data.entry_values[j][0], &tokenized[4]);
                }
                j++;
            }

            tokenized = strtok(NULL, " ");
        }
    }
    // Run evaluation on the final EOF entry
    valid_passport = validate_passport(passport_data);
    if (valid_passport == true)
    {
        valid_passport_count++;
    }

    // Close file, print result, return
    fclose(batch_file);
    printf("Valid passports: %i\n", valid_passport_count);
    return 0;
}
