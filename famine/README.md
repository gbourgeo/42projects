# FAMINE
*This project consist of creating a simple virus.*

### The Program
Famine is a binary that modifies one or more other binary (s) to apply it additional functionalities, without altering the initial behavior of said binary.

### Specifications
- The executable applies his "signature" to all binaries present in specific folders temporary.
- The "signature" have the form:
```
Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx
```
- Specific folders are '/tmp/test/' and '/tmp/test2/'.
- No output is done, at all.
- Only ONE infection is done on binaries.

- The program has been made on:
```
Linux debian 4.9.0.9-amd64 #1 SMP Debian 4.9.168-1+deb9u5 (2019-08-11) x86_64 GNU/Linux
```
- Works only on 64 bit system.

### Usage
```sh
$> git clone https://github.com/gbourgeo/42Projects
$> make -C 42Projects/famine
```

### How It Works
1. The program loop through all the directories contained in the `dir_all` variable.
2. The program then open each files in the given directories.
3. If the file is not an ELF 64bit executable, it goes to the next one.
4. If it is, the program check the executable headers sanity.
6. Get the Segment containing the ".text" section, otherwise, get the Segment of the executable entry point.
7. Check if the executable is already infected.
8. Save the old entry point to execute it at the end of this routine.
9. Write the new entry point.
10. Check if we have space to write our code at the end of the ".text" segment.
11. If not, change the offset of the section following the ".text" section (or the entry point section)
    and the offset of the following segments.
12. Finally, rewrite the binary.
  
If you are more comfortable with C, there is the C code of the assembler in the folder Ressources.

### Credits
Gilles BOURGEOIS

### :warning: WARNING :warning:
- A computer virus is a self-replicating automaton with a non-malicious base, but today often added malicious code (so classified as malicious software), designed to spread to other computers by inserting in software the legitimate, called "hosts". It can more or less disrupt the functioning of the infected computer. It can spread by any means of data exchange such as computer networks and CD-ROMs, USB keys, etc.
- This code is for pedagogical use only, I disclaim all responsibility when its use for malicious purposes.
