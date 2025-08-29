#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // For getch()

// --- Constants Definition ---
#define BOOK_DB_FILE "books.dat"
#define MEMBER_DB_FILE "members.dat"

#define MAX_NAME_LEN 50
#define MAX_DEPT_LEN 50
#define MAX_BOOK_NAME_LEN 100

// Book Status Constants
#define STATUS_IN_STOCK 1
#define STATUS_ISSUED 0

// --- Data Structures ---
typedef struct {
    int book_id;
    char name[MAX_BOOK_NAME_LEN];
    char author[MAX_NAME_LEN];
    int status; // 1 for IN, 0 for OUT
} Book;

typedef struct {
    int member_id;
    char name[MAX_NAME_LEN];
    char department[MAX_DEPT_LEN];
    int cards_available;
} Member;

// --- Utility Function Prototypes ---
void clear_screen();
void clear_input_buffer();
void press_enter_to_continue();
int get_numeric_input();

// --- Core Function Prototypes ---
void add_book();
void display_all_records();
void search_book();
void list_books_by_author();
void check_stock_status();
void add_member();
void issue_book();
void return_book();

// --- Main Program ---
int main() {
    int choice = 0;

    // Ensure database files exist
    FILE *fp_book = fopen(BOOK_DB_FILE, "ab+");
    if (fp_book == NULL) {
        perror("Error creating book database file");
        return 1;
    }
    fclose(fp_book);

    FILE *fp_member = fopen(MEMBER_DB_FILE, "ab+");
    if (fp_member == NULL) {
        perror("Error creating member database file");
        return 1;
    }
    fclose(fp_member);


    do {
        clear_screen();
        printf("\n\t\t--- Library Management System ---\n");
        printf("\n\t-------------------- MENU --------------------\n");
        printf(" \n\t1. Add a New Book");
        printf(" \n\t2. Display All Books & Members");
        printf(" \n\t3. Search for a Book by Name");
        printf(" \n\t4. List Books by an Author");
        printf(" \n\t5. Check Book Stock Status");
        printf(" \n\t6. Add a New Member");
        printf(" \n\t7. Issue a Book");
        printf(" \n\t8. Return a Book");
        printf(" \n\t9. Exit");
        printf("\n\n\t--------------------------------------------\n");
        printf("\tEnter your choice <1-9>: ");

        choice = get_numeric_input();

        switch (choice) {
            case 1: add_book(); break;
            case 2: display_all_records(); break;
            case 3: search_book(); break;
            case 4: list_books_by_author(); break;
            case 5: check_stock_status(); break;
            case 6: add_member(); break;
            case 7: issue_book(); break;
            case 8: return_book(); break;
            case 9: printf("\n\tThank you for using the system. Goodbye!\n"); break;
            default:
                printf("\n\t! Invalid Input. Please enter a number between 1 and 9.\n");
                press_enter_to_continue();
        }
    } while (choice != 9);

    return 0;
}

// --- Core Function Implementations ---

void add_book() {
    clear_screen();
    printf("\n\t--- Add a New Book ---\n");
    Book new_book;
    new_book.status = STATUS_IN_STOCK;

    FILE *fp = fopen(BOOK_DB_FILE, "ab");
    if (fp == NULL) {
        perror("Error opening book database");
        press_enter_to_continue();
        return;
    }

    printf("\nEnter Book ID (integer): ");
    new_book.book_id = get_numeric_input();

    printf("Enter Book Name: ");
    fgets(new_book.name, MAX_BOOK_NAME_LEN, stdin);
    new_book.name[strcspn(new_book.name, "\n")] = 0; // Remove newline

    printf("Enter Author Name: ");
    fgets(new_book.author, MAX_NAME_LEN, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0; // Remove newline

    fwrite(&new_book, sizeof(Book), 1, fp);
    fclose(fp);

    printf("\n\t(^^) A new book has been added successfully!\n");
    press_enter_to_continue();
}

void display_all_records() {
    clear_screen();
    Book book;
    Member member;
    FILE *fp_book, *fp_member;

    printf("\n\t--- All Book Records ---\n");
    fp_book = fopen(BOOK_DB_FILE, "rb");
    if (fp_book == NULL) {
        perror("Cannot open book database");
    } else {
        printf("\n%-10s %-40s %-25s %-10s\n", "Book ID", "Name", "Author", "Status");
        printf("------------------------------------------------------------------------------------\n");
        while (fread(&book, sizeof(Book), 1, fp_book) == 1) {
            printf("%-10d %-40s %-25s %-10s\n",
                   book.book_id, book.name, book.author,
                   (book.status == STATUS_IN_STOCK) ? "In Stock" : "Issued");
        }
        fclose(fp_book);
    }

    printf("\n\n\t--- All Member Records ---\n");
    fp_member = fopen(MEMBER_DB_FILE, "rb");
    if (fp_member == NULL) {
        perror("Cannot open member database");
    } else {
        printf("\n%-10s %-25s %-25s %-15s\n", "Member ID", "Name", "Department", "Cards Left");
        printf("----------------------------------------------------------------------------\n");
        while (fread(&member, sizeof(Member), 1, fp_member) == 1) {
            printf("%-10d %-25s %-25s %-15d\n",
                   member.member_id, member.name, member.department, member.cards_available);
        }
        fclose(fp_member);
    }

    press_enter_to_continue();
}

void search_book() {
    clear_screen();
    printf("\n\t--- Search for a Book by Name ---\n");
    char target_name[MAX_BOOK_NAME_LEN];
    int found = 0;
    Book book;

    printf("\nEnter the name of the book to search: ");
    fgets(target_name, MAX_BOOK_NAME_LEN, stdin);
    target_name[strcspn(target_name, "\n")] = 0; // Remove newline

    FILE *fp = fopen(BOOK_DB_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening book database");
        press_enter_to_continue();
        return;
    }

    while (fread(&book, sizeof(Book), 1, fp) == 1) {
        if (stricmp(book.name, target_name) == 0) {
            printf("\n\t--- Book Found! ---\n");
            printf("\tBook ID   : %d\n", book.book_id);
            printf("\tName      : %s\n", book.name);
            printf("\tAuthor    : %s\n", book.author);
            printf("\tStatus    : %s\n", (book.status == STATUS_IN_STOCK) ? "In Stock" : "Issued");
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("\n\t! Sorry, no book found with that name.\n");
    }
    press_enter_to_continue();
}

void list_books_by_author() {
    clear_screen();
    printf("\n\t--- List Books by an Author ---\n");
    char target_author[MAX_NAME_LEN];
    int found = 0;
    Book book;

    printf("\nEnter the name of the author: ");
    fgets(target_author, MAX_NAME_LEN, stdin);
    target_author[strcspn(target_author, "\n")] = 0; // Remove newline

    FILE *fp = fopen(BOOK_DB_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening book database");
        press_enter_to_continue();
        return;
    }
    
    printf("\n--- Books by %s ---\n", target_author);
    printf("%-10s %-40s %-10s\n", "Book ID", "Name", "Status");
    printf("-------------------------------------------------------------\n");
    
    while (fread(&book, sizeof(Book), 1, fp) == 1) {
        if (stricmp(book.author, target_author) == 0) {
             printf("%-10d %-40s %-10s\n",
                   book.book_id, book.name,
                   (book.status == STATUS_IN_STOCK) ? "In Stock" : "Issued");
            found = 1;
        }
    }
    fclose(fp);

    if (!found) {
        printf("\n\t! No books found by this author.\n");
    }
    press_enter_to_continue();
}

void check_stock_status() {
    clear_screen();
    printf("\n\t--- Library Stock Status ---\n");
    int stock_count = 0, issued_count = 0;
    Book book;
    
    FILE *fp = fopen(BOOK_DB_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening book database");
        press_enter_to_continue();
        return;
    }

    while (fread(&book, sizeof(Book), 1, fp) == 1) {
        if (book.status == STATUS_IN_STOCK) {
            stock_count++;
        } else {
            issued_count++;
        }
    }
    fclose(fp);

    printf("\n\tTotal Books in Stock : %d\n", stock_count);
    printf("\tTotal Books Issued   : %d\n", issued_count);
    
    press_enter_to_continue();
}

void add_member() {
    clear_screen();
    printf("\n\t--- Add a New Member ---\n");
    Member new_member;
    new_member.cards_available = 5; // Default value

    FILE *fp = fopen(MEMBER_DB_FILE, "ab");
    if (fp == NULL) {
        perror("Error opening member database");
        press_enter_to_continue();
        return;
    }

    printf("\nEnter Member ID (integer): ");
    new_member.member_id = get_numeric_input();

    printf("Enter Member Name: ");
    fgets(new_member.name, MAX_NAME_LEN, stdin);
    new_member.name[strcspn(new_member.name, "\n")] = 0;

    printf("Enter Department: ");
    fgets(new_member.department, MAX_DEPT_LEN, stdin);
    new_member.department[strcspn(new_member.department, "\n")] = 0;

    fwrite(&new_member, sizeof(Member), 1, fp);
    fclose(fp);

    printf("\n\t(^^) A new member has been added successfully!\n");
    press_enter_to_continue();
}

void issue_book() {
    clear_screen();
    printf("\n\t--- Issue a Book ---\n");
    int member_id, book_id, member_found = 0, book_found = 0;
    Member member;
    Book book;
    FILE *fp_member, *fp_book;
    FILE *temp_member, *temp_book;

    printf("\nEnter Member ID: ");
    member_id = get_numeric_input();

    // 1. Validate Member
    fp_member = fopen(MEMBER_DB_FILE, "rb");
    if (fp_member == NULL) {
        perror("Error");
        press_enter_to_continue();
        return;
    }
    while (fread(&member, sizeof(Member), 1, fp_member) == 1) {
        if (member.member_id == member_id) {
            member_found = 1;
            if (member.cards_available < 1) {
                printf("\n\t! This member has no available cards to issue a book.\n");
                fclose(fp_member);
                press_enter_to_continue();
                return;
            }
            break;
        }
    }
    fclose(fp_member);

    if (!member_found) {
        printf("\n\t! Member ID not found.\n");
        press_enter_to_continue();
        return;
    }

    printf("Enter Book ID to issue: ");
    book_id = get_numeric_input();

    // 2. Validate Book
    fp_book = fopen(BOOK_DB_FILE, "rb");
    if (fp_book == NULL) {
        perror("Error");
        press_enter_to_continue();
        return;
    }
    while (fread(&book, sizeof(Book), 1, fp_book) == 1) {
        if (book.book_id == book_id) {
            book_found = 1;
            if (book.status == STATUS_ISSUED) {
                printf("\n\t! This book is already issued.\n");
                fclose(fp_book);
                press_enter_to_continue();
                return;
            }
            break;
        }
    }
    fclose(fp_book);
    
    if (!book_found) {
        printf("\n\t! Book ID not found.\n");
        press_enter_to_continue();
        return;
    }

    // 3. Update Files if both are valid
    // Update Member File
    temp_member = fopen("temp_member.dat", "wb");
    fp_member = fopen(MEMBER_DB_FILE, "rb");
    while (fread(&member, sizeof(Member), 1, fp_member) == 1) {
        if (member.member_id == member_id) {
            member.cards_available--;
        }
        fwrite(&member, sizeof(Member), 1, temp_member);
    }
    fclose(fp_member);
    fclose(temp_member);
    remove(MEMBER_DB_FILE);
    rename("temp_member.dat", MEMBER_DB_FILE);
    
    // Update Book File
    temp_book = fopen("temp_book.dat", "wb");
    fp_book = fopen(BOOK_DB_FILE, "rb");
    while (fread(&book, sizeof(Book), 1, fp_book) == 1) {
        if (book.book_id == book_id) {
            book.status = STATUS_ISSUED;
        }
        fwrite(&book, sizeof(Book), 1, temp_book);
    }
    fclose(fp_book);
    fclose(temp_book);
    remove(BOOK_DB_FILE);
    rename("temp_book.dat", BOOK_DB_FILE);
    
    printf("\n\t(^^) Book issued successfully!\n");
    press_enter_to_continue();
}

void return_book() {
    clear_screen();
    printf("\n\t--- Return a Book ---\n");
    int member_id, book_id, member_found = 0, book_found = 0;
    Member member;
    Book book;
    FILE *fp_member, *fp_book;
    FILE *temp_member, *temp_book;

    printf("\nEnter Member ID who is returning: ");
    member_id = get_numeric_input();

    // 1. Validate Member
    fp_member = fopen(MEMBER_DB_FILE, "rb");
    if (fp_member == NULL) {
        perror("Error");
        press_enter_to_continue();
        return;
    }
    while (fread(&member, sizeof(Member), 1, fp_member) == 1) {
        if (member.member_id == member_id) {
            member_found = 1;
            break;
        }
    }
    fclose(fp_member);

    if (!member_found) {
        printf("\n\t! Member ID not found.\n");
        press_enter_to_continue();
        return;
    }

    printf("Enter Book ID to return: ");
    book_id = get_numeric_input();

    // 2. Validate Book
    fp_book = fopen(BOOK_DB_FILE, "rb");
    if (fp_book == NULL) {
        perror("Error");
        press_enter_to_continue();
        return;
    }
    while (fread(&book, sizeof(Book), 1, fp_book) == 1) {
        if (book.book_id == book_id) {
            book_found = 1;
            if (book.status == STATUS_IN_STOCK) {
                printf("\n\t! This book is already in stock. Cannot be returned.\n");
                fclose(fp_book);
                press_enter_to_continue();
                return;
            }
            break;
        }
    }
    fclose(fp_book);

    if (!book_found) {
        printf("\n\t! Book ID not found.\n");
        press_enter_to_continue();
        return;
    }
    
    // 3. Update Files
    // Update Member File
    temp_member = fopen("temp_member.dat", "wb");
    fp_member = fopen(MEMBER_DB_FILE, "rb");
    while (fread(&member, sizeof(Member), 1, fp_member) == 1) {
        if (member.member_id == member_id) {
             if(member.cards_available < 5) member.cards_available++;
        }
        fwrite(&member, sizeof(Member), 1, temp_member);
    }
    fclose(fp_member);
    fclose(temp_member);
    remove(MEMBER_DB_FILE);
    rename("temp_member.dat", MEMBER_DB_FILE);
    
    // Update Book File
    temp_book = fopen("temp_book.dat", "wb");
    fp_book = fopen(BOOK_DB_FILE, "rb");
    while (fread(&book, sizeof(Book), 1, fp_book) == 1) {
        if (book.book_id == book_id) {
            book.status = STATUS_IN_STOCK;
        }
        fwrite(&book, sizeof(Book), 1, temp_book);
    }
    fclose(fp_book);
    fclose(temp_book);
    remove(BOOK_DB_FILE);
    rename("temp_book.dat", BOOK_DB_FILE);
    
    printf("\n\t(^^) Book returned successfully!\n");
    press_enter_to_continue();
}


// --- Utility Function Implementations ---

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void press_enter_to_continue() {
    printf("\n\tPress Enter to continue...");
    getch();
}

int get_numeric_input() {
    int value;
    char buffer[100];

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &value) == 1) {
            return value;
        } else {
            printf("\t! Invalid input. Please enter a number: ");
        }
    }
}