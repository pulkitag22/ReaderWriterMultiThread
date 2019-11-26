REQUIRED FILES INFORMATION:
	main.c - This is the main file, which consist of all the logic and whis is the file which gets build to object file.
	defiantions.h - this is the header file for main.c. This consist of all the header files required for main.c and all the function declarations and declaration of all the global variables.
	Makefile - for building the final object file of main.c. This consist of all the dependencies. Type the following commands in the terminal for:
		building - make all
		removing the build files - make clean
	In order to run the program, first type "make all", then, "main" file is created which can be run through "./main"
	
HOW TO COMPILE:
	Type "make all" in the directory where the above 3 files are there. The flow takes care of the dependencies.

HOW TO EXECUTE:
	Type "./main" to execute.

DESCRIPTION OF PROGRAM:
	The written program is an implementation of the classic reader-writer example using pthreads. In the given solution the writer tries to write an element in the shared buffer and reader tries to read an element from the shared buffer whenever the buffer is not emply. Readers are given priority over writers, so if there are mutiple writer threads but a single reader thread, reader thread executes first. This program uses the concepts of Mutexes and conditional variables in order to control the execution of the program.(Question.pdf)
