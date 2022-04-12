struct stack {
      void* nodo;
      struct stack* next;
     };
typedef struct stack STACK;

STACK* push(STACK* st,void*T);
STACK* pop(STACK *st);
void* top(STACK *st);
