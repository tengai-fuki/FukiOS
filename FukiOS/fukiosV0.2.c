__asm__(
    ".code16gcc\n"
    ".section .boot, \"ax\"\n"
    ".global _start\n"
    ".intel_syntax noprefix\n"

    "_start:\n"
    "cli\n"

    "jmp 0x0000:duzelt\n"
    "duzelt:\n"
    
    "xor ax, ax\n"
    "xor bx, bx\n"
    "mov ds, ax\n"
    "mov es, ax\n"
    "mov ss, ax\n"
    "mov sp, 0x7C00\n"
    "mov di, 0\n"
    
    "sti\n"

    "mov [ondepo], dl\n"

    "mov si, offset paket\n"
    "mov ah, 0x42\n"
    "mov dl, [ondepo]\n"
    "int 0x13\n"

    "jmp fuki\n"

    ".global kuusoru_gyou\n"
    "kuusoru_gyou: .byte 12\n"
    
    ".global kuusoru_retsu\n"
    "kuusoru_retsu: .byte 12\n"

    "ondepo: .byte 0\n"
    "paket:\n"
    ".byte 0x10\n"
    ".byte 0\n"
    ".word 10\n"
    ".word 0x7E00\n"
    ".word 0x0000\n"
    ".quad 1\n"

    ".org 0x1fe\n"
    ".word 0xaa55\n"
    ".att_syntax prefix\n"
    ".text\n"
);

#define moji_iro 0x12

static int shouten_kondate = 0;

static inline void port_kaku(unsigned short port, unsigned char deta) {
    __asm__ __volatile__ ( "outb %0, %1" : : "a"(deta), "Nd"(port) );
}

static inline unsigned char port_yomu(unsigned short port) {
    unsigned char kekka;
    __asm__ __volatile__ ( "inb %1, %0" : "=a"(kekka) : "Nd"(port) );
    return kekka;
}

static inline void outb(unsigned short port, unsigned char val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline unsigned char inb(unsigned short port) {
    unsigned char kekka;
    asm volatile ( "inb %1, %0" : "=a"(kekka) : "Nd"(port) );
    return kekka;
}

static inline void bideo(int konum, char deger) {
    unsigned short eski_ds;
    __asm__ __volatile__ (
        "pushf\n"
        "cli\n"
        "mov %%ds, %0\n"
        "mov $0xB800, %%ax\n"
        "mov %%ax, %%ds\n"
        "movb %2, (%1)\n"
        "mov %0, %%ds\n"
        "popf\n"
        : "=&r"(eski_ds)
        : "b"(konum), "q"(deger)
        : "ax"
    );
}

void ivt_junbi();
void lpt_kontrol();
void tokei_koushin();
void sumasu(char iro);
void sentakushi_kirikae();
void kuusoru_idou(int hucre);
void gamen(int gyou, int retsu, int haba, int iro);
void kaku(int gyou, int retsu, char *mesaj, char iro);
void mado(int gyou, int retsu, int haba, int takasa, int iro);

void fuki(){
    ivt_junbi();
    sumasu(moji_iro);
    gamen(0, 0, 80, 0x70);
    gamen(24, 0, 80, 0x70);
    kaku(0, 1, "FukiOS", 0x70);
    kaku(0, 68, "sentakushi", 0x70);  

    while(1){
        tokei_koushin();
        lpt_kontrol();
    }
}

__attribute__((interrupt)) void kenban_isr(void *frame) {
    unsigned char kei_koodo;
    
    static int kuusoru_gyou __attribute__((section(".text"))) = 1;
    static int kuusoru_retsu __attribute__((section(".text"))) = 0;
    //static int shouten_kondate __attribute__((section(".text"))) = 0;

    static char keiboodo_chizu[256] __attribute__((section(".text"))) = {
   0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',

  't', 'y', 'u', '\xA1', 'o', 'p', '[', ']', '\n', '\f', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',

  '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, '\x98',

   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

   0, 0, 0, 0, 0, 0, 0, 0,           
}; 

    __asm__ __volatile__("inb %1, %0" : "=a"(kei_koodo) : "Nd"(0x60));

    if (kei_koodo & 0x80) {
    port_kaku(0x20, 0x20);
    return;
    }

    if (kei_koodo == 0x0F) {

        sentakushi_kirikae();
        port_kaku(0x20, 0x20);
        return;
    }

if (shouten_kondate == 0){

     char harf = keiboodo_chizu[kei_koodo];
        if (harf != 0) {

            if (harf == '\b') {

                if (kuusoru_retsu > 0) kuusoru_retsu--;
                else if (kuusoru_gyou > 1) { kuusoru_gyou--; kuusoru_retsu = 79; }
                
                bideo((kuusoru_gyou * 80 + kuusoru_retsu) * 2, ' ');
                bideo((kuusoru_gyou * 80 + kuusoru_retsu) * 2 + 1, moji_iro); 
                kuusoru_idou(kuusoru_gyou * 80 + kuusoru_retsu);
            } 

            else if (harf == '\n') {

                kuusoru_retsu = 0;
                kuusoru_gyou++;

                if(kuusoru_gyou >= 24){
                    kuusoru_gyou = 1;
                }
                kuusoru_idou(kuusoru_gyou * 80 + kuusoru_retsu);
            }
            
            else {

                bideo((kuusoru_gyou * 80 + kuusoru_retsu) * 2, harf);
                bideo((kuusoru_gyou * 80 + kuusoru_retsu) * 2 + 1, moji_iro);
                kuusoru_retsu++;

                if (kuusoru_retsu >= 80) { kuusoru_retsu = 0; kuusoru_gyou++; }
                kuusoru_idou(kuusoru_gyou * 80 + kuusoru_retsu);
            }
        }
    }
        port_kaku(0x20, 0x20); 
}


void ivt_junbi() {

    while (port_yomu(0x64) & 0x01) {
    port_yomu(0x60);
}
    unsigned short *ivt = (unsigned short *)0x00000;
    unsigned int isr_adres = (unsigned int)kenban_isr;
    
    __asm__ __volatile__("cli");
    ivt[9 * 2] = isr_adres & 0xFFFF;
    ivt[(9 * 2) + 1] = 0x0000;
    __asm__ __volatile__("sti");
}

void kaku(int gyou, int retsu, char *mesaj, char iro) {

    int sousai = ((gyou * 80 ) + retsu) * 2;
    
    int i = 0;

    while(mesaj[i] != 0){
        bideo(sousai, mesaj[i]);
        bideo(sousai + 1, iro);

        i++;
        sousai += 2;
    }
}

void bcd_kaku(int gyou, int retsu, unsigned char bcd, char iro) {
    
    int juusho = ((gyou * 80) + retsu) * 2;
    
    char juu = (bcd >> 4) + '0';
    char ichi = (bcd & 0x0F) + '0';
    
    bideo(juusho, juu);
    bideo(juusho + 1, iro);
    bideo(juusho + 2, ichi);
    bideo(juusho + 3, iro);
}

void sumasu(char iro){

    for(int i = 0; i < 80 * 25 * 2; i+=2 ){
        bideo(i, ' ');
        bideo(i + 1, iro);
    } 
}

void gamen(int gyou, int retsu, int haba, int iro){

    int sousai = ((gyou * 80) + retsu) * 2;

    for(int x = 0; x < haba; x++){

        bideo(sousai, ' ');
        bideo(sousai + 1, iro);
        sousai += 2;
    }
}

void mado(int gyou, int retsu, int haba, int takasa, int iro){

    for(int x = 0; x < takasa; x++){
        gamen(gyou, retsu, haba, iro);
        gyou += 1;
    }
}

void kuusoru_idou(int hucre) {
    port_kaku(0x3D4, 0x0F);
    port_kaku(0x3D5, hucre & 0xFF);
    port_kaku(0x3D4, 0x0E);
    port_kaku(0x3D5, (hucre >> 8) & 0xFF);
}

unsigned char rtc_yomu(unsigned char kiroku) {
    port_kaku(0x70, kiroku); 
    return port_yomu(0x71);
}

void tokei_koushin() {
    unsigned char ji = rtc_yomu(0x04);
    unsigned char fun = rtc_yomu(0x02);
    unsigned char byou = rtc_yomu(0x00);
    
    kaku(23, 149, "jikan", 0x70);
    bcd_kaku(23, 155, ji, 0x70);
    kaku(23, 157, ":", 0x70);
    bcd_kaku(23, 158, fun, 0x70);
    //kaku(23, 157, ":", 0x70);
    //bcd_kaku(23, 158, byou, 0x70);
}

void sentakushi_kirikae() {
    if (shouten_kondate == 0) {
        shouten_kondate = 1;
        kaku(0, 68, "sentakushi", 0x07);
    } else {
        shouten_kondate = 0;
        kaku(0, 68, "sentakushi", 0x70);
    }
}

void lpt_kontrol() {
    outb(0x378, 0xFF);

    outb(0x378, 0x01);

    outb(0x378, 0x00);
}
