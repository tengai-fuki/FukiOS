__asm__(
    ".code16gcc\n"
    ".section .boot, \"ax\"\n"
    ".global _start\n"
    ".intel_syntax noprefix\n"

    "_start:\n"
    "cli\n"
    
    "xor ax, ax\n"
    "xor bx, bx\n"
    "mov ds, ax\n"
    "mov es, ax\n"
    "mov ss, ax\n"
    "mov sp, 0x7C00\n"
    "mov di, 0\n"
    
    "sti\n"

    "mov ah, 0x02\n"
    "mov al, 10\n"
    "mov ch, 0\n"
    "mov cl, 0x02\n"
    "mov dh, 0\n"
    "mov bx, 0x7E00\n"
    "int 0x13\n"

    "jmp main\n"

    ".org 0x1fe\n"
    ".word 0xaa55\n"
    ".att_syntax prefix\n"
    ".text\n"
);

void fuki();
void sumasu(char iro);

void main(){
    sumasu(0x07);
    fuki();

    while(1){

    }
}

void fuki() {

    volatile char *video = (volatile char*)0xB8000;
    
    char *mesaj = " FukiOS";
    char renk = 0x05; 
    
    int i = 0;
    int v_idx = 0;

    while (mesaj[i] != 0) {
        video[v_idx] = mesaj[i];
        video[v_idx + 1] = renk;
        i++;
        v_idx += 2;
    }

    while(0) {
    } 
}

void sumasu(char iro){
    volatile char *video = (volatile char*)0xB8000;

    for(int i = 0; i < 80 * 25 * 2; i+=2 ){
        video[i] = ' ';
        video[i + 1] = iro;
    } 
  }

void gamen(int yukseklik; ){

}