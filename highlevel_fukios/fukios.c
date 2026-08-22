#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

void login(){

char user[50];
char password[50];

while (1){
printf("user: ");
scanf("%s", user);
printf("password: ");
scanf("%s", password);

if(strcmp(user, "tengai") == 0 && strcmp(password, "1234") == 0){
break;
}

else{
printf("wrong username or password\n");
  }
 }
}

void fuki(){
printf("obey fuki-sama\n");
}

void jill(){
printf("jill-sama\n");
}

void calc(){
long sayi;
long sayi2;
scanf("%ld %ld", &sayi, &sayi2);
printf("%ld\n", sayi + sayi2);
}

void roulette(){
int mermi;
int dealer = 1;

srand((unsigned)time(NULL));

while(1){

printf("dealer %d, press any key for click trigger\n", dealer);
getch();

mermi = rand() % 6;

if (mermi == 0){
HWND windows = GetActiveWindow();
SendMessage(windows, WM_CLOSE, 0, 0);
exit(0);
}

else{
	printf("bos\n");

	if(dealer == 1){
		dealer = 2;
		}
		else{
		dealer = 1;
		}
	 }
  }
}

void help(){
	printf("shiki: fuki, jill, calc, roulette, poweroff\n");
}

void poweroff(){
HWND windows = GetActiveWindow();
SendMessage(windows, WM_CLOSE, 0, 0);
exit(0);
}

int main(){

char shell[50];

login();

while(1){

printf("FukiOS>");
scanf("%s", shell);

if(strcmp(shell, "fuki") == 0){
fuki();
}

else if(strcmp(shell, "jill") == 0){
jill();
}

else if(strcmp(shell, "calc") == 0){
calc();
}

else if(strcmp(shell, "roulette") == 0){
roulette();
}

else if(strcmp(shell, "help") == 0){
help();
}

else if(strcmp(shell, "poweroff") == 0){
poweroff();
}

else{
printf("wrong command\n");
  }
 }
return 0;
}
