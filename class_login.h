struct login
{
	char username[10];
	char pass[25];
	int verified;
};

void getCheckOut()
{
	
	FILE * fp = fopen("Rooms.dat","rb"),
		 * f  = fopen("customer_history.dat","rb");
	Room * tmp = (Room*)malloc(sizeof(Room));
	Customer * temp = (Customer*)malloc(sizeof(Customer));
	fread(tmp,1,sizeof(Room),fp);
	while(!feof(fp) )
	{
		if(tmp->isOccupied && date_diff(tmp->Check_Out,getCurrentDate()) == 0)
		{
			fseek(f,(tmp->cust_id - 1)*sizeof(Customer),0);
			fread(temp,1,sizeof(Customer),f);
			putCustomer(*temp);
			printf("\n");
		}
		fread(tmp,1,sizeof(Room),fp);
	}
	fclose(fp);
	fclose(f);
	free(tmp);
	free(temp);
}