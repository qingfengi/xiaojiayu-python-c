
void print()
{
	char a;
	scanf_s("%c", &a);
	if (a != '#')
		print();
	if (a != '#')
		printf("%c", a);
	else
		return;
}