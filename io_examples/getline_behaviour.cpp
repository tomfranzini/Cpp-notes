# include <iostream>
using namespace std;

int main( ){
    //Defin a pointer to char and initialize to an array of 20 chars
    char *p = new char[20];

    //Using standard input (keybord) I extract and save in p.
    //The second argument will STOP get after the first 8 bytes
    cin . getline(p, 9);

    cout << p << '\n';

    //If the stream was longer, cin has been falisified. Tehrefore
    if(!cin) cout << "Stream was longer than what I extracted...\n";
}
