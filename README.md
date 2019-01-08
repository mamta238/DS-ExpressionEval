# Expression Evaluator

The code evaluates mathematical expressions.The code supports **integers** as well as **float** values (both postive and negative) along with operators-`+,-,*,/,%`

## Language:
- C language	
	
## Concepts and Data Structures in Use:
[Deterministic Finite Automaton](https://en.wikipedia.org/wiki/Deterministic_finite_automaton)
[Stack Data Structure](https://www.geeksforgeeks.org/stack-data-structure/)
[Linked List](https://www.geeksforgeeks.org/data-structures/linked-list/)
[Structure and Union in C](https://www.codingunit.com/c-tutorial-structures-unions-typedef) 
[Types of Expression Notation](http://interactivepython.org/runestone/static/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html)
	 

## Steps Of Execution
>1. >**Enter** the expression. `eg:23.0--3*(5%2)`
>2. >The entered expression is in the form of string,the **validity of expression** is evaluated by reading it character by character and if the string is accepted by [**dfa**](https://github.com/mamta238/DS-ExpressionEval/blob/master/dfa.jpg) then the expression is **valid** else **invalid**.
If **Valid** goto `Step3` else goto `Step6`.
>3. >Once the expression is valid it is evaluated to **check for balanced parantheses** using **[Stack](https://www.codingalpha.com/balanced-parantheses-using-stack-c-program/) Data Structure**.
If **Valid** goto `Step4` else goto `Step6`.
>4. >The expression is in the **infix form**. For further processing it is converted to **postfix form** by using **[Stack](http://condor.depaul.edu/ichu/csc415/notes/notes9/Infix.htm) Data Structure** and the postfix expression is stored in a **Linked List**.
>5. >The **postfix expression**(represented in Linked List) is then evaluated to shrink the list into a **single node** after complete evaluation of the expression.This single node then contains the result of expression. 
>6. >Stop.

