/* dataset.h - common dataset used by BST, AVL and Hashing programs
   Application: Student Record Search (key = Register Number) */
#ifndef DATASET_H
#define DATASET_H

#define N 40
#define N_UNSUCC 5

typedef struct {
    int  reg_no;
    char name[30];
    char dept[5];
} Student;

static const int KEYS[N] = {
    4521, 2310, 6789, 1234, 8901, 3456, 7777, 5050, 9100, 2468,
    1357, 6024, 8642, 4096, 7531, 3141, 2718, 5555, 9999, 1111,
    6666, 3333, 8080, 4444, 7070, 2222, 9090, 1515, 5959, 3737,
    8484, 6161, 4242, 7373, 2929, 1818, 9696, 5252, 3030, 8787
};

static const char *NAMES[N] = {
    "Arun Kumar", "Priya Sharma", "Karthik Raja", "Divya Lakshmi", "Rahul Verma",
    "Sneha Iyer", "Vignesh S", "Meena Devi", "Ajay Nair", "Pooja Reddy",
    "Suresh Babu", "Ananya Das", "Harish M", "Nithya Rao", "Mohan Raj",
    "Kavya Menon", "Dinesh K", "Lavanya P", "Gokul Krishnan", "Swathi R",
    "Naveen Kumar", "Ishwarya T", "Prakash J", "Revathi S", "Surya Prakash",
    "Deepak Joshi", "Janani V", "Bharath Y", "Keerthana M", "Sathish R",
    "Aishwarya N", "Vimal Raj", "Shalini G", "Manoj Kumar", "Harini S",
    "Tarun Patel", "Gayathri K", "Lokesh B", "Pavithra D", "Yogesh S"
};

static const char *DEPTS[5] = {"CSE", "ECE", "IT", "MECH", "EEE"};

/* keys that are NOT in the dataset (for unsuccessful search) */
static const int UNSUCC_KEYS[N_UNSUCC] = {1000, 2000, 5000, 7000, 9500};

/* new record used for the insertion test / viva */
#define NEW_KEY 4747

#endif
