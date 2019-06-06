// Encrypt_Decrypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <map>

void DisplayIntro();
char* CharacterToBinary(char Character);
unsigned int* EncryptString(std::string PlainText, int lengthOfPlainText);
char* DecryptString(std::string CypherText, int lengthOfCypherText);
std::string IntegerToString(int stringify);
void AssembleOutput(unsigned int* inNumbers, int length);
std::string AssembleOutput(char* inCharacters);
char BinaryToString(int Binary);

int main()
{
	DisplayIntro();
	std::string UserResponse;
	std::getline(std::cin, UserResponse);

	if (UserResponse[0] == '!')
	{
		UserResponse.erase(0, 1);
		unsigned int* CypherText = EncryptString(UserResponse, UserResponse.length());
		AssembleOutput(CypherText, UserResponse.length());
		std::cout << std::endl;
		free(CypherText);
	}
	else if (UserResponse[0] == '*')
	{
		UserResponse.erase(0, 1);
		AssembleOutput(DecryptString(UserResponse, UserResponse.length()));
	}
}

char* CharacterToBinary(char Character)
{

	//NOTE: There is specifically no free on BinaryNumber because it's the return value and is important to the functionality of the entire application and is in turn freed later on

	//Convert our Character to ASCII
	int ascii = int(Character);

	//Create an Array of characters to store our binary number
	char* BinaryNumber;
	BinaryNumber = (char*) malloc(8);
	
	//Loop through the Array and get each binary number out of the ASCII number and stick it in its rightful spot in the array
	for (int i = 1; i <= 8; i++)
	{
		int temp = ascii % 2;
		BinaryNumber[8 - i] = (temp > 0) ? '1' : '0';
		ascii /= 2;
	}
	return BinaryNumber;
}

unsigned int* EncryptString(std::string PlainText, int lengthOfPlainText)
{
	//Create a new unsigned integer array to contain the Decimal versions of the binary numbers we create in CharacterToBinary()
	unsigned int* modifiedNumbers;
	modifiedNumbers = (unsigned int*)malloc(sizeof(unsigned int) * lengthOfPlainText);

	//Create a string to temporarily house the Binary Numbers so we can use the stoi() function
	std::string tempstr = "";

	
	//Loop through the plaintext that was submitted to be encrypted and turn each charater into binary
	for (int i = 0; i < lengthOfPlainText; i++)
	{
		//Create a temporary char pointer to store out character array in
		char* temp = CharacterToBinary(PlainText[i]);

		//Loop through each decimal character 
		for (int j = 0; j < 8; j++)
		{
			//Add each character to the string
			tempstr += temp[j];
		}
		modifiedNumbers[i] = (stoi(tempstr) * 465); //Turn the binary number into a decimal number and scramble it by multiplying by 465
		tempstr = ""; //Empty the string so we can add the next binary number to our decimal number array
		free(temp); //We can free temp because we no longer need temp this loop and we will cause a memory leak if we dont
	}
	return modifiedNumbers; //Return our array of integers we can display
}

char* DecryptString(std::string CypherText, int lengthOfCypherText)
{
	//Before we decrypt, we know all of our encrypted text are just integer values, so we will check to make sure there are no Alpabetical numbers
	for (int i = 0; i < lengthOfCypherText; i++)
	{
		if (isalpha(CypherText[i]))
		{
			std::cout << "Invalid Decrypt Scheme." << std::endl;
			return (char*) ' ';
		}
	}

	//Create and array that will store each integer that represents a character of the encrypted text
	unsigned int* ModifiedNumbers = (unsigned int*)malloc(sizeof(unsigned int) * lengthOfCypherText);
	//This index will be the value we need when chopping up our CypherText string to continue getting more out of it
	int index = 0;
	char Space = ' ';

	//Keeping track of how many characters are actually in the string to make some loops later possible/easier to implement
	int NumOfChars = 0;

	//Loop through the CypherText and pull out each encrypted character
for (int i = 0; i < lengthOfCypherText && CypherText.length() > 0; i++)
{
	for (int j = 0; j < CypherText.length(); j++)
	{
		//When we find a space that will be the index we need to shave off from 0 on the CypherText string and we will want to set foundSpace to true so we know to use the space shaving block later
		if (CypherText[j] == Space)
		{
			index = j + 1;
			break;
		}
		else
		{
			//If we don't find any spaces we can safely assume the next character is the rest of the string
			index = CypherText.length();
		}
	}
		//We turn the character(string) we found into an integer we can reverse engineer back into a letter and stick it in our array of ModifiedNumbers
		ModifiedNumbers[i] = stoi(CypherText.substr(0, index));
		//remove the character we already pulled out of the string, so we don't find it again
		CypherText.erase(0, index);
		NumOfChars++;
}

//Create a new array that will store each Alpahbetical character of our text
char* Characters;
Characters = (char*)malloc(sizeof(char) * (NumOfChars) + 1);
//Adding this null character allows us to use the array just like a string
Characters[NumOfChars] = '\0';

//Loop through each modifiedCharacter and pull out the original Letter
for (int i = 0; i < NumOfChars; i++)
{
	ModifiedNumbers[i] /= 465;
	Characters[i] = BinaryToString(ModifiedNumbers[i]);
}

free(ModifiedNumbers);

	return Characters;
}

void AssembleOutput(unsigned int* inNumbers, int length)
{
	std::cout << "Encrypted Plaintext: ";
	//Loop through each encrypted character and output it which are now represented as unsigned long integers
	for (int i = 0; i < length; i++)
	{
		std::cout << inNumbers[i] << " ";
	}
	std::cout << std::endl;
	return;
}

std::string AssembleOutput(char* inCharacters)
{
	std::cout << "Decrypted PlainText: ";
	//Loop through each character in the array until we hit the the null character signifying the end of the array of characters
	for (int i = 0; inCharacters[i] != '\0'; i++)
	{
		std::cout << inCharacters[i];
	}
	std::cout << std::endl;
	free(inCharacters);
	return "";
}

std::string IntegerToString(int stringify)
{
	int temp = stringify;
	std::string stringifiedInt = "";
	//Create a new character array to store each place of the decimal number as a character
	char* decimalPlace = (char*) malloc(sizeof(char));
	
	//We can safely say to loop as many times as the decimal number goes into ten as thats as many places as we will get out of it
	for (int i = 0; temp > temp / 10; i++)
	{
		//Using modulus division gets the current value of the last place in the Decimal number and then we add 48 to it to get the correct ASCII value
		*decimalPlace = (char) 48 + (temp % 10);
		stringifiedInt.insert(stringifiedInt.begin(), *decimalPlace);
		//This removes the last place of the decimal number so we can get the next value on the next pass
		temp /= 10;
	}

	//Dont want any memory leaks
	free(decimalPlace);
	return stringifiedInt;
}

char BinaryToString(int Binary)
{
	//Convert the Binary integer to a string because it is easier to convert binary to decimal from a string than Decimal to Binary
	std::string BinaryStr = IntegerToString(Binary);
	//This will end up being a collector that will become our decimal value of the binary value
	int Decimal = 0;
	char One = '1';
	//Loop through the string and pull out the value of each place of the binary number
	for (int i = 0; i < BinaryStr.length(); i++)
	{
		//We only need to do things if the current binary number is a one
		if (BinaryStr[i] == One)
		{
			//This equation determines the power of 2 we are looking at currently in our binary number
			int power = BinaryStr.length() - i - 1;
			//Add The current power of two we are looking at
			Decimal += (int) pow(2, power);
		}
	}

	//std::cout << Decimal << std::endl;

	return (char) Decimal;
}

void DisplayIntro()
{
	//Introduce the program and what to do
	std::cout << "Enter a string to encrypt or decrypt please :)" << std::endl;
	std::cout << "Put either a '!' to encrypt or a '*' to decrypt!" << std::endl;
	std::cout << "String to encrypt: ";
}