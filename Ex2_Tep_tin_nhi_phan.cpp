#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[100];
    char id[20];
    float score;
} Student;

void inputStudentInfo(Student *student) {
    printf("Nhap thong tin sinh vien:\n");
    printf("Ho ten: ");
    while (getchar() != '\n');
    fgets(student->name, sizeof(student->name), stdin);

    printf("Ma sinh vien: ");
    fgets(student->id, sizeof(student->id), stdin);

    printf("Diem: ");
    scanf("%f", &student->score);
}

void displayStudentInfo(Student *student) {
    printf("Ho ten: %s", student->name);
    printf("Ma sinh vien: %s", student->id);
    printf("Diem: %.2f\n", student->score);
}

void saveToFile(Student *studentArray, int numStudents) {
    FILE *file = fopen("studentdata.bin", "wb");
    if (file == NULL) {
        perror("Khong the mo tep tin");
        return;
    }

    fwrite(studentArray, sizeof(Student), numStudents, file);

    fclose(file);
}

void loadFromFile(Student *studentArray, int *numStudents) {
    FILE *file = fopen("studentdata.bin", "rb");
    if (file == NULL) {
        perror("Khong the mo tep tin");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    *numStudents = fileSize / sizeof(Student);

    fread(studentArray, sizeof(Student), *numStudents, file);

    fclose(file);
}

int main() {
    int numStudents = 0;
    Student *studentArray = (Student *)malloc(sizeof(Student));

    loadFromFile(studentArray, &numStudents);

    int choice;

    do {
        printf("Menu:\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Luu va thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                //Them sinh vien
                studentArray = (Student *)realloc(studentArray, (numStudents + 1) * sizeof(Student));
                inputStudentInfo(&studentArray[numStudents]);
                numStudents++;
                break;
            case 2:
                //Hien thi danh sach sinh vien
                printf("\nDanh sach sinh vien:\n");
                for (int i = 0; i < numStudents; ++i) {
                    printf("Sinh vien %d:\n", i + 1);
                    displayStudentInfo(&studentArray[i]);
                    printf("\n");
                }
                break;
            case 3:
                saveToFile(studentArray, numStudents);
                break;
            default:
                printf("Chon chuc nang khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 3);

    free(studentArray);

    return 0;
}
 
