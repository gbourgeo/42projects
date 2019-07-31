# 21SH

*Intermediate shell*

This project is an introduction to command interpreter, lexical, syntactic and semantic rules

## USAGE

```sh
$> make && ./21sh
```

## BEHAVIOUR

21sh is in the continuity of the [**minishell**](https://github.com/gbourgeo/42projects/tree/master/minishell) project with,
obviously, new features :

#### 1. Line Edition ( TERMCAPS )
- Use the left and right arrow to move the cursor on the command line.
- Edit the line where the cursor is.
- Use the up and down arrows to navigate the command history.
- Shift + LEFT | RIGHT : Select character(s) from command line at cursor position.
- Alt + X : Cut the selected characters from the command line.
- Alt + C : Copy the selected characters from the command line.
- Alt + V : Paste at cursor position.
- Alt + LEFT  : Move by 'words' to the left.
- Alt + RIGHT : Move by 'words' to the right.
- HOME    : Goes to the begining of the line.
- END     : Goes to the end of the line.

#### 2. Ctrl + C | Ctrl + D

#### 3. Command Separator
- ;
- &&
- ||

#### 4. Pipes
```sh
$> ls | cat -e | wc -l
```

#### 5. Redirections
- <
- \>
- <<
- \>>

#### 6. Aggregations of file descriptors
- 2>&1
- \>&-
- 2>/dev/null
- ...

#### 7. Quotes
- Fully handling single and double quotes, on a single or multiple lines.

## AUTHORS

- [Gilles BOURGEOIS](https://github.com/gbourgeo)
- [Remy FONTAINE](https://github.com/remyft)
