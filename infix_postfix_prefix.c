#include<stdio.h>
#include<ctype.h>
#include<string.h>
char stack[25];
char stack1[25][25];
char t[25];
int top=-1;
int top1=-1;
void intopost(char infix[25]);
void post_pre(char E[25]);
void pre_post(char F[25]);
int main()
{
char infix[25];
printf("Enter the infix expression: ");
scanf("%s",infix);
intopost(infix);
char E[25];
printf("Enter the postfix expression: ");
scanf("%s",E);
post_pre(E);
char F[25];
printf("Enter the prefix expression: ");
scanf("%s",F);
pre_post(F);
return 0;
}
void push(char c)
{
top++;
stack[top]=c;

}
char pop()
{
char t;
t=stack[top];
top--;
return t;
}
void push1(char s[25])
{
top1 ++;
strcpy(stack1[top1],s);
}
char* pop1()
{

strcpy(t,stack1[top1]);
top1 --;
return(t);
}
int ISP(char c)
{
if(c=='+'||c=='-')
return(1);
if(c=='*'||c=='/')
return(2);
if(c=='^')
return(3);
if(c=='(')
return(0);
else
return(-1);
}
int ICP(char c)
{
if(c=='+'||c=='-')
return(1);
if(c=='*'||c=='/')
return(2);
if(c=='^')
return(4);
if(c=='(')
return(5);
else
return(-1);
}
void intopost(char infix[25])
{
char postexp[25];
int k=0,i=0;
char tkn;
tkn=infix[i];
while(tkn!='\0')
{
if(isalpha(tkn)!=0)
{
postexp[k]=infix[i];
k++;
}
else
{
if(tkn=='(')
{
push('(');
}
else
{
if(tkn==')')
{
while((tkn=pop()) !='(')
{
postexp[k]=tkn;
k++;
};
}
else
{
while(top!=-1 && ISP(stack[top])>=ICP(tkn))
{
postexp[k]=pop();
k++;
}
push(tkn);
}
}
}
i++;
tkn=infix[i];
}
while(top!=-1)
{
postexp[k]=pop();
k++;
}
postexp[k]='\0';
printf("\n Postfix exp=%s\n",postexp);
}
void post_pre(char E[25])
{
char str1[25],op1[25],op2[25],pre[25];
char str2[25];
//int l;
//l=strlen(E);
int i;
for(i=0;E[i] !='\0';i++)
{
char x=E[i];
if(isalpha(x)!=0)
{
str1[0]='\0';
str1[0]=x;
str1[1]='\0';
//printf("\n%s",str1);
push1(str1);
}
else
{
strcpy(op2,pop1());
printf("\nop2=%s",op2);
strcpy(op1,pop1());
printf("\nop1=%s",op1);
str2[0]='\0';
str2[0]=x;
str2[1]='\0';
strcat(str2,op1);
strcat(str2,op2);
//printf("\n%s",str2);
push1(str2);
}
}
strcpy(pre,pop1());
printf("\nprefix exp=%s\n",pre);
}
void pre_post(char F[25])
{
char str1[25],op1[25],op2[25],p[25];
char str2[25];
int l=strlen(F);
int i;
for(i=l-1;i>=0;i++)
{
char x=F[i];
if(isalpha(x)!=0)
{
str1[0]='\0';
str1[0]=x;
str1[1]='\0';
//printf("\n%s",str1);
push1(str1);
}
else
{
strcpy(op2,pop1());
printf("\nop2=%s",op2);
strcpy(op1,pop1());
printf("\nop1=%s",op1);
str2[0]='\0';
str2[0]=x;
str2[1]='\0';
strcat(op1,op2);
strcat(op1,str2);
//printf("\n%s",str2);
push1(op1);
}
}
strcpy(p,pop1());
printf("\npostfix exp=%s\n",p);
}