/* Purpose Statement	: Program that manipulates bit sets. Rotates, shifts, counts, and prints.
 * Authors		: David Dalmatoff && Jared McDonald
 * File	Name	: BitManipulator.c
 * Date Started	: 10/20/15
 * Date Ended	: 11/03/15
 */




#include <stdio.h>
#include <string.h>

typedef unsigned long set;
const set empty = 0x0;

//Prototypes
set complement(set);
set intersection(set,set);
set bitUnion(set,set);
int countBits(set);
void printBits(unsigned long);
set rrotate(set,int);
void leftShift(set);

//Global variables
int c,i,j,k; 	//Loop variables
set firstdec; 	//stores the first hexadecimal argument from the command line
set seconddec;	//stores the second hexadecimal argument from the command line
set result; 	//Result from performed operations

int main(int argc, char *argv[]){
	if(argc < 2 ||argc > 4){								//If command line has less than 2 or more than 3 arguments
		perror("Not enough or too many args provided.\n");	//Print an error
		return(-1);											//Return -1 instead of a positive number
	}
	else if(argv[1][1] != 'p' && argv[1][1] != 'c' && argv[1][1] != 's' && argv[1][1] != 'u' && argv[1][1] != 'i' && argv[1][1] != 'r' && argv[1][1] != 'm'){ //If the first argument isnt a valid operation
		perror("Invalid procedure from command line argument!\n"); //Print error
		return(-1);
	}
	else{
		char *proc = argv[1];								//Put procedure into a char array
		
		if(argc == 3){										//for -p,-c,-s, or -m operations
			
			if(argv[2][2] == 'x'){ 							//If the hexadecimal is a 0x hexadecimal number
				firstdec = strtol(argv[2],NULL,0);			//do a string to long in base 0
			}
			
			else{											//Otherwise if it isn't a 0x hexadecimal
				firstdec = strtol(argv[2],NULL,16); 		//do a string to Long in base 16
			}
			
			if(proc[1] == 'p'){								//If the operation is print
				printf("Bits: ");
				printBits(firstdec);						//Call printBits function to print the bits
			}
			
			else if(proc[1] == 'c'){
				printf("Original   : ");
				printBits(firstdec);						//Print bits of the first hexadecimal
				printf("Complement: ");
				result = complement(firstdec);				//Get complement bits of the first hexadecimal
				printBits(result); 							//Print bits of the result
			}
			else if(proc[1] == 's'){						//If Find set Bits operation
				int setbits = countBits(firstdec);			//call countBits function to find how many set bits the number has
				printf("%d bits set\n",setbits);			//Print the number
				printBits(firstdec);						//Print the bits of the argument
			}
			else if(proc[1] == 'm'){						//If left shift operation
				printf("Original set: ");
				printBits(firstdec); 						//print bits of the argument
				printf("Left Shifted: ");
				leftShift(firstdec);						//Call leftShift function to print the bits of the left shifted	
			}
		}
		else if(argc == 4){									//for -u, -i, or -r
			if(argv[2][2] == 'x'){							//If the hexadecimal is a 0x hexadecimal number
				firstdec = strtol(argv[2],NULL,0); 			//do a string to long in base 0
			}
			else{
				firstdec = strtol(argv[2],NULL,16);			//do a string to long in base 16
			}
			if(proc[1] != 'r'){
				if(argv[3][2] == 'x'){						//If the hexadecimal is a 0x hexadecimal number
					seconddec = strtol(argv[3],NULL,0); 	//do a string to long in base 0
				}
				else if(argv[3][2] != 'x'){ 				//If the hexadecimal isn't a 0x hexadecimal number
					seconddec = strtol(argv[3],NULL,16);	//do a string to long in base 16
				}
				if(proc[1] == 'i'){							//If intersect operation
					result = intersection(firstdec,seconddec);//Place intersection result in result variable
					printf("The result is %ld!\n",result);
					printBits(result); 						//Print result bits
				}
				else{										//-u operation
					result = bitUnion(firstdec,seconddec);	//Find the result of bit union
					printf("The result of the union is %ld!\n",result);
					printBits(result); 						//print bits of the result
				}
			}
			else{ 											// rotation operation
				int rotateby = strtol(argv[3],NULL,16);//
				printf("Rotate bits by %d bit positions:\n",rotateby);
				set rotated = rrotate(firstdec,rotateby);
				printBits(rotated);
			}
		}
	}
	return 0;
}

set complement(set num){
	return ~num;
}

void printBits(unsigned long i){
	int printed = 1;
	for (c = 31; c >= 0; c--){
    		k = i >> c;
 		if (k & 1){
     			printf("1");
		}
		else{
			printf("0");
		}
		printed++;
		if(printed == 5){
			printf(" ");
			printed = 1;
		}
  	}
	printf("\n");
}

set bitUnion(set a,set b){
	set ans = a | b;
	return ans;
}

set intersection(set a,set b){
	set ans = a & b;
	return ans;
}

int countBits(set a){
	int setbits = 0;
	int printed = 1;
	for (c = 31; c >= 0; c--){
    		k = a >> c;
 		if (k & 1){
     			//printf("1");
			setbits++;
		}
  	}
	return setbits;
}

set rrotate(set a,int num){
	return (a >> num)|(a << (32 - num));
}

//function to shift bits to the left; passes through the set of bits you would like to shift
void leftShift(set a){
	int setbits = countBits(a);
	int printedbits = 1;			
	for(i =0;i < setbits;i++){
		printf("1");
		printedbits++;
		if(printedbits == 5){
			printf(" ");
			printedbits = 1;
		}
	}
	printedbits = 1;
	for(j = 0;j <(32-setbits);j++){
		printf("0");
		printedbits++;
		if(printedbits == 5){
			printf(" ");
			printedbits = 1;
		}
	}
	printf("\n");
}