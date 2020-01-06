.name "add"
.comment ""

ld		%-5678, r2
ld		%6543, r4
add		r1, r2, r3
st		r3, 50
sub		r1, r4, r3
st		r3, 50
and		r1, r2, r3
st		r3, 50
or		r1, r4, r3
st		r3, 50
xor		r1, r4, r3
st		r3, 50
