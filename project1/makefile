cipher: project1.c
	gcc project1.c -o cipher
cipher.o: project1.c

test: test1 test2
test1:
	./cipher 1 abacaedi test1.txt test1.txt.enc > test1enc.o
	./cipher 2 abacaedi test1.txt.enc test1.txt.dec > test1dec.o
test2:
	./cipher 1 thisisakeyaz test2.txt test2.txt.enc > test2enc.o
	./cipher 2 thisisakeyaz test2.txt.enc test2.txt.dec > test2dec.o
