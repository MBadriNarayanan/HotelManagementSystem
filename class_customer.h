#define RATE 3000.0
typedef struct
{
	char 	name[30];
	char 	ph[11];
	Room 	r;
} Customer;
void CreateCustomer(Customer * const Cptr)//Constructor Equivalent
{	
	(*Cptr).name[0] = '\0';
	(*Cptr).ph[0] = '\0';
	CreateRoom( &(Cptr->r) );
}
void CheckIn()
{

	Customer *Cptr = (Customer*)malloc(sizeof(Customer));
	CreateCustomer(Cptr);
	Cptr -> r = Book_Room();
	if( (Cptr->r).rno == 0)
	{
		printf("\n\n No rooms available!!\n\n");
		return;
	}
	FILE* fp = fopen("customer_history.dat","rb");
	fseek(fp,0,2);
	const int last_id = ftell(fp)/sizeof(Customer);
	Cptr->r.cust_id = last_id + 1;
	fclose(fp);
	printf("\n\n Enter your name: ");
	scanf("%[^\n]*c",Cptr->name);
	getchar();
	do
	{
		printf("\n\n Enter contact number: ");
		scanf("%s",Cptr->ph);
		getchar();
		if(strlen(Cptr->ph) != 10)
		{
			printf("\n\n Invalid Contact Number!Try again!\n\n");
		}
	}while(strlen(Cptr->ph) != 10);
	fp = fopen("Rooms.dat","rb+");
	fseek(fp,((Cptr->r).rno - 1)*sizeof(Room),0);
	fwrite(&(Cptr->r),1,sizeof(Room),fp);
	fclose(fp);
	fp = fopen("customer_history.dat","ab");
	fwrite(Cptr,1,sizeof(Customer),fp);
	fclose(fp);
	free(Cptr);
	printf("\n\n Successfully booked room!\n\n");
}
void putCustomer(const Customer C)
{
	printf("\n\n Name           : %s\n\n",C.name);
	printf(" Phone Number   : %s\n\n",C.ph);
	printf(" Rooom Number   : %d\n\n",C.r.rno);
	putDate(" Check In date ",C.r.Check_In);
	putDate(" Check Out date",C.r.Check_Out);
	printf("\n\n");
}
float CheckOut()
{

	const Date CurrentDate = getCurrentDate();
	FILE * fp = fopen("Rooms.dat","rb+");
	Room *tmp = (Room*)malloc(sizeof(Room));
	Customer *temp = (Customer*)malloc(sizeof(Customer));
	int rno,opt;

	do
	{
		do
		{
			printf(" Enter the room number to vacate: ");
			scanf("%d",&rno);
			getchar();

			if(rno < 1 || rno > MAX_ROOMS)
			{

				printf(" Invalid Input!Try again!\n\n");
			}

		}while(rno<1||rno>MAX_ROOMS);
		fseek(fp,(rno-1)*sizeof(Room),0);
		fread(tmp,1,sizeof(Room),fp);
		if(!tmp -> isOccupied)
		{
			printf("\n\n Invalid Room Number!Try again!\n\n");
		}
	}while(!tmp -> isOccupied && !feof(fp));
	const int cust_id = tmp -> cust_id;
	do
	{
		printf("\n\n Are you sure you want to check out 1/0?: ");
		scanf("%d",&opt);
		getchar();
		if(!(opt == 1 || opt == 0))
		{
			printf("\n\n Invalid Input!Try again\n\n");
		}
	}while(!(opt==1||opt==0));
	if (opt == 0)
	{
		return -1;
	}
	CreateRoom(tmp);
	tmp->rno = rno;
	fseek(fp,(rno - 1)*sizeof(Room),0);
	fwrite(tmp,1,sizeof(Room),fp);
	free(tmp);
	fclose(fp);
	fp = fopen("customer_history.dat","rb+");
	fseek(fp,(cust_id-1)*sizeof(Customer),0);
	fread(temp,1,sizeof(Customer),fp);
	int date_diff1 = date_diff((temp->r).Check_Out,(temp->r).Check_In);
	int date_diff2 = date_diff(CurrentDate,(temp->r).Check_In);
	if(date_diff2 < date_diff1)
	{
		temp->r.Check_Out = CurrentDate;
		fseek(fp,-sizeof(Customer),1);
		fwrite(temp,1,sizeof(Customer),fp);
	}
	fclose(fp);
	putCustomer(*temp);
	int date_diff = (date_diff1>date_diff2)? date_diff2 : date_diff1;
	date_diff++;
	free(temp);
	printf("\n\n Successfully Checked out!\n\n");
	return date_diff * RATE;
}
void Room_History()
{
	int rno;
	do
	{
		printf("\n\n Enter a room number : ");
		scanf("%d",&rno);
		getchar();
		if(rno<1||rno>MAX_ROOMS)
		{
			printf("\n\n Invalid Input!Try again!\n\n");
		}
	}while(rno<1||rno>100);
	FILE *fp = fopen("customer_history.dat","rb");
	Customer *tmp = (Customer*)malloc(sizeof(Customer));
	fread(tmp,1,sizeof(Customer),fp);
	while(!feof(fp))
	{
		if((tmp->r).rno == rno)
			putCustomer( (*tmp) );
		fread(tmp,1,sizeof(Customer),fp);
	}
	fclose(fp);
	free(tmp);
}
void Date_History()
{
	Date tmp,d;
	CreateDate(&tmp);
	CreateDate(&d);
	getDate("required",&d,tmp);

	FILE * fp = fopen("customer_history.dat","rb");
	Customer *c = (Customer*)malloc(sizeof(Customer));
	
	fread(c,1,sizeof(Customer),fp);
	while(!feof(fp)){
		if( (date_diff(c->r.Check_In,d) <= 0) && (date_diff(c->r.Check_Out,d) >= 0) )
			putCustomer(*c);
		fread(c,1,sizeof(Customer),fp);
	}
	fclose(fp);
	free(c);
}