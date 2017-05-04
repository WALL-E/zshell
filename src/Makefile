all: zshell md5sum

zshell:main.c
	gcc main.c -O3 -o zshell -lcrypto
	strip zshell

md5sum:md5sum.c
	gcc md5sum.c -lcrypto -o md5sum

install:
	cp zshell ../bin
	cp md5sum ../bin

clean:
	rm -f zshell md5sum
