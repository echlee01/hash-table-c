ht : main.o hash_table.o
	gcc -Wall -o ht build/main.o build/hash_table.o -g

main.o: src/main.c src/hash_table.h
	gcc -Wall -c -o build/main.o src/main.c -g

hash_table.o: src/hash_table.c src/hash_table.h
	gcc -Wall -c -o build/hash_table.o src/hash_table.c -g

# dict: main.o read.o ll.o dict.o utils.o data.o k-d_tree.o
# 	gcc -Wall -o dict main.o read.o ll.o dict.o utils.o data.o k-d_tree.o -g

# main.o: main.c read.h k-d_tree.h
# 	gcc -Wall -c -o main.o main.c -g

# read.o: read.c read.h
# 	gcc -Wall -c -o read.o read.c -g
    
# ll.o: ll.c ll.h
# 	gcc -Wall -c -o ll.o ll.c -g

# dict.o: dict.c dict.h
# 	gcc -Wall -c -o dict.o dict.c -g

# utils.o: utils.c utils.h
# 	gcc -Wall -c -o utils.o utils.c -g

# data.o: data.c data.h
# 	gcc -Wall -c -o data.o data.c -g
	
# k-d_tree.o: k-d_tree.c k-d_tree.h
# 	gcc -Wall -c -o k-d_tree.o k-d_tree.c -g
