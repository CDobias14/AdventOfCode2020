#include<cstdio>
#include<string.h>
#include<math.h>

int main()
{
    // Calculate positional delta of each binary partition for rows
    int plane_rows_count = 128;  // Numbered 0-127
    int row_characters_count = 7;  // Number of characters used to define the seat's row position
    int row_pos_delta[row_characters_count];
    int i = 0;
    while (i <= row_characters_count)
    {
        int delta = 0;
        delta = plane_rows_count/(int)pow(2, i);
        row_pos_delta[i] = delta;
        printf("i = %i || Row delta = %i\n", i, delta);
        i++;
    }

    // Calculate positional delta of each binary partition for columns
    int plane_columns_count = 8;  // Numbered 0-7
    int column_characters_count = 3;  // Number of characters used to define the seat's column position
    int column_pos_delta[column_characters_count];
    i = 0;
    while (i <= column_characters_count)
    {
        int delta = 0;
        delta = plane_columns_count/(int)pow(2, i);
        column_pos_delta[i] = delta;
        printf("i = %i || Column delta = %i\n", i, delta);
        i++;
    }

    // Define vars for final answers
    int highest_seat_id = 0;
    bool seat_taken_array [plane_rows_count * plane_columns_count];  // index == seat_id

    // Open input file
    FILE * input_file;
    input_file = fopen("input.txt", "r");

    // Setup for while loop
    int total_char_count = row_characters_count+column_characters_count+1;
    char line [total_char_count];
    while (fgets(line, total_char_count, input_file))
    {
        char column_str [3];
        memmove(&column_str, &line[7], 3);
        int seat_row = 0;
        int seat_column = 0;

        // Calculate row position
        i = 0;
        while (i < row_characters_count)
        {
            if (!strcspn(&line[i], "F"))
            {
                ; // Pass. Delta for F is 0
            }
            else if(!strcspn(&line[i], "B"))
            {
                ; // Add delta for B
                seat_row += row_pos_delta[i+1];
            }
            i++;
        }
        // Calculate column position
        i = 0;
        while (i < column_characters_count)
        {
            if (!strcspn(&column_str[i], "L"))
            {
                ; // Pass. Delta for L is 0
            }
            else if(!strcspn(&column_str[i], "R"))
            {
                ; // Add delta for R
                seat_column += column_pos_delta[i+1];
            }
            i++;
        }

        // Calculate seat ID, update seat_taken_array, check for new highest seat ID
        int seat_id = seat_row * 8 + seat_column;
        seat_taken_array[seat_id] = true;
        if (seat_id > highest_seat_id)
        {
            highest_seat_id = seat_id;
        }
    }

    // Find the seat ID whose neighboring seats are taken
    i = 0;
    while (i < sizeof(seat_taken_array))
    {
        if (!seat_taken_array[i])
        {
            if (!seat_taken_array[i-1] || !seat_taken_array[i+1])
            {
                i++;
                continue;
            }
            printf("My Seat ID = %i\n", i);
        }
        i++;
    }

    printf("Highest seat ID = %i", highest_seat_id);
    return 0;
}
