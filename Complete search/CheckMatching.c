#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_STACK 100
#define FALSE 0
#define TRUE 1


// 1. 왼쪽 괄호의 개수와 오른쪽 괄호의 개수가 같다.
// 2. 같은 타입의 괄호에서 왼쪽 괄호는 오른쪽 괄호보다 먼저 나와야 한다.
// 3. 서로 다른 타입의 왼쪽 괄호와 오른쪽 괄호 쌍은 서로를 교차하면 안된다.

typedef int element;
typedef struct {
    element stack[MAX_SIZE_STACK];
    int top;
} StackType;

void init(StackType *s){
    s->top = -1;
}

int is_empty(StackType *s){
    return s->top == -1;
}

int is_full(StackType *s){
    return s->top == MAX_SIZE_STACK-1;
}

void push(StackType *s, element item){
    if (is_full(s))
        exit(1);
    s->stack[++(s->top)] = item;
}

element pop(StackType *s){
    if (is_empty(s))
        exit(1);
    return s->stack[(s->top)--];
}

element peek(StackType *s){
    if (is_empty(s))
        exit(1);
    return s->stack[s->top];
}

int check_matching(char *in){
    StackType s;
    char ch; // character from in
    char open_ch; // character from stack
    int i;
    int n = (int) strlen(in);
    init(&s);
    
    for (i=0; i<n; i++) {
        ch = in[i];
        switch (ch) {
            case '(': case '{' : case '[':
                push(&s, ch);
                break;
            case ')': case '}' : case ']':
                if (is_empty(&s)) // condition 1, 3
                    return FALSE;
                open_ch = pop(&s); // condition 2, 3
                if ((open_ch == '(' && ch != ')') ||
                    (open_ch == '{' && ch != '}') ||
                    (open_ch == '[' && ch != ']')) {
                    return FALSE;
                }
                break;
        }
    }
    if (!is_empty(&s)) // condition 1
        return FALSE;
    return TRUE;
}

int main(){
    if (check_matching("{A[(i+1)]=0;}")==TRUE) {
        printf("Success\n");
    } else {
        printf("Fail\n");
    }
    return 0;
}
