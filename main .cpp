#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
typedef unsigned int	uint;
typedef unsigned char	uchar;

using namespace std;

//Encoding
int encode(int keyID, size_t alphNum, string alphabet, const char *inputFile, const char *outputFile) {
    char symb; 
     FILE *in;
	 FILE *out;
        in = fopen(inputFile, "r+"); 
        if (in == NULL) printf("Input file not found!"); 
		
        out = fopen(outputFile, "r+"); 
        if (out == NULL) printf("Output file not found!"); 

    if ((in != NULL) && (out != NULL)) {
    while (!feof(in)) {  
        fread (&symb, sizeof(char), 1, in);
        for (int i = 0; i<alphNum; i++) {
            if (symb == alphabet[i]) {
                for (int k = 0; k<keyID; k++) {    
                symb = symb++;
            }
            break; }
        }
        fwrite (&symb, sizeof(char), 1, out); 
        symb = ' ';
     }

fclose(in);
fclose(out);
      
    }
}

//Decoding
int decode(int keyID, size_t alphNum, string alphabet, const char *inputFile, const char *outputFile) {
    char symb, symbol; 
     FILE *in;
	 FILE *out;
        in = fopen(inputFile, "r+"); 
        if (in == NULL) printf("Input file not found!"); 

        out = fopen(outputFile, "r+"); 
        if (out == NULL) printf("Output file not found!"); 

    if ((in != NULL) && (out != NULL)) {    
    while (!feof(in)) {   
        fread (&symb, sizeof(char), 1, in);
        symbol = symb;
        
        for (int i = 0; i<keyID; i++) {          
            symbol = symbol--;                             
        }
        for (int i = 0; i<alphNum; i++) {    
            if (symbol == alphabet[i]) {               
                for (int k = 0; k<keyID; k++) {
                symb = symb--;
            }
            break; }
        }
        fwrite (&symb, sizeof(char), 1, out);
        symb = ' ';
     }

fclose(in);
fclose(out);
      
    }
}

//Main Function
int main(int argc, char* argv[]){
string alphabet="AaBbCcDdEeFfGgHhIiKkLlMmNnOoPpQqRrSsTtVvXxYyZz0123456789";
int key, keyID, index;
char symbol;
bool type = false; 	
bool files = false; 	
string tmp;
const char *inputFile;
const char *outputFile;

//Work with arguments
if(argc == 2)
	{
		if((!(strcmp(argv[1],"-h"))) || (!(strcmp(argv[1],"--help"))))
		{
		printf ("\nUsage: crypt [options] <key> <source> [<dest>]\n");
		printf ("\noptions:\n");
		printf ("\t-a, --alphabet=<alphabet>  alphabet for chipher (default: AaBbCc..Zz0..9)\n"); 
		printf ("\t-t, --type=<type>          'encode' or 'decode', encode if not specified\n");
		printf ("\t-h, --help                 display this help\n");

		printf ("key:\n");
		printf ("\tencode/decode key (positive number)\n");

		printf ("source:\n");
		printf ("\tsource file for encode/decode\n");

		printf ("dest:\n");
		printf ("\tdestination file for encode/decode. Overwritting source file if not specified\n");;
			return 0;
		}
		else
		{
			printf ("\nError!\n");
			return -1;
		}
	}
	else if(argc > 2) 
	{
		for(int i=1; i<argc; i++) 
		{
			if((!(strcmp(argv[i],"-a")))) 			
			{						
				i++;					
				alphabet = argv[i];
			}
			
			else if(strstr(argv[i],"--alphabet="))		 
			{					
				alphabet = string(argv[i]).erase(0,11);
			}
			
			else if(strstr(argv[i],"-t"))			
			{						
				if(strstr(argv[i],"--type="))		
				{		
					tmp = string(argv[i]).erase(0,7);
				}
				else
				{					
					i++; 				
					tmp = string(argv[i]);
				}
				if(tmp == "encode")			
					type = false;
				else if(tmp == "decode")
					type = true;
				else						
				{
					printf ("Argument is uncorrect!");
					return -1;
				}	
			}
			else if(key = atoi(argv[i]))			
			{
				if (key < 1)
					{
					printf ("Arguments are wrong!");
					return -1;				  
				}
				keyID = i;
				break;
			}
			else			 
			{					
				printf ("Arguments are wrong!");
				return -1;
			}
		}
	}	
	
	size_t alphNum = alphabet.length();
	if (type == true) encode (keyID, alphNum, alphabet, inputFile, outputFile);
    if (type == false) decode(keyID, alphNum, alphabet, inputFile, outputFile);
	
	printf ("\nDone\n");
	
	return 0;
}