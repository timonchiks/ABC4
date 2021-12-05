
section .text

extern memcpy

strlen:
    ; Адрес сообщения уже загружен в rdi
    mov rcx, -1     ; ecx должен быть < 0
    xor al, al      ; конечный симврл = 0
    cld             ; направление обхода от начала к концу
    repne   scasb   ; while(msg[rdi]) != al) {rdi++, rcx--}
    neg rcx
    sub rcx, 2      ; ecx = length(msg)
    mov rax, rcx
    ret

;double CompareValue(void *l) {
;    int len = strlen((char*)l);
;    return (double) *(int*)(l + nameSize) / len;
;}
global CompareValue
CompareValue:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 12; двиагаем stack pointer на 12 вниз
    mov     [rbp - 8], rdi; сохраняем l
    call    strlen
    mov     [rbp - 12], eax; сохраняем длину  
    mov     rax, [rbp - 8]; записываем l
    cvtsi2sd        xmm0, [rax + 30]; берем creation_year и переводим в double
    cvtsi2sd        xmm1, [rbp - 12]; берем длину и переводим в double
    divsd   xmm0, xmm1; делим
    add     rsp, 12; возвращаем обратно stack pointer
    pop     rbp
    ret

; void ShellSort(void *c, int len)
;     for (int d = len / 2; d > 0; d /= 2)
;         for (int i = d; i < len; i++)
;             for (int j = i; j >= d && CompareValue(c + j * languageSize + intSize) < CompareValue(c + (j - d) * languageSize + intSize); j -= d) {
;                 void *tmp[languageSize];
;                 memcpy(tmp, c + j * languageSize, languageSize);
;                 memcpy(c + j * languageSize, c + (j - d) * (languageSize), languageSize);
;                 memcpy(c + (j - d) * (languageSize), tmp, languageSize);
;             }
global ShellSort
ShellSort:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 64; двигаем стек для хранения переменных
        mov     [rbp - 8], rdi; сохраняем l
        mov     [rbp - 12], esi; сохраняем len
        mov     eax, [rbp - 12]
        mov     ecx, 2
        cdq     ; расширяем eax для деления
        idiv    ecx
        mov     [rbp - 16], eax; сохраняем d
.outer_loop:                                ; =>This Loop Header: Depth=1
        cmp     dword [rbp - 16], 0; если d <= 0
        jle     .leave_outer_cycle; заканчиваем
        mov     eax, [rbp - 16]
        mov     [rbp - 20], eax; сохраняем i
.inner_loop:
        mov     eax, [rbp - 20]
        cmp     eax, [rbp - 12]; если i >= d
        jge     .step_outer_loop
        mov     eax, [rbp - 20]
        mov     [rbp - 24], eax; j = i
.inner_inner_loop:
        mov     eax, [rbp - 24]; j
        cmp     eax, [rbp - 16]; если j < d
        jl      .step_inner_loop
        mov     rdi, [rbp - 8]; кладем в первый аргумент l
        imul    eax, [rbp - 24], 50; j * language_size
        cdqe
        add     rdi, rax; c + j * language_size
        add     rdi, 4;  c + j * language_size + intSize
        call    CompareValue
        movsd   [rbp - 32], xmm0; сохраним CompareValue(c + j * language_size + intSize)
        mov     rdi, [rbp - 8]; делаем все то же самое для c + (j - d) * language_size + intSize
        mov     eax, [rbp - 24]
        sub     eax, [rbp - 16]
        imul    eax, eax, 50
        cdqe
        add     rdi, rax
        add     rdi, 4
        call    CompareValue
        movsd   [rbp - 40], xmm0; сохраним CompareValue(c + (j - d) * language_size + intSize)
        movsd   xmm0, [rbp - 32]
        ucomisd xmm0, [rbp - 40]; если cv1 < cv2
        jb      .swap; меняем местами элементы
        jmp     .step_inner_loop; иначе начинаем заново
.swap:
        mov     [rbp - 48], rsp; запомним место под tmp
        mov     rdi, rsp; первый аргумент - tmp
        add     rdi, -400
        mov     [rbp - 56], rdi
        mov     rsp, rdi
        mov     rsi, [rbp - 8]; c
        imul    eax, [rbp - 24], 50; j * languageSize
        cdqe
        add     rsi, rax; второй аргумент - c + j * languageSize
        mov     edx, 50; третий аргумент - languageSize
        call    memcpy; memcpy(tmp, c + j * languageSize, languageSize)
        mov     rdi, [rbp - 8]; c
        imul    eax, [rbp - 24], 50; j * languageSize
        cdqe
        add     rdi, rax ; первый аргумет - c + j * languageSize
        mov     rsi, [rbp - 8]; аналогичное вычисление c + (j - d) * (languageSize)
        mov     eax, [rbp - 24]
        sub     eax, [rbp - 16]
        imul    eax, eax, 50
        cdqe
        add     rsi, rax; второй аргумент - c + (j - d) * (languageSize)
        mov     edx, 50; третий аргумент - languageSize
        call    memcpy; memcpy(c + j * languageSize, c + (j - d) * (languageSize), languageSize)
        mov     rsi, [rbp - 56]; полностью аналогичный вызов memcpy(c + (j - d) * (languageSize), tmp, languageSize);
        mov     rdi, [rbp - 8]
        mov     eax, [rbp - 24]
        sub     eax, [rbp - 16]
        imul    eax, eax, 50
        cdqe
        add     rdi, rax
        mov     edx, 50
        call    memcpy; memcpy(c + (j - d) * (languageSize), tmp, languageSize);
.inner_inner_loop_step:        
        mov     ecx, [rbp - 16]; d
        mov     eax, [rbp - 24]; j
        sub     eax, ecx; j - d
        mov     [rbp - 24], eax; j = j - d;
        mov     rsp, [rbp - 48]; возвращаем стек обратно
        jmp     .inner_inner_loop
.step_inner_loop:
        mov     eax, [rbp - 20]; i
        inc     eax; i + 1
        mov     [rbp - 20], eax; i = i + 1
        jmp     .inner_loop
.step_outer_loop:
        mov     eax, [rbp - 16]; d
        mov     ecx, 2
        cdq
        idiv    ecx ; d / 2
        mov     [rbp - 16], eax; d /= 2;
        jmp     .outer_loop
.leave_outer_cycle:
        mov     rsp, rbp
        pop     rbp
        ret