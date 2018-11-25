
V6SH = inode.c main.c util.c

v6sh:	$(V6SH)
	gcc $(V6SH) -o v6sh

run:
	./v6sh

clean:
	rm -rf ./v6sh
