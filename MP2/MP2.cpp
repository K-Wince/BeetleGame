/* MP2.cpp : 10.20.2021 : Kaden Wince
*  Description: This program lets 2 users play a game against each other called "BEETLE", in which they roll a die which corresponds to a
*  certain body part of the beetle and they compete to see who can build their beetle first while deciding whether to build or consume the
*  other beetle.
*/

// Needed Includes
#include <iostream>
#include <string>
using namespace std;


// Declaration of Function Prototypes
int  rollDie();
bool isBodyPart(string currentBody, char c);
bool isBeetleComplete(string currentBody);
char getUserInput();
char convertDieToPart(int roll);
string convertPartToBody(char part);
void printBody(string str);
void showLogo();
bool addPart(string& body, char part);
bool removePart(string& body, char part);
void endScreen(string pName);



void main() {

    // Declaration of Variables
    string p1Body = "             "; // init to 13 spaces
    string p2Body = "             ";
    string p1 = "";
    string p2 = "";
    bool done = false;
    bool player = false;             // player 1 = false, player 2 = true

    srand(time(0));                  // Sets the srand generation to be random

    // Start the Game and then get the player's names
    showLogo();
    cout << "What is the name of Player 1? ";
    cin >> p1;
    cout << "What is the name of Player 2? ";
    cin >> p2;
    system("pause"); // Pauses game so it doesn't jump right in
    system("CLS");   // Clears screen to allow for maximum screen real estate
    
    while (!done) {
        // Rolls the die for the current player then converts it to the body part
        int currentDieRoll = rollDie();
        char part = convertDieToPart(currentDieRoll);
        string bodyPart = convertPartToBody(part);

        // Asks the player what they want to do during their turn
        if (!player) { cout << p1; } else { cout << p2; }
        cout << ", would you like to build on to your own beetle or consume the others?(B or E) ";
        char answer = getUserInput();

        // Tells the player what body part they rolled
        if (!player) { cout << p1; } else { cout << p2; }
        cout << ", your rolled body part is: " << currentDieRoll << ". " << bodyPart << endl;

        // If the answer is to build, it adds the body part or if it can't it says the beetle already has that part
        if (answer == 'B') {
            if (!player) { // Player 1
                if (part == 'E' || part == 'A') {  // If its an antenna or eye check if head is there
                    if (isBodyPart(p1Body, 'H')) {
                        bool success = addPart(p1Body, part);
                         if (success)  { cout << "Your beetle has been built onto.\n"; }
                         if (!success) { cout << "Your beetle already has that part.\n"; }
                    }
                    else {
                        cout << "Sorry, your beetle does not have a head.";
                    }
                }
                else if (part == 'L' || part == 'T' || part == 'H') { // If Its a leg, tail, or head then check if the body is there
                    if (isBodyPart(p1Body, 'B')) {
                        bool success = addPart(p1Body, part);
                        if (success) { cout << "Your beetle has been built onto.\n"; }
                        if (!success) { cout << "Your beetle already has that part.\n"; }
                    }
                    else {
                        cout << "Sorry, your beetle does not have a body yet.";
                    }
                }
                else {  // If its body then add it
                    bool success = addPart(p1Body, part);
                    if (success) { cout << "Your beetle has been built onto.\n"; }
                    if (!success) { cout << "Your beetle already has that part.\n"; }
                }
            }
            if (player) {  // Player 2
                if (part == 'E' || part == 'A') {
                    if (isBodyPart(p2Body, 'H')) { // If its an antenna or eye check if head is there
                        bool success = addPart(p2Body, part);
                        if (success) { cout << "Your beetle has been built onto.\n"; }
                        if (!success) { cout << "Your beetle already has that part.\n"; }
                    }
                    else {
                        cout << "Sorry, your beetle does not have a head.";
                    }
                }
                else if (part == 'L' || part == 'T' || part == 'H') { // If Its a leg, tail, or head then check if the body is there
                    if (isBodyPart(p2Body, 'B')) {
                        bool success = addPart(p2Body, part);
                        if (success) { cout << "Your beetle has been built onto.\n"; }
                        if (!success) { cout << "Your beetle already has that part.\n"; }
                    }
                    else {
                        cout << "Sorry, your beetle does not have a body yet.";
                    }
                }
                else { // If Its a leg, tail, or head then check if the body is there
                    bool success = addPart(p2Body, part);
                    if (success) { cout << "Your beetle has been built onto.\n"; }
                    if (!success) { cout << "Your beetle already has that part.\n"; }
                }
            }
        }

        // If the answer is to consume, then checks whether they can eat it or not and then removes if so
        if (answer == 'E') {
            if (part == 'H' || part == 'B') {
                cout << "Sorry, you are unable to eat that body part.\n";
            }
            else {
                if (!player) { // Player 1
                    if (isBodyPart(p2Body, part)) {
                        removePart(p2Body, part);
                        cout << "You have consumed the other beetle's " << bodyPart << ".\n";
                    }
                    else {
                        cout << "Sorry, the other beetle does not have that part.\n";
                    }
                }
                if (player) {  // Player 2
                    if (isBodyPart(p2Body, part)) {
                        removePart(p2Body, part);
                        cout << "You have consumed the other beetle's " << bodyPart << ".\n";
                        
                    }
                    else {
                        cout << "Sorry, the other beetle does not have that part.\n";
                    }
                }
            }
        }
        
        // Prints the players beetle after adding or removing parts
        if (!player) { printBody(p1Body); }
        if (player) { printBody(p2Body); }
        system("pause");
        system("CLS");

        // Checks whether the beetle is complete and if so then ends the game and shows the win screen, otherwise it prepares for next player
        if (!player && isBeetleComplete(p1Body)) {
            done = true;
            system("CLS");
            endScreen(p1);
            system("pause");
        }
        else if (player && isBeetleComplete(p2Body)) {
            done = true;
            system("CLS");
            endScreen(p2);
            system("pause");
            
        }
        else {
            player = !player; // Swithces the current player for the next turn
        }

    }

}

/**
 rollDie Function - Calculates a random number for use in the program to act similar to a die
 @return n -- whatever random number that the function calculated
 */
int rollDie() {
    int n = rand() % 6 + 1;
    return n;
}

/**
 isBodyPart Function - checks the given string(Player Body) to see if there is a certain given character(Body Part) in it
 @param currentBody -- the player's body that you want to check
 @param c -- the body part that you want the function to check for
 @return boolean -- returns whether the body part has(true) that part or not(false)
 */
bool isBodyPart(string currentBody, char c) {
    for (auto i : currentBody) {
        if (i == c) { return true; }
    }
    return false;
}

/**
 isBeetleComplete Function - checks whether the given string(player's body) is completed against another string
 @param currentBody -- the players body that needs to be checked
 @return boolean -- whether or not the player's body is a complete body(true) or not(false
 */
bool isBeetleComplete(string currentBody) {
    string finishedBody = "BHLLLLLLEEAAT";
    if (currentBody == finishedBody) {
        return true;
    }
    else {
        return false;
    }
}

/**
 getUserInput Function - gets the user input as a char and returns it
 @return userInput -- whatever the user entered
 */
char getUserInput() {
    string answer = "";
    while (cin >> answer) {
        answer[0] = toupper(answer[0]);
        if (answer[0] == 'B' || answer[0] == 'E') { return answer[0]; }
        cout << "Not a choice. Please enter (B or E). ";
    }
}

/**
 convertDieToPart Function - takes whatever the die rolled and converts that to the corresponding body part
 @param roll - whatever the die rolled for the turn
 @return part -- the body part that is returned from the roll
 */
char convertDieToPart(int roll) {
    switch (roll) {
        case 1: return 'B'; break;
        case 2: return 'H'; break;
        case 3: return 'L'; break;
        case 4: return 'E'; break;
        case 5: return 'A'; break;
        case 6: return 'T'; break;
    }
}

/**
 convertPartToBody Function - takes whatever the part that was rolled and changes it to the full string format of it
 @param part -- whatever part the current player rolled
 @return bodyPart -- the complete string of the part that is rolled 
 */
string convertPartToBody(char part) {
    switch (part) {
        case 'B': return "body"; break;
        case 'H': return "head"; break;
        case 'L': return "leg"; break;
        case 'E': return "eye"; break;
        case 'A': return "antenna"; break;
        case 'T': return "tail"; break;
    }
}

/**
 printBody Function - prints the players body from a given string
 @param str -- the player's body that is checked to print
 */
void printBody(string str) {
    // Initialize the variables needed for the if statements to check
    bool body, head, leg1, leg2, leg3, leg4, leg5, leg6, eye1, eye2, ant1, ant2, tail;
    body = head = leg1 = leg2 = leg3 = leg4 = leg5 = leg6 = eye1 = eye2 = ant1 = ant2 = tail = false;

    // Iterate through the string to see which body parts are actually there and which are not.
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            switch (i) {
                case 0:  body = true; break;
                case 1:  head = true; break;
                case 2:  leg1 = true; break;
                case 3:  leg2 = true; break;
                case 4:  leg3 = true; break;
                case 5:  leg4 = true; break;
                case 6:  leg5 = true; break;
                case 7:  leg6 = true; break;
                case 8:  eye1 = true; break;
                case 9:  eye2 = true; break;
                case 10: ant1 = true; break;
                case 11: ant2 = true; break;
                case 12: tail = true; break;
            }
        }
    }

    cout << "\n\nYour Beetle: \n";

    // Line 1
    cout << "       "; 
    if (leg1) { cout << ",_    "; }  else { cout << "      "; } 
    if (ant1) { cout << "/) "; }     else { cout << "   "; }
    if (ant2) { cout << "(\\    "; } else { cout << "      "; }
    if (leg2) { cout << "_,\n"; }    else { cout << "  \n"; }
    // Line 2
    cout << "        "; 
    if (leg1) { cout << ">>  "; } else { cout << "    "; } 
    if (ant1) { cout << "<<"; }   else { cout << "  "; }
    if (head) { cout << ",_,"; }  else { cout << "   "; }
    if (ant2) { cout << ">>  "; } else { cout << "    "; }
    if (leg2) { cout << "<<\n"; } else { cout << "  \n"; }
    // Line 3
    cout << "       "; 
    if (leg1) { cout << "//   "; }  else { cout << "     "; } 
    if (head) { cout << "_"; }      else { cout << " "; }
    if (eye1) { cout << "0"; }      else { cout << " "; }
    if (head) { cout << ".-."; }    else { cout << "   "; }
    if (eye2) { cout << "0"; }      else { cout << " "; }
    if (head) { cout << "_   "; }   else { cout << "    "; }
    if (leg2) { cout << "\\\\\n"; } else { cout << "  \n"; }
    // Line 4
    cout << "       "; 
    if (leg1) { cout << "\\'._"; }        else { cout << "    "; } 
    if (head) { cout << "/       \\"; }   else { cout << "         "; }
    if (leg2) { cout << "_.'/\n"; }       else { cout << "    \n"; }
    // Line 5
    cout << "        "; 
    if (leg1) { cout << "'-."; }       else { cout << "   "; } 
    if (head) { cout << "\\"; }        else { cout << " "; }
    if (body) { cout << ".--.--."; }   else { cout << "       "; }
    if (head) { cout << "/"; }         else { cout << " "; }
    if (leg2) { cout << ".-'\n"; }     else { cout << "   \n"; }
    // Line 6
    cout << "        "; 
    if (leg3) { cout << "__"; }             else { cout << "  "; } 
    if (body) { cout << "/ : :Y: : \\"; }   else { cout << "           "; }
    if (leg4) { cout << "__\n"; }           else { cout << "  \n"; }
    // Line 7
    if (leg3) { cout << "';,  .-(_"; }       else { cout << "         "; } 
    if (body) { cout << "| : : | : : |"; }   else { cout << "             "; }
    if (leg4) { cout << "_)-.  ,:'\n"; }     else { cout << "         \n"; }
    // Line 8
    cout << "  "; 
    if (leg3) { cout << "\\\\/.'  "; }         else { cout << "       "; } 
    if (body) { cout << "|: : :|: : :|  "; }   else { cout << "               "; }
    if (leg4) { cout << "`.\\//\n"; }          else { cout << "     \n"; }
    // Line 9
    cout << "   "; 
    if (leg3) { cout << "(/    "; }              else { cout << "      "; } 
    if (body) { cout << "|: : :|: : :|    "; }   else { cout << "                 "; }
    if (leg4) { cout << "\\)\n"; }               else { cout << "  \n"; }
    // Line 10
    cout << "         "; 
    if (body) { cout << "|: : :|: : :|\n"; }   else { cout << "\n"; }
    // Line 11
    cout << "        "; 
    if (leg5) { cout << "/"; }                else { cout << " "; } 
    if (body) { cout << "\\ : : | : : /"; }   else { cout << "             "; }
    if (leg6) { cout << "\\\n"; }             else { cout << "  \n"; }
    // Line 12
    cout << "       "; 
    if (leg5) { cout << "(_/"; }           else { cout << "   "; } 
    if (tail) { cout << "'.: :.: :.'"; }   else { cout << "           "; }
    if (leg6) { cout << "\\_)\n"; }        else { cout << "   \n"; }
    // Line 13
    cout << "        "; 
    if (leg5) { cout << "\\\\  "; }        else { cout << "    "; } 
    if (tail) { cout << "`\"\"`\"\"`"; }   else { cout << "       "; }
    if (leg6) { cout << "  //\n"; }        else { cout << "    \n"; }
    // Line 14 
    cout << "         "; 
    if (leg5) { cout << "\\\\         "; } else { cout << "           "; } 
    if (leg6) { cout << "//\n"; }          else { cout << "  \n"; }
    // Line 15
    cout << "          "; 
    if (leg5) { cout << "':.     "; } else { cout << "        "; } 
    if (leg6) { cout << ".:'\n"; }    else { cout << "   \n"; }
    /*
    * What the code prints out line by line
    *  1 "       ,_    /) (\\    _,\n"
    *  2 "        >>  <<,_,>>  <<\n"
    *  3 "       //   _0.-.0_   \\\\\n"
    *  4 "       \\'._/       \\_.'/\n"
    *  5 "        '-.\\.--.--./.-'\n"
    *  6 "        __/ : :Y: : \\__\n"
    *  7 "';,  .-(_| : : | : : |_)-.  ,:'\n"
    *  8 "  \\\\/.'  |: : :|: : :|  `.\\//\n"
    *  9 "   (/    |: : :|: : :|    \\)\n"
    * 10 "         |: : :|: : :|\n"
    * 11 "        /\\ : : | : : /\\\n"
    * 12 "       (_/'.: :.: :.'\\_)\n"
    * 13 "        \\\\  `\"\"`\"\"`  //\n"
    * 14 "         \\\\         //\n"
    * 15 "          ':.     .:'\n"
    */
}

/**
 showLogo Function - prints out the Logo for the start of the game
 */
void showLogo() {
    // Fancy Title for the Game
    cout << "                            ";
    cout << "   _____     _____    _____   _______    __        _____  \n";
    cout << "                            ";
    cout << " /\\  __/\\  /\\_____\\ /\\_____\\/\\_______)\\ /\\_\\     /\\_____\\ \n";
    cout << "                            ";
    cout << " ) )(_ ) )( (_____/( (_____/\\(___  __\\/( ( (    ( (_____/ \n";
    cout << "                            ";
    cout << "/ / __/ /  \\ \\__\\   \\ \\__\\    / / /     \\ \\_\\    \\ \\__\\   \n";
    cout << "                            ";
    cout << "\\ \\  _\\ \\  / /__/_  / /__/_  ( ( (      / / /__  / /__/_  \n";
    cout << "                            ";
    cout << " ) )(__) )( (_____\\( (_____\\  \\ \\ \\    ( (_____(( (_____\\ \n";
    cout << "                            ";
    cout << " \\/____\\/  \\/_____/ \\/_____/  /_/_/     \\/_____/ \\/_____/ \n";
    cout << "\n\n\n\n\n";
}

/**
 addPart Function - adds a body part to the player's body string
 @param body -- the player's body to be added to
 @param part -- the part to be added
 @return boolen -- whether or not it successfully(true) added or not(false)
 */
bool addPart(string& body, char part) {
    for (int i = 0; i < body.length(); i++) {
        if (part == 'B' && i == 0 && body[i] == ' ') {
            body[i] = part;
            return true;
        }
        if (part == 'H' && i == 1 && body[i] == ' ') {
            body[i] = part;
            return true;
        }
        if (part == 'L' && i >= 2 && i <= 7 && body[i] == ' ') {
            body[i] = part;
            return true;
        }
        if (part == 'E' && i >= 8 && i <= 9 && body[i] == ' ') {
            body[i] = part;
            return true;
        }
        if (part == 'A' && i >= 10 && i <= 11 && body[i] == ' ') {
            body[i] = part;
            return true;
        }
        if (part == 'T' && i == 12 && body[i] == ' ') {
            body[i] = part;
            return true;
        }
    }
    return false;
}

/**
 removePart Function - removes a body part to the player's body string
 @param body -- the player's body to be removed from
 @param part -- the part to be removed
 @return boolen -- whether or not it successfully(true) removed or not(false)
 */
bool removePart(string& body, char part) {
    for (int i = 12; i >= 0; i--) {
        if (part == 'L' && i >= 2 && i <= 7 && body[i] == 'L') {
            body[i] = ' ';
            return true;
        }
        if (part == 'E' && i >= 8 && i <= 9 && body[i] == 'E') {
            body[i] = ' ';
            return true;
        }
        if (part == 'A' && i >= 10 && i <= 11 && body[i] == 'A') {
            body[i] = ' ';
            return true;
        }
        if (part == 'T' && i == 12 && body[i] == 'T') {
            body[i] = ' ';
            return true;
        }
    }
    return false;
}

/**
 endScreen Function - prints the final screen telling which player won
 @param pName -- the string name of the player who won
 */
void endScreen(string pName) {
    // Prints out the name
    cout << "Congratulations, " << pName << endl;
    // Prints out the ascii art
    cout << "                       .,,uod8B8bou,,.                                                  _,.---._\n";
    cout << "              .., uod8BBBBBBBBBBBBBBBBRPFT ? l!i : .                    ,--.-.  .-,--.,-.' , -  `.  .--.-. .-.-.\n";
    cout << "         ,=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||                       /==/- / /=/_ //==/_,  ,  - \/==/ -|/=/  |\n";
    cout << "         !...:!TVBBBRPFT||||||||||!!^^\"\"'   ||||                       \\==\\, \\/=/. /|==|   .=.     |==| ,||=| -|\n";
    cout << "         !.......:!?|||||!!^^\"\"'            ||||                        \\==\\  \\/ -/ |==|_ : ;=:  - |==|- | =/  |\n";
    cout << "         !.........||||                     ||||                         |==|  ,_/  |==| , '='     |==|,  \\/ - |\n";
    cout << "         !.........||||  ##BEETLE           ||||                         \\==\\-, /    \\==\\ -    ,_ /|==|-   ,   /\n";
    cout << "         !.........||||  #Congrats!         ||||                         /==/._/      '.='. -   .' /==/ , _  .'  \n";
    cout << "         !.........||||                     ||||                         `--`-`         `--`--''   `--`..---'   \n";
    cout << "         !.........||||                     ||||                                ,-.-.  .=-.-..-._         .=-.-. \n";
    cout << "         !.........||||                     ||||                       ,-..-.-./  \\==\\/==/_ /==/ \\  .-._ /==/_ /\n";
    cout << "         `.........||||                    ,||||                       |, \\=/\\=|- |==|==|, ||==|, \\/ /, /==|, | \n";
    cout << "          .;.......||||               _.-!!|||||                       |- |/ |/ , /==/==|  ||==|-  \\|  ||==|  | \n";
    cout << "   .,uodWBBBBb.....||||       _.-!!|||||||||!:'                         \\, ,     _|==|==|- ||==| ,  | -|/==/. / \n";
    cout << "!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....                    | -  -  , |==|==| ,||==| -   _ |`--`-`  \n";
    cout << "!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.                   \\  ,  - /==/|==|- ||==|  /\\ , | .=.    \n";
    cout << "!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.                 |-  /\\ /==/ /==/. //==/, | |- |:=; :  \n";
    cout << "!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^\"`;:::       `.               `--`  `--`  `--`-` `--`./  `--` `=`  \n";
    cout << "!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         iBBbo.\n";
    cout << "`..........YBRPFT?!::::::::::::::::::::::::;iof68bo.      WBBBBbo.\n";
    cout << "  `..........:::::::::::::::::::::::;iof688888888888b.     `YBBBP^'\n";
    cout << "    `........::::::::::::::::;iof688888888888888888888b.     `\n";
    cout << "      `......:::::::::;iof688888888888888888888888888888b.\n";
    cout << "        `....:::;iof688888888888888888888888888888888899fT!\n";
    cout << "         `..::!8888888888888888888888888888888899fT | !^ \"'\n";
    cout << "            `' !!988888888888888888888888899fT|!^\"'\n";
    cout << "                `!!8888888888888888899fT|!^\"'\n";
    cout << "                  `!988888888899fT|!^\"'\n";
}
