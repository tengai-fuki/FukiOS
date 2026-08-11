bits 16
org 0x7C00

start:
    cli

    xor ax, ax
    xor bx, bx

    mov bx, 0xB800
    mov ds, ax
    mov es, bx
    mov ss, ax
    mov sp, 0x7C00
    mov di, 0

    sti

    mov di, 0
    mov cx, 2000

    ekran:

    mov byte [es:di], ' '
    mov byte [es:di+1], 0x00
    add di, 2

    loop ekran

    mov di, 0
    mov cx, 80

    ust:

    mov byte [es:di], ' '
    mov byte [es:di+1], 0x70
    add di, 2

    loop ust

    mov di, 3840
    mov cx, 80

    alt:

    mov byte [es:di], ' '
    mov byte [es:di+1], 0x70
    add di, 2

    loop alt

    jmp jikan

    kaku:

    mov di, [si]
    add si, 2

    .kaku_maji:
    mov al, [si]
    cmp al, 0
    je .owatta

    mov byte[es:di], al
    mov byte[es:di+1], bl

    inc si
    add di, 2
    jmp .kaku_maji

    .owatta:
    ret

    jikan:

    mov ah, 0x02
    int 0x1A

    mov al, ch
    and al, 0x0F
    add al, '0'
    mov dl, al

    mov al, ch
    shr al, 4
    add al, '0'

    mov di, 3990

    mov byte[es:di], al
    mov byte[es:di+1], 0x70

    add di, 2

    mov byte[es:di], dl
    mov byte[es:di+1], 0x70

;-----------------------------------

    mov al, cl
    and al, 0x0F
    add al, '0'
    mov dl, al

    mov al, cl
    shr al, 4
    add al, '0'

    add di, 2

    mov byte[es:di], ':'
    mov byte[es:di+1], 0x70

    add di, 2

    mov byte[es:di], al
    mov byte[es:di+1], 0x70

    add di, 2

    mov byte[es:di], dl
    mov byte[es:di+1], 0x70

    mov si, messeji
    mov bl, 0x70
    call kaku

    mov si, jikan_msj
    mov bl, 0x70
    call kaku

    mov si, random
    mov bl, 0x05
    call kaku

    mov si, randomm
    mov bl, 0x05
    call kaku

    mov si, randommm
    mov bl, 0x05
    call kaku

    hang:
    jmp jikan

    messeji:
    dw 0
    db " FukiOS", 0

    jikan_msj:
    dw 3978
    db "jikan ", 0

    random:
    dw 160
    db "i'm super power bitch!!!", 0

    randomm:
    dw 320
    db "f4t1'i gotten sikin", 0

    randommm:
    dw 480
    db "Fuki said: f-f4t1 wo h-hentai, hanatte oite kudasai!!!", 0

    times 510-($-$$) db 0
    dw 0xAA55
