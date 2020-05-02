#define MAX_ROOMS 100
typedef struct
{
	int rno;
	Date Check_In , Check_Out;
	unsigned isOccupied : 1;
	unsigned int cust_id;
} Room;
void CreateRoom(Room * Rptr)
{
	Rptr->rno = 0;
	CreateDate(&(Rptr->Check_In) );
	CreateDate(&(Rptr->Check_Out) );
	Rptr->isOccupied = 0;
}
void DisplayAvailableRooms(int * arr)
{

	if(arr == 0)
	{
		printf("\n\n No rooms available!\n\n");
		return;
	}
	printf("\n\n The available rooms are : \n\n");
	for(int i = 0 ; i < 100 && arr[i] ; i++){
		printf("%-3d ",arr[i]);
		if( (i+1)%10 == 0)
			printf("\n");
	}
}
int* const getRoomNo()
{
	
	static int arr[MAX_ROOMS];
	for(int i = 0 ; i < MAX_ROOMS ; i++)
		arr[i] = 0;
	FILE * fp = fopen("Rooms.dat","rb");
	int c = -1;
	for(int i = 0 ; i<MAX_ROOMS && !feof(fp) ; i++)
	{
		Room tmp;
		fread(&tmp,1,sizeof(Room),fp);
		if( !tmp.isOccupied)
			arr[++c] = tmp.rno;
	}
	fclose(fp);
	if(c != 0) //Some rooms available
		return arr;
return 0;
}
Room Book_Room()
{
	Room tmp;
	CreateRoom(&tmp);
	const Date Current_Date = getCurrentDate();
	int rno , found = 0;
	int * available_rno = getRoomNo();
	if(available_rno == 0)
		return tmp;
	DisplayAvailableRooms(available_rno);
	printf("\n");
	do
	{
		printf("\n\n Enter a Room No from the above list : ");
		scanf("%d",&rno);
		getchar();
		for(int i = 0 ; i < 100 && available_rno[i]; i++)
			if(rno == available_rno[i])
			{
				found = 1;
				break;
			}
		if(!found)
			printf("\n\n Enter another Room Rumber!\n\n");

	}while(!found);		
	tmp.rno = rno;
	tmp.isOccupied = 1;
	do
	{
		getDate("Check In" , &(tmp.Check_In)  , Current_Date);
		getDate("Check Out", &(tmp.Check_Out) , Current_Date);
		if(date_diff( (tmp.Check_In),(tmp.Check_Out) ) ==1 ||
		   date_diff( (tmp.Check_In),Current_Date ) ==0)
			printf("\n\n Invalid Check In Check Out Dates!Try again!\n\n");
	}while(date_diff( (tmp.Check_In),(tmp.Check_Out) ) ==1 ||
		   date_diff( (tmp.Check_In),Current_Date ) ==0);
	return tmp;
}