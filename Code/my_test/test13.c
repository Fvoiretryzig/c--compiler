struct ccc{
	int dd;
};

struct {
	float b1[2][4];
	struct ccc bbb;
}test[1][2];

float f()
{
	float a = test[1][2].b1[2][4];
	return a;
}
int main()
{
	test[1][2].bbb.abcd = f();
	return 0;
}