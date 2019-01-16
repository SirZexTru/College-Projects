int cpfValidator(char personDocument[])
{

    #define bool int
    #define true = 1
    #define false = 0

    int cpfResult;
    unsigned long soma;
    int j = 10, a, b;
	
	for (int i = 0; i < 9; i++)
    {
		soma += j * (personDocument[i] - 48);
		j--;
	}
	
	if ((soma * 10) % 11 == 10)
        a = 0;
    else
        a = (soma * 10) % 11;
		
	soma = 0;
	
	j = 11;
	for (int i = 0; i < 10; i++)
	{
		soma += j * (personDocument[i] - 48);
		j--;
	}
		
	if ((soma * 10) % 11 == 10)
        b = 0;
    else
        b = (soma * 10) % 11;
		
	if ((a == (personDocument[9] - 48)) && (b == (personDocument[10] - 48)))
        cpfResult = 1;
	else
        cpfResult = 0;
    return cpfResult;
    
}