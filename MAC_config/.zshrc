# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '~/.zshrc'

autoload -Uz compinit promptinit
compinit -u
promptinit

setopt correctall
#keep background processes at full speed
setopt NOBGNICE
#restart running processes on exit
setopt HUP
#
setopt PROMPT_SUBST
#never ever beep ever
setopt NO_BEEP
#"running" `/etc` actually does a `cd /etc`
setopt AUTO_CD
#correct mistakes
setopt CORRECT
setopt AUTO_LIST
#allow tab completion in the middle of a word
setopt COMPLETE_IN_WORD
#tab completion moves to end of word
setopt ALWAYS_TO_END
setopt listtypes
# %1 killed. will show up exactly when it is killed.
setopt interactivecomments
unsetopt flowcontrol

setopt HIST_IGNORE_DUPS

# End of lines added by compinstall
if [ -f "${HOME}/.my_zshrc" ]; then
  source "${HOME}/.my_zshrc"
fi
# /etc/zshrc is sourced in interactive shells. It
# should contain commands to set up aliases, functions,
# options, key bindings, etc.
#
if [ -r /etc/profile ] ; then
. /etc/profile
fi

##zstyle ':completion:*:descriptions' format '%U%B%d%b%u'
zstyle ':completion:*:warnings' format '%BDésolé, pas de résultats pour : %d%b'
zstyle ':completion:*' menu select=2
zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
#
zstyle ':completion:*:rm:*' ignore-line yes
zstyle ':completion:*:mv:*' ignore-line yes
zstyle ':completion:*:cp:*' ignore-line yes
#

# Shell functions
setenv() { export $1=$2 } # csh compatibility
# Set prompts
autoload -U colors && colors
PROMPT='%{$fg[cyan]%}%T %{$fg[red]%}%n%{$fg[yellow]%}@%{$reset_color%}%M %{$fg[green]%}%~ %{$reset_color%}%' # default prompt
RPROMPT='%D %T' # prompt for right side of screen
#key setups
# bindkey SO HERE'S HOW I CONFIGURED THE PROMPT FOR ZSH:-v # vi key bindings
bindkey -e # emacs key bindings
bindkey ' ' magic-space # also do history expansion on space
#delete key
bindkey '\e[3~' delete-char
#home
bindkey '\e[1~' beginning-of-line
#m really dependent of th
#end
bindkey '\e[4~' end-of-line
#insert
bindkey '\e[2~' overwrite-mode
#tab completion
bindkey '^i' expand-or-complete-prefix
#pick your favorite editor
export EDITOR="emacs"
######## Apparence de l'autocompletion ##############
zstyle ':completion:*:descriptions' format '%U%B%d%b%u'
zstyle ':completion:*:warnings' format '%BDésolé, pas de résultats pour : %d%b'
zstyle ':completion:*' menu select=2
zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
#
zstyle ':completion:*:rm:*' ignore-line yes
zstyle ':completion:*:mv:*' ignore-line yes
zstyle ':completion:*:cp:*' ignore-line yes
#

# Shell functions
setenv() { export $1=$2 } # csh compatibility
# Set prompts
autoload -U colors && colors
PROMPT='%{$fg[cyan]%}%T %{$fg[red]%}%n%{$fg[yellow]%}@%{$reset_color%}%M %{$fg[green]%}%~ %{$reset_color%}%' # default prompt
RPROMPT='%D %T' # prompt for right side of screen
#key setups
# bindkey SO HERE'S HOW I CONFIGURED THE PROMPT FOR ZSH:-v # vi key bindings
bindkey -e # emacs key bindings
bindkey ' ' magic-space # also do history expansion on space
#delete key
bindkey '\e[3~' delete-char
#home
bindkey '\e[1~' beginning-of-line
#m really dependent of th
#end
bindkey '\e[4~' end-of-line
#insert
bindkey '\e[2~' overwrite-mode
#tab completion
bindkey '^i' expand-or-complete-prefix
#pick your favorite editor
export EDITOR="emacs"

export PATH=$HOME/homebrew/bin:$PATH