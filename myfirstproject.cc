#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
};

void addBook() {
    struct Book book;
    FILE *fp = fopen("library.txt", "a");

    printf("Enter Book ID: ");
    scanf("%d", &book.id);
    getchar(); // clear newline
    printf("Enter Book Title: ");
    fgets(book.title, sizeof(book.title), stdin);
    strtok(book.title, "\n");
    printf("Enter Author Name: ");
    fgets(book.author, sizeof(book.author), stdin);
    strtok(book.author, "\n");

    fwrite(&book, sizeof(struct Book), 1, fp);
    fclose(fp);
    printf("Book added successfully!\n");
}

void displayBooks() {
    struct Book book;
    FILE *fp = fopen("library.txt", "r");

    printf("\n--- Book List ---\n");
    while (fread(&book, sizeof(struct Book), 1, fp)) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\n\n", book.id, book.title, book.author);
    }
    fclose(fp);
}

void searchBook() {
    struct Book book;
    int id, found = 0;
    FILE *fp = fopen("library.txt", "r");

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&book, sizeof(struct Book), 1, fp)) {
        if (book.id == id) {
            printf("Book Found!\nID: %d\nTitle: %s\nAuthor: %s\n", book.id, book.title, book.author);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Book not found.\n");
}

void deleteBook() {
    struct Book book;
    int id, found = 0;
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&book, sizeof(struct Book), 1, fp)) {
        if (book.id != id)
            fwrite(&book, sizeof(struct Book), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("Book deleted successfully.\n");
    else
        printf("Book not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n=== Library Management System ===\n");
        printf("1. Add Book\n2. Display Books\n3. Search Book\n4. Delete Book\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}

