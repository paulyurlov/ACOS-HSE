        .section        .rodata
format:
        .string "%d %d %d\n"

        .text
        .global print_fib

print_fib:
        
        pushl   %ebp
        movl    %esp, %ebp
        movl    A, %eax
        addl    B, %eax
        movl    %eax, %edx
        addl    B, %edx
        movl    %edx, %ecx
        addl    %eax, %ecx
        pushl   %ecx
        pushl   %edx
        pushl   %eax
        pushl   $format
        call    printf
        addl    $8, %esp
        addl    $8, %esp
        popl    %ebp
        ret
