typedef int List;
// La 表示 A 集合，Lb 表示 B 集合。
void unionL(List *La, List Lb)
{
	int La_len, Lb_len, i;
	typedef int ElemType;

	ElemType e;
	La_len = ListLength(*La);
	Lb_len = ListLength(Lb);

	for (i = 1; i <= Lb_len; i++)
	{
		GetElem(Lb, i, &e);
		if (!LocateElem(*La, e))
		{
			ListInsert(La, ++La_len, e);
		}
	}
}