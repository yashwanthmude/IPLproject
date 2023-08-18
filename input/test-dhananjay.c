int main()
{
    int *a, *b;
    float c;
    int d;
    d = -c;
    a = 0;           /* No error */
    /* a = 1; */     /* Gives error, Error at line 8: Incompatible assignment when assigning to type "int*" from type "int"*/
    /* a = a < b; */ /* Gives error now */
    /* c = !a; */
    /* c = -a; */ /*Gives error*/
}
struct s
{
    int* x;
};

struct s f(int a)
{
    struct s b;
    int arr[10];

}
int  h(int* a)
{
  

}

void g ()
{
    struct s a;
    int* b;
    int c;
    /* f(1)=a; */ 
    /* f(1).x=b; */
    *(f(1).x)=c;
    h(0);

}

