/*
Student Name: Mikey Sinno (Metcalfe)   Student Number: C3256595
The following K&R indentation code will cipher and decipher texts based off the
principles of Rotation and Substitution ciphers. Each section of calculations
for the code is presented as 4 different functions while the main body of the
code acts to initialise the various variables and strings as well as sort
between the different ciphering options. Follow the instructions that are
printed to the screen when you run the code to choose between the different
calculation paths.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void RotCipherfunc(char* msgtext, int key);     // Rotation Cipher function prototype
void RotDecipherfunc(char* msgtext, int key);   // Rotation Decipher function prototype
void SubCipherfunc(char* subAlpha, char* plaintxt, char* ciphertxt);    // Substitution Cipher function prototype
void SubDecipherfunc(char* subAlpha, char* ciphertxt, char* plaintxt, char* normAlpha);    // Substitution decipher prototype

int main() {

	int k;           // Initialised k as integer to calculate Key     
	int key;
	char msgtext[200];    // Character string of 200 size
	char plaintxt[200];
	char ciphertxt[200];
	char decision[10];
	char subAlpha[26];
	char* normAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // Character type string for assigning the normal alphabet needed for substitution
	char rot[] = "ROT";      // Character type string for choosing the type of calculation when running the code
	char sub[] = "SUB";


	printf("Enter 'ROT' for Rotation Cipher or 'SUB' for Substitution Cipher: ");  // Standard screen printing text

	fgets(decision, sizeof(decision), stdin);     // Standard input for a the 'decision' string with size 10

	char* rotation = strpbrk(decision, rot);        // Code to locate characters within a string. Locates characters of 'rot' string within 'decision' string
	char* substitution = strpbrk(decision, sub);

	if (rotation != NULL) {         // If statement to send user to calculate rotation cipher when a character from 'rot' is found in 'decision'
		char decision2[10];         // Initialising strings to repeat previous operation to give user option between cipher and decipher
		char ciph[] = "CI";
		char deci[] = "DE";
		
		printf("\nEnter 'CI' to Cipher a text or 'DE' to Decipher a text: ");
		
		fgets(decision2, sizeof(decision2), stdin);
		
		
		char* ciphr = strpbrk(decision2, ciph);
		char* deciphr = strpbrk(decision2, deci);
		
		if (ciphr != NULL) {            // Code enters the Rotation Ciphering calculations
		    
			printf("\nInsert text for encryption: ");
			
			fgets(msgtext, sizeof(msgtext), stdin);    // Gets the text input by the user for the plain text
			
			printf("Enter key: ");
			
			scanf("%d", &k);          // Gets user input of the value 'k' used in calculating Key
			
			key = 26 - k;         // size of alphabet minus k to shift the alphabet to the right instead of left
			
			printf("\nThe ciphered text is: ");
			
			RotCipherfunc(msgtext, key);    // Calls the Rotation cipher function (Rotcipherfunc) and prints ciphered text
			
		}
		else if (deciphr != NULL) {    // Enters Rotation Deciphering calculations, same body as ciphering code
			
			printf("\nInsert text for decryption: ");
			
			fgets(msgtext, sizeof(msgtext), stdin);
			
			printf("Enter Key: ");
			
			scanf("%d", &k);
			
			key = 26 - k;
			
			printf("\nThe deciphered text is: ");
			
			RotDecipherfunc(msgtext, key);    // Calls Rotation decipering function (RotDecipherfunc) and prints deciphered text
			
			
		}
	}
	else if (substitution != NULL) {  // Follows Substitution code path
		
		char decision3[10];
		char ciph[] = "CI";
		char deci[] = "DE";
		
		printf("\nEnter 'CI' to Cipher a text or 'DE' to Decipher a text: ");
		
		fgets(decision3, sizeof(decision3), stdin);
		
		
		char* ciphr = strpbrk(decision3, ciph);
		char* deciphr = strpbrk(decision3, deci);
		
		if (ciphr != NULL) {               // Enters Substitution ciphering code
            
            printf("\nEnter Text for Encryption: ");
            
            fgets(plaintxt, sizeof(plaintxt), stdin);
            
            printf("\nEnter Substitute Alphabet Key: ");
            
            fgets(subAlpha, sizeof(subAlpha), stdin);
            
            char ciphertxt[strlen(plaintxt)];
            
            SubCipherfunc(subAlpha, plaintxt, ciphertxt);   // Calls Substitution ciphering function (SubCipherfunc)
		} 
		else if (deciphr != NULL) {        // Enters Substitution deciphering code
           
            printf("\nEnter Text for Decryption: ");
            
            fgets(ciphertxt, sizeof(ciphertxt), stdin);
            
            printf("\nEnter Substitute Alphabet Key: ");
            
            fgets(subAlpha, sizeof(subAlpha), stdin);
            
            char plaintxt[strlen(ciphertxt)];
            
            SubDecipherfunc(subAlpha, ciphertxt, plaintxt, normAlpha);    // Calls Substitution deciphering function (SubDecipherfunc)
		}
	}
}
/*
This function will take the string of plain text (msgtxt) and integer key as
input by the user and does not return a value but prints the ciphered letters
and show the encrypted text. The function features a loop that continues until
a non character value is input or the length of the input text is reached. 
During the loop, the function will convert any lowercase letter as by the ASCII
table and convert it to uppercase as well as return the value to the standard 
letter format (A=0, B=1, C=2,... etc.). The ciphering equation is then used with 
the input key and stored into 'cipher' to continue calculations.
*/

void RotCipherfunc(char* msgtext, int key) {   // Function header with input msgtxt and key

	int i = 0;       // Initialise i as 0 for starting position in while loop
	int letterval;   // letter value integer
	int cipherval;   // cipher value integer
	char cipher;     // String for cipher which is printed as the result

	while (msgtext[i] != '\0' && strlen(msgtext) - 1 > i) {          // Loop to continue starting at i = 0, until non character value is found and string length 200 is exceeded
		
		if (msgtext[i] >= 97 && msgtext[i] <= 122) {       // If statement to locate any lowercase letters in input text (ASCII values within [97,122] range)
			
			letterval = msgtext[i] - 97;                   // To reduce the value to standard letter value (A=0, B=1, C=2, etc) so minus 97
			
		}
		else if (msgtext[i] >= 65 && msgtext[i] <= 90) {   // Find letters wihtin uppercase range
			
			letterval = msgtext[i] - 65;                   // Reduce to standard letter values
			
		}
		
		cipherval = (letterval + key) % 26 + 65;           // Equation for ciphering text. Add 65 to return standard letter value to uppercase ASCII format
		
		cipher = cipherval;                  // Store the uppercase letter value in cipher to proceed within calculating next letter
		
		printf("%c", cipher);   // Print the value in cipher to the screen as the ciphered text
		
		i++;     // Increase the value of i to continue the while loop until limit is reached
	}

}
/*
This is the Rotation deciphering function. It operates in the same way as the 
ciphering function however the deciphering equation is used and if the value of
the letter minus the key produces a negative, 26 is added to the result as the 
modulus of a negative number can produce undesireable results.
*/
void RotDecipherfunc(char* msgtext, int key) {     // Function header with msgtxt string and key integer inputs

	int i = 0;        
	int letterval;   
	int decipherval;
	int LminusK;
	char decipher;

	while (msgtext[i] != '\0' && strlen(msgtext) - 1 > i) {  // Same while loop and lowercase-uppercase check as in previous function
        
		if (msgtext[i] >= 97 && msgtext[i] <= 122) {
			
			letterval = msgtext[i] - 97;
			
		}
		else if (msgtext[i] >= 65 && msgtext[i] <= 90) {
			letterval = msgtext[i] - 65;
		}
		
		LminusK = letterval - key;   // Store letter value minus key in LminusK for simplicity
		
		if (LminusK < 0) {                  // If statement for when LminusK is negative
			LminusK = LminusK + 26;         // Increase by 26 to remove negative
		}
		
		decipherval = LminusK % 26 + 65;     // Deciphering equation
		
		decipher = decipherval;              // Store in decipher to continue calculations
		
		printf("%c", decipher);              // Print decipher values
		
		i++;                                 // Increase i by 1 during each loop
	}
}
/*
This is the Substitution ciphering function which has 3 string inputs, 2 of 
which are input by the user (the substitute alphabet and plain text). The 3rd
input is the resulting string of ciphered text. Similar to the rotation 
functions this function will convert lowercase to uppercase and restore them to 
standard letter values. Based off the input substitute Alphabet, the 'for' loop
will continue until all the standard values of the plaintxt are calculated and 
checked against the substitute alphabet as the position in the string.
*/
 void SubCipherfunc(char* subAlpha, char* plaintxt, char* ciphertxt) {     // function header with string inputs substitute alphabet, plain text and ciphered text
 
    for(int i = 0; i < strlen(plaintxt); i++) {              // For loop with i initialised as integer at 0 which will continue to increase by 1 each loop until length of plain text (200) is reached   
        
        int index;
        int letterval;
        
        letterval = ((int)plaintxt[i]);                      // Store plain text input as an integers in letter value to calculate lowercase-uppercase values
        
        if (letterval >= 97 && letterval <= 122) {
            index = letterval - 97;
        }
        else if (letterval >= 65 && letterval <= 90) {
            index = letterval - 65;
        }
        
        ciphertxt[i] = subAlpha[index];               // Use index value as positioning within substitute alphabet string and store in cipher text 
        
    }
    
    printf("\nThe Encrypted text by substitution is: %s", ciphertxt);                   // Print cipher text as result  
}
/*
This Subtitution deciphering function accepts 4 string inputs, the user input 
substitute alphabet and ciphered text, as well as the resulting plain text and 
a stored normal alphabet string. The function converts lowercase to uppercase 
same as the other functions although it features a 'for' loop which will 
continue until the length of an alphabet is exceed and checks the standard 
letter value (index) against each standard letter value of the input ciphered
text (index2). When these to values are equal, the function will use the 
standard letter value of the ciphered text as a position within the normal
alphabet string, then store that letter in plaintxt. The plaintxt string is then
printed as the result.
*/
void SubDecipherfunc(char* subAlpha, char* ciphertxt, char* plaintxt, char* normAlpha) {   // Function header with 4 string inputs, ciphered text, plain text (result), substitute alphabet and normal stored alphabet
 
    for(int i = 0; i < strlen(ciphertxt); i++) {      // Same for loop used in substitution cipher function
        
        int index;
        int letterval;
        
        letterval = ((int)ciphertxt[i]);
        
        if (letterval >= 97 && letterval <= 122) {
            index = letterval - 97;
        }
        else if (letterval >= 65 && letterval <= 90) {
            index = letterval - 65;
        }
        
        for (int j = 0; j < 25; j++) {               // for loop where j will increase by 1 from 0 until length of alphabet is reached
            int index2;
            int subletterval;
            
            subletterval = ((int)subAlpha[j]);       // Value of each letter in the substitute alphabet is stored as an integer in subletterval
            
            index2 = subletterval - 65;              // index2 is the standard letter value of each letter within the substitute alphabet
            
            if (index == index2) {                   // If statement to find when the index of a letter within the input cipher text is equal to the index of a letter within the sub Alphabet
                plaintxt[i] = normAlpha[j];          // The value of j when index=index2 is used as a position within the normal alphabet string and stored in plaintxt to produce result
            }
            
        }
        
        
    }
    
    printf("\nThe Decrypted text by substitution is: %s", plaintxt);  // Print the resulting deciphered text. 
    
}

