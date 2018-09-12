#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include "stackstruct.c"
#include "stackheader.h"
#include "stackfunc.c"
#include <stdlib.h>



#define ERROR 1001
#define VALID 1000
#define INPUT stdin
#define OUTPUT stdout
#define INVALID {\
					fprintf(OUTPUT,"\nInvalid expression");\
					return 0;\
				}	
				
typedef union value
{
 float num1;
 int num2;
 char ope;
}val;


typedef struct expr
{
 val *ele;
 int type;
 struct expr *prev,*next;
}expr;

				
				
int checkpara(char **,stack **);
int getPriority(char);
int infixToPostfix(char *,stack *(*),expr *(*),expr *(*));
void eval(expr *(*));
float powf(float,float);
void convert(expr *(*),expr *(*),expr *(*),int);
void display(expr *(*));

int checkpara(char *(*exp),stack **top)
{
 int i,res;
 for(i=0;(*exp)[i]!='\0';i++)
 {
  if((*exp)[i]=='(')
     {
      res=push(top,'(');
      if(res==0)
       break;
     } 
  else if((*exp)[i]==')')
  	 {
  	  res=pop(top);
  	  if(res==0)
  	     break;
  	 }    
 }
 if(res==0)
    return 0;
 else
 {   
  if(*top==NULL)
   return 1;
  else
   return 0;
 }    
}


int getPriority(char op)
{
  if(op=='$' || op=='^')
     return 3;
  else if(op=='%' || op=='/' || op=='*')
	 return 2;
  else if(op=='+' || op=='-')
     return 1;
  else
	 return 0;   	    
}

void convert(expr *(*head),expr *(*tail),expr *(*new),int type)
{
  
  if(NULL!=(*new=(expr*)malloc(sizeof(expr))))
     	{
            if(NULL!=((*new)->ele=(val*)malloc(sizeof(val))))
            {
                   
                   (*new)->type=type;
                   (*new)->next=(*new)->prev=NULL;
                   if(*head==NULL)
                    *head=*tail=*new;
                   else
                   {   
                    (*tail)->next=(*new);
                    (*new)->prev=*tail;
                    (*tail)=(*new);
                  }
  			}}
}

int infixToPostfix(char *exp,stack *(*top),expr *(*head),expr *(*tail))
{
  int i,j,x,y,flag=0,k=0;
  char *num,p;
  expr *new;
  num=(char*)malloc(sizeof(char)*15);
  for(i=0;exp[i]!='\0';i++)
  {
     if(exp[i]=='(')
     {
          push(top,'(');
     }
     else if(exp[i]==')')
     {
  	     while((*top)->data!='(') 
         {
                convert(head,tail,&new,3);
                new->ele->ope=(char)pop(top); 
         } 
         pop(top);
     }    
     else if(exp[i]=='$' || exp[i]=='^' || exp[i]=='*' || exp[i]=='/' || exp[i]=='%' || exp[i]=='+' || exp[i]=='-')
     {  
         if(exp[i]=='+' || exp[i]=='-')
     	 {  
     	   if(!((exp[i-1]>=48 && exp[i-1]<=57) || exp[i-1]=='.' || exp[i-1]==')'))
     	   {
     	     num[k++]=exp[i];
     	     continue;
     	   }
     	 } 
     	     
      	 p=(char)peek(top);
      	 x=getPriority(p);
      	 y=getPriority(exp[i]);
      	 while(x>=y)
      	 {
      		convert(head,tail,&new,3);
            new->ele->ope=(char)pop(top);
        	p=(char)peek(top);
        	x=getPriority(p);
      	 }
         push(top,exp[i]);
         
    }         
    else 
    {   flag=0;
    	for(j=i;;j++)
     	{
       		if(exp[j]=='.')
          	{ 
          	  flag=1;
          	  num[k++]=exp[j];
          	}
          	else if(exp[j]>=48 && exp[j]<=57)
          	{
           	  num[k++]=exp[j];
           	}
       		else
          	{
           	  break;
          	}       
     	}
     	 i=j-1;
         convert(head,tail,&new,1);
         if(flag==1)
          new->ele->num1=(float)atof(num);
     	 else
     	  { new->ele->num2=atoi(num); new->type=2;}
         free(num);
         num=(char*)malloc(sizeof(char)*15);
         k=0;
     	
    }
  }
 
  while(*top!=NULL)
  {
   convert(head,tail,&new,3);
   new->ele->ope=(char)pop(top); 
  }
  free(num);
  return flag;
}


void eval(expr *(*head))
{
  
  expr *temp1,*temp2,*temp3,*temp,*new;
  int n1,n2;
  float no1,no2,no3;
  for(temp=*head;temp!=NULL;)
  {
    if(temp->type==3)
    { 
      temp3=temp; temp2=temp->prev; temp1=temp2->prev;
      
      if(temp2->type==1)
         no2=temp2->ele->num1;
      else if(temp2->type==2)
         no2=temp2->ele->num2;
      
      if(temp1->type==1)
         no1=temp1->ele->num1;  
      else if(temp1->type==2)
         no1=temp1->ele->num2;
         
               
      switch(temp->ele->ope)
      {
       case '$':
       case '^':no3=powf(no1,no2);
       			break;
       case '/':no3=no1 / no2;
       			break;
       case '%':n1=(int)no1; n2=(int)no2;
       			no3=(n1 % n2);
       			break;
	   case '*':no3=no1 * no2;
       			break;
	   case '+':no3=no1 + no2;
       			break;
	   case '-':no3=no1 - no2;
       			break;
		
	  }
	  
	  new=(expr*)malloc(sizeof(expr));     	
      new->ele=(val*)malloc(sizeof(val));
      
	  if(temp1->type==1 || temp2->type==1)
	      { new->ele->num1=no3; new->type=1; }
	  else
	      { new->ele->num2=(int)no3; new->type=2; }
	  if(temp1==*head)
	     *head=new;
	         
	  new->prev=temp1->prev;
	  	          	  
	  if(temp->next!=NULL)
	  {
	   temp->next->prev=new;  
	  }
	  new->next=temp->next;
	  temp=temp->next;
	  free(temp1);free(temp2);free(temp3);
    } 
    else
       temp=temp->next;
  }
}

void display(expr *(*head))
{
    expr *temp; 
    for(temp=*head;temp!=NULL;temp=temp->next)
    {
   	 if(temp->type==1)
      fprintf(OUTPUT,"\t%f",temp->ele->num1);
     if(temp->type==2)
      fprintf(OUTPUT,"\t%d",temp->ele->num2); 
   	 if(temp->type==3)
      fprintf(OUTPUT,"\t%c",temp->ele->ope);	      
    }
}   


int main(void)
{
 char *exp;
 stack *top=NULL;
 int i,value,ch,result;
 expr *head=NULL,*tail=NULL;
 
 exp=(char*)malloc(sizeof(char)*255);
 
 fprintf(OUTPUT,"\nEnter expression:");
 fscanf(INPUT,"%s",exp);
 fprintf(OUTPUT,"\nExp:%s",exp);
 
 i=1;
  ch=exp[0];
  if (ch>=48 && ch<=57)
     value=1;
  else if(ch=='.')
     value=2;
  else if(ch=='(')
     value=3;
  else if(ch=='+' || ch=='-')
  	 value=6;   
  else 
     value=ERROR;
 do
 {
   ch=exp[i];
   i++;
   if(ch!='\0')
   {
    switch(value)
    {
     case 1:if(ch>=48 && ch<=57)
     			value=1;
     		else if(ch=='$' || ch=='^' || ch=='/' || ch=='*' || ch=='%' || ch=='+' || ch=='-')
     			value=4;
     		else if(ch=='.')
     			value=2;
     		else if(ch==')')
     			value=5;	
     		else value=ERROR;
     		    break;
     case 2:if(ch>=48 && ch<=57)
     			value=2;
     		else if(ch=='$' || ch=='^' || ch=='/' || ch=='*' || ch=='%' || ch=='+' || ch=='-')
     			value=4;	
     		else if(ch==')')
     			value=5;		
     		else value=ERROR;
     			break;	
     case 3:if(ch>=48 && ch<=57)
     			value=1;
     		else if(ch=='.')
     			value=2;
     		else if(ch=='(')
     			value=3;
     		else if(ch=='+' || ch=='-')
     			value=6;			
     		else value=ERROR;
     		 	break;	
     case 4:if(ch>=48 && ch<=57)
     			value=1;
     		else if(ch=='.')
     			value=2;
     		else if(ch=='(')
     			value=3;
     		else if(ch=='+' || ch=='-')
     			value=6;		
     		else value=ERROR;
     			break;	
     case 5:if(ch=='$' || ch=='^' || ch=='/' || ch=='*' || ch=='%' || ch=='+' || ch=='-')
     			value=4;
     		else if(ch==')')
     			value=5;	
     		else value=ERROR;
     		    break;	
     case 6:if(ch>=48 && ch<=57)
     			value=1;
     		else if(ch=='.')
     			value=2;
		    else value=ERROR;
     		    break;	 		    
     								
     		    		 	
    }
   }
    else
   {
    if(value==4) 
    value=ERROR;
    else
    value=VALID;
     break;
   }
   
   if(value==ERROR)
      break;
 }while(1); 
 
 if(value==ERROR || value==4)
      {INVALID;}
 else {
 		result=checkpara(&exp,&top);
 		if(result==1)
 		{
 		  top=NULL;
   		  result=infixToPostfix(exp,&top,&head,&tail);
   		  /*display(&head);*/
   		  eval(&head);
   		  printf("\n");
   		  /*display(&head);*/
   		  if(head->type==1)
   		     fprintf(OUTPUT,"\nResult:%f\n",head->ele->num1);
   		  else
   		     fprintf(OUTPUT,"\nResult:%d\n",head->ele->num2);    
   		}  
 		else   
 		  fprintf(OUTPUT,"\nPara Not Balanced");
 	  }  
return 0;
}
