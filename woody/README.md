# WOODY
Simple packer

## RESUME
First of all, the executable will encrypt a program passed as a parameter.
64 bits are handled by default.
A newly program, named **woody**, will be created. When this new program will be executed,
it will have to decipher to be able to launch.
Its execution will be identical in every respect with the first program passed in parameter
in the previous step.

## BEHAVIOUR
+ The executable name is **woody_woodpacker**.
+ The executable take as parameter a bianry file (64 bits by default).
+ The executable create a second executable, **woody**, at the end of its execution.
+ The algorithm choosen for encryption: TEA (Tiny Encryption Algorythm).
+ The cipher key holds on 128 bits and will be printed on the standart output.
+ **Woody** will print "....WOODY...." followed by a new line, to indicate that the binary is decrypted.
+ **Woody** then execute the program infected like nothing happened.

## BONUS

+ The text printed can be modified as second parameter of the initial program.
+ Support of ELF 32 bits.
+ Support of Mach-O 64 Bits.
+ Optimization of the algorithm used via the assembler.

## USAGE
+ File used to test
```sh
$> cat Ressources/sample.c
#include <stdio.h>

int main(void) {
	printf("Hello, World!\n");
	return (0x0);
}
```
+ Binaries created to test
```sh
$> make elf64
or
$> make elf32
or
$> make macho64
```

+ Compilation for ELF 64 bit executables
```sh
$> make
$> ./woody_woodpacker elf32
woody_woodpacker: Invalid ELF Class (64 bit only).
$> ./woody_woodpacker elf64
$> ./woody
....WOODY....
Hello, World!
$> ./woody_woodpacker macho64
woody_woodpacker: Invalid ELF file architecture.
```

+ Compilation for ELF 32 bit executables
```sh
$> make BIT32=1
$> ./woody_woodpacker32 test32
$> ./woody
....WOODY....
Hello, World!
$> ./woody_woodpacker test64
woody_woodpacker: Invalid ELF Class (32 bit only).
$>
```

## AUTHOR(S)
+ gilles Bourgeois
