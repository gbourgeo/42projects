.name "lld"
.comment "coucou"

lld		%10000, r2
st		r2, 500
lld		%20000, r2
st		r2, 500
lld		%30000, r2
st		r2, 500
lld		%40000, r2
st		r2, 500
lld		%50000, r2
st		r2, 500
lld		10000, r2
st		r2, 500
lld		20000, r2
st		r2, 500
lld		30000, r2
st		r2, 500
lld		40000, r2
st		r2, 500
lld		50000, r2
st		r2, 500
lld		%0, r2
zjmp	%-7
st		r2, 500
lld		0, r2
zjmp	%-7
st		r2, 500
