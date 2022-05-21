#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

Employee EPS[MAXEMPLOYEE];

typedef struct {
  char* EmployeeID;
  char* ProjectID;
  char* Progress;
}Progress;

Progress PGS[MAXPROGRESS];

typedef struct {
  char* ProjectID;
  char* ProjectName;
  char* Week;
}Project;

Project PJS[MAXPROJECT];

int read_project(char* filename){

	char buffer[MAXCHAR];
  char token[MAXCHAR];

  Project *PJ;
	int PJ_size = 0;
	FILE* file = fopen(filename, "r");
	int ii = 0;
	while (fgets(buffer, MAXCHAR, file) != NULL){
		if(ii == 0){
			ii++;
			continue;
		}
	    PJ = (Project*)malloc(sizeof(Project));
	    PJ->ProjectID = strdup(strtok(buffer, ","));
	    PJ->ProjectName = strdup(strtok(NULL, ","));
	    PJ->Week = strdup(strtok(NULL, "\n"));
	    PJS[PJ_size++] = *PJ;
	}
	fclose(file);
	return PJ_size;
}
int read_progress(char* filename){

	char buffer[MAXCHAR];
  char token[MAXCHAR];

  Progress *PG;
	int PG_size = 0;
	FILE* file = fopen(filename, "r");
	int ii = 0;
	while (fgets(buffer, MAXCHAR, file) != NULL){
		if(ii == 0){
			ii++;
			continue;
		}
	    PG = (Progress*)malloc(sizeof(Progress));
	    PG->EmployeeID = strdup(strtok(buffer, ","));
	    PG->ProjectID = strdup(strtok(NULL, ","));
	    PG->Progress = strdup(strtok(NULL, "\n"));
	    PGS[PG_size++] = *PG;
	}
	fclose(file);
	return PG_size;
}
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
	    EP->Country = strdup(strtok(NULL, "\n"));
	    EPS[EP_size++] = *EP;
	}
	fclose(file);
	return EP_size;
}
void menu(){
  char command[20];
  char para[20];
  scanf("%s %s", command, para);
  if (strcmp(command,"count") == 0) {
    count_department(para);
    return 0;
  }
  else if (strcmp(command, "list")==0) {
    if (strcmp(para, "male")==0) {
      list_male();
      return 0;
    };
    if (strcmp(para, "female")==0) {
      list_female();
      return 0;
    };
  }
  else if (strcmp(command, "report") == 0) {
    report(para);
     return 0;
  }
  else if (strcmp(command, "average") == 0) {
    average(para);
     return 0;
  };
  if (strcmp(command, "sort") == 0) {
    sort(para);
     return 0;
  };
  if (strcmp(command, "country") == 0) {
    country(para);
  };
}
void count_department(char department[20]){

  int EP_size = read_employee("./Employee.csv");
  FILE* result = fopen("result.txt", "w");
  int count = 0;
  for (int j = 0; j < EP_size; j++) {
    if (strcmp(EPS[j].Department, department) == 0) {
      count++;
      };
  };
  fprintf(result, "%d",count);
  fclose(result);
}
void list_male(){
  int EP_size = read_employee("./Employee.csv");
  FILE* result = fopen("result.txt","w");
  for (int j = 0; j < EP_size; j++) {
    if (strcmp(EPS[j].Gender, "Male") == 0) {
      fprintf(result, "%s - %s - %s - %s - %s\n",EPS[j].EmployeeID, EPS[j].FirstName, EPS[j].LastName, EPS[j].Gender, EPS[j].DateOfBirth, EPS[j].Department, EPS[j].Country);
      };
  };
  fclose(result);
}
void list_female(){
  int EP_size = read_employee("./Employee.csv");
  FILE* result = fopen("result.txt","w");
  for (int j = 0; j < EP_size; j++) {
    if (strcmp(EPS[j].Gender, "Female") == 0) {
      fprintf(result, "%s - %s - %s - %s - %s - %s - %s\n",EPS[j].EmployeeID, EPS[j].FirstName, EPS[j].LastName, EPS[j].Gender, EPS[j].DateOfBirth, EPS[j].Department, EPS[j].Country);
      };
  };
  fclose(result);
}
void report(char progress[10]){
  int PG_size = read_progress("./Progress.csv");
  FILE* result = fopen("result.txt","w");
  if (atof(progress) <= 1 && atof(progress) >= 0) {
  for (int j = 0; j < PG_size; j++) {
    if (strcmp(PGS[j].Progress, progress)) {
      fprintf(result, "%s\n",PGS[j].EmployeeID);
      };
  };
  fclose(result);
  };
}
void average(char pgopj[20]){
  int PG_size = read_progress("./Progress.csv");
  FILE* result = fopen("result.txt", "w");
  int count = 0;
  float sumpg = 0;
  for (int j = 0; j < PG_size; j++) {
    if (strcmp(PGS[j].ProjectID, pgopj) == 0) {
      sumpg += atof(PGS[j].Progress);
      count++;
      };
  };
  float average = sumpg/count;
  fprintf(result, "%f",average);
  fclose(result);
}
void sort(char select[10]){
  int EP_size = read_employee("./Employee.csv");
  FILE* result = fopen("result.txt", "w");
  if (strcmp(select, "desc")==0){
    int i,j;
    for ( i = 0; i < EP_size; i++){
      for ( j = i+1; j < EP_size; j++){
        if (strcmp(EPS[i].LastName, EPS[j].LastName) < 0){
          Employee temp = EPS[i];
          EPS[i] = EPS [j];
          EPS[j] = temp;
        };
        if (strcmp(EPS[i].LastName, EPS[j].LastName) == 0 && EPS[i].FirstName, EPS[j].FirstName < 0){
          Employee temp = EPS[i];
          EPS[i] = EPS [j];
          EPS[j] = temp;
        };
      };
    };
  }
  if (strcmp(select, "asc")==0){
    for (int i = 0; i < EP_size; i++){
      for (int j = i+1; j < EP_size; j++){
        if (strcmp(EPS[i].LastName, EPS[j].LastName)> 0){
          Employee temp = EPS[i];
          EPS[i] = EPS [j];
          EPS[j] = temp;
        }
      }
    }
  };
  for (int j = 0; j < EP_size; j++) {
    fprintf(result, "%s - %s - %s - %s - %s - %s - %s\n",EPS[j].EmployeeID, EPS[j].FirstName, EPS[j].LastName, EPS[j].Gender, EPS[j].DateOfBirth, EPS[j].Department, EPS[j].Country);
  };
   fclose(result);
}
void country(char ct[20]){
  int EP_size = read_employee("./Employee.csv");
  FILE* result = fopen("result.txt", "w");
  for (int j = 0; j < EP_size; j++) {
    if (strcmp(EPS[j].Country, ct) == 0) {
      fprintf(result, "%s - %s - %s - %s - %s - %s - %s\n",EPS[j].EmployeeID, EPS[j].FirstName, EPS[j].LastName, EPS[j].Gender, EPS[j].DateOfBirth, EPS[j].Department, EPS[j].Country);
    };
  };
  fclose(result);
}
int main (int argc, char *argv[])
{
  menu();
  return 0;
}
