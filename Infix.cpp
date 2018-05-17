/*
    Gabriella Uwadiegwu
    5/17/2017
    
    Main() performs infix operation.
*/
#include <iostream>
#include <stack>
#include <map>
#include <string>
using namespace std;

stack<int>operands;//stack for integer operands
stack<char>operators;//stack for char operands
map<char,int>op_preference;//dictionary to know preference
                           //this works by using an integer to represent a character

//method declarations. I prefer to see the main method first :)
void process();
void process_p();

int main()
{

    //This is to know the integers associated with the operators
    op_preference['/']=1;
    op_preference['*']=2;
    op_preference['+']=3;
    op_preference['-']=3;
    op_preference['(']=4;

    string exp; //expression
    cout<<"Enter an expression, e.g 3*4(5+6-7)/8:\n";
    getline(cin,exp);//gets expression
    char last_val=':';//needed to know the start of the expression

    int i=0;
    int checkDig=0;//check digit to check if a value is double digit or more
    int neg=0;//neg to check if a value is negative
    for(i=0; i<exp.size(); i++){

        if (exp[i]==' ')
            continue;//continues if a space(basically goes back to loop). so space as much as you want.

            /**
            Overall, in this if statement, it checks if the value is a digit and using checkDig
            I would know if there is a recurring digit is the in the value. so when checkDig = 0;
            that means its a single digit and if it is 1, when the code goes on to loop, it see the
            value as "whole" value
            **/
        if (isdigit(exp[i])){//if the character is a digit

            if (checkDig==0){
                int temp = (int)exp[i]-'0';//so values are read in characters and we would then have cast
                                                //to int. e.g'0' is 48 in ASCII and 3 is 51 so casting 3 to int
                                                //would be (int)51-48 or else we would just be passing 51.
                if (neg==1){

                    temp=temp* -1;//so neg is 1 means the value is negative
                    operators.pop();//pop the value
                }
                neg=0;
                operands.push(temp);//push the negative value which is now temp
                checkDig=1;
            }

            else {
                    /**
                    So, this pushes a value with more than one digit into the operand stack
                    so let say I have 25 what happens is (2*10)+ 5, and this gets pushed to the stack
                    **/
                    int temp = operands.top()*10 + ((int)exp[i]-'0');//also the casting from ASCII to int
                    operands.pop();
                    operands.push(temp); //the double digit or more value being pushed into the stack
            }
        }

        else {

            checkDig=0; //checkDig now becomes 0 since the next character read is an operator
            neg=0; //neg now 0 if it was 1 (being reset)

            //pushes operators with those conditions
            if (operators.size()==0 || exp[i]=='('){
                operators.push(exp[i]);
            }
            //we then want to evaluate whatever is in a bracket.
            else if (exp[i]==')') {
                process_p();//calls the process_p() method that calls the process method to evaluate the
                            //values
            }

            /**Else statement: we want to push our operators based on their preference.
            so + is 3 and * is 2. So if + is already in the stack and since 3 that represents it and it is
            is greater than 2 that represent * we push *. This is so that when we process, Multiplication
            occurs first.**/
            else {

                if (op_preference[exp[i]]<op_preference[operators.top()]) {
                    operators.push(exp[i]);
                }
                /**
                else statement: here if we have * in already and + is then read, we process the
                multiplication then push the +
                **/
                else {
                    process();
                    operators.push(exp[i]);
                }
            }

            //for a negative number, two cases are considered. e.g -4*(1+2) or 3+(-1*2)
            if (exp[i]=='-') {
                if (last_val=='(' || last_val==':')//hence ':' to indicate the beginning of the expression
                      neg=1;                       //and for the case its in a bracket.
            }
        }
            last_val=exp[i];//when we loop again, if the if statement directly above weighs last_val
                            //as either of those conditions, we evaluate as the value as negative.
    }

    //it now then goes on to evaluate the finely/well organized stack.
    while(!operators.empty()){
        process();
    }

    cout<<"Infix evaluation: "<<operands.top()<<"\n";

return 0;
}

/**This method assigns the operand at the top position to a variable, then pops it. It then does the same
again for the second value, and then for whatever value in the operator stack.
after wards it then checks what operator the character (operator variable) holds and evaluates the
value variables(val1 and val2) based on whatever the operator is.**/
void process()
{
        int val1=0; int val2=0; char op; int flag=0;

        if (!operands.empty())
        {
                val1=operands.top();
                operands.pop();
        }
        if (!operands.empty())
        {
                val2=operands.top();
                operands.pop();
        }
        if (!operators.empty())
        {
                op=operators.top();
                operators.pop();
        }

        //checks for Operators, evaluate operands and then pushes them to operand stack
        if (op=='+')
        {
                operands.push(val2+val1);
        }
        else if (op=='-')
        {
                operands.push(val2-val1);
        }
        else if (op=='*')
        {
                operands.push(val2*val1);
        }
        else if (op=='/')
        {
                operands.push(val2/val1);
        }
}

//Method that calls the process method to evaluate
void process_p()
{
    while (operators.top()!='('){
        process();
    }

    operators.pop();
}

