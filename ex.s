.name "zork
      .lll" #tutu
.comment "just a basic living prog"

     l1: #comment
     l2:	sti r1, %:live, %9
	and	r1, %:l1,r1
ld :live, r1
live: 
     live	%214
	zjmp %:live
     
