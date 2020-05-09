.name "zork
      .lll" #tutu
.comment "just a basic living prog"
		
     l1: #comment
     l2:	sti r1, %:live, %9
	and	r1,%0,r1

ld :live, r2
live:
     live	%1
	zjmp %:live
