int factorial(n)
{
	if (0 == n)
		return 1;
	else
		return n * factorial(n - 1);
}