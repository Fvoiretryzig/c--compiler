struct {                                                                
    int a1,c1;
    float b1[2][3];
}test[1][2];

struct hello{
   int a2,c2;
   float b2[2][3];
};
int f(int aa, float bb)
{
	int x = 1;
	return x;
}
int main(int a3, int b4[1][4]) 
{
    struct hello a;
	int tmp;
	tmp = f(a.a2, test[0][1].b1);
    return tmp;
}
