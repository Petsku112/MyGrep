/* MyGrep Project
	Made by Petteri Laukkanen

	This is a simple version of the grep utility found in linux.
	This project meets the reguirements of the highest score available for this project.
	
	With mygrep you can:
	search for text in a given string.
	Usage:
	mygrep [string to search for] [string to search from]

	search for text in a textfile.
	Usage: mygrep [string to search for] [file to search from]

	search for text in a textfile with added starting arguments:
	Usage: mygrep -o[arguments to be used] [string to search for] [file to search from]
	For example: mygrep - olo  following man_grep_plain_ASCII.txt

	list possible arguments and their syntax (kind of a help page)
	Usage mygrep -o
	
	Possible variables:
			
			-o	base for options to be added to. (If alone shows this Variables list)
			-ol	Show line numbering
			-oo	Print amount of occurences
			-or	Reverse search
			-oi	Make search case insensitive


*/
#include <iostream>
#include <fstream>
#include <string>
#include<clocale>
#include <algorithm>

using namespace std;

//Giving main two arguments, argc (how many arguments are present) and argv (what those arguments are)
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "finnish");
	
	string search;	//Storing string that user wants to search for
	string target;	//Storing string that user wants to search from

	//if the value of argc is one (mygrep command was executed with no parameters)
	if (argc == 1) {

		//Asking user for string from which to search from and using get line to get the entire string that was inputted.
		cout << "Give a string from which to search for: ";
		getline(cin, target);

		//Asking user for string to find and using get line to get the entire string that was inputted.
		cout << "Give search string: ";
		getline(cin, search);


		size_t found = target.find(search); //Finding the the position of the first occurence of search in target and storing it in found.

		//If the value of found is not npos meaning that the search string was found in the target.
		if (found != string::npos) {
			
			//Output the what was found and in what position.
			cout << "\n\"" << search << "\" found in \"" << target << "\" position " << found;
		}

		//If the string wasn't found, inform user that the search string wasn't found in the target string.
		else {
			cout << "\n\"" << search << "\" NOT found in \"" << target << "\"";
		}
	}
	//else if the value of argc c is 2 and the second argument is -o (mygrep -o), output help "page" 
	else if (argc == 2 && string(argv[1]) == "-o") {
			cout << "\nVariables\n\n";
			cout << "Usage:\n";
			cout << "mygrep -o[Variables to be used] [text to search for] [file to search from]\n";
			cout << "For example: mygrep - olo  following man_grep_plain_ASCII.txt\n\n";
			cout << "Variables can be stacked!\n";
			cout << "List of possible variables:\n";
			cout << "-o	base for options to be added to.\n	If alone shows this Variables list.\n\n";
			cout << "-ol	Show line numbering\n";
			cout << "-oo	Print amount of occurences\n";
			cout << "-or	Reverse search\n";
			cout << "-oi	Make search case insensitive";
	}

	//else (There are more than 2 arguments)
	else {
		string filename;	//Filename to be opened
		ifstream file;		//ifstream variable for storing the file where to search from.
		string variables = argv[1];	//Storing the second argument from argv to string variables (array starts from 0)
			
			//If valua of argc is 3
			if (argc == 3) {
				search = argv[1];		//Store second variable in search
				filename = argv[2];		//Store third variable in filename
				file.open(filename);	//Open file with the name stored in filename

				//(Special case) //If the file couldn't be opened (Name was incorrect or the file doesn't exist / is corrupted, inform the user
				if (file.fail()) {
					cerr << "Error opening file!\nMake sure that the filename was correct and that you have access to the file.";
					return 0;
				}

				string line;	//String to store current line that is being compared to string search

				//While there are new lines to go through in file (Goes through every line of the file)
				while (getline(file, line)) {

					//If the search finds the string search in the file, output the line that contained the search string
					if (line.find(search) != string::npos) {
						cout << line << endl;
					}

				}
			}

			//If value of argc is 4 and the variable called variables starts with -o (Testing for correct syntax)
			if (argc == 4 && variables.substr(0, 2) == "-o") {

				//Create booleans for all possible starting arguments
				bool l = false;
				bool o = false;
				bool r = false;
				bool i = false;

				size_t pos = 1;		//Variable for storing position while searching for the occurence of the letter "o" starting from 1 because postion 0 never contains an "o"
				int count_o = 0;	//Store how many time o has been found

				//While pos is not npos (the current position doesn't have an "o")
				while (pos != string::npos) {
					count_o++;								//Add 1 to count_o
					pos = variables.find('o', pos + 1);		//find "o" in the argument starting from position pos + 1 (Starting search after first "o" that is always there 
				}

				//Testing for which variables should be active.
				
				//if the previous while loop found a second "o" in the argument set boolean o to true
				if (count_o > 1) {
					o = true;
				}

				//If there is an "l" in the variables string, set l to true
				if (variables.find('l') != string::npos) {
					l = true;
				}

				//If there is an "r" in the variables string, set r to true
				if (variables.find('r') != string::npos) {
					r = true;
				}

				//If there is an "i" in the variables string, set i to true
				if (variables.find('i') != string::npos) {
					i = true;
				}

				int line_number = 1;	//Store line where the search is currently
				int line_count = 0;		//Store how many times the search string has been found
				search = argv[2];		//String to search for is the third argument given
				filename = argv[3];		//Filename of file to search from is the fourth argument given
				file.open(filename);	//Open file with the name in "filename"

				//(Special case) If the file couldn't be opened (Name was incorrect or the file doesn't exist / is corrupted, inform the user
				if (file.fail()) {
					cerr << "Error opening file!\nMake sure that the filename was correct and that you have access to the file.";
					return 0;
				}
				string line;					//Store current line
				string line_copy;				//Store copy of current line to restore original format
				string search_copy = search;	//Store copy of the search string to restore original format

				//If r (reverse search) was not in the parameters
				if (r == false) {

					//Get every line in the file one by one until at the end of the file
					while (getline(file, line)) {

						line_copy = line;		//Store the current line into line_copy

						//If i (case insensitive) was in the parameters
						if (i == true) {

							//Make every character of the search and line strings lowercase (enables searching case insensitively)
							transform(search.begin(), search.end(), search.begin(), ::tolower);
							transform(line.begin(), line.end(), line.begin(), ::tolower);
						}

						//if the current line contains the search string
						if (line.find(search) != string::npos) {

							//If l (line numbering) was in the parameters
							if (l == true) {
								
								//Output the current line number
								cout << line_number << ":	";
							}
							cout << line_copy << endl; //Output the current line from line_copy so upper case letters are shown correctly
							line_count++;			   // Add one the the amount of linus that have included the search string
						}
						line_number++;				   //Add one to the current line number

					}

					//If o (Occurences) was in the parameters
					if (o == true) {
						
						//Output the amount of lines that contained the search string
						cout << "\nOccurences of lines containing \"" << search_copy << "\": " << line_count;
					}
				}

				//If r (reverse search) was in the parameters
				else if (r == true) {

					//Get every line in the file one by one until at the end of the file
					while (getline(file, line)) {
						line_copy = line;		//Store the current line into line_copy

						//Make every character of the search and line strings lowercase (enables searching case insensitively)
						if (i == true) {
							transform(search.begin(), search.end(), search.begin(), ::tolower);
							transform(line.begin(), line.end(), line.begin(), ::tolower);
						}

						//If current line include search string
						if (line.find(search) == string::npos) {

							//If l (line numbering) was in the parameters
							if (l == true) {

								//Output line number before every line
								cout << line_number << ":	";
							}
							cout << line_copy << endl; //Output the current line from line_copy so upper case letters are shown correctly
							line_count++;			   //Add one the the amount of lines found containing the search string
						}
						line_number++;				   //Add one to the current line number

					}
						//Output how many rows NOT containing the search string were in the file
						cout << "\nOccurences of lines NOT containing \"" << search_copy << "\": " << line_count;
					}
				}


			}
		
}