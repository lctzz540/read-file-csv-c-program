#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXCHAR 1000
#define MAXPROJECT 1000
#define MAXPROGRESS 1000
#define MAXEMPLOYEE 1000




typedef struct {
	char* EmployeeID;
	char* FirstName;
	char* LastName;
	char* Gender;
	char* DateOfBirth;
	char* Department;
	char* Country;
}Employee;

Employee EPS[1000];

int read_employee(char* filename){
	
	char buffer[MAXCHAR]; 
    char token[MAXCHAR];
    
    Employee *EP;
	int EP_size = 0;
	FILE* file = fopen(filename, "r");
	int ii = 0;
	while (fgets(buffer, MAXCHAR, file) != NULL){
		if(ii == 0){
			ii++;
			continue;
		}
	    EP = (Employee*)malloc(sizeof(Employee));
	    EP->EmployeeID = strdup(strtok(buffer, ","));
	    EP->FirstName = strdup(strtok(NULL, ","));
	    EP->LastName = strdup(strtok(NULL, ","));
	    EP->Gender = strdup(strtok(NULL, ","));
	    EP->DateOfBirth = strdup(strtok(NULL, ","));
	    EP->Department = strdup(strtok(NULL, ","));
	    EP->Country = strdup(strtok(NULL, ","));
	    EPS[EP_size++] = *EP;
	}
	fclose(file);
	return EP_size;
}




int main(int argc, char *argv[]) {
	
	int EP_size, index;
    char* filename = "Employee.csv";

    EP_size = read_employee(filename);
	
    if(EP_size)
    {
        printf("EP size: %d\n", EP_size);

        //for(index = 0; index < EP_size; index++)
            printf("%s, %s - %s - %s - %s - %s - %s \n", EPS[index].EmployeeID, EPS[index].FirstName, EPS[index].LastName, 
			//EPS[index].Gender, EPS[index].DateOfBirth, EPS[index].Department, EPS[index].Country);
    }
    
	return 0;
}


