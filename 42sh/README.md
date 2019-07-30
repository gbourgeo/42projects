# 42SH

*Advanced shell*

## USAGE

```sh
$> make && ./42sh
```

## BEHAVIOUR

42sh is in the continuity of the [**minishell**](https://github.com/gbourgeo/42projects/tree/master/minishell) and [**21sh**](https://github.com/gbourgeo/42projects/tree/master/21sh) project with,
obviously, new features :

### From Minishell
1. A prompt.
2. Command execution with parameters and PATH management.
4. Errors managed without **errno** and good return values.
5. Whitespaces management.

### From 21sh
1. Line Edition.
2. Redirection and Aggregation operators.
3. Pipes.
4. Separators.

#### 1. Builtins
Most of them are POSIX:
- cd
- echo
- exit
- type
- export
- set (partially-posix)
- unset (partially-posix)
- jobs
- fg
- bg
- alias
- unalias
- test

#### 2. Logical Operators
- &&
- ||

#### 3. Intern Variable
- Using the syntax : **name=value**
- Exporting them with the builtin **export**
- List them with the builtin **set**
- Removing them with the builtin **unset**
- Temporary environment variable like **HOME=/tmp cd**
- Parameter Expansion with **${}**
- Special Parameter Expansion like **?** or **@** (see http://pubs.opengroup.org/onlinepubs/9699919799/ Shell&Utilities -> 2.5.2 for a full list of them)

#### 4. Job Control

Handled with the Builtins: jobs, fg, bg and the Operator: &.

#### 5. Signals
Fully handled.

#### 6. Inhibitors
- " (double quote)
- ' (single quote)
- \\ (backslash)

#### 7. Globing
- \*
- ?
- \[]
- !

#### 8. Expansions
- ~
- ${parameter:-word}
- ${parameter:=word}
- ${parameter:?word}
- ${parameter:+word}
- ${#parameter}
- ${parameter%}
- ${parameter%%}
- ${parameter#}
- ${parameter##}

#### 9. Command Substitution
- $(...)

#### 10. Dynamic Completion
Contextual Dynamic Completion of
- commands
- built-ins
- files
- intern and environment variable

#### 11. Alias
Alias management via built-ins **alias** and **unalias**

#### 12. Test
Built-in **test** with the operators -b, -c, -d, -e, -f, -g, -L, -p, -r, -S, -s, -u, -w, -x, -z, =, !=, -eq, -ne, -ge, -lt, -le, !.

#### 13. POSIX compliance
[POSIX](http://pubs.opengroup.org/onlinepubs/9699919799/)

## AUTHORS

- **:rocket:** [Rémy FONTAINE](https://github.com/remyft)
- :sparkling_heart: [Dorian BAFFIER](https://github.com/dbaffier) :sparkling_heart:
- :princess: [Tsitsi SADAGHASHVILI](https://github.com/tsitsi314) 
- :fire: [Gilles BOURGEOIS](https://github.com/gbourgeo) 
