
int MyPrintf (char* msg, ...);

int main()
{
		char s1[] = "Binary";
		char s2[] = "Octal";
		char s3[] = "Decimal";
		char s4[] = "Hexadecimal";

		int a = 0;
		
		for (a = 0; a < 3803 ; a++)
			MyPrintf ("%s %b %s %o %s %d  %s %x \n", s1, a, s2, a, s3, a, s4, a);

		MyPrintf("Amount %%: %%d\n", MyPrintf("%s %s %s %s %%! and %c %s %x %d %%\n", s1, s2, s3, s4, 'I', "LOVE", 3802, 100));	

		return 0;
}
