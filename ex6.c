#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH_DESCRIPTION 211

typedef enum { false, true } bool;
enum hobbies { BASEBALL = 1, BASKETBALL, BICYCLE, BOOKS, DRAWING, GYM, MOVIES, POETRY };

//in this program we have 3 kind of structs
typedef struct
{
	char* id;
	char* firstName;
	char* lastName;
	int age;
	char sex;
	char* userName;
	char* password;
	char* description;
	char* hobbies;
} member;

typedef struct womenItem womenItem;
struct womenItem {
	member* data;
	womenItem* next;
};

typedef struct
{
	womenItem *head, *last;
}womenList;

//functions declarations 
member* readText(member* men, womenList* wList, int* countMen, int* sizePtr, int j);
int login(member* men, womenList* wList, int* countMen, int *sizePtr);
member* mainMenuForMen(member* men, womenList* wList, int* countMen, member* maleUser, int *sizePtr);
void mainMenuForWomen(member* men, womenList* wList, int* countMen, int* sizePtr, womenItem* iterator);
int findMatchForMen(member* men, womenList* wList, int* countMen, member* maleUser);
int findMatchForWomen(member* men, womenList* wList, int* sizePtr, womenItem* iterator);
int matcHobbies(member* maleUser, womenItem* iterator);
void printHobbies(char hobbie);
void hobbieCases(int temp);
//for the read text
member* newMember1(womenList* wList, char* id, char* firstName, char* lastName, int age, char sex, char* userName, char* password, char* description, char hobbies);
member* newMember2(int *sizePtr, int* countMen, member* men, womenList* wlist);
//void freeWomenItem( womenItem* item);
void freeWomanItem(womenItem* iterator);
//creating a new womenlist
womenList* newWomenList();
//Adding a new women to the end of the List
void add(womenList* wList, member* newWomen);
//Adding a women to the beginning of the List
void push(womenList* wList, member* newWomen);
womenItem* newIterator(womenList*  wList);
void printWomenList(womenList* wList);
void printMember(member* member);
void freeMember(member* member);
int nameComparator(member* a, member* b);
void bubbleSort(womenList* wList);
void switchWomenItems(womenItem* a, womenItem* b);
char turnOnThebits(int h1, int h2, int h3, int h4);
int firstMenu(member* men, womenList* wList, int* countmen, int *sizePtr);
void outPutText(womenList* wList, member* men, int* sizePtr);
member addNewMen(member* men, char* idNew, char* firstNameNew, char* lastNameNew, int ageNew, char sexNew, char* userNameNew, char* passwordNew, char* descriptionNew, char hobb);
//void freeLinkedList(womenList* wList);
//void deleteWomen(member* men, womenList* wList, int* countMen, int* sizePtr, womenItem* theRequiredUser);
void deleteWoman(womenList* wList, member* woman);
member* freeDynamicMen(member* men, int* sizePtr);
//member* freeDynamicMen(member* men, int* sizePtr);
void freeWomenItemLast(womenItem* item);
void freeWomenList(womenList* wList);

int main()
{
	int option = 0, countMen = 0, i = 0;
	//the following int represent the counter of the men
	int *sizePtr;
	int j = 0;
	sizePtr = &j;
	int loginValue = 0;
	womenItem* noNeed = NULL;
	//will contain the men list (dinamic array)
	member* men = (member*)malloc(sizeof(member));
	//verify if the allocation exists
	if (men == NULL)
	{
		printf("Allocation failed\n");
		exit(1);
	}
	//allocating a list for the women (linked-list)
	womenList* wList = newWomenList();
	//men = readText(men, wList, &countMen, &sizePtr, j);
	men = readText(men, wList, &countMen, sizePtr, j);
	//firstMenu(men, wList, &countMen, sizePtr);
	while (option != 3)
	{
		printf("Welcome! please choose an option\n");
		printf("1 - Log in\n");
		printf("2 - New member\n");
		printf("3 - Exit\n");
		scanf("%d", &option);
		//login option
		if (option == 1)
		{
			//loginValue = login(men, wList, &countMen, &sizePtr);
			loginValue = login(men, wList, &countMen, sizePtr);
		}
		//sign in option
		if (option == 2)
		{
			//need to check if the user isnt exist
			//call the function newMember
			//men = newMember2(&sizePtr, countMen, men, wList);
			men = newMember2(sizePtr, countMen, men, wList);
		}
		//exit from the system
		if (option == 3)
		{
			//call the output function 
			outPutText(wList, men, sizePtr);
			//call this function in order to free the dynamic men array
			men = freeDynamicMen(men, sizePtr);
			free(men);
			//use this function in order to free the women list
			freeWomenList(wList);
			free(wList);
			return 0;
		}
		else if (option != 1 && option != 2 && option != 3)
		{
			printf("Bad choice, please try again\n");
		}
	}
	//option = 0;
	return 0;
}

/************************************************************************
* function name: readText
* The Input: member* men, womenList* wList, int* countMen, int* sizePtr, int j
* The output: rerturn the dinamic array called men
* The Function operation: the function load from the input file the details of each member
 and sorts any member according to this gender into 2 diffrent data bases: dinamic array for men
 and linked list for women.
 the dinamic men's array is the array men whereas the linked list of the women is wList.
*************************************************************************/
member* readText(member* men, womenList* wList, int* countMen, int* sizePtr, int j)
{
	member* pMember = NULL;
	//a temp list which will contain all the data before we split it to 2 diffrent bases (males and females)
	member* list;
	int h1 = 0, h2 = 0, h3 = 0, h4 = 0;
	int noName = 0;
	char savechar[2];
	list = (member*)malloc(sizeof(member));
	//verify if the allocation exists
	if (list == NULL)
	{
		printf("Allocation is failed\n");
		exit(1);
	}
	//the file pointer
	FILE* fp;
	//when numOfLine equal to 0 it means that the file ptr is on the first line/ first member's details
	int  numOfLine = 0, i = 0;
	int age;
	char dummy;
	char sex;
	char* idNum[10], pName[15], lName[15], uName[15], pass[15], hob[9], det[211];
	//fp is a pointer to the data in the input file
	fp = fopen("input.txt", "rt");
	//verify the success of opening the file
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	fscanf(fp, "%c", &dummy);
	//the following loop run until the end of the input file
	while (!feof(fp))
	{
		//if the file pointer is on the begining of the first line move 1 byte backward
		if (numOfLine == 0)
		{
			//SEEK_CUR moves file's pointer position to the given location
			//i use SEEK_CUR to find backward 1 byte from current position
			fseek(fp, -1, SEEK_CUR);
		}
		//fscanf reads from a file pointed by the FILE pointer (fp)
		fscanf(fp, "%[^;]", idNum);
		//SEEK_CUR move the pointer of the file 1 forward anytime
		fseek(fp, 1, SEEK_CUR);
		//using fscanf to save any field of the struct according to the condition of the delimiter which is until ;
		fscanf(fp, "%[^;]", pName);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%[^;]", lName);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%d", &age);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%c", &sex);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%[^;]", uName);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%[^;]", pass);
		fseek(fp, 1, SEEK_CUR);
		//the insert of the hobbs is an array which include the numbers of each hobbie and the commas
		fscanf(fp, "%[^;]", hob);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%[^\n]", det);
		//savechar[0] equal to the first hobbie (number with no comma)
		savechar[0] = hob[0];
		savechar[1] = 0;
		//save the char as int by the function atoi
		h1 = atoi(savechar);
		//savechar[0] equal to the second hobbie (number with no comma)
		savechar[0] = hob[2];
		savechar[1] = 0;
		//save the char as int by the function atoi
		h2 = atoi(savechar);
		//savechar[0] equal to the third hobbie (number with no comma)
		savechar[0] = hob[4];
		savechar[1] = 0;
		//save the char as int
		h3 = atoi(savechar);
		//savechar[0] equal to the 4th hobbie (number with no comma)
		savechar[0] = hob[6];
		savechar[1] = 0;
		//save the char as int by the function atoi
		h4 = atoi(savechar);


		//don't forget to verify all the allocations !!!!!!!!!!!
		list[numOfLine].id = (char*)malloc(strlen(idNum) + 1);
		//verify the allocation
		if (list[numOfLine].id == NULL)
		{
			printf("Allocation is failed\n");
			exit(1);
		}
		list[numOfLine].firstName = (char*)malloc(strlen(pName) + 1);
		//verify the allocation
		if (list[numOfLine].firstName == NULL)
		{
			printf("Allocation is failed\n");
			exit(1);
		}
		list[numOfLine].lastName = (char*)malloc(strlen(lName) + 1);
		//verify the allocation
		if (list[numOfLine].lastName == NULL)
		{
			printf("Allocation is failed\n");
			exit(1);
		}
		list[numOfLine].userName = (char*)malloc(strlen(uName) + 1);
		//verify the allocation
		if (list[numOfLine].userName == NULL)
		{
			printf("Allocation is failed\n");
			exit(1);
		}
		list[numOfLine].password = (char*)malloc(strlen(pass) + 1);
		//verify the allocation
		if (list[numOfLine].password == NULL)
		{
			printf("Allocation is failed\n");
			exit(1);
		}
		list[numOfLine].hobbies = (char*)malloc(sizeof(char));
		//verify the allocation
		if (list[numOfLine].hobbies == NULL)
		{
			printf("Allocation is failed\n");
			exit(1);
		}
		list[numOfLine].description = (char*)malloc(strlen(det) + 1);
		//verify the allocation
		if (list[numOfLine].description == NULL)
		{
			printf("Allocation is failed\n");
			exit(1);
		}
		//filling the fields by copying the strings
		strcpy(list[numOfLine].id, idNum);
		strcpy(list[numOfLine].firstName, pName);
		strcpy(list[numOfLine].lastName, lName);
		strcpy(list[numOfLine].userName, uName);
		strcpy(list[numOfLine].password, pass);
		//calling the function turnOntheBits
		*(list[numOfLine].hobbies) = turnOnThebits(h1, h2, h3, h4);
		strcpy(list[numOfLine].description, det);
		list[numOfLine].age = age;
		list[numOfLine].sex = sex;
		//finish the first line of the input file, means we finish to insert the deatils of the member
		//thererfore we add 1 to numOfLine and continue to the next line
		//"numOfLine+1" represent the number of lines, each line is a member.
		numOfLine += 1;
		//after adding a new member from the file i have to maximize the array
		list = (member*)realloc(list, sizeof(member)*(numOfLine + 1));
	}
	//numOfLine = numOfLine - 1;
//	freeMember(&list[numOfLine]);
	list = (member*)realloc(list, sizeof(member)*(numOfLine));

	//declaration
	womenItem tempFemale;

	//the following loop run over the number of members\lines in the file
	for (i = 0; i < numOfLine; i++)
	{
		//if the gender is male
		if (list[i].sex == 'M')
		{
			//copy the fields to the dinamic array of the males\men
			men[j].id = list[i].id;
			men[j].firstName = list[i].firstName;
			men[j].lastName = list[i].lastName;
			men[j].userName = list[i].userName;
			men[j].password = list[i].password;
			men[j].hobbies = list[i].hobbies;
			men[j].description = list[i].description;
			men[j].age = list[i].age;
			men[j].sex = list[i].sex;
			//adding to the counter 1
			j++;
			(*countMen) = (*countMen) + 1;
			//using realloc to enlarge the array of men 
			men = (member*)realloc(men, sizeof(member)*(j + 1));
		}
		//if the gender is female
		else
		{
			//using a temporary women item which contain the data of the female
			tempFemale.data = newMember1(wList, list[i].id, list[i].firstName, list[i].lastName, list[i].age, list[i].sex
				, list[i].userName, list[i].password, list[i].description, *(list[i].hobbies));
			//calling the fucntion push
			push(wList, tempFemale.data);
			freeMember(&list[i]);
		}
	}
	men = (member*)realloc(men, sizeof(member)*(j));
	//the conters of the men number
	*sizePtr = j;
	//*sizePtr = *countMen;
	//we don't need the list because we sent the data to men and wlist so we use the function free
	free(list);
	//calling the function in order to sort the women last names according to the ABC 
	bubbleSort(wList);
	//return the new dinamic array of the males from the input.txt
	fclose(fp);
	return men;
	//list contains all the input list M and F
	//men contains just the men list
	//wList contains the women linked list
}

/************************************************************************
* function name: newMember1
* The Input: char* id, char* firstName, char* lastName, int age, char sex, char* userName, char* password,
char* description, char* hobbies
* The output: the function return the array of the new member for the readText function
* The Function operation: i use this function in order to copy the temporary women array.
in addition i use this fucntion in order to add a new woman to the linked list in a case
that the user chose the option of "new member" in first menu.
*************************************************************************/
member* newMember1(womenList* wList, char* id, char* firstName, char* lastName, int age, char sex, char* userName, char* password,
	char* description, char hobbies)
{
	member* woman = (member*)malloc(sizeof(member));
	woman->firstName = (char*)malloc(strlen(firstName) + 1);
	strcpy(woman->firstName, firstName);
	woman->id = (char*)malloc(strlen(id) + 1);
	strcpy(woman->id, id);
	woman->lastName = (char*)malloc(strlen(lastName) + 1);
	strcpy(woman->lastName, lastName);
	woman->age = age;
	woman->sex = sex;
	woman->userName = (char*)malloc(strlen(userName) + 1);
	strcpy(woman->userName, userName);
	woman->password = (char*)malloc(strlen(password) + 1);
	strcpy(woman->password, password);
	woman->description = (char*)malloc(strlen(description) + 1);
	strcpy(woman->description, description);
	woman->hobbies = (char*)malloc(sizeof(char));
	*(woman->hobbies) = hobbies;
	return woman;
}

/************************************************************************
* function name: login
* The Input: member* men, womenList* wList, int* countMen, int *sizePtr
* The output: none its void
* The Function operation: firstly, the function check the gender of the user and if its exist in the system.
moreover,if the user exists it calls the functions of the main menu according to the gender,
else it prints that the user isnt exist.
*************************************************************************/
int login(member* men, womenList* wList, int* countMen, int *sizePtr)
{
	char userNameTMP[15];
	char passwordTMP[15];
	char userNameTMP2[15];
	char dummy;
	int i = 0, flag = 0;
	womenItem* iterator = newIterator(wList);
	printf("Please enter your username:\n");
	//scanf("%c", &dummy);
	scanf("%s", &userNameTMP);
	printf("Please enter your password:\n");
	//scanf("%c", &dummy);
	scanf("%s", &passwordTMP);
	//the following loop check if the male username is a exist
	for (i = 0; i < *sizePtr; i++)
	{
		if (strcmp(men[i].userName, userNameTMP) == 0 && strcmp(men[i].password, passwordTMP) == 0)
		{
			flag = 1;
			men = mainMenuForMen(men, wList, countMen, &men[i], sizePtr);
			return 0;
		}
	}
	// the following conditions by flag verify if the user is a women which exist
	if (flag == 0)
	{
		iterator = wList->head->next;
		while (iterator != NULL)
		{
			if (strcmp(iterator->data->userName, userNameTMP) == 0 && strcmp(iterator->data->password, passwordTMP) == 0)
			{
				flag = 1;
				mainMenuForWomen(men, wList, &countMen, sizePtr, iterator);
				return 0;
			}
			iterator = iterator->next;
		}
	}
	//in a case the user isn't exist
	if (flag == 0)
	{
		printf("User do not exist in the system, please try again\n");
	}

	//another chance to the user
	flag = 0;
	printf("Please enter your username : \n");
	scanf("%s", &userNameTMP2);
	//the following loop check if the male username is a exist
	for (i = 0; i < *countMen; i++)
	{
		//if the username isn't exist.
		if (strcmp(men[i].userName, userNameTMP2) != 0)
		{
			//maybe it's a woman
			flag = 0;
		}
		//if the username exist but the password isnt correct
		if (strcmp(men[i].userName, userNameTMP2) == 0 && strcmp(men[i].password, passwordTMP) != 0)
		{
			//it means that it's a man
			flag = 1;
			printf("Wrong password\n");
			return;
		}
		//if they both correct (username and password)
		if (strcmp(men[i].userName, userNameTMP2) == 0 && strcmp(men[i].password, passwordTMP) == 0)
		{
			flag = 1;
			//men = mainMenuForMen(men, wList, countMen, &men[i], &sizePtr);
			men = mainMenuForMen(men, wList, countMen, &men[i], sizePtr);
		}
	}
	// the following conditions by flag verify if the user is a women which exist
	if (flag == 0)
	{
		iterator = wList->head->next;
		while (iterator != NULL)
		{
			//if the username of the woman isn't exist return.
			if (strcmp(iterator->data->userName, userNameTMP2) != 0)
			{
				return;
			}
			//if the username is correct but the password is wrong
			if (strcmp(iterator->data->userName, userNameTMP2) == 0 && strcmp(iterator->data->password, passwordTMP) != 0)
			{
				printf("Wrong password\n");
				return;
			}
			//if they both correct (username and password)
			if (strcmp(iterator->data->userName, userNameTMP2) == 0 && strcmp(iterator->data->password, passwordTMP) == 0)
			{
				mainMenuForWomen(men, wList, &countMen, sizePtr, iterator);
			}
			iterator = iterator->next;
		}
	}


}
/************************************************************************
* function name: mainMenuForMen
* The Input: member* men, womenList* wList, int* countMen, member* maleUser, int *sizePtr
* The output: men - the new men arrays after the change
* The Function operation: if the user press 1 it calls the function findMatchForMen,
if the user chose 2 it return the new men array minus the specific user which chose delete me,
if the user press it return with no value back to the first menu.
*************************************************************************/

member* mainMenuForMen(member* men, womenList* wList, int* countMen, member* maleUser, int *sizePtr)
{

	int i = 0, k = 0, option = 0;
	printf("Hello %s!\n", maleUser->firstName);
	while (option != 3)
	{
		printf("Please choose an option:\n");
		printf("1. Find a match\n");
		printf("2.found love, DELETE me\n");
		printf("3. Log out\n");
		scanf("%d", &option);
		//find match
		if (option == 1)
		{
			findMatchForMen(men, wList, countMen, maleUser);
		}
		//delete the men
		if (option == 2)
		{
			//the following loop run over the men's number 
			for (i = 0; i < *sizePtr; i++)
			{
				if (strcmp(men[i].id, maleUser->id) == 0)
				{
					//in the following we move each men right
					for (k = i; k < *sizePtr - 1; k++)
					{
						men[k] = men[k + 1];
					}
					//small the array of the mens -1
					men = (member*)realloc(men, sizeof(member)*((*sizePtr) - 1));
					break;
				}
			}
			//we delete 1 men so the counter is smaller by 1
			*sizePtr = *sizePtr - 1;
			//return the new men array
			return men;
		}
		//logout
		if (option == 3)
		{
			return;
		}
	}
	return;
}

/************************************************************************
* function name: mainMenuForWomen
* The Input: none its void. it just call to other functions in specific cases.
* The output: it just call to other functions in specific cases.
* The Function operation: if the user press 1 the function sends him to find a match by calling the function
findMatchForWomen, if the user press 2 it sends him to the function deleteWomen,
if th user chose 3 it just logs out and return to the first menu.
*************************************************************************/

void mainMenuForWomen(member* men, womenList* wList, int* countMen, int* sizePtr, womenItem* iterator)
{
	int i = 0, option = 0;
	printf("Hello %s!\n", iterator->data->firstName);
	while (option != 3)
	{
		printf("Please choose an option:\n");
		printf("1. Find a match\n");
		printf("2.found love, DELETE me\n");
		printf("3. Log out\n");
		scanf("%d", &option);
		//find match for the women
		if (option == 1)
		{
			findMatchForWomen(men, wList, sizePtr, iterator);
		}
		//delete the women
		if (option == 2)
		{
			//deleteWomen(men, wList, &countMen, sizePtr, iterator);
			deleteWoman(wList, iterator->data);
			break;
		}
		//logout
		if (option == 3)
		{
			return;
		}
	}
	return;
}

/************************************************************************
* function name: findMatchForMen
* The Input: member* men, womenList* wList, int* countMen, member* maleUser
* The output:if it found matches it prints the user's fullname, age, hobbies and description.
* The Function operation: the function input from the user range of required ages and check if there is
any match in the range. if there is it continues to the next step which verify if there are at least 2
appropirate hobbies between the users. if there are at least 2 hobbies it prints the matches by builded
printf function. in this proccess the function call the function matchHobbies in order to check if therer is any
hobbies match and the function printHobbies in order to print the correct hobbies (if they exist).
*************************************************************************/
int findMatchForMen(member* men, womenList* wList, int* countMen, member* maleUser)
{
	int fromAge, toAge, match = 0;
	womenItem* iterator = newIterator(wList);
	printf("Please choose ages range:\n");
	scanf("%d %d", &fromAge, &toAge);
	//iterator = wList->head->next;
	while (iterator != NULL)
	{
		//check the age range for the match
		if (iterator->data->age >= fromAge && iterator->data->age <= toAge)
		{
			//hobbies function. if match == 1 they have the same hobbies
			match = matcHobbies(maleUser, iterator);
			if (match == 1)
			{
				printf("Name:%s %s Age:%d ", iterator->data->firstName, iterator->data->lastName, iterator->data->age);
				printHobbies(*(iterator->data->hobbies));
				printf(" Description:%s\n\n", iterator->data->description);
			}
		}
		iterator = iterator->next;
	}
}
/************************************************************************
* function name: findMatchForWomen
* The Input: member* men, womenList* wList, int* sizePtr, womenItem* iterator
* The output: if it found matches it prints the user's fullname, age, hobbies and description.
* The Function operation:  the function input from the user range of required ages and check if there is
any match in the range. if there is it continues to the next step which verify if there are at least 2
appropirate hobbies between the users. if there are at least 2 hobbies it prints the matches by builded
printf function. in this proccess the function call the function matchHobbies in order to check if therer is any
hobbies match and the function printHobbies in order to print the correct hobbies (if they exist).
*************************************************************************/

int findMatchForWomen(member* men, womenList* wList, int* sizePtr, womenItem* iterator)
{
	int fromAge, toAge, i = 0, match = 0;
	printf("Please choose ages range:\n");
	scanf("%d %d", &fromAge, &toAge);
	//printf(" %d \n", *sizePtr);
	for (i = 0; i < *sizePtr; i++)
	{
		//seek for a men which is in the compatible ages range
		if (men[i].age >= fromAge && men[i].age <= toAge)
		{
			//if match == 1 they have the same hobbies
			match = matcHobbies(&men[i], iterator);
			//in a case they have the same hobbies
			if (match == 1)
			{
				printf("Name:%s %s Age:%d ", men[i].firstName, men[i].lastName, men[i].age);
				printHobbies(*(men[i].hobbies));
				printf(" Description:%s\n\n", men[i].description);
			}
		}
	}
}
/************************************************************************
* function name:  matcHobbies
* The Input: member* maleUser, womenItem* iterator
* The output: return value 0 if there is no match and 1 if there is match.
* The Function operation: the function recieves from the findMatch functions the specific members:
men - which is maleUser and women which is iterator and verify according to the bits if there is at least
2 overlapping hobbies. the run over each bit of the member by the shift operation in a loop that runs max
8 times because they are 8 hobbies as the bits numbers.
the function return the value 1 if there is at least 2 overlapping hobbies and 0 if there less than 2.
*************************************************************************/
int matcHobbies(member* maleUser, womenItem* iterator)
{
	int i = 0;
	int flag = 0;
	char menHobbie = *(maleUser->hobbies);
	char womenHobbie = *(iterator->data->hobbies);
	char temp = menHobbie & womenHobbie;
	char mask = 1;
	for (i = 0; i < 8; i++)
	{
		if ((mask&temp) == 1)
		{
			flag++;
		}
		temp = temp >> 1;
	}
	if (flag < 2)
	{
		return 0;
	}
	//if the function return the value 1 it means that they have the same hobbie
	return 1;
}

/************************************************************************
* function name: printHobbies
* The Input: char hobbie
* The output: none its void
* The Function operation:
*************************************************************************/
void printHobbies(char hobbie)
{
	int i = 0;
	char mask = 1;
	int counter = 0;
	for (i = 0; i < 8; i++)
	{
		//using a bitwise mask "and"
		if ((hobbie&mask) == 1)
		{

			hobbieCases(i + 1);
			counter++;
			if (counter < 4)
			{
				printf("%c ", ',');
			}

		}
		hobbie = hobbie >> 1;
	}

}

/************************************************************************
* function name: hobbieCases
* The Input: int temp
* The output: none its void, it just print the hobbies.
* The Function operation: it recieve an integer which have the value of the correct hobbie
according to the enum values which declared in the begining of the code.
according to the value in the this variable it prints an appropirate notice.
*************************************************************************/
void hobbieCases(int temp)
{
	switch (temp)
	{
	case BASEBALL:
		printf("Baseball");
		break;
	case BASKETBALL:
		printf("Basketball");
		break;
	case BICYCLE:
		printf("Bicycle");
		break;
	case BOOKS:
		printf("Books");
		break;
	case DRAWING:
		printf("Drawing");
		break;
	case GYM:
		printf("Gym");
		break;
	case MOVIES:
		printf("Movies");
		break;
	case POETRY:
		printf("Poetry");
		break;

	default:
		break;
	}
}

/************************************************************************
* function name:  newMember2
* The Input: int* sizePtr,int* countMen, member* maleUser, member* men,
womenList* wList, char* idNew, char* firstNameNew, char* lastNameNew,
int* ageNew, char* sexNew, char* userNameNew, char* passwordNew, char* descriptionNew, char* hobbiesNew
* The output: if the new member is a male it returns the new men array else it call a function
called push which call to another function in order to add the new women to the linked list.
* The Function operation: the calling to this function is from the main function in a case that
the user chose option no.2. the funtion allocate a new memory for a new user and input all
his details according to his input. after the user insert all his details the function check
the member's gender. if he is a male it adds him to the men array and return the new men array.
else (if she is a female) it calls to another function (push) which call to the funtion add
in order to add the new women to the linked list.
*************************************************************************/
member* newMember2(int* sizePtr, int* countMen, member* men, womenList* wList)
{
	int h1 = 0, h2 = 0, h3 = 0, h4 = 0;
	int i = 0;
	char hobb = 0, dummy = 0;
	int ageNew;
	char sexNew;
	char idNew[10], firstNameNew[15], lastNameNew[15], userNameNew[15], passwordNew[15], hob[9], descriptionNew[211];

	member newUser;
	womenItem newWoman;
	womenItem* iterator = newIterator(wList);
	printf("Please enter your ID:\n");
	scanf("%s", idNew);
	//check the id input if it's a male
	for (i = 0; i < *sizePtr; i++)
	{
		if (strcmp(men[i].id, idNew) == 0)
		{
			printf("Error: User already exists\n");
			return men;
		}
	}
	//check the id input if it's a female
	while (iterator != NULL)
	{
		if (strcmp(iterator->data->id, idNew) == 0)
		{
			printf("Error: User already exists\n");
			return men;
		}
		iterator = iterator->next;
	}
	printf("Please enter your first name:\n");
	scanf("%s", firstNameNew);
	printf("Please enter your last name:\n");
	scanf("%s", lastNameNew);
	printf("Please enter your age (18 to 100):\n");
	scanf("%d", &ageNew);
	//check the ages range
	if (ageNew < 18 || ageNew > 100)
	{
		return men;
	}
	printf("Please enter your gender (F-female, M-male):\n");
	scanf(" %c", &sexNew);
	printf("Choose a username (3-10 characters):\n");
	scanf("%s", userNameNew);
	//check the user name input
	if (!(userNameNew[0] >= 'a' && userNameNew[0] <= 'z' || userNameNew[0] >= 'A' && userNameNew[0] <= 'Z') ||
		strlen(userNameNew) < 3 || strlen(userNameNew) > 10)
	{
		return men;
	}
	printf("Choose a password (attention-minimum 6 characters):\n");
	scanf("%s", passwordNew);
	//check the password input
	if (strlen(passwordNew) < 3 || strlen(passwordNew) > 10)
	{
		return men;
	}
	printf("Some words about yourself:\n");
	scanf("%c", &dummy);
	fgets(descriptionNew, MAX_LENGTH_DESCRIPTION, stdin);
	printf("please choose 4 hobbies: Baseball = 1,Basketball = 2, Bicycle = 3, Books = 4,Drawing = 5, Gym = 6");
	printf(",Movies = 7, Poetry = 8\n");
	scanf("%d %d %d %d", &h1, &h2, &h3, &h4);
	hobb = turnOnThebits(h1, h2, h3, h4);

	//check the gender of the new member in order to add him to the appropriate list
	if (sexNew == 'M')
	{
		newUser = addNewMen(men, idNew, firstNameNew, lastNameNew, ageNew, sexNew, userNameNew, passwordNew, descriptionNew, hobb);
		//add 1 to the counter of the men
		*sizePtr = *sizePtr + 1;

		//just verify that the pointer isn't NULL
		if ((men = (member*)realloc(men, sizeof(member)*(*sizePtr + 1))) == NULL)
		{
			exit(1);
		}
		//add 1 to the counter of the men
		//*sizePtr - 1 because its an array
		men[*sizePtr - 1].id = newUser.id;
		men[*sizePtr - 1].firstName = newUser.firstName;
		men[*sizePtr - 1].lastName = newUser.lastName;
		men[*sizePtr - 1].userName = newUser.userName;
		men[*sizePtr - 1].password = newUser.password;
		men[*sizePtr - 1].hobbies = newUser.hobbies;
		men[*sizePtr - 1].description = newUser.description;
		men[*sizePtr - 1].age = newUser.age;
		men[*sizePtr - 1].sex = newUser.sex;
		mainMenuForMen(men, wList, countMen, &newUser, sizePtr);
		//return the new array of the mens
		return men;
	}

	else
	{
		newWoman.data = newMember1(wList, idNew, firstNameNew, lastNameNew, ageNew, sexNew, userNameNew, passwordNew, descriptionNew, hobb);
		//call the function push in order to add a new women to the linked-list
		push(wList, newWoman.data);
		bubbleSort(wList);
		mainMenuForWomen(men, wList, countMen, sizePtr, &newWoman.data);
		return men;
	}
}

//creating a new womenlist
womenList* newWomenList()
{
	womenList* w1 = (womenList*)malloc(sizeof(womenList));
	w1->head = (womenItem*)malloc(sizeof(womenItem));
	w1->head->data = NULL;
	w1->head->next = NULL;
	w1->last = w1->head;
	//return the new list which called w1
	return w1;
}

//Adding a new women to the end of the List
void add(womenList* wList, member* newWomen)
{
	womenItem* item = (womenItem*)malloc(sizeof(womenItem*));
	item->data = newWomen;
	item->next = NULL;
	wList->last->next = item;
	wList->last = item;
}

//Adding a women to the beginning of the List
void push(womenList* wList, member* newWomen)
{
	if (wList->last == wList->head)
	{
		add(wList, newWomen);
	}
	else
	{
		womenItem* item = (womenItem*)malloc(sizeof(womenItem));
		item->data = newWomen;
		item->next = wList->head->next;
		wList->head->next = item;
	}
}

womenItem* newIterator(womenList* wList)
{
	return wList->head->next;
}

void printWomenList(womenList* wList)
{
	womenItem* iterator = newIterator(wList);
	while (iterator != NULL)
	{
		printMember(iterator->data);
		iterator = iterator->next;
	}
	printf("\n");
}

/************************************************************************
* function name: printMember
* The Input: a struct of a member (male or female)
* The output: none its void. it just prints the member details.
* The Function operation: recieve the male or female member and prints his details.
*************************************************************************/
void printMember(member* pm)
{
	printf("%s %s %s %d %s %s %s %s %s", pm->id, pm->firstName, pm->lastName, pm->age, pm->sex, pm->userName, pm->password, pm->description, pm->hobbies);
}

/************************************************************************
* function name: freeMember
* The Input: a struct of a member (women member).
* The output: none it's a void function.
* The Function operation: the function recieve a struct of a member and free the memory.
* of this member (means it deletes the member).
*************************************************************************/


/************************************************************************
* function name: nameComparator
* The Input: two structs of two members
* The output: int which is equal to zero, bigger or smmaller.
* The Function operation: the function recieve 2 structs of 2 members and use the function
strcmp in order to notice if they have the same last names.
this function is used during the proccess of sorting the women's last names
in the linked-list according the ABC's serial.
*************************************************************************/
int nameComparator(member* a, member* b)
{
	return strcmp(a->lastName, b->lastName);
}

/************************************************************************
* function name:  bubbleSort
* The Input: the linked-list of the women - wList
* The output: none its a void function.
* The Function operation: the function recieves the linked list and sorts the womens
accordinig to the ABC's serial of their last names.
this function calls other function in order to complete the sorting (nameComparator and switchWomenItems).
*************************************************************************/
void bubbleSort(womenList* wList)
{
	womenItem* i;
	bool switched = true;
	while (switched == true)
	{
		switched = false;
		i = newIterator(wList);
		//the following loop runs while the next women exists
		while (i->next != NULL)
		{
			//using the function nameCompartor
			//if the last names of both women is not the same 
			//if the ASCI value of the first women is bigger than the next women, we should switch them.
			if (nameComparator(i->data, i->next->data) > 0)
			{
				switched = true;
				//calling the function switchWommenItems
				switchWomenItems(i, i->next);
			}
			//same as i++ (to the next women in the womenlist)
			i = i->next;
		}
	}
}
/************************************************************************
* function name: switchWomenItems
* The Input: two structs of two women from the linked-list.
* The output: none its a void function.
* The Function operation: the function switches by pointers (not by value) the data of two
women from the women list. this function is used during the proccess of sorting the women's last names
in the linked-list according the ABC's serial.
*************************************************************************/
void switchWomenItems(womenItem* a, womenItem* b)
{
	member* temp = a->data;
	a->data = b->data;
	b->data = temp;
}

/************************************************************************
* function name: deleteWomen
* The Input: womenList* wList (the linked list), womenItem* theRequiredUser(a women member which we want to
* delete).
* The output: none its a void function.
* The Function operation:
*************************************************************************/
/*void deleteWomen(member* men, womenList* wList, int* countMen, int* sizePtr, womenItem* theRequiredUser)
{
	womenItem* iterator = newIterator(wList);
	womenItem* back = wList->head;
	while (iterator != NULL && strcmp(iterator->data->id, theRequiredUser->data->id) != 0)
	{
		back = iterator;
		iterator = iterator->next;
	}
	if (strcmp(iterator->data->id, theRequiredUser->data->id) == 0)
	{
		back->next = iterator->next;
		iterator->next = NULL;
		freeWomenItem(iterator);
		if (iterator == wList->last)
		{
			wList->last = back;
		}
		//back->next = iterator->next;
		//freeMember(iterator->data);
		//free(iterator);
		//iterator->next = NULL;
		//freeWomenItem(iterator);
	}

}*/


/************************************************************************
* function name: turnOnThebits
* The Input: int h1, int h2, int h3, int h4 - each one contain the 4th hobbies of a member
* The output: the char called bits - the char consist of 1 byte which 4 of his 8 bits are open
in the appropirate place (according to the hobbie).
* The Function operation: it takes 1 byte of a char(bits1, bits2, bits3, bits4) and shifts the bit
inside it to the left according the selected hobbie (h1, h2, h3, h4).
*************************************************************************/
char turnOnThebits(int h1, int h2, int h3, int h4)
{
	char bits1 = 1, bits2 = 1, bits3 = 1, bits4 = 1;
	char bits = 0;

	bits1 = bits1 << (h1 - 1);
	bits2 = bits2 << (h2 - 1);
	bits3 = bits3 << (h3 - 1);
	bits4 = bits4 << (h4 - 1);
	bits = bits1 ^ bits2^bits3^bits4;
	return bits;
}


void outPutText(womenList* wList, member* men, int* sizePtr)
{
	int i = 0;
	FILE* f;
	f = fopen("output.txt", "w+");
	womenItem* iterator = newIterator(wList);
	for (i = 0; i < *sizePtr; i++)
	{
		fprintf(f, "%s", men[i].id);
		fprintf(f, ";");
		fprintf(f, "%s", men[i].firstName);
		fprintf(f, ";");
		fprintf(f, "%s", men[i].lastName);
		fprintf(f, ";");
		fprintf(f, "%d", men[i].age);
		fprintf(f, ";");
		fprintf(f, "%c", men[i].sex);
		fprintf(f, ";");
		fprintf(f, "%s", men[i].userName);
		fprintf(f, ";");
		fprintf(f, "%s", men[i].password);
		fprintf(f, ";");
		fprintf(f, "%s", men[i].hobbies);
		fprintf(f, ";");
		fprintf(f, "%s", men[i].description);
		fprintf(f, "\n");
	}
	bubbleSort(wList);
	while (iterator != NULL)
	{
		fprintf(f, "%s", iterator->data->id);
		fprintf(f, ";");
		fprintf(f, "%s", iterator->data->userName);
		fprintf(f, ";");
		fprintf(f, "%s", iterator->data->lastName);
		fprintf(f, ";");
		fprintf(f, "%d", iterator->data->age);
		fprintf(f, ";");
		fprintf(f, "%c", iterator->data->sex);
		fprintf(f, ";");
		fprintf(f, "%s", iterator->data->userName);
		fprintf(f, ";");
		fprintf(f, "%s", iterator->data->password);
		fprintf(f, ";");
		fprintf(f, "%s", iterator->data->hobbies);
		fprintf(f, ";");
		fprintf(f, "%s", iterator->data->description);
		fprintf(f, "\n");
		iterator = iterator->next;
	}
	fclose(f);
}

member addNewMen(member* men, char* idNew, char* firstNameNew, char* lastNameNew, int ageNew, char sexNew, char* userNameNew, char* passwordNew, char* descriptionNew, char hobb)
{
	member newMen;
	//newMen.id = idNew;
	newMen.id = (char*)malloc((strlen(idNew) + 1) * sizeof(char));
	strcpy(newMen.id, idNew);
	newMen.firstName = (char*)malloc((strlen(firstNameNew) + 1) * sizeof(char));
	//verify if the allocation exists
	if (newMen.firstName == NULL)
	{
		printf("Allocation is failed\n");
		exit(1);
	}
	strcpy(newMen.firstName, firstNameNew);
	newMen.lastName = (char*)malloc(strlen(lastNameNew) + 1);
	//verify if the allocation exists
	if (newMen.lastName == NULL)
	{
		printf("Allocation is failed\n");
		exit(1);
	}
	strcpy(newMen.lastName, lastNameNew);
	newMen.age = ageNew;
	newMen.userName = (char*)malloc(strlen(userNameNew) + 1);
	//verify if the allocation exists
	if (newMen.userName == NULL)
	{
		printf("Allocation is failed\n");
		exit(1);
	}
	strcpy(newMen.userName, userNameNew);
	newMen.password = (char*)malloc(strlen(passwordNew) + 1);
	//verify if the allocation exists
	if (newMen.password == NULL)
	{
		printf("Allocation is failed\n");
		exit(1);
	}
	strcpy(newMen.password, passwordNew);
	newMen.description = (char*)malloc(strlen(descriptionNew) + 1);
	//verify if the allocation exists
	if (newMen.description == NULL)
	{
		printf("Allocation is failed\n");
		exit(1);
	}
	strcpy(newMen.description, descriptionNew);
	//hobbies
	newMen.hobbies = (char*)malloc(sizeof(char));
	*(newMen.hobbies) = hobb;
	//verify if the allocation exists
	if (newMen.hobbies == NULL)
	{
		printf("Allocation is failed\n");
		exit(1);
	}
	//return the new men member to the dinamic array of mens
	return newMen;
}

/*void freeLinkedList(womenList* wList)
{
	while (wList != NULL)
	{
		womenList *nextUser = wList->head->next;
		//calling freeWomenItem function
		freeWomenItem(wList->head);
		wList = nextUser;
	}
}*/

void freeWomenList(womenList* wList)
{
	freeWomenItemLast(wList->head);
	free(wList);
}

/*void freeWomenItem(womenItem* item)
{
	if (item != NULL)
	{
		if (item->data != NULL)
		{
			printf("freeing %s\n", item->data->firstName); //for debug
		}
		freeMember(item->data);
		free(item->data);
		//recursion calling
		//freeWomenItem(item->next);
		free(item);
	}
}*/

void freeWomenItemLast(womenItem* item)
{
	if (item != NULL)
	{
		freeMember(item->data);
		free(item->data);
		freeWomenItemLast(item->next);
		free(item);
	}
}

member* freeDynamicMen(member* men, int* sizePtr)
{
	int i = 0;
	if (men != NULL)
	{
		//the loop run over each male in the dynamic men array and free his field
		for (i = 0; i < *sizePtr; i++)
		{
			free(men[i].id);
			free(men[i].firstName);
			free(men[i].lastName);
			free(men[i].userName);
			free(men[i].password);
			free(men[i].description);
			free(men[i].hobbies);
		}

	}
	return men;

}

/************************************************************************
* function name: freeMember
* The Input: a struct of a member (women member).
* The output: none it's a void function.
* The Function operation: the function recieve a struct of a member and free the memory.
* of this member (means it deletes the member).
*************************************************************************/

void freeMember(member* member)
{
	if (member != NULL)
	{
		free(member->id);
		free(member->firstName);
		free(member->lastName);
		free(member->userName);
		free(member->password);
		free(member->description);
		free(member->hobbies);
	}

}

void deleteWoman(womenList* wList, member* woman)
{
	womenItem* iterator = wList->head->next;
	womenItem* previous = wList->head;
	while (iterator != NULL && nameComparator(iterator->data, woman) != 0) {
		previous = iterator;
		iterator = iterator->next;
	}

	// We either found the woman or we got to the end of the list
	if (nameComparator(iterator->data, woman) == 0) {
		previous->next = iterator->next;
		iterator->next = NULL;
		freeWomanItem(iterator);
		// If this is the first woman
		if (iterator == wList->head)
		{
			wList->head = wList->head->next;
		}
		// If this is the last woman
		else if (iterator == wList->last)
		{
			wList->last = previous;
		}
		//free(iterator->data);
		free(iterator);
	}
}

void freeWomanItem(womenItem* iterator)
{
	free(iterator->data->firstName);
	free(iterator->data->lastName);
	free(iterator->data->userName);
	free(iterator->data->password);
	free(iterator->data->hobbies);
	free(iterator->data->description);
}

/*member* freeDynamicMen(member* men, int* sizePtr)
{
	int i = 0;
	for (i = 0; i < *sizePtr; i++)
	{
		freeMember(men[i]);
	}
	return men;
}*/