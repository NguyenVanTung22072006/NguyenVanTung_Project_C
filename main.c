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
void login();
void adminMenu();
void addUser();
void displayAllUsers();
void searchUser();
//void toggleUserStatus();
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
                login();
                break;
            case 2:
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
void login(){
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
//        printf("      [4] Lock/Unlock A User\n");
        printf("      [0] Exit\n");
        printf("      ========================\n");
        printf("      Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                addUser();
                break;
            case 2:
                displayAllUsers();
                break;
            case 3:
                searchUser();
                break;
//            case 4:
//                toggleUserStatus();
//                break;
            case 0:
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}
void addUser(){
//	FILE *file;
//	flie=fopen("user.bin","wb");
//	
//	
	
   if(userCount>=100){
        printf("Danh Sach Da Day\n");
        return;
    }
    User newUser;
    printf("Enter user ID: ");
    scanf("%s", newUser.id);
    printf("Enter user name: ");
    while (getchar()!='\n');
    scanf(" %[^\n]", newUser.name);
    printf("Enter user email: ");
    scanf("%s", newUser.email);
    printf("Enter user phone: ");
    scanf("%s", newUser.phone);
    printf("Status (Open/Lock): ");
    scanf("%s", newUser.status);
    if(isUnique(newUser.id, newUser.email, newUser.phone)){
        users[userCount++]=newUser;
        printf("Them Thanh Cong\n");
    }else {
        printf("Loi: ID hoac Email Hoac Phone Bi Trung. Nguoi Dung Khong Duoc Them Vao\n");
    }
}
void displayAllUsers(){
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
//void toggleUserStatus(){
//    char userId[15];
//    printf("Nhap ID Nguoi Dung De Lock/Unlock: ");
//    scanf("%s", userId);
//    for(int i=0; i<userCount; i++){
//        if(strcmp(users[i].id, userId)==0){
//            if(strcmp(users[i].status, "Open")==0){
//                strcpy(users[i].status, "Lock");
//                printf("User %s Hien Da Bi Khoa\n", users[i].name);
//            }else{
//                strcpy(users[i].status, "Open");
//                printf("User %s Hien Da Duoc Mo Khoa\n", users[i].name);
//            }
//            return;
//        }
//    }
//    printf("Khong Tim Thay ID Nguoi Dung\n");
//}
int isUnique(char id[], char email[], char phone[]){
    for(int i=0; i<userCount; i++){
        if(strcmp(users[i].id, id)==0 || strcmp(users[i].email, email)==0 || strcmp(users[i].phone, phone)==0){
            return 0;
        }
    }
    return 1;
}
