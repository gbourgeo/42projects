.name		"Clownito"
.comment	"Los Santos del Pablos muchos Clownitos del tacos y nachos ranchos con Sergio Ramos"

fork %:shotgun
live:
	live	%2
	zjmp	%:live

shotgun:
	ldi		%7, %:shotgun, r2
	st      r2, 256
	live	%2
	st		r3, 256
