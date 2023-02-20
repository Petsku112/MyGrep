MyGrep is a command-line based utility written in order to show what I have learned during the course and the state if my skills in writing C++ and it meets the requirements of the highest score possible for the project. The project is a simplified version of the grep utility that is found on Linux. The utility is capable of performing a string search within a given string, searching for text within a text file and searching for text within a text file with additional starting arguments.

The starting arguments that can be used with the MyGrep utility are as follows:

'-o’ - base for options to be added to. If this argument is used alone, it shows the
        variables list.
'-ol' - shows line numbering.
'-oo' - prints the number of occurrences of the search string.
'-or' - performs a reverse search.
'-oi' - makes the search case-insensitive.
If the MyGrep utility is used with no arguments, the user is prompted to input a string to search from and a string to search for. The program then searches for the string and outputs the position of the first occurrence of the search string in the target string.

If the MyGrep utility is used with two arguments and the second argument is '-o', a help page is outputted to the console.

If the MyGrep utility is used with more than two arguments, the program will search for the search string in a text file. The text file to search from is specified as the third argument. If the file could not be opened, the program informs the user. If the file was opened, the program goes through every line of the file and outputs the lines that contain the search string.

If the MyGrep utility is used with four arguments and the second argument starts with '-o', the program will search for the search string in a text file with additional arguments. The third argument specifies the file to search from, while the fourth argument is the search string. If the search string is found within the file, the program outputs the line that contains the search string. The starting arguments '-ol', '-oo', '-or', and '-oi' can be used to further modify the search.

Created by: Petteri Laukkanen