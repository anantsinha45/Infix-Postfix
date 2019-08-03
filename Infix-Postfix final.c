#include <stdio.h>
#include <stdlib.h>

typedef struct STACK{
    int top;
    unsigned capacity;
    int * array;
}Stack;

Stack* create_stack(unsigned cap){
    Stack* stack=(Stack*)malloc(sizeof(Stack));
    stack->top=-1;
    stack->capacity=cap;
    stack->array=(int*)malloc(stack->capacity*sizeof(int));
    
    if(!stack->array)
        return NULL;
    return stack;
}

int isEmpty(Stack* stack){
    return (stack->top==-1);
}

void push(Stack* stack,char ch){
    stack->array[++stack->top]=ch;
}
char pop(Stack* stack){
    if(!isEmpty(stack))
        return(stack->array[stack->top--]);
    return '$';
}
    
int ifOperand(int a){
    if(a=='+'||a=='-'||a=='*'||a=='/'||a=='%'||a=='('||a==')'||a=='^')
        return 0;
    return 1;
}

int ifOperand2(int a){
    if(a=='+'||a=='-'||a=='*'||a=='/'||a=='%'||a=='^')
        return 0;
    return 1;
}

char peak(Stack* stack){
    return stack->array[stack->top];
}

int prec(char c){
    switch(c){
        case '+':
        case '-':
            return 1;
        case '*':
            return 2;
        case '%':
        case '/':
            return 3;
        case '^':
            return 4;
    }
    return -1;
}
void convert(char* exp,int n){
    Stack* stack=create_stack(n);
    int i=0,k=0;
    int ans[1000000];
    for(i=0;i<n;i++){
        if(ifOperand(exp[i]))
            ans[k++]=exp[i];
            
        else if(exp[i]=='('){
            push(stack,exp[i]);
            
        }
        else if(exp[i]==')'){
            while(!isEmpty(stack)&&peak(stack)!='('){
                ans[k++]=pop(stack);
                ans[k++]=' ';
            }
            pop(stack);
        }
            
        else if(exp[i]=='+'||exp[i]=='-'){
            while(!isEmpty(stack)&&peak(stack)!='('){
                ans[k++]=pop(stack);
                ans[k++]=' ';
            }
            push(stack,exp[i]);
        }
        
        else if(exp[i]=='*'){
            while(!isEmpty(stack)&&peak(stack)!='('&&peak(stack)!='+'&&peak(stack)!='-'){
                ans[k++]=pop(stack);
                ans[k++]=' ';
            }
            push(stack,exp[i]);
        }
        
        else if(exp[i]=='/'||exp[i]=='%'){
            while(!isEmpty(stack)&&peak(stack)!='('&&peak(stack)!='+'&&peak(stack)!='-'&&peak(stack)!='*'){
                ans[k++]=pop(stack);
                ans[k++]=' ';
            }
            push(stack,exp[i]);
        }
        else if(exp[i]=='^')
            push(stack,exp[i]);
     }
     //printf("%d",k);
    while(!isEmpty(stack)){
        ans[k++]=' ';
        ans[k++]=pop(stack);
        
    }
    ans[k]='\0';
    int flag=0;
    for(int i=0;i<k;i++){
        if(i==0&&ans[i]==' ')
            continue;
        else if(ans[i]==' '){
            flag++;
            if(flag<2){
                printf("%c",ans[i]);
            }
        }
        else{
          flag=0;
          printf("%c",ans[i]); 
        }
    
    }
    //printf("%c",ans[1]);
    //printf("%s",exp);
    printf("\n");
    //printf("%s %d",exp,k);
    
    
}

int neighbourhood(char* a,int i){
    if(a[i-1]=='('||a[i-1]==')'||a[i+1]=='('||a[i+1]==')')
        return 1;
    return 0;
}
int validity(char* exp,int n){
    int flag=0;
    for(int i=0;i<n;i++){
        
        if(exp[i]=='('){
            flag++;
            if(i!=0){
                if(ifOperand2(exp[i-2])||(!ifOperand2(exp[i+2]))||exp[i-2]==')'||exp[i+2]==')')
                    return 0;
            }
            else if(i==0){
                if(!ifOperand2(exp[i+2])||exp[i+2]==')')
                    return 0;
            }
        }
        else if(exp[i]==')'){
            flag--;
            if(i!=n-1){
                if(!(ifOperand2(exp[i-2]))||(ifOperand2(exp[i+2]))||exp[i+2]=='('||exp[i-2]=='(')
                    return 0;
            }
            else if(i==n-1){
                if(!(ifOperand2(exp[i-2]))||exp[i-2]=='(')
                    return 0;
            }
        }
        else if(exp[i]==' '&&!neighbourhood(exp,i)){
            if(!(ifOperand2(exp[i-1])^ifOperand2(exp[i+1])))
                return 0;
        }
        else if(i==0||i==n-1){
            if(!ifOperand2(exp[i]))
                return 0;
        }
        else if(flag<0)
            return 0;
    }
    if(flag!=0)
        return 0;
    return 1;
}
int main() {
	int t;
	scanf("%d\n",&t);
	while(t--){
	   
	    char exp[10000];
	    char el;
	    int count=0;
	    el=getchar();
	    while(el!= EOF&&el!='\n'){
	        exp[count]=el;
	        count++;
	        el=getchar();
	    }
	    
        if(validity(exp,count)){
            convert(exp,count);
        }
        else{
            printf("INVALID\n");
        }
        //printf("%d %c",neighbourhood(exp,3),exp[4]);
 	}
	    
	    
	
	return 0;
}