typedef struct
{
	int m,d,y;
} Date;
void CreateDate(Date * const Dptr)//Constructor Equivalent
{
	Dptr->m = Dptr->d = Dptr->y = -1;	
}
int datecmp(const Date d1,const Date d2)//Returns 1 if d1 is after or same as d2 else returns false
{			
	if(d2.y > d1.y || (d2.y == d1.y && d2.m > d1.m) || (d2.y == d1.y && d2.m == d1.m && d2.d > d1.d))
		return 0;
	return 1;

}
void getDate(const char * const str,Date * const Dptr,const Date Current_Date)//Verifies and accepts a date
{ 
	
	int date,month,year;
	Date tmp;
	do
	{
		printf("\n\n Enter the %s date[dd/mm/yyyy]: ",str);
		scanf("%d/%d/%d",&date,&month,&year);
		getchar();
 		tmp.m = month;
 		tmp.y = year;
 		tmp.d = date;
 		if( date<1||date>31||month>12||month<1 ||
		 	( (month==4||month==6||month==7||month==9||month==11) && date>30 ) ||
		 	( (year%4!=0) && (month==2) && date>28 ) ||
		 	( (year%4==0) && (month==2) && date>29 )  ||
		 	datecmp(tmp,Current_Date) == 0)
 			printf("\n\n Invalid Date!Please enter again!\n\n");

 	}while(   date<1||date>31||month>12||month<1 ||
		 	( (month==4||month==6||month==7||month==9||month==11) && date>30 ) ||
		 	( (year%4!=0) && (month==2) && date>28 ) ||
		 	( (year%4==0) && (month==2) && date>29 )  ||
		 	datecmp(tmp,Current_Date) == 0 );
 	Dptr -> d = date;
 	Dptr -> m = month;
 	Dptr -> y = year;
 }

Date getCurrentDate()//get current date 
{			
	Date tmp;
	time_t t=time(0);
	struct tm * now = localtime(&t);
	tmp.m = now -> tm_mon + 1;
	tmp.y = now -> tm_year + 1900;
	tmp.d = now -> tm_mday; 
	return tmp;
}
void putDate(const char * const str , const Date date)//Prints out the date on screen
{ 			
	printf("%s : %d/%d/%d\n" , str , date.d , date.m , date.y);
}
int countLeapYears(Date d) 
{ 
    int years = d.y; 
    if (d.m <= 2) 
        years--; 
    return years / 4 - years / 100 + years / 400; 
} 
int date_diff(const Date d1,const Date d2)
{
	const int monthDays[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};
	long int n1 = d1.y*365 + d1.d; 
    for (int i=0; i<d1.m - 1; i++) // Add days for months passed 
        n1 += monthDays[i]; 
    n1 += countLeapYears(d1); // Add a day for every leap year 
    long int n2 = d2.y*365 + d2.d; 
    for (int i=0; i<d2.m - 1; i++) //Add days for months passed
        n2 += monthDays[i]; 
    n2 += countLeapYears(d2); //Add a day for every leap year
  	return (n1 - n2); 
}