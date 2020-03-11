// Name:  Kyle O'Dell
// Email: ko1041449@swccd.edu
// ID:    1041449

#include <stdio.h>
#include <stdlib.h>

char* instList(unsigned int, unsigned int);
int main(int argc, char* argv[])
{
    unsigned int hex, op, func, rs, rt, rd, shamt, imm;
    int  opsum = 0;
    char format;
    long long int k = 10000000000000000000000000000;
    printf("%d\n", k);
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = fopen("decoded.csv", "w");
    // Performs operations if file is available, else prints failed message.
    if(inFile != NULL)
    {
        printf("Machine Code, opcode, func, Inst, Format, rs, rt, rd, shamt, Imm\n");
        fprintf(outFile, "Machine Code, opcode, func, Inst, Format, rs, rt, rd, shamt, Imm\n");

        // Reads inFile, translates instruction formats, and writes data to a new file.
        // Utilizes bit shifting in order to decode the read in machine code.
        while(fscanf(inFile, "%x", &hex) != EOF)
        {
            printf("0x%08x, ", hex);
            fprintf(outFile, "0x%08x, ", hex);
            op = hex >> 26;
            opsum += op;     // keeps a running total of the opcodes.
            rs = hex << 6;
            rs = rs >> 27;
            rt = hex << 11;
            rt = rt >> 27;
            shamt = hex << 21;
            shamt = shamt >> 27;

            printf("0x%02x, ", op);
            fprintf(outFile, "0x%02x, ", op);

            if(op == 0)
            {
                format = 'R';
                rd = hex << 16;
                rd = rd >> 27;
                func = hex << 26;
                func = func >> 26;
                printf("0x%x, ", func);
                fprintf(outFile, "0x%x, ", func);
            }
            else
            {
                format = 'I';
                imm = hex;
                imm = imm << 16;
                imm = imm >> 16;
                printf("----, ");
                fprintf(outFile, "----, ");//func
            }

            printf("%s, ", instList(op, func));
            printf("%c, ", format);
            printf("%d, ", rs);//rs
            printf("%d, ", rt);//rt
            fprintf(outFile, "%s, ", instList(op, func));
            fprintf(outFile, "%c, ", format);
            fprintf(outFile, "%d, ", rs);//rs
            fprintf(outFile, "%d, ", rt);//rt

            if(op == 0)
            {
                printf("%d, ", rd);
                printf("%d, ", shamt);
                printf("- \n"); // imm
                fprintf(outFile, "%d, ", rd);
                fprintf(outFile, "%d, ", shamt);
                fprintf(outFile, "- \n"); // imm
            }
            else
            {
                printf("-, "); // rd
                printf("-, "); // shamt
                printf("0x%04x \n", imm);
                fprintf(outFile, "-, "); // rd
                fprintf(outFile, "-, "); // shamt
                fprintf(outFile, "0x%04x \n", imm);
            }
        }// End loop

        printf("\nOpcode sum: %d\n\n", opsum);
        fprintf(outFile, "\nOpcode sum: %d\n", opsum);
    }
    else
    {
        printf("File cannot be found. New file will be empty.\n");
    }

    fclose(inFile);
    fclose(outFile);
    printf("Successfully created a new file called \"decoded.csv\"\n");
    printf("Please check the file directory.\n");
    return 0;
}

// Uses opcode and function code to determine instruction name.
char* instList(unsigned int op, unsigned int func)
{
    char* inst = "-";
    if(op == 0)
    {
        if(func == 0x20)
            inst = "add";
        else if(func == 0x21)
            inst = "addu";
        else if(func == 0x24)
            inst = "and";
        else if(func == 0x08)
            inst = "jr";
        else if(func == 0x27)
            inst = "nor";
        else if(func == 0x25)
            inst = "or";
        else if(func == 0x2a)
            inst = "slt";
        else if(func == 0x2b)
            inst = "sltu";
        else if(func == 0x00)
            inst = "sll";
        else if(func == 0x02)
            inst = "srl";
        else if(func == 0x22)
            inst = "sub";
        else if(func == 0x23)
            inst = "subu";
    }
    else
    {
        if(op == 0x8)
            inst = "addi";
        else if(op == 0x9)
            inst = "addiu";
        else if(op == 0xc)
            inst = "andi";
        else if(op == 0x4)
            inst = "beq";
        else if(op == 0x5)
            inst = "bne";
        else if(op == 0x2)
            inst = "j";
        else if(op == 0x3)
            inst = "jal";
        else if(op == 0x24)
            inst = "lbu";
        else if(op == 0x25)
            inst = "lhu";
        else if(op == 0x30)
            inst = "ll";
        else if(op == 0xf)
            inst = "lui";
        else if(op == 0x23)
            inst = "lw";
        else if(op == 0xd)
            inst = "ori";
        else if(op == 0xa)
            inst = "slti";
        else if(op == 0xb)
            inst = "sltiu";
        else if(op == 0x28)
            inst = "sb";
        else if(op == 0x38)
            inst = "sc";
        else if(op == 0x29)
            inst = "sh";
        else if(op == 0x2b)
            inst = "sw";
    }

    return inst;
}
