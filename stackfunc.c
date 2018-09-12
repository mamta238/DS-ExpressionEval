




int push(stack **top,int n)
{
 stack *new;
 if(!(NULL==(new=(stack*)malloc(sizeof(stack)))))
 {
  new->data=n;
  new->next=*top;
  *top=new;
  return (*top)->data;
 }
 else
  return 0;  
}


int pop(stack **top)
{
  stack *temp;
  int n;
  if(*top==NULL)
   return 0;
  else
   {
    temp=*top;
    n=temp->data;
    *top=(*top)->next;
    free(temp);
    return n;
   } 
}

int peek(stack **top)
{
  if(*top==NULL)
     return 0;
  else
     return (*top)->data;    
}	

int isEmpty(stack **top)
{
 if(*top==NULL)
	return 1;
 else
 	return 0;   
}
