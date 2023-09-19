#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MV_LEFT '<'
#define MV_RIGHT '>'
#define INC_VAL '+'
#define DEC_VAL '-'
#define PRINT_ASCII '.'
#define READ_ASCII ','
#define LOOP_BEG '['
#define LOOP_END ']'
#define LOG_MEM '!'

bool debug;
unsigned short position;
unsigned char memory[30000];

void logMem(int start, int current)
{
    printf("\nLogging surrounding memory\n");
    for(int i = 0; i < 10; i++)
    {
        printf("MemAddr %i:%u %s\n", i + start, memory[i+start], start + i == current ? "(Current position)": "");
    }
}

bool endsWith(char* str, char* end)
{
    size_t len = strlen(str);
    size_t elen = strlen(end);
    size_t diff = len - elen;
    char check[64];
    for(int i = 0; i < elen; i++)
    {
        check[i] = str[i+diff];
    }
    return strcmp(check, end);
}

char* readFile(char* fp)
{
    FILE *file = fopen(fp, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* out = malloc(fsize + 1);
    fread(out, fsize, 1, file);
    fclose(file);
    out[fsize] = 0;
    return out;
}

#define printfdbg(fmt, ...) if(debug) printf(fmt, ##__VA_ARGS__)

int main(int argc, char** argv) {

    bool isBFFile = argc != 1 && endsWith(argv[1], ".bf");
    if(!isBFFile)
    {
        printf("Expected .bf file input! Recieved %s", argv[1] == NULL ? "none" : argv[1]);
        return 1;
    }

    debug = argc == 3 && strcmp(argv[2], "--debug") == 0;
    printfdbg("Running in debug mode\n");

    const char* content = readFile(argv[1]);
    const size_t instructions = strlen(content);

    for(int i = 0; i < instructions; i++)
    {
        printfdbg("Reading char %i = ", i);
        char ch = content[i];
        printfdbg("%c\n", ch);
        if(ch == MV_RIGHT)
        {
            printfdbg("MV_RIGHT\n");
            position++;
        }
        else if(ch == MV_LEFT)
        {
            printfdbg("MV_LEFT\n");
            position--;
        }
        else if(ch == INC_VAL)
        {
            printfdbg("INC_VAL\n");
            memory[position]++;
        }
        else if(ch == DEC_VAL)
        {
            printfdbg("DEC_VAL\n");
            memory[position]--;
        }
        else if(ch == PRINT_ASCII)
        {
            printfdbg("PRINT_ASCII\n");
            printfdbg("%u", position);
            printf("%c", memory[position]);
        }
        else if(ch == READ_ASCII)
        {
            printfdbg("READ_ASCII\n");
            char c;
            scanf("%c", &c);
            getchar(); // Remove blank char left by pressing enter
            memory[position] = c;
        }
        else if(ch == LOG_MEM)
        {
            int start = position - 5;
            logMem(start, position);
        }
        else if(ch == LOOP_BEG)
        {
            printfdbg("LOOP_BEG\n");
            // We dont even need to do anything for this one
        }
        else if(ch == LOOP_END)
        {
            printfdbg("LOOP_END\n");
            if(memory[position] <= 0)
            {
                continue;
            }

            int skipLoops = 0;
            while (true)
            {
                i--;
                ch = content[i];

                if(ch == LOOP_END)
                {
                    skipLoops++;
                    printfdbg("Found loop end, now skipping %i loops");
                    continue;
                }

                if(ch == LOOP_BEG)
                {
                    if(skipLoops == 0)
                    {
                        printfdbg("Returning to loop start\n");
                        break;
                    }
                    else
                    {
                        printfdbg("Skipping loop start instruction\n");
                        skipLoops--;
                    }
                }
            }
        }
    }
    
    return 0;
}