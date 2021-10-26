LOGIN = xkeprt03
PROGS = tail wordcount wordcount-dynamic 
LIBS = libhtab.a libhtab.so
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -fPIC -O2
LIBS_OFILES = htab_hash_function.o htab_init.o create_htab_item.o free_htab_item.o htab_move.o htab_clear.o htab_free.o 
LIBS_OFILES += htab_lookup_add.o htab_erase.o htab_find.o htab_for_each.o print_htab_item_values.o htab_size.o htab_bucket_count.o
#CFLAGS += -fsanitize=address
#CFLAGS += -D HASHTEST
#CFLAGS += -D MOVETEST
#CFLAGS += -g

all: $(LIBS) $(PROGS)

-include dependencies

tail: tail.o
	$(CC) $(CFLAGS) -o $@ $^

%: %.c  
	$(CC) $(CFLAGS) "$@" "$^"

wordcount-dynamic: wordcount.o libhtab.so io.o			
	$(CC) $(CFLAGS) -o $@ $^

wordcount: wordcount.o libhtab.a io.o 		 		
	$(CC) $(CFLAGS) -o $@ -static $^ 

#staticka knihovna	
libhtab.a: $(LIBS_OFILES)
	ar crs $@ $^

#dynamicka knihovna
libhtab.so: $(LIBS_OFILES)
	$(CC) $(CFLAGS) -shared -o $@ $^

dependencies:
	gcc -MM *c >dependencies
	
pack:
	zip $(LOGIN).zip *.c *.h Makefile
	
clean:
	rm -f $(PROGS) *fifo *.o pocitadlo $(LIBS) dependencies

#########################################################################################
#testovaci prikazy, pro kontrolu pouzit C++ program ze zadani DU2
#soubory *.cc nemaji byt soucasti odevzdani
TESTPRG = wordcount-dynamic
TESTFILE = /usr/share/dict/words
compare: $(TESTPRG) pocitadlo
	mkfifo a_fifo b_fifo	
	LD_LIBRARY_PATH="." ./$(TESTPRG) <$(TESTFILE) | sort > a_fifo &	
	./pocitadlo <$(TESTFILE) | sort > b_fifo &	
	diff a_fifo b_fifo	
	rm -f *fifo	

run: wordcount-dynamic
	LD_LIBRARY_PATH="."	./wordcount-dynamic <$(TESTFILE)

pocitadlo: pocitadlo.cc
	g++ -std=c++11 -O2 -o pocitadlo  pocitadlo.cc