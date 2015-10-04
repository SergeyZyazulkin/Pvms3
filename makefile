proc=0

all: make

make:
	mkdir -p out
	gcc src/client.c -o out/client.out
	gcc src/server.c -pthread -Dproc=$(proc) -o out/server.out
clean:
	rm -rf out
