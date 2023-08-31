rnx2rtkp.exe:*.o
	gcc *.o -o $@
%.o:%.c
	gcc -c $< -o $@
	
clean:
	rm -f *.o rnx2rtkp.exe