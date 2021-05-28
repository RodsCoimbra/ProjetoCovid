# Makefile do projeto covid

# escolha do compilador
CC= gcc
# flags para a compilação
CFLAGS= -Wall -std=c11 -g
# flags para linkar, incluíndo a biblioteca matemática
LDFLAGS= -lm
# gerar variáveis com listas de ficheiros, essenciais para a utilização do "makefile"
SRCS=$(wildcard *.c)	# contém todos os .c
OBJS = $(SRCS:.c=.o) # A variável objs é igual à variável srcs, mas substitui todos os .c por .o 
HEADERS=$(wildcard *.h)	# contém todos os .h
PDFS=$(wildcard *.pdf) # contém todos os .pdf

# nome do executável após fazer "makefile"
all: covid19

# compilar executável com optimização, dar o comando "make release"
release: CFLAGS+= -O3
release: clean
release: covid19


covid19: $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

# listar dependências. para simplificar, cada ficheiro .o depende do correspondente .c, de todos os ficheiros .h e da Makefile
%.o: %.c $(HEADERS) Makefile
	$(CC) -c $(CFLAGS) -o $@ $<

# para criar um tar.gz com todos os ficheiros, ao usar o comando "make tgz"
tgz: covid19.tar.gz

covid19.tar.gz: Makefile $(SRCS) $(HEADERS) $(PDFS)
	tar czvf $@ $^

# para forçar recompilação, dar o comando "make clean" e depois "make" ou o comando "make clean ; make"
clean:
	rm -f *.o covid19
