struct a {
	int aa[2][3];
	float b;
};
struct c{
	int u[2][3][4];
	float v;
};
int tmp_a[10][6];
int tmp_b[3][5];
int main()
{
	struct a aaa;
	struct c ccc;
	tmp_a = tmp_b;
	tmp_a[1][0] = tmp_b[0][1];
	aaa = ccc;
	return 0;
}
