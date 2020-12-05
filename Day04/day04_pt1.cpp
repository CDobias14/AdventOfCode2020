#include<cstdio>
#include<string.h>

static const char* entry_names[8] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

struct PassportData
{
    char entry_values [8][24];
};

bool validate_passport(PassportData passport_data)
{
    bool valid_passport = false;
    if (!passport_data.entry_values[0][0])  // "byr"
    {
        valid_passport = false;
    }
    else if (!passport_data.entry_values[1][0])  // "iyr"
    {
        valid_passport = false;
    }
    else if (!passport_data.entry_values[2][0])  // "eyr"
    {
        valid_passport = false;
    }
    else if (!passport_data.entry_values[3][0])  // "hgt"
    {
        valid_passport = false;
    }
    else if (!passport_data.entry_values[4][0])  // "hcl"
    {
        valid_passport = false;
    }
    else if (!passport_data.entry_values[5][0])  // "ecl"
    {
        valid_passport = false;
    }
    else if (!passport_data.entry_values[6][0])  // "pid"
    {
        valid_passport = false;
    }
    else if (!passport_data.entry_values[7][0])  // "cid"
    {
        valid_passport = true;  // "cid" entry optional on passport
    }
    else  // Valid passport! Everything had an entry
    {
        valid_passport = true;
    }

    return valid_passport;
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
                //printf("VALID passport:\n");
            }
            else
            {
                ;
                //printf("Invalid passport:\n");
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
            //printf("Entry complete. Proceeding to next passport.\n");
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
