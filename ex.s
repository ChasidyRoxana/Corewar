.name "zork
      .lll" #tutu
.comment "just a basic living prog"

     l1: #comment
     live %1
     l2:	sti r1, %:live, %9
	and	r1, %:l1, r1
ld :live, r1
live: 
     live	%-21454768967346896796438768
	zjmp %:live
     
