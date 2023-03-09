#include<stdio.h>
#include<stdbool.h>
int mat[100];
int C[100],R[100];
bool Gol(int row,int col);
bool Safe ();
bool bkt();
void afisare();

int lin,col;

int main()
{
freopen("sudoku.in", "r", stdin);
freopen("sudoku.out", "w", stdout);
 int i,j;
 for(i=1;i<=9;i++)
    for(j=1;j<=9;j++)
       {
        scanf("%d", &mat[i*10+j]);
        R[i*10+mat[i*10+j]]=1;
        C[j*10+mat[i*10+j]]=1;
       }
 bkt();
 afisare();
return 0;
}
int n, inceputi,inceputj,row,col,finali,finalj;

bool  Safe()
{
	__asm
	(

//"pushl %ebp;"
"movl %esp, %ebp;"
"movl 8(%ebp), %eax  ;"
"movl 12(%ebp), %edx ;"
"movl 16(%ebp), %ecx ;"
"movl %eax, row;"
"pushl %ebx;"
"pushl %esi;"

"pushl %edx;"
"movl $10, %ebx;"
"mull %ebx;"
"popl %edx;"
"addl %ecx, %eax;"

"movl $R, %esi;"
"movl (%esi,%eax,4), %ebx   ;"

"cmp $0, %ebx;"
"jne ret0;"

"pushl %edx;"
"movl %edx, %eax;"
"movl $10, %ebx;"
"mull %ebx;"
"popl %edx;"
"addl %ecx, %eax;"

"movl $C, %esi;"
"movl (%esi,%eax,4), %ebx    ;"

"cmp $0, %ebx;"
"jne ret0;"

"movl %ecx, n;"
"movl %edx, col;"

"xorl %ecx,%ecx;"

"movl row, %eax;"
"subl $1, %eax;"
"movl $3, %ebx;"
"xorl %edx, %edx;"
"divl %ebx;"
"mull %ebx;"
"incl %eax  ;"
"movl %eax, inceputi;"
"addl $2,%eax;"
"movl %eax, finali;"

"movl col, %eax;"
"subl $1, %eax;"
"movl $3, %ebx;"
"xorl %edx, %edx;"
"divl %ebx;"
"mull %ebx;"
"incl %eax  ;"
"movl %eax, inceputj;"
"addl $2,%eax;"
"movl %eax, finalj;"


"movl inceputi, %ecx;"
"subl $1, %ecx;"
"for_i:;"
"  movl inceputj, %ebx;"
"  subl $1,%ebx;"

"  incl %ecx;"
"  movl finali,%edx;"
"  cmp %edx, %ecx;"
"  jg ret1;"

"  for_j:;"
"     incl %ebx;"
"     movl finalj,%edx;"
"     cmp %edx, %ebx;"
"     jg for_i;"

"     movl %ecx,%eax;"
"     movl $10, %edx;"
"     mull %edx;"
"     addl %ebx, %eax;"
"     movl $mat, %esi;"
"     movl (%esi,%eax,4), %edx;"
"     movl n,%eax;"
"     cmp %edx,%eax;"
"     je ret0;"

"     jmp for_j;"

"ret1:;"
"movl $1, %eax;"
"popl %esi;"
"popl %ebx;"
"popl %ebp;"
"ret;"

"ret0:;"
"movl $0, %eax;"
"popl %esi;"
"popl %ebx;"
"popl %ebp;"
"ret;"

	);
	
}

bool bkt()
{

__asm
	(

	//"movl %esp, %ebp;"

	"pushl %ebx;"
	"pushl %edi;"
	"pushl %esi;"
	
	"xorl %eax, %eax;"
	"xorl %edx, %edx;"
	"incl %eax;"
	"incl %edx;"
	"movl $mat, %esi;"         //vom parcurge matricea cu eax si edx

	"fori:;"
		"cmp $10,%eax;"		//caut un element 0
		"je nu_am_gasit;"

		"forj:;"
			"pushl %eax;"
			"movl $10, %ebx;"
			"pushl %edx;"
			"mull %ebx;"
			"popl %edx;"
			"addl %edx, %eax;"
			"movl %eax, %ecx;"   //in ecx am pozitia elementului curent
			"popl %eax;"
			"movl (%esi, %ecx,4), %ebx;"
			"cmp $0, %ebx;"
			"je am_gasit;"

			"incl %edx;"
			"cmp $10,%edx;"
			"je foric;"

			"jmp forj;"

			"foric:;"
			"incl %eax;"
			"xorl %edx,%edx;"
			"incl %edx;"
			"jmp fori;"

	"nu_am_gasit:;"
		"movl $1, %eax;"
		"popl %esi;"
		"popl %edi;"
		"popl %ebx;"

		"popl %ebp;"    //nu inteleg dc trebuie 
		"ret;"

	"am_gasit:;"
		"movl %eax, lin;"
		"movl %edx, col;"

		"xorl %ecx,%ecx;"
		
		"for_numar:;"
			"incl %ecx;"
			"cmp $10, %ecx;"     //daca ajung la 10 inseamna ca nu am gasit nimic potrivit si trebuie sa ma intorc
			"jl cont;"
						"nu:;"
						"movl $0, %eax;"
						"popl %esi;"
						"popl %edi;"
						"popl %ebx;"

						"popl %ebp;"
						"ret;"
			
			"cont:;"
			"pushl %ecx;"
			"pushl col;"
			"pushl lin;"
			"call Safe;"
			"popl %ebx;"
			"popl %ebx;"
			"popl %ecx;"

			"cmp $0, %eax;"
			"je for_numar;"

			"se_potriveste:;"
			"movl lin, %eax;"
			"movl col, %edx;"
			"movl $10, %ebx;"
			"pushl %edx;"
			"mull %ebx;"
			"popl %edx;"
			"addl %edx, %eax;"
			"verif:;"
			"movl $mat, %esi;"
			"movl %ecx, (%esi, %eax, 4)  ;"

			"subl %edx,%eax;"
			"addl %ecx,%eax;"

			"movl $R, %esi;"
			"movl $1, (%esi, %eax, 4)  ;"
			
			"movl col, %eax;"
			"movl %ecx, %edx;"
			"movl $10, %ebx;"
			"pushl %edx;"
			"mull %ebx;"
			"popl %edx;"
			"addl %edx, %eax;"
			
			
			"movl $C, %esi;"
			"movl $1, (%esi, %eax, 4) ;"
			
			"pushl %ecx;"
			"pushl lin;"
			"pushl col;"
			"call bkt;"
			"popl %ebx;"
			"movl %ebx, col;"
			"popl %ebx;"
			"movl %ebx, lin;"
			"popl %ecx;"
			
			"v:;"
			"cmp $1, %eax;"
			"je return1;"

			"movl lin, %eax;"
			"movl col, %edx;"
			"movl $10, %ebx;"
			"pushl %edx;"
			"mull %ebx;"
			"popl %edx;"
			"addl %edx, %eax;"

			"movl $mat, %esi;"
			"movl $0, (%esi, %eax, 4) ;"

			"subl %edx,%eax;"
			"addl %ecx,%eax;"

			"movl $R, %esi;"
			"movl $0, (%esi, %eax, 4)  ;"
			
			"movl col, %eax;"
			"movl %ecx, %edx;"
			"movl $10, %ebx;"
			"pushl %edx;"
			"mull %ebx;"
			"popl %edx;"
			"addl %edx, %eax;"
			
			"movl $C, %esi;"
			"movl $0, (%esi, %eax, 4) ;"
			
			"movl lin, %eax;"
			"movl col, %edx;"
			
			"jmp for_numar;"


		"return1:;"
		"movl $1, %eax;"
		"popl %esi;"
		"popl %edi;"
		"popl %ebx;"

		"popl %ebp;"
		"ret;"

	);
}

void afisare()
{
 int i,j;
 for (i=1;i<=9;i++)
    {for (j=1;j<=9;j++)
        printf("%d ", mat[i*10+j]);
     printf("\n");
    }
 printf("\n");	
}

