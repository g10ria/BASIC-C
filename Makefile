compile=gcc
buildDir=bin
headersDir=headers

deps = headers/interpreter.h hashmap/headers/hashmapLite.h

obj = interpreter.o scanner/scanner.o parser/evals.o parser/parser.o hashmap/hashmapLite.o hashmap/hashfunctions.o

%.o: %.c
	$(compile) -c -o $@ $<

interpreter: $(obj)
	$(compile) -o ${buildDir}/$@.bin $^ -I/$(headersDir)