#include<cstdio>
#include<string.h>

struct Instructions
{
    char instruction_type;
    int instruction_value;
};

int run_boot_sequence(Instructions instruction_array[650])
{
    bool boot_line_run[650] = {false};  // Whether a line has already been executed or not
    int accumulator = 0;
    int i = 0;
    while (i < 650)
    {
        int i_stash = i;
        if (boot_line_run[i] == true)
        {
            if (i == 623)
            {
                printf("This is your stop, dummy. Get off the train.\n");
                return accumulator;
            }
            return NULL;
        }
        boot_line_run[i] = true;
        char type = instruction_array[i].instruction_type;
        int value = instruction_array[i].instruction_value;
        if (type == 'n') // "nop" i.e. No Operation
        {
            i++;
        }
        else if (type == 'a')  // "acc" i.e. Accumulator
        {
            accumulator += value;
            i++;
        }
        else if (type == 'j')  // "jmp" i.e. Jump
        {
            i += value;
        }
    }
    printf("Returning accumulator value (%i), no loop found. Last line = %i\n", accumulator, i);
    return accumulator;
}

int main()
{
    // Open input file
    FILE * input_file;
    char file_name [30] = "input.txt";
    input_file = fopen(file_name, "r");

    Instructions instruction_array [650];

    char line[10];
    int i = 0;
    while (fgets(line, 256, input_file))
    {
        char type;
        char trash_string [4];
        int value;
        sscanf(line, "%c%s %i", &type, &trash_string, &value);
        instruction_array[i].instruction_type = type;
        instruction_array[i].instruction_value = value;
        i++;
    }
    fclose(input_file);

    int accumulator = NULL;
    i = 0;
    while (i < 650)
    {
        Instructions test_instructions[650];
        memcpy(&test_instructions, &instruction_array, sizeof(instruction_array));
        char type = instruction_array[i].instruction_type;
        int value = instruction_array[i].instruction_value;
        if (type == 'n')
        {
            test_instructions[i].instruction_type = 'j';
            accumulator = run_boot_sequence(test_instructions);
        }
        else if (type == 'j')
        {
            test_instructions[i].instruction_type = 'n';
            accumulator = run_boot_sequence(test_instructions);
        }

        if (accumulator)
        {
            printf("ACC=%i\n", accumulator);
            printf("End of program reached.\n");
            break;
        }
        i++;
    }

    if (!accumulator)
    {
        printf("Loop found.\n");
    }
    else
    {
        printf("No loop found.\n");
    }

    printf("Accumulator value = %i\n", accumulator);
    return 0;
}
