TARGET = tests/8.c

IMPORTS += binaryTree
IMPORTS += vector
IMPORTS += deque

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

INCLUDES = $(addprefix -I, $(IMPORTS))
OBJS = $(foreach IMPORT, $(IMPORTS), $(foreach S, $(call rwildcard, $(IMPORT), *.c), $(if $(findstring /tests/, $S), ,$S)))
HEADERS = $(foreach IMPORT, $(IMPORTS), $(foreach S, $(call rwildcard, $(IMPORT), *.h), $(if $(findstring /tests/, $S), ,$S)))

all: main
	
main:  $(TARGET) $(OBJS) $(HEADERS)
	gcc -o main $(TARGET) $(OBJS) $(INCLUDES) -lm -g

clean:
	rm -rf main