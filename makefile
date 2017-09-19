#Christopher Snyder ICSI402 Programming Project 3 CS146375

p3: main.o initialize.o select.o numRows.o rowStat.o numCols.o colStat.o project.o runQueries.o
	gcc main.o initialize.o select.o numRows.o rowStat.o numCols.o colStat.o project.o runQueries.o -o p3

main.o: main.c structs.h
	gcc -c main.c

initialize.o: initialize.c structs.h
	gcc -c initialize.c

select.o: select.c structs.h
	gcc -c select.c

numRows.o: numRows.c structs.h
	gcc -c numRows.c

rowStat.o: rowStat.c structs.h
	gcc -c rowStat.c

numCols.o: numCols.c structs.h
	gcc -c numCols.c

colStat.o: colStat.c structs.h
	gcc -c colStat.c

project.o: project.c structs.h
	gcc -c project.c

runQueries.o: runQueries.c structs.h
	gcc -c runQueries.c

clean:
	rm -f *.o core p3
