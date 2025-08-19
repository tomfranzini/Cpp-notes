# include <iostream>
# include <fstream>
using namespace std;

int main(  ){
    bool b;
    int count = 0;

    const char * ErrorCode = "ERROR: exiting the program.\n";

    //To store the name of the file
    char * name_of_file = new char[201], c, *s;

    cout << "Tell me the name of the file\n(NO SPACES and less than 200 characters) ";

    //Initialize name of file via standard input
    //this STOPS at the first space!! Everything else REMAIS IN THE BUFFER READY TO BE READ
    cin >> name_of_file;

    //Now I check what is left in the buffer
    do{
        //In case there are no spaces in the name, everything is read and c is \n
        c = cin.get(); //I get the next byte in the buffer

        cout<<'['<<c<<']'<<endl;

        b = c != ' ' && c != '\t' && c != '\n';

        //b is false if the name contained NO space
        //b is false also if there is a space or a tab
        cout<<b<<endl;

        if(b) break; //this will work ONLY when the char read is NOT a space
    }
    while(c != '\n');

    //if the name contained no spaces, then b is FALSE and c=\n will exit the loop

    //b is true ONLY IF there was a space or a tab and THEN other chars.
    if(b){
        cout << "Name of document contains spaces. "<< ErrorCode;
        return 1;
    }

    //Declaring input stream
    ifstream is(name_of_file);

    //Check if file exists
    if(!is){
        cout << "File " << name_of_file<<" not existing." << ErrorCode;
        return 2;
    }

    //Input the initial
    cout << "Which initial? ", cin >> c;

    //Check if the input was a letter
    if(c < 'A' || c > 'Z' && c < 'a' || c > 'z'){
        cout << "Give me a letter!" << ErrorCode;
        return 3;
    }

    while(true){ //Has to run forever because we don't know the number of lines
        //First I will check if the line starts with that letter if not I will skip that line
        while(is.peek() != c){
            is.ignore(20000, '\n'); //Ignoring the whole line and moving to teh next
            if(b == is.eof(  )) //In case the file ends I exit both loops
                break; //Exit 1
        }

        if(b) break;//Exit 2 if we are at the end of file

        //here I am at the beginning of an "ineresting" line
        streamsize this_line = is.tellg();

        is.ignore(20000, '\n'); //Ignore the line and skip at the first \n so now
                                //the index is AT THE BEGINNING of the new line
                                //
        streamsize next_line = is.tellg(); //new position

        is.seekg(this_line); //Move at the beginning of the line
                             //Everything before has been THROWN AWAY

        s = new char[next_line-this_line+2]; //Allocate for the name on this line
        is.getline(s, next_line-this_line, '\n'); //save the line in s
        ++ count; //increase count
        cout << s << '\n';
    }

    is.clear(); //This deactivates all warnings
    is.close();

    //In case there are no names in the file
    if(!count) cout << "No names/a\n";
}
