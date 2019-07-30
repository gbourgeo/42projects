# MINISHELL
*Simple shell*

This project is a mini interpreter of UNIX commands.

# USAGE
```sh
$> make && ./minishell
```

# BEHAVIOUR

#### 1. Prompt
- Gives user name and current directory position :
```sh
<gbourgeo@~/42/minishell> 
```
#### 2. Commands
- Simple commands, no pipes or redirections or more complex functions.

#### 3. Execution
- Command execution are manage by the environment variable **PATH**.

#### 4. Errors
- *errno** is forbidden, all errors are managed manually.

#### 5. Environment
- Fully manage environment ( by copy of "extern char **environ" ).

#### 5. Builtins
Manage of a set of built-ins (POSIX compliant) :
- echo
- cd
- setenv
- unsetenv
- env
- exit

#### 6. Expansions
Manage of the expansion (POSIX compliant) :
- $
- ~

#### 7. Reference
I used *bash* as my shell reference.

# AUTHOR
- [Gilles BOURGEOIS](https://github.com/gbourgeo)
