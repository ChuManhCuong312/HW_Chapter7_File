#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_CONTACTS 100

typedef struct Contact {
    char name[
    char phone[
    char email[
} Contact;

void inputContactInfo(Contact *contact) {
    printf("Nhap thong tin lien lac:\n");
    printf("Ho ten: ");
    while (getchar() != '\n');
    fgets(contact->name, sizeof(contact->name), stdin);

    printf("So dien thoai: ");
    fgets(contact->phone, sizeof(contact->phone), stdin);

    printf("Email: ");
    fgets(contact->email, sizeof(contact->email), stdin);
}

void displayContactInfo(Contact *contact) {
    printf("Ho ten: %s", contact->name);
    printf("So dien thoai: %s", contact->phone);
    printf("Email: %s", contact->email);
}

int findContactIndexByName(Contact *contacts, int numContacts, const char *name) {
    for (int i = 0; i < numContacts; ++i) {
        if (strcmp(contacts[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Khong tim thay
}

void addContact(Contact *contacts, int *numContacts) {
    if (*numContacts < 
        inputContactInfo(&contacts[*numContacts]);
        (*numContacts)++;
        printf("Da them lien lac.\n");
    } else {
        printf("Danh ba da day, khong the them lien lac moi.\n");
    }
}

void deleteContact(Contact *contacts, int *numContacts) {
    char nameToDelete[
    printf("Nhap ten lien lac can xoa: ");
    while (getchar() != '\n');
    fgets(nameToDelete, sizeof(nameToDelete), stdin);

    int indexToDelete = findContactIndexByName(contacts, *numContacts, nameToDelete);

    if (indexToDelete != -1) {
        // Di chuyen lien lac cuoi cung len vi tri cua lien lac can xoa
        contacts[indexToDelete] = contacts[(*numContacts) - 1];
        (*numContacts)--;
        printf("Da xoa lien lac.\n");
    } else {
        printf("Khong tim thay lien lac can xoa.\n");
    }
}

void searchContact(Contact *contacts, int numContacts) {
    char nameToSearch[
    printf("Nhap ten lien lac can tim kiem: ");
    while (getchar() != '\n');
    fgets(nameToSearch, sizeof(nameToSearch), stdin);

    int indexToSearch = findContactIndexByName(contacts, numContacts, nameToSearch);

    if (indexToSearch != -1) {
        printf("Thong tin lien lac tim thay:\n");
        displayContactInfo(&contacts[indexToSearch]);
    } else {
        printf("Khong tim thay lien lac.\n");
    }
}

void updateContact(Contact *contacts, int numContacts) {
    char nameToUpdate[
    printf("Nhap ten lien lac can cap nhat: ");
    while (getchar() != '\n');
    fgets(nameToUpdate, sizeof(nameToUpdate), stdin);

    int indexToUpdate = findContactIndexByName(contacts, numContacts, nameToUpdate);

    if (indexToUpdate != -1) {
        printf("Thong tin lien lac hien tai:\n");
        displayContactInfo(&contacts[indexToUpdate]);
        printf("Nhap thong tin moi:\n");
        inputContactInfo(&contacts[indexToUpdate]);
        printf("Da cap nhat lien lac.\n");
    } else {
        printf("Khong tim thay lien lac can cap nhat.\n");
    }
}

void saveToFile(Contact *contacts, int numContacts) {
    FILE *file = fopen("contacts.bin", "wb");
    if (file == NULL) {
        perror("Khong the mo tep tin");
        return;
    }

    fwrite(contacts, sizeof(Contact), numContacts, file);

    fclose(file);
}

void loadFromFile(Contact *contacts, int *numContacts) {
    FILE *file = fopen("contacts.bin", "rb");
    if (file == NULL) {
        perror("Khong the mo tep tin");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    *numContacts = fileSize / sizeof(Contact);

    fread(contacts, sizeof(Contact), *numContacts, file);

    fclose(file);
}

int main() {
    int numContacts = 0;
    Contact *contactArray = (Contact *)malloc(MAX_CONTACTS * sizeof(Contact));

    loadFromFile(contactArray, &numContacts);

    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Them lien lac\n");
        printf("2. Xoa lien lac\n");
        printf("3. Tim kiem lien lac\n");
        printf("4. Cap nhat lien lac\n");
        printf("5. Hien thi danh sach lien lac\n");
        printf("6. Luu va thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(contactArray, &numContacts);
                break;
            case 2:
                deleteContact(contactArray, &numContacts);
                break;
            case 3:
                searchContact(contactArray, numContacts);
                break;
            case 4:
                updateContact(contactArray, numContacts);
                break;
            case 5:
                printf("\nDanh sach lien lac:\n");
                for (int i = 0; i < numContacts; ++i) {
                    printf("Lien lac %d:\n", i + 1);
                    displayContactInfo(&contactArray[i]);
                    printf("\n");
                }
                break;
            case 6:
                saveToFile(contactArray, numContacts);
                break;
            default:
                printf("Chon chuc nang khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 6);

    free(contactArray);

    return 0;
}

