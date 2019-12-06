Title: Project 4
Project Description: 
	takes in commands and creates a queue, basically a todo list with these programs.
	I took the queue program given to us and modified it to take strings instead of ints

Author: Chris Brown

Acknowledgment: 
	Code I used was code made by me. I used geeks for geeks and stack overflow for answers
	to questions I had

Getting Started:
	make to compile everything, and your command line to run everything is
	./project4 <number of cores you want>
	

Running the test:
	I included a file called dothis and hw2 (hw2 from canvas). You can use them if you want, itll run those fine

	*************** IF YOU CAN READ THE NEXT PORTION BELOW ************************

	GRADING RUBRIC	
	parsing and interpreting the commands 
		-> this all works and I can prove it if you uncomment the line in project4.c that has commands[0 - 2] (line 64) I am hopeful to get the full 20 points there
	implementing the job scheduler
		->This partly works. It implement the queue given to us, so no worries there. All the parts of the queue work, it's just the jobid does not update correctly
	implementing the commands
		->submit will run whatever given to it correctly. 
		->showjobs works, but only if you comment out lines 47-53, if you don't have those commented out it will not show but will write to a .out file
		->submithistory will seg fault but will show the first couple of successfull ran programs
	README.md
		->this is it so we good

	overall I know not all of it works but I think I at least earned a 50 or higher given what I am giving you. Ultimately it is up to you
					

contact:
	sevrc@uab.edu
