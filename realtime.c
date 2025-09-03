#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **data;
    int top;
    int cap;
} Stack;


void stack_init(Stack *s, int cap) {
    s->data = (char**)malloc(sizeof(char*) * cap);
    s->top = -1;
    s->cap = cap;
}

int stack_empty(Stack *s) { return s->top < 0; }

int stack_full(Stack *s)  { return s->top + 1 >= s->cap; }

void stack_grow(Stack *s) {
    int ncap = s->cap * 2;
    char **ndata = (char**)realloc(s->data, sizeof(char*) * ncap);
    if (!ndata) { fprintf(stderr, "realloc failed\n"); exit(1); }
    s->data = ndata;
    s->cap = ncap;
}

static char *my_strdup(const char *src) {
    size_t n = strlen(src) + 1;
    char *p = (char*)malloc(n);
    if (!p) { fprintf(stderr, "malloc failed\n"); exit(1); }
    memcpy(p, src, n);
    return p;
}

void stack_push(Stack *s, const char *str) {
    if (stack_full(s)) stack_grow(s);
    s->data[++s->top] = my_strdup(str);
}

char* stack_pop(Stack *s) {
    if (stack_empty(s)) return NULL;
    char *v = s->data[s->top--];
    return v; // caller must free
}

char* stack_peek(Stack *s) {
    if (stack_empty(s)) return NULL;
    return s->data[s->top];
}

void stack_clear(Stack *s) {
    while (!stack_empty(s)) {
        char *v = stack_pop(s);
        free(v);
    }
}

void stack_free(Stack *s) {
    stack_clear(s);
    free(s->data);
}


typedef struct {
    Stack backStack;
    Stack fwdStack;
    char *current;
} Browser;

void browser_init(Browser *b) {
    stack_init(&b->backStack, 8);
    stack_init(&b->fwdStack, 8);
    b->current = my_strdup("about:blank");
}

void browser_free(Browser *b) {
    stack_free(&b->backStack);
    stack_free(&b->fwdStack);
    free(b->current);
}

void browser_show(Browser *b) {
    printf("\n--- STATE ---\n");
    printf("Current: %s\n", b->current);
    printf("Back   : ");
    if (stack_empty(&b->backStack)) printf("(empty)\n");
    else {
        for (int i = 0; i <= b->backStack.top; i++)
            printf("%s%s", b->backStack.data[i], (i==b->backStack.top)?"\n":" | ");
    }
    printf("Forward: ");
    if (stack_empty(&b->fwdStack)) printf("(empty)\n\n");
    else {
        for (int i = 0; i <= b->fwdStack.top; i++)
            printf("%s%s", b->fwdStack.data[i], (i==b->fwdStack.top)?"\n\n":" | ");
    }
}

void browser_visit(Browser *b, const char *url) {
    // Push current to back, move to new URL, clear forward (new branch).
    stack_push(&b->backStack, b->current);
    free(b->current);
    b->current = my_strdup(url);
    stack_clear(&b->fwdStack);
    printf("Visited: %s\n", b->current);
}

void browser_back(Browser *b) {
    if (stack_empty(&b->backStack)) {
        printf("No page in Back history.\n");
        return;
    }
    // Move current to Forward; pop from Back to current.
    stack_push(&b->fwdStack, b->current);
    char *prev = stack_pop(&b->backStack);
    b->current = prev;
    printf("Back -> %s\n", b->current);
}

void browser_forward(Browser *b) {
    if (stack_empty(&b->fwdStack)) {
        printf("No page in Forward history.\n");
        return;
    }
    
    stack_push(&b->backStack, b->current);
    char *next = stack_pop(&b->fwdStack);
    b->current = next;
    printf("Forward -> %s\n", b->current);
}


static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n && (s[n-1] == '\n' || s[n-1] == '\r')) s[n-1] = '\0';
}

int main(void) {
    Browser b; browser_init(&b);

    printf("Browser Navigation Demo (Stacks)\n");
    printf("Commands:\n");
    printf("  visit <url>\n");
    printf("  back\n");
    printf("  forward\n");
    printf("  show\n");
    printf("  quit\n");

    char line[512];
    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        trim_newline(line);

        if (strncmp(line, "visit ", 6) == 0) {
            const char *url = line + 6;
            if (*url == '\0') { printf("Usage: visit <url>\n"); continue; }
            browser_visit(&b, url);
        } else if (strcmp(line, "back") == 0) {
            browser_back(&b);
        } else if (strcmp(line, "forward") == 0) {
            browser_forward(&b);
        } else if (strcmp(line, "show") == 0) {
            browser_show(&b);
        } else if (strcmp(line, "quit") == 0) {
            break;
        } else if (*line) {
            printf("Unknown command. Try: visit <url> | back | forward | show | quit\n");
        }
    }

    browser_free(&b);
    return 0;
}
