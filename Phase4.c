
//Daniela Tamayo
//CSCI 3334
//Phase 4
//Description: Finish rest of commands - integret command interpret with the 
//simulation code of the SIC computer.

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

/*
//Phase2-3
void assemCommand(char *);
void passOne(FILE *);
void passTwo(FILE *);
*/


//Phase 4
#include "stdbool.h"
#include "sicengine.c"
void loadCommand(char *);
void dumpCommand(char *, char *);
void executeCommand();


void load(FILE *);
void dump(int, int);

int startLoc = -1;


/*
//par1 name of file
void assemCommand(char *par1){ 
	int length = strlen(par1);

	if(length == 0){
		printf("Assemble command needs filename.\n");
	}
	else {
	//opens source file
	FILE *f1=fopen(par1,"r");

	//Pass 1
	//symbol table and intermediate file
	passOne(f1);

	passTwo(f1);

	fclose(f1);
	}

}

//**************************PASS ONE********************************
void passOne(FILE *f1source){

FILE *f2, *f3, *f4, *f5;
int plength, locctr, startad, length, hex, temp;
static int flag =0;
//int line = 0;
char label[50], opcode [50], operand[50], opndtable[100], mnemonic[50], gar[50];


f2 = fopen("opctable.txt", "r");
f3 = fopen("symtable.txt", "w");
f4 = fopen("intermediate.txt", "w");
f5 = fopen("length.txt", "w");

fscanf(f1source,"%s %s %s %[^\n]",label, opcode, operand, gar);


if(strcmp (opcode, "START" )==0){
	sscanf(operand,"%x", &locctr);
	plength=locctr;

	startad=atoi(operand);

	//locctr=startad;

	//start writing intermediate file
	fprintf(f4, "\t\tOPCODE\tOPERAND\n");
	fprintf(f4,"********************************************\n");

	fprintf(f4,"%d\t\t%s\t%s\n",startad, opcode, operand);
	fscanf(f1source,"%s %s %s %[^\n]", label, opcode, opndtable, gar);
	fprintf(f4,"%d\t\t%s\t%s\n",startad, opcode, opndtable);

}
else{
	locctr = 0;
}


while (strcmp(opcode, "END") != 0) {
//line = 2;

	//if this is not a comment line
	//handle line
	//**********************************

	if (strcmp(label,  ".") != 0){
		//SYMTAB for LABEL
		//create symbol table
		/**********************************
		if(strcmp(label,"	") != 0){
		fscanf(f3,"%d %s", &locctr, opndtable);
			if(strcmp(label, opndtable) == 0){		//if symbol in label field
				flag = 1;
			}
			else{
				fprintf(f3, "%x\t%s\n", locctr, label);	//print on symbol table
			}
			fscanf(f3,"%d %s", &locctr, opndtable);
		}
		/***********************************/


		//search OPTAB for OPCODE
		/***********************************
		rewind(f2);
		fscanf(f2,"%s %d", mnemonic, &hex);
		while(!feof(f2)){
			if(strcmp(opcode,mnemonic)==0){
				locctr+=3;
				//fprintf(f3, "%s", mnemonic);
				break;
			}
		fscanf(f2, "%s %d", mnemonic, &hex);
		}
		/***********************************


		if(strcmp(opcode,"WORD")==0){
			locctr+=3;
		}
		else if(strcmp(opcode, "RESW")==0){
			sscanf(operand, "%d", &temp);
			locctr+=(3*temp);
		}
		else if(strcmp(opcode, "RESB")==0){
			sscanf(operand, "%d", &temp);
			locctr+=temp;
		}
		else if(strcmp(opcode, "BYTE")==0){
			if(opndtable[0] == 'X'){
				locctr += 1;
			}
			else {
				length=strlen(opndtable)-2;
				locctr+=length;
			}
		}
		else {
			//set error flag
			flag = 1;
		}

	}
	/**********************************

fscanf(f1source,"%s %s %s %[^\n]",label, opcode, opndtable, gar);
if (strcmp(label,  ".") != 0){

	//get rid of "--" to print intermediate file
	// print or not label
	if(strcmp(label, "--") ==0){
		strcpy(label, "	");
		fprintf(f4,"%x\t\t%s\t%s\n",locctr, opcode, opndtable);
	//line++;
	}
	else{

		fprintf(f4,"%x\t\t%s\t%s\n",locctr, opcode, opndtable);
	//line++;
	}
}

}//end while

plength=locctr-startad;
printf("The length of the program is %d \n",plength);
fprintf(f5, "%d",plength);


fclose(f2);
fclose(f3);
fclose(f4);
fclose(f5);

}

//******************************PASS TWO********************************

void passTwo(FILE *f1source){

FILE *fintermediate,*fopctable, *fsymtable, *flength, *flisting, *fobject;
int address, length, mnevalue, symaddress, flag;
int i;
char label[20], opcode[20], operand[20], start[20], opmnemonic[20],symbol[20], gar[50];

fintermediate = fopen("intermedaite.txt", "r");
fopctable = fopen("opctable.txt","r");
fsymtable = fopen("symtable.txt","r");
flength = fopen("length.txt", "r");
fobject = fopen("object.txt", "w");
flisting = fopen("listing.txt", "w");

fscanf(fintermediate,"%[^\n]",gar);
fscanf(fintermediate,"%[^\n]",gar);
fscanf(fintermediate,"%d%s%s%s",&address,label,opcode,operand);//read first input line
	if(strcmp(opcode,"START")==0){
		strcpy(start,operand);
		fscanf(flength,"%d",&length);
		fprintf(flisting, "%d%s%s%s",address,label,opcode,operand);//listing file
	}
fprintf(fobject, "H^%s^%s^%d\nT^00%s^",label,start,length,start);

fscanf(fintermediate,"%d%s%s%s",&address,label,opcode,operand);
while(strcmp(opcode,"END")!=0){
	//if(strcmp(label,"--") != 0){ if not comment
	fscanf(fopctable,"%s%d",opmnemonic,&mnevalue);//search  OPTAB for OPCODE
	while(!feof(fopctable)){
		if(strcmp(opcode,opmnemonic)==0){//if found then
			if(strcmp(label,"--") != 0){//if there is a symbol in OPERAND fiel then
				fscanf(fsymtable,"%d%s",&symaddress,symbol);//search SYMTAB for OPERAND
				while(!feof(fsymtable)){
					if(strcmp(operand,symbol)==0){//if found then
						symaddress = mnevalue;//store symbol value as operand address
						break;
					}
					else{
						symaddress = 0;
						flag = 1;
					}
				fscanf(fsymtable,"%d%s",&symaddress,symbol);
				}
			fscanf(fopctable,"%s%d",opmnemonic,&mnevalue);
			}
			else if((strcmp(opcode,"BYTE")==0)||(strcmp(opcode,"WORD")==0)){
					if(strcmp(opcode,"WORD")==0){
						fprintf(fobject, "0000%s^",operand);
					}
					else{
						length=strlen(operand);
						for(i=2;i<length;i++){
							printf("%d",operand[i]);
						}
						fprintf(fobject,"^");
					}
			}
		fscanf(fintermediate,"%d%s%s%s",&address,label,opcode,operand);
		}
	}

}

fprintf(fobject, "\nE^00%s",start);

fclose(fintermediate);
fclose(fopctable);
fclose(fsymtable);
fclose(flength);
fclose(fobject);
fclose(flisting);

}
*/


void loadCommand(char *par1){
	int length = strlen(par1);

	if(length == 0){
		printf("Load command needs filename.\n");
	}
	else{
		//open object file
		FILE *f1object = fopen(par1, "r");

		//actually runs
		load(f1object);

		printf("File loaded!\n");

		fclose(f1object);
	}
}


void dumpCommand(char *par1, char *par2){
	int length1 = strlen(par1);
	int length2 = strlen(par2);

	if (length1 == 0){
		printf("Dump command needs two parameters");
	}
	else {
		//strings into ints
		sscanf(par1, "%x", &length1);
		sscanf(par2, "%x", &length2);

		//actually runs
		dump(length1, length2); 
	}
}

void executeCommand(){
	
	unsigned long temp = (long unsigned long)startLoc;
	//from sicengine.c
	SICRun(&temp, 0);
}


void load(FILE *fobject){

	char record[100], name[6], stad[6], plength[6];
	char temp[6], temp2[2], temp3[2], end[6];

	int start, totalLength, length, recordAd, recordNum;
	int location = 1;//H
	int bytehex = 0;
	char *byte;

	//start by getting header record
	fgets(record, 100, fobject);

	//copy name to array and increment loc of record
	for(int i = 1; i <= 6; i++)
	{
		name[i-1] = record[i];//exclude H
		location++;
	}

	//in other array get what is next (start address)
	for(int i = 0; i < 6; i++)
	{
		stad[i] = record[location];
		location++;
	}
	//start address into actual number
	sscanf(stad, "%x", &start);

	// following the program length
	for(int i = 0; i < 6; i++)
	{
		plength[i] = record[location];
		location++;
	}
	//total length into actual number
	sscanf(plength, "%x", &totalLength);

	//start from beginning text record,
	//location at 1 to exclude T
	location = 1;
	fgets(record, 100, fobject);
	length = strlen(record)-1;

	//loop through file
	while(record[0] != 'E'){

		//start record address
		for(int i = 1; i<=6; i++){
			temp[i-1] = record[i];
			location++;
		}
		//convert it to hex
		sscanf(temp, "%x", &recordAd);

		//first two after address
		for(int i = 0; i < 2; i++){
			temp2[i] = record[location];
			location++;
		}
		//number of records
		sscanf(temp2, "%d", &recordNum);

		while(location < length){
			//next two following ch
			for(int i = 0; i < 2; i++){
				temp3[i] = record[location];
				location++;
			}

			//store in bytes
			sscanf(temp3, "%02x", &bytehex);
			byte = (char *)&bytehex;
			//load into memory
			PutMem(recordAd, byte, 0);	//sicengine- always 0
			recordAd++;
		}
		//next text record
		fgets(record, 100, fobject);
		length =strlen(record)-1;
		location = 1;
	}
	//end record
	for(int i = 1; i<=6; i++){
		end[i-1]=record[i];
	}
	sscanf(end, "%x", &startLoc);

}
void dump(int startAd, int endAd){
	unsigned char value;
	int counter =0;

	printf("%x: ", startAd);
	for(int i = startAd; i<=endAd; i++){
		if(counter == 0x10){
			counter = 0;
			printf("\n%x: ",i);
		}
		
		GetMem(i, &value, 0);	//sicengine
		printf("%02x  ", value);
		counter++;
	}
	printf("\n\n");
}




int main(){

char a[100], pm1[50], pm2[50], command[50];
SICInit();//initialize simulator

//repeat until exit
while (strcmp(a, "exit") != 0) {

	printf("ENTER A COMMAND \n");
	//command
	fgets(a, 100, stdin);

	sscanf(a,"%s %s %s", command, pm1, pm2);

//compare input from user
	if (strcmp(command, "load") == 0){
		loadCommand(pm1);//loads into memory
		
	}
	else if (strcmp(command, "execute") == 0){
		executeCommand();//calls SIC simulator
		
	}
	else if (strcmp(command, "debug") == 0){
		printf("Command not prepared.\n");
	}
	else if (strcmp(command, "dump") == 0){
		dumpCommand(pm1, pm2);//displays a portion of contents of memory 
		
	}
	else if (strcmp(command, "help") == 0){
		printf("******COMMANDS******** \n");
		printf("load filename: will call the load function to load the specified file. \n");
		printf("execute: will call the computer simulation program to exxecute the program that was previously loaded in memory. \n");
		printf("debug: will allow you to execute in debug mode. \n");
		printf("dump start end: will call the dump function, passing the values of start and end. Start and end will be hexadecimal values. \n");
		printf("help: will print out a list of availabe commands. \n");
		printf("assemble filename: will assemble an SIC assembly language program into a load module and store it in a file. \n");
		printf("directory: will list the files stored in the current directory. \n");
		printf("exit: will exit from the simulator. \n");
	}
	else if (strcmp(command, "assemble") == 0){
		//assemCommand(pm1);
		printf("Command not prepared.\n");
	}
	else if (strcmp(command, "directory") == 0){
		system("ls -l");
	}
	else if(strcmp(command, "exit") == 0){
		break;
	}
	else {
		printf("Command not found, type help to display all commands. \n");
		fgets(a,100, stdin);
	}
}
return 0;
}
