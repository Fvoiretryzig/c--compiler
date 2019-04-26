struct {
	int a1,c1;
	float b1[2][3];
}test[1][2];

struct hello{
   int a2,c2;
   float b2[2][3];
};
int main(int a3, int b4[1][4]) 
{
	struct hello a;
	a.b2[1][0] = 3.3;
	test[0][1].b1[1][2] = a.b2[1][0];
    return a.b2[1][0];
}

