mj/* Student Record Search using AVL Tree
   Compile: gcc avl_student.c -o avl  
   Run    : ./avl                                              */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

typedef struct Node {
    Student data;
    struct Node *left, *right;
    int height;                 /* leaf = 1 */
} Node;

int cmp_count = 0;              /* comparisons during insertion */
int rotations = 0;

Student make_student(int i) {
    Student s;
    s.reg_no = KEYS[i];
    strcpy(s.name, NAMES[i]);
    strcpy(s.dept, DEPTS[i % 5]);
    return s;
}

int h(Node *n)            { return n ? n->height : 0; }
int max(int a, int b)     { return a > b ? a : b; }
int balance(Node *n)      { return n ? h(n->left) - h(n->right) : 0; }
void update(Node *n)      { n->height = 1 + max(h(n->left), h(n->right)); }

Node *create_node(Student s) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = s;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

Node *rotate_right(Node *y) {
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    update(y); update(x);
    rotations++;
    return x;
}

Node *rotate_left(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    update(x); update(y);
    rotations++;
    return y;
}

/* ---------- Insertion ---------- */
Node *insert(Node *node, Student s) {
    if (node == NULL) return create_node(s);

    cmp_count++;
    if (s.reg_no < node->data.reg_no)
        node->left = insert(node->left, s);
    else if (s.reg_no > node->data.reg_no)
        node->right = insert(node->right, s);
    else {
        printf("Duplicate key %d ignored\n", s.reg_no);
        return node;
    }

    update(node);
    int bal = balance(node);

    if (bal > 1 && s.reg_no < node->left->data.reg_no)            /* LL */
        return rotate_right(node);
    if (bal < -1 && s.reg_no > node->right->data.reg_no)          /* RR */
        return rotate_left(node);
    if (bal > 1 && s.reg_no > node->left->data.reg_no) {          /* LR */
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (bal < -1 && s.reg_no < node->right->data.reg_no) {        /* RL */
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

/* ---------- Searching ---------- */
Node *search(Node *root, int key, int *comps, int path[], int *plen) {
    Node *cur = root;
    *comps = 0;
    *plen = 0;
    while (cur != NULL) {
        (*comps)++;
        path[(*plen)++] = cur->data.reg_no;
        if (key == cur->data.reg_no) return cur;
        cur = (key < cur->data.reg_no) ? cur->left : cur->right;
    }
    return NULL;
}

/* ---------- Traversals ---------- */
void inorder(Node *r)   { if (r) { inorder(r->left);  printf("%d ", r->data.reg_no); inorder(r->right); } }
void preorder(Node *r)  { if (r) { printf("%d ", r->data.reg_no); preorder(r->left); preorder(r->right); } }
void postorder(Node *r) { if (r) { postorder(r->left); postorder(r->right); printf("%d ", r->data.reg_no); } }

int main(void) {
    Node *root = NULL;
    int comps, plen, path[64], i;

    printf("============================================================\n");
    printf(" STUDENT RECORD SEARCH - AVL TREE\n");
    printf("============================================================\n");

    for (i = 0; i < N; i++)
        root = insert(root, make_student(i));
    printf("Inserted %d records\n", N);
    printf("Total comparisons during insertion : %d\n", cmp_count);
    printf("Total rotations performed          : %d\n", rotations);
    printf("Tree height (levels)               : %d\n", h(root));

    printf("\n--- Traversals (Register Numbers) ---\n");
    printf("Inorder (sorted): "); inorder(root);   printf("\n");
    printf("Preorder        : "); preorder(root);  printf("\n");
    printf("Postorder       : "); postorder(root); printf("\n");

    printf("\n--- Successful Search (all %d keys) ---\n", N);
    int sum = 0, mx = 0, mn = 1000;
    for (i = 0; i < N; i++) {
        search(root, KEYS[i], &comps, path, &plen);
        sum += comps;
        if (comps > mx) mx = comps;
        if (comps < mn) mn = comps;
    }
    printf("Average comparisons : %.2f\n", (double)sum / N);
    printf("Maximum comparisons : %d\n", mx);
    printf("Minimum comparisons : %d\n", mn);

    printf("\n--- Unsuccessful Search ---\n");
    sum = 0;
    for (i = 0; i < N_UNSUCC; i++) {
        Node *r = search(root, UNSUCC_KEYS[i], &comps, path, &plen);
        sum += comps;
        printf("Key %d: %s | comparisons = %d | path = ", UNSUCC_KEYS[i],
               r ? "FOUND" : "NOT FOUND", comps);
        for (int j = 0; j < plen; j++) printf("%d ", path[j]);
        printf("\n");
    }
    printf("Average comparisons : %.2f\n", (double)sum / N_UNSUCC);

    printf("\n--- Insertion of a new record ---\n");
    Student ns = {NEW_KEY, "Viva Student", "CSE"};
    int before = cmp_count;
    root = insert(root, ns);
    printf("Inserted %d with %d comparisons. New height = %d\n", NEW_KEY, cmp_count - before, h(root));

    printf("\n--- Viva demo: search any key ---\n");
    int key;
    printf("Enter Register Number to search (0 to skip): ");
    if (scanf("%d", &key) == 1 && key != 0) {
        Node *r = search(root, key, &comps, path, &plen);
        printf("Path followed: ");
        for (i = 0; i < plen; i++) printf("%d ", path[i]);
        if (r) printf("\nFOUND: %d | %s | %s | comparisons = %d\n", r->data.reg_no, r->data.name, r->data.dept, comps);
        else   printf("\nNOT FOUND | comparisons = %d\n", comps);
    }
    return 0;
}
