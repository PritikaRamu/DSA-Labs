int search (int arr[], int n)
{
int i;
int min = arr[0];
for (i=1;i<n;i++)
{
if (arr[i] < min)
min = arr[i];
}
	printf ("Inside function, min = %d",min);
	return min;
}
