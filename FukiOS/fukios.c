/*asm(
    ".code16gcc\n"
    ".section .boot,\"ax\"\n"
    ".global _start\n"
    "_start:\n"
    "cli\n"
    "xor %ax, %ax\n"
    "mov %ax, %ds\n"
    "mov %ax, %es\n"
    "mov %ax, %ss\n"
    "mov $0x7c00, %sp\n"
    "sti\n"
    "movb $0x02, %ah\n"
    "movb $0x10, %al\n"
    "movb $0x00, %ch\n"
    "movb $0x02, %cl\n"
    "movb $0x00, %dh\n"
    "movw $0x7E00, %bx\n"
    "int $0x13\n"
    "jmp main\n"
    ".org 510\n"
    ".word 0xAA55\n"
    ".text\n"
);*/

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

    "jmp fuki\n"

    ".org 0x1fe\n"
    ".word 0xaa55\n"
    ".att_syntax prefix\n"
    ".text\n"
);

#define moji_iro 0x50

void kenban();
void sumasu(char iro);
void gamen(int gyou, int retsu, int haba, int iro);
void kaku(int gyou, int retsu, char *mesaj, char iro);
void mado(int gyou, int retsu, int haba, int takasa, int iro);

void fuki(){
    sumasu(0x10);
    gamen(0, 0, 80, 0x70);
    gamen(24, 0, 80, 0x70);
    //mado(8, 21, 39, 9, 0x00);
    //mado(7, 20, 38, 9, 0xB0);
    kaku(0, 1, "FukiOS", 0x70);  

    while(1){
        kenban(); 
    }
}

void kaku(int gyou, int retsu, char *mesaj, char iro) {

    volatile char *video = (volatile char*)0xB8000;

    int sousai = ((gyou * 80 ) + retsu) * 2;
    
    int i = 0;

    while(mesaj[i] != 0){
        video[sousai] = mesaj[i];
        video[sousai + 1] = iro;

        i++;
        sousai += 2;
    }
}

void sumasu(char iro){
    volatile char *video = (volatile char*)0xB8000;

    for(int i = 0; i < 80 * 25 * 2; i+=2 ){
        video[i] = ' ';
        video[i + 1] = iro;
    } 
}

void gamen(int gyou, int retsu, int haba, int iro){

    volatile char *video = (volatile char*)0xB8000;

    int sousai = ((gyou * 80) + retsu) * 2;

    for(int x = 0; x < haba; x++){

        video[sousai] = ' ';
        video[sousai + 1] = iro;
        sousai += 2;
    }
}

void mado(int gyou, int retsu, int haba, int takasa, int iro){

    for(int x = 0; x < takasa; x++){
        gamen(gyou, retsu, haba, iro);
        gyou += 1;
    }
}

void kenban() {
    unsigned char durum;
    unsigned char kei_koodo;
    
    static int kuusoru_gyou = 1;
    static int kuusoru_retsu = 0;

static const char klavye_haritasi[256] = {
   0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',

  't', 'y', 'u', '\xA1', 'o', 'p', '[', ']', '\n', '\f', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',

  '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, '\x98',

   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

   0, 0, 0, 0, 0, 0, 0, 0,           
};
    volatile char *video = (volatile char*)0xB8000;

    __asm__ __volatile__("inb %1, %0" : "=a"(durum) : "Nd"(0x64));
    
    if (!(durum & 1)) {
        return; 
    }
        
    __asm__ __volatile__("inb %1, %0" : "=a"(kei_koodo) : "Nd"(0x60));
    
    if (kei_koodo > 0 && kei_koodo < 0x80) {
        if (kei_koodo == 1) {
            __asm__ __volatile__("cli; hlt");
        }
        
        char harf = klavye_haritasi[kei_koodo];
        if (harf != 0) {
            video[(kuusoru_gyou * 80 + kuusoru_retsu) * 2] = harf;
            video[(kuusoru_gyou * 80 + kuusoru_retsu) * 2 + 1] = moji_iro;
            kuusoru_retsu++;

            if (kuusoru_retsu >= 80) {
                kuusoru_retsu = 0;
                kuusoru_gyou++;
            }
        }
    }
}
