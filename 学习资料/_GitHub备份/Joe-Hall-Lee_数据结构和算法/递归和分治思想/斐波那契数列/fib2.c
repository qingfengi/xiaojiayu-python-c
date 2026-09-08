int Fib(int i)
{
	if (i < 2)
		return i == 0 ? 0 : 1;
	return Fib(i - 1) + (i - 2);
}