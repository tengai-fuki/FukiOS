bits 16
org 0x7C00

start:
    cli
    
    xor ax, ax
    xor dx, dx
    xor bx, bx
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    mov di, 0
    
    sti

    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 0x02
    mov dh, 0
    mov bx, 0x7E00
    int 0x13
    jc disc_error

    jmp main

    times 510-($-$$) db 0
    dw 0xAA55

    main:

    mov bx, 0xB800
    mov es, bx

    call gamen
    jmp jikan

    disc_error:
    jmp $

    gamen:

    mov di, 0
    mov cx, 2000
    mov al, ' '
    mov ah, 0x00
    call enogu

    mov di, 0
    mov cx, 80
    mov al, ' '
    mov ah, 0x70
    call enogu 

    mov di, 3840
    mov cx, 80
    mov al, ' '
    mov ah, 0x70
    call enogu

    jmp jikan

    enogu:

    mov byte [es:di], al
    mov byte [es:di+1], ah
    add di, 2

    loop enogu

    ret

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

;-----------------------------------    

    mov si, messeji
    mov bl, 0x70
    call kaku

    mov si, jikan_msj
    mov bl, 0x70
    call kaku

;-----------------------------------

    mov ah, 0x01
    int 0x16
    jz jikan

    mov ah, 0x00
    int 0x16

    mov di, [kuusoru]
    mov byte [es:di], al
    
    mov bh, [moji_iro]
    mov byte [es:di+1], bh

    add di, 2
    mov [kuusoru], di
                                                                 
    hang:
    jmp jikan

    moji_iro:
    db 0x15

    kuusoru:
    dw 160

    messeji:
    dw 0
    db " phobOS", 0

    jikan_msj:
    dw 3978
    db "jikan ", 0
        
   times 10240-($-$$) db 0
