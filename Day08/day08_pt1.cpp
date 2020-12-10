#include<cstdio>
#include<string.h>

struct Instructions
{
    char instruction_type;
    int instruction_value;
};

int main()
{
    // Open input file
    FILE * input_file;
    char file_name [30] = "input.txt";
    input_file = fopen(file_name, "r");

    bool boot_line_run[650] = {false};  // Whether a line has already been executed or not
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

    int accumulator = 0;
    i = 0;
    while (i < 650)
    {
        if (boot_line_run[i] == true)
        {
            break;
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

    printf("Loop found at i = %i\n", i);
    printf("Accumulator value = %i\n", accumulator);

    fclose(input_file);
    return 0;
}
