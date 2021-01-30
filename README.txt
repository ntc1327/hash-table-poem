Author: Noah Cribelar
Date Completed: 3/11/19

PROGRAM SUMMARY

This program reads in a given text file to a hash table that uses a form of external chaining to recognize all the unique words in the table and counts duplicates of the words in order to give a word count. The hash table is then sorted both alphabetically and reverse numerically with the word displayed with its associated count. 

INVOKING THE PROGRAM

After unzipping the zip file, the program can be run using make commands.

Use "make" to compile the program from the command line, and after running make, use "make run" to execute the program.

The program will ask the user to choose which file they want to use, if what the user types in does not match either of the file names, then an error message will be given asking the user to provide an appropriate file.

Use enter to progress through the program should it seem execution stops, the program will also prompt the user to press enter after they input the text file.

Use "make clean" to remove any object file after one is finished with executing the program. If one wants to execute after running make clean, simply enter "make" again and use "make run" again to execute.


PROGRAM INPUT

The only input necessary is the selection of the text file and pressing enter to advance after that point. Valid text file names are "paper.txt" and "poem.txt". It is also described in the program how to input the files.


PROGRAM OUTPUT

Output will be instructions showing the user how to enter in files, prompts to continue, and two lists of words sorted by alphabetical order and reverse numerical order. A sample of outputs when run on both files can be found in output1.txt and output2.txt, which are included in the zip file.


ADDITIONAL NOTES

I made the decision to use ASCII values to help with reading characters and removing punctuation after reading Dr. Finkel's e-mail about it.

I made the decision to use external chaining after reading Dr. Finkel's e-mail about how to use the counts within the nodes and increment them if you see that word again in the file. I believe I mentioned this email to both Jackson Danna and Evan Shepherd as well, so if they use that method as well, they learned of it first from me.

After struggling to begin implementing a QuickSort or heapsort, I first implemented insertion sorts for both the alphabetical and reverse numerical sort. I got the reverse numerical insertion sort working at first but could not get an alphabetical sort working, which is when Jackson Danna reccomended to use a selectionsort to deal with what I perceived to be issues with pointers not being implemented correctly in my insertion sort (To be precise, I believe null values were being pointed to, more on that in a bit). He also reccomended checking the ASCII values of the first character in the string and converting them to lower case to help when comparing the strings, so I credit that to him. 

I had implemented both a working alphabetical sort and reverse numerical sort by Friday morning when tested on The Raven, but when I brought in my second text file to test, the alphabetical sort worked but the insertion sort for the reverse numerical sorting gave me a segmentation fault. I messed with it for the greater part of the day and tried debugging using GDB, but ultimately I determined that it would take longer to find the issue with my insertion sort and just make a selection sort for the reverse numerical sorting as well. There was some weird error that neither me nor upper-level student Matthew Thompson could figure out, whether it was with the text file, or in my estimation, a weirdly read-in value that caused the insertion sort to believe it was looking at a null node. Whatever the cause, I implemented a selection sort based on what I had for my alphabetical sort and was finished with it.

Jackson Danna and I both whiteboarded together the process on the function that helps split strings that contained two words in them. We figured out the cases we needed to consider in splitting the strings and went our seperate ways to implement them. I made a change when the email about the clarification about when to remove punctuation came out to just keep the string as one in some cases, such as turning "demon's" into "demons".
