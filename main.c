#include <stdio.h>
#include <string.h>

typedef struct{
    char id[15];
    char name[50];
    char email[50];
    char phone[15];
    char status[10];
}User;

User users[100];
int userCount=0;
void mainMenu();
void loginAdmin();
void adminMenu();
void addUser();
void displayAllUsers();
void searchUser();
void searchUserById();
void arrangeUser();
void toggleUserStatus();
int isUnique(char id[], char email[], char phone[]);
int main(){
    mainMenu();
    return 0;
}
void mainMenu(){
    int choice;
    while(1){
        printf("\n*** User Management System ***\n");
        printf("          CHOOSE YOUR ROLE\n");
        printf("      ========================\n");
        printf("      [1] Admin\n");
        printf("      [2] User\n");
        printf("      [0] Exit the Program\n");
        printf("      ========================\n");
        printf("      Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            	system("cls");
                loginAdmin();
                break;
            case 2:
            	system("cls");
                printf("\nChua Them Chuc Nang\n");
                break;
            case 0:
                printf("Goodbye\n");
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}
void loginAdmin(){
    char email[50], password[50];
    printf("\n*** User Management System ***\n");
    printf("               LOGIN\n");
    printf("      ========================\n");
    printf("      Email: ");
    scanf("%s", email);
    printf("      Password: ");
    scanf("%s", password);
    if(strcmp(email, "admin@gmail.com")==0 && strcmp(password, "admin")==0){
        adminMenu();
    }else{
        printf("Email hoac mat khau khong hop le\n");
    }
}
void adminMenu(){
    int choice;
    while(1){
        printf("\n*** User Management System ***\n");
        printf("               Menu\n");
        printf("      ========================\n");
        printf("      [1] Add A New User\n");
        printf("      [2] Show ALL Users\n");
        printf("      [3] Search Users\n");
        printf("      [4] Lock/Unlock A User\n");
        printf("      [5] Search Users By Id\n");
        printf("      [6] Arrange\n");
        printf("      [0] Exit\n");
        printf("      ========================\n");
        printf("      Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
            	system("cls");
                addUser();
                break;
            case 2:
            	system("cls");
                displayAllUsers();
                break;
            case 3:
            	system("cls");
                searchUser();
                break;
            case 4:
            	system("cls");
                toggleUserStatus();
                break;
            case 5:
            	system("cls");
            	searchUserById();
            	break;
            case 6:
            	system("cls");
            	arrangeUser();
            	break;
            case 0:
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}
void addUser(){
    if (userCount>=100){
        printf("Danh Sach Da Day\n");
        return;
    }
    User newUser;
	fflush(stdin);
    printf("Enter user ID: ");
    fgets(newUser.id, sizeof(newUser.id), stdin);
    newUser.id[strcspn(newUser.id, "\n")]=0;
    fflush(stdin);
    printf("Enter user name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")]=0;
    fflush(stdin);
    printf("Enter user email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")]=0;
    fflush(stdin);
    printf("Enter user phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")]=0;
    fflush(stdin);
    printf("Status (Open/Lock): ");
    fgets(newUser.status, sizeof(newUser.status), stdin);
    newUser.status[strcspn(newUser.status, "\n")]=0;

    if (!isUserInfoNotEmpty(newUser.id, newUser.name, newUser.email, newUser.phone)){
        return;
    }
    if (isUserInfoValid(newUser.id, newUser.name, newUser.phone) && isUnique(newUser.id, newUser.email, newUser.phone)){
        users[userCount++] = newUser;
        FILE *file = fopen("user.txt", "a");
        if(file==NULL){
            printf("Loi: Khong the mo file de ghi\n");
            return;
        }
        fprintf(file, "%s,%s,%s,%s,%s\n", newUser.id, newUser.name, newUser.email, newUser.phone, newUser.status);
        fclose(file);
        printf("Them Thanh Cong\n");
    }else{
        printf("Loi: ID hoac Email Hoac Phone Bi Trung. Nguoi Dung Khong Duoc Them Vao\n");
    }
}
void displayAllUsers(){
	userCount=0;
    FILE *file = fopen("user.txt","r");
    if(file==NULL){
        printf("Khong The Mo File user.txt\n");
        return;
    }
    while(fscanf(file, "%[^,],%[^,],%[^,],%[^,],%s\n",
                  users[userCount].id,
                  users[userCount].name,
                  users[userCount].email,
                  users[userCount].phone,
                  users[userCount].status) == 5){
        userCount++;
        if(userCount>=100){
            printf("Danh Sach Da Day\n");
            break;
        }
    }
    fclose(file);
    if(userCount==0){
        printf("Khong Co Nguoi Dung\n");
        return;
    }
    printf("\n==================================================================================\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++){
        printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
               users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }
    printf("---------------------------------------------------------------------------------\n");
}
void searchUser(){
    char searchName[50];
    printf("Nhap Ten De Tim Kiem: ");
    while(getchar()!='\n');
    scanf(" %[^\n]", searchName);
    int found=0;
    printf("\n----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++){
        if(strstr(users[i].name, searchName)!=NULL){
            found=1;
            printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("---------------------------------------------------------------------------------\n");
    if(!found){
        printf("Khong Tim Thay Nguoi Dung '%s'\n", searchName);
    }
}
void toggleUserStatus(){
    char userId[15];
    printf("Nhap ID Nguoi Dung De Lock/Unlock: ");
    scanf("%s", userId);
    for(int i=0; i<userCount; i++){
        if(strcmp(users[i].id, userId)==0){
            if(strcmp(users[i].status, "Open")==0){
                strcpy(users[i].status, "Lock");
                printf("User %s Hien Da Bi Khoa\n", users[i].name);
            }else{
                strcpy(users[i].status, "Open");
                printf("User %s Hien Da Duoc Mo Khoa\n", users[i].name);
            }
            FILE *file;
			file=fopen("user.txt", "w");
            if(file == NULL){
                printf("Khong the mo file de ghi\n");
                return;
            }
            for(int j=0; j<userCount; j++){
                fprintf(file, "%s,%s,%s,%s,%s\n",
                        users[j].id, users[j].name, users[j].email, users[j].phone, users[j].status);
            }
            fclose(file);
            return;
        }
    }
    printf("Khong Tim Thay ID Nguoi Dung\n");
}
void searchUserById(){
    char searchId[50];
    printf("Nhap ID De Tim Kiem: ");
    while(getchar()!='\n');
    scanf(" %[^\n]", searchId);
    int found=0;
    printf("\n----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++){
        if(strstr(users[i].id, searchId)!=NULL){
            found=1;
            printf("| %-10s | %-20s | %-20s | %-10s | %-5s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("---------------------------------------------------------------------------------\n");
    if(!found){
        printf("Khong Tim Thay Nguoi Dung ID %s\n", searchId);
    }
}
void arrangeUser(){
    displayAllUsers();
    if(userCount==0){
        printf("Danh sach nguoi dung trong. Khong co gi de sap xep.\n");
        return;
    }
    int thuTu;
    printf("\nChon thu tu sap xep:\n");
    printf("[1] Tang dan (A-Z)\n");
    printf("[2] Giam dan (Z-A)\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &thuTu);
    if(thuTu!=1 && thuTu!=2){
        printf("Lua chon khong hop le. Quay lai menu.\n");
        return;
    }
    for(int i=0; i<userCount-1; i++){
        for(int j=i+1; j<userCount; j++){
            if((thuTu == 1 && strcmp(users[i].name, users[j].name) > 0) || (thuTu == 2 && strcmp(users[i].name, users[j].name) < 0)){
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
    printf("Da sap xep danh sach theo ten\n");
    FILE *file; 
	file=fopen("user.txt", "w");
    if(file==NULL){
        printf("Khong the mo file de ghi\n");
        return;
    }
    for(int i=0; i<userCount; i++){
        fprintf(file, "%s,%s,%s,%s,%s\n",
                users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }
    fclose(file);
    userCount=0;
    file=fopen("user.txt", "r");
    if(file==NULL){
        printf("Khong the mo file user.txt\n");
        return;
    }
    while(fscanf(file, "%[^,],%[^,],%[^,],%[^,],%s\n",
                  users[userCount].id,
                  users[userCount].name,
                  users[userCount].email,
                  users[userCount].phone,
                  users[userCount].status)==5){
        userCount++;
    }
    fclose(file);
    displayAllUsers();
}
int isUnique(char id[], char email[], char phone[]){
    for(int i=0; i<userCount; i++){
        if(strcmp(users[i].id, id)==0 || strcmp(users[i].email, email)==0 || strcmp(users[i].phone, phone)==0){
            return 0;
        }
    }
    return 1;
}
int isUserInfoValid(char id[], char name[], char phone[]){
    if(strlen(id)<2 || strlen(id)>5 || 
        strlen(name)<=3 ||
        strlen(phone)!=10){
        printf("\nThong tin khong hop le. ID nguoi dung phai dai 2-5 ky tu, Ten phai nhieu hon 3 ky tu, So dien thoai phai dai 10 ky tu.\n");
        return 0;
    }
    return 1;
}
int isUserInfoNotEmpty(char id[], char name[], char email[], char phone[]){
    if(strlen(id)==0 || strlen(name)==0 || strlen(email)==0 || strlen(phone)==0){
        printf("\nThong tin nguoi dung khong duoc de trong\n");
        return 0;
    }
    return 1;
}

