
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXLEN 20 //max size of the strct strings
//create the struct of strings called strings_t
struct strings{
	
	char statename[MAXLEN];
	char capital[MAXLEN];
	int population;
	char timezone[MAXLEN];
	float tallestpeak;
	
};
typedef struct strings strings_t;


void makearrays(strings_t data[]); //creates the array from the file 
void linecount(void); //counts lines
void alphabetsort(strings_t data[],int n);//sorts the file alphabetically
void numericalsort(strings_t data[],int n);//sorts the data numerically
void add(strings_t data[], int *n);//adds a record
void search(strings_t data[], int n);//search by cap or state
void searchcap(strings_t data[], int n);//helper functions for search
void searchst(strings_t data[], int n);
void delete(strings_t data[], int *n);//delete a record by statename 
void view(strings_t data[], int n);//view the data
void savetofile(strings_t data[], int n);//save data to a new file

void main (void){
	int n=50;//number of lines to start
	char rubbish;//character to hold extra enters 
	strings_t data[61];//main array
	makearrays(data);//function to make arrays from files
	int on=1;//on and off switch to stay in or exit the program
	char menuselect=' ';//selection char for menu

	printf("\nThis database holds information about the 50 U.S states.\n");
	printf("Each record holds the state name, capital city, population, time zone, and height of the tallest peak in ft.\n\n\n");
	printf("Within this menu you may:\n\n");
	printf("press (v) to simply view the database sorted in alphabetcal order by state\n");
	printf("press (a) to alphabetically sort the database by capital city names\n");
	printf("press (n) to sort the data by their population sizes, greatest to least\n");
	printf("press (+) to create a new state of your own and add it to the database\n");
	printf("press (-) to delete any record from the database by typing in the state name\n");
	printf("press (s) to search the data by capital name or by state name\n");
	printf("press (l) to print out the number of records in the database \n");
	printf("press (w) to save the database to your own new file\n\n");
	
	while (on){
		scanf("%c", &menuselect);// scan user input for menu selection
		switch (menuselect){
			case 'v':
				view(data,n);
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case 'a':
				alphabetsort(data,n);
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case 'n':
				numericalsort(data,n);
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case '+':
				add(data,&n);
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case '-':
				delete(data,&n);
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case 's':
				scanf("%c", &rubbish);
				search(data,n);
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case 'l':
				linecount();
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case 'w':
				savetofile(data,n);
				printf("\n\nselect a new menu item or press e to exit the program\n");
				break;
			case 'e':
				on=0;
				break;
		}		
	}
}



void savetofile(strings_t data[], int n){
	char filename[40];//initialize filename string
	int k=0;//lopp counter
	FILE *savefile;//name of the saved file
	printf("Enter the file you want to save the data to :\n");
	scanf("%s", filename); //takes in the filename
	if (filename!= "statedata.txt"){
		
		savefile=fopen(filename,"w");//open file 
		
		for (k=0;k<n;k++){
			fprintf(savefile, "%s, %s, %d, %s, %f\n",data[k].statename,data[k].capital,
			data[k].population,data[k].timezone,data[k].tallestpeak);
		}
		fclose(savefile);
	}
}

void view(strings_t data[], int n){
	int k=0;// loop counter
	for (k=0;k<n;k++){
		printf("%s, %s, %d, %s, %f\n",data[k].statename,data[k].capital,
		data[k].population,data[k].timezone,data[k].tallestpeak);
	}
	
}

void delete(strings_t data[], int *n){
	char statename[10];
	char capitalname[20];
	int population;
	char timezone[30];
	float tallestpeak;
	char delete=' ';
	int i=0;
	int k=0;
	int on =1;
	char menu=' ';
	makearrays(data);

	


	if (*n>0){
		printf("\nenter a state name to delete that state's record from the database:\n\n");
		scanf("%s", &statename[10]);
		int j=0;
		for(i=0; i<*n; i++){
			
					
			if(strcmp(&statename[10],data[i].statename)==0){
				for(j=i; j<*n; j++){
					strcpy(data[j].statename,data[j+1].statename);
					strcpy(data[j].capital,data[j+1].capital);
					data[j].population=data[j+1].population;
					strcpy(data[j].timezone,data[j+1].timezone);
					data[j].tallestpeak=data[j+1].tallestpeak;
					
				}
				*n-=1;

			}
	}
			for (k=0;k<*n;k++){
			printf("%s, %s, %d, %s, %f\n",data[k].statename,data[k].capital,
			data[k].population,data[k].timezone,data[k].tallestpeak);
		}
		//call menu
		
	}

	else{ 
	printf("You have no more records.\n");
	//call the menue function
	}
}

void searchcap(strings_t data[], int n){
	int j=0;//loop counter
	char capitalname[20];//string for the capital name 
	scanf("%s", &capitalname[10]);//take in the users input
	
	for(j=0; j<n; j++){//loop through and check each item in the file 
			
		if(strcmp(&capitalname[10],data[j].capital)==0){// if it is the same as the entered capital 
				//retrieve the data and print it
			printf("%s -> state name: %s, population: %d, time zone: %s, tallest peak: %f.\n\n", data[j].capital,data[j].statename,
			data[j].population,data[j].timezone,data[j].tallestpeak);
			printf("\nPlease press d to default search data by statename or press enter then c to search data by capital. Press e to exit: \n");
		}
	}
}

void searchst(strings_t data[], int n){
	int i=0;//loop counter
	char statename[20];//statename string
	scanf("%s", &statename[10]);//take in user input
	for(i=0; i<n; i++){//loop through array of state names
		if(strcmp(&statename[10],data[i].statename)==0){//if one is the same as the entered statename
			//retrieve and print the data
			printf("%s -> capital: %s, population: %d, time zone: %s, tallest peak: %f.\n\n", data[i].statename,data[i].capital,
			data[i].population,data[i].timezone,data[i].tallestpeak);
			printf("\nPlease press d to default search data by statename or press enter then c to search data by capital. Press e to exit: \n");			
		}
	}
}		

void search(strings_t data[], int n){
	int j=0;// loop counter
	int on=1;//switch to keep the function running until specificied
	char srchselection=' '; //selecion char
	char bufferchar= ' '; //char to sink un-needed input 

	printf("\nPlease press d to default search data by statename or press enter then c to search data by capital. Press e to exit [d]: \n");
	
	while (on){// while the user hasnt pressed e to return to menu 
		scanf("%c", &bufferchar); //sink unneeded enter
		scanf("%c",&srchselection);//take the selection of what to search 
	
		switch(srchselection){//switch based on entered srch selection 
			case 'c':
				printf("\nPlease enter the name of a capital to retrieve its data: \n\n");
				searchcap(data,n);//search by capital
				break;
				
			case '\n':
				printf("\nPlease enter the name of a state to retrieve its data: \n\n");
				searchst(data,n);//search by state 
				break;
				
			case 'd':
				printf("\nPlease enter the name of a state to retrieve its data: \n\n");
				searchst(data,n);//search default by state
				break;
							
			case 'e':
				on=0;//return to menu 
				break;
		
		}	
	}		
}

void add(strings_t data[], int *n){
	//placeholders for each part of the struct
	char statename[20];
	char capitalname[20];
	int population;
	char timezone[30];
	float tallestpeak;
	
	if (*n<60){//if the n isnt greater than the max of the array 
		//take in user input for each part of the record they want to add
		printf("Enter a new statename, capital, population, timezone, and tallest peak height in inches:\n");
		scanf("%s %s %d %s %f",&statename[20], &capitalname[20], &population, &timezone[30], &tallestpeak);
		strcpy(data[*n].statename,&statename[20]);
		strcpy(data[*n].capital,&capitalname[20]);
		data[*n].population=population;
		strcpy(data[*n].timezone,&timezone[30]);
		data[*n].tallestpeak=tallestpeak;
		//keep a count of the records and the max
		printf("You now have %d entries. Enter no more than 60\n",*n);
		
	}

	else{ 
		printf("You have no more space to add more records. I will return you to the menu.\n");
	}
}

void numericalsort(strings_t data[], int n){
	//counter variables
	int capnum=0;
	int sortindex=0;
	//placeholder temporary strings for each part of the struct
	int sortarray[50];
	char tempcap[30];
	char tempst[30];
	int temppop;
	char temptz[30];
	float temptp;
	int popnum;
	
	
	for (sortindex=0; sortindex<n; sortindex++){//loop through and create a sortarray
		//set the element equal to the index
		sortarray[sortindex]=sortindex;
	}

	
	for (popnum=1;popnum<n;popnum++){//loop through and compare the population sizes
		for (sortindex=1;sortindex<50;sortindex++){
			
			
			//if one population size is greater than another 
			if(data[sortarray[sortindex-1]].population < data[sortarray[sortindex]].population){
			
			//swap around all parts of the struct to correspond with the switched population size
				strcpy(tempcap, data[sortindex - 1].capital);
				stpcpy(tempst, data[sortindex-1].statename);
				temppop=data[sortindex-1].population;
				stpcpy(temptz, data[sortindex-1].timezone);
				temptp= data[sortindex-1].tallestpeak;
				
				strcpy(data[sortindex - 1].capital, data[sortindex].capital);
				strcpy(data[sortindex - 1].statename, data[sortindex].statename);
				data[sortindex - 1].population=data[sortindex].population;
				strcpy(data[sortindex - 1].timezone, data[sortindex].timezone);
				data[sortindex - 1].tallestpeak=data[sortindex].tallestpeak;
				
				strcpy(data[sortindex].capital, tempcap);
				strcpy(data[sortindex].statename, tempst);
				data[sortindex].population=temppop;
				strcpy(data[sortindex].timezone, temptz);
				data[sortindex].tallestpeak= temptp;
			
			}	
		}
	}
	for (int i=0;i<n;++i){// loop through and print the data
		printf("%s, %s, %d, %s, %f\n", data[sortarray[i]].statename,data[sortarray[i]].capital,
		data[sortarray[i]].population,data[sortarray[i]].timezone,data[sortarray[i]].tallestpeak);
	}
}

void alphabetsort(strings_t data[],int n){
//counter variables
	int capnum=0;
	int sortindex=0;
	//placeholder temporary strings for each part of the struct
	int sortarray[50];
	char tempcap[30];
	char tempst[30];
	int temppop;
	char temptz[30];
	float temptp;
	
	for (sortindex=0; sortindex<n; sortindex++){// loop through and create sort array
		//se the index equal to the element
		sortarray[sortindex]=sortindex;
	}
	
	for (capnum=1;capnum<n;capnum++){//loop through and sort by capital alphabetical order
	
		for (sortindex=1;sortindex<n;sortindex++){
		
		//if the capital the first is above the second, swap the two
			if(strcmp(data[sortarray[sortindex-1]].capital, data[sortarray[sortindex]].capital)>0){
			
				strcpy(tempcap, data[sortindex - 1].capital);
				stpcpy(tempst, data[sortindex-1].statename);
				temppop=data[sortindex-1].population;
				stpcpy(temptz, data[sortindex-1].timezone);
				temptp= data[sortindex-1].tallestpeak;
				
				strcpy(data[sortindex - 1].capital, data[sortindex].capital);
				strcpy(data[sortindex - 1].statename, data[sortindex].statename);
				data[sortindex - 1].population=data[sortindex].population;
				strcpy(data[sortindex - 1].timezone, data[sortindex].timezone);
				data[sortindex - 1].tallestpeak=data[sortindex].tallestpeak;
				
				strcpy(data[sortindex].capital, tempcap);
				strcpy(data[sortindex].statename, tempst);
				data[sortindex].population=temppop;
				strcpy(data[sortindex].timezone, temptz);
				data[sortindex].tallestpeak= temptp;
			
			}	
		}
	}
	for (int i=0;i<50;++i){//loop through and print the data
		printf("%s, %s, %d, %s, %f\n", data[sortarray[i]].statename,data[sortarray[i]].capital,
		data[sortarray[i]].population,data[sortarray[i]].timezone,data[sortarray[i]].tallestpeak);
	}
}

void makearrays(strings_t data[]){
	//counter variable 
	int i=0;
	char n=50;// initial n to create the arrays
	FILE *statedata;//file for the state data

	statedata=fopen("statedata.txt","r");// open the file 
		
	while(i<n){// loop through the file and add to each part of the struct
		fscanf(statedata,"%[^,],%[^,],%d,%[^,],%f\n", data[i].statename,data[i].capital,&data[i].population,
		data[i].timezone,&data[i].tallestpeak);
		i++;	
	}
	fclose(statedata);//close file
	}

	
void linecount(){
	FILE *statedata;//file name
	statedata=fopen("statedata.txt","r");//open file
	int lines=0;//line counter 
	char character=' ';//char variable for the scan
    if(statedata== NULL){ // if the file doesnt exist 
        printf("file not found\n");
	}
	else{
		while(fscanf(statedata, "%c", &character) !=EOF){// loop to the end of file 
			if(character=='\n'){// each backslash will increment the counter
				lines++;
			}
		}
		printf("%d", lines);
		fclose(statedata);
	}
}