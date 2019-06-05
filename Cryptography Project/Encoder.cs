// frantically pressing ctrl - z
// -- Kiran "imoffended" Forrest

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Cryptography_Project
{
    class Encoder
    {
        readonly Dictionary<string, int> dict = new Dictionary<string, int>()
            {
                { " ", 00100000 },
                { "a", 01100001 },
                { "b", 01100010 },
                { "c", 01100011 },
                { "d", 01100100 },
                { "e", 01100101 },
                { "f", 01100110 },
                { "g", 01100111 },
                { "h", 01101000 },
                { "i", 01101001 },
                { "j", 01101010 },
                { "k", 01101011 },
                { "l", 01101100 },
                { "m", 01101101 },
                { "n", 01101110 },
                { "o", 01101111 },
                { "p", 01110000 },
                { "q", 01110001 },
                { "r", 01110010 },
                { "s", 01110011 },
                { "t", 01110100 },
                { "u", 01110101 },
                { "v", 01110110 },
                { "w", 01110111 },
                { "x", 01111000 },
                { "y", 01111001 },
                { "z", 01111010 },
                { "!", 00100001 },
            };

        // TODO: Cleanup and optimize Encrypt, Decrypt, and IsEncrypted
        // TODO: Add comments to Encrypt, Decrypt, and IsEncrypted

        // A basic encryption method. Takes input string, converts it to its binary equivalent,
        // and multiplies that by two (2), and subtracts five-hundred (500).
        public string Encrypt(string toEncrypt)
        {
            // Dictionary of all lowercase letters relating them to their binary values

            List<int> toEncInBinary = new List<int>();

            //Converts toEncrypt to binary, stores each char in toEncInBinary
            foreach (char character in toEncrypt)
            {
                toEncInBinary.Add(dict[character.ToString()]);
            }

            List<double> multiplyTwoToEnc = new List<double>();

            foreach (int x in toEncInBinary)
            {
                multiplyTwoToEnc.Add(3.393251 * x);
            }

            List<double> toEncMinusFiveHundred = new List<double>();

            foreach (double x in multiplyTwoToEnc)
            {
                toEncMinusFiveHundred.Add(x - 500);
            }

            string final = "";

            //Constructs final string
            foreach (double x in toEncMinusFiveHundred)
            {
                final += $"{x} ";
            }

            return final;
        }

        // A basic decryption method. Decrypts the above Encrypt method.
        public string Decrypt(string toDecrypt)
        {
            string newStr = "";
            string oldStr = toDecrypt;
            string tempStr = "";

            while (oldStr.IndexOf(" ") != -1)
            {
                int index1 = oldStr.IndexOf(" ");

                for (int i = 0; i < index1; i++)
                {
                    tempStr += oldStr[i];
                }

                var stringBuilder = new StringBuilder(oldStr);
                stringBuilder.Remove(0, index1 + 1);
                oldStr = stringBuilder.ToString();
            
                double tempInt = double.Parse(tempStr);
                tempInt += 500;
                tempInt /= 3.393251;

                foreach (KeyValuePair<string, int> entry in dict)
                {
                    if (entry.Value == (int)tempInt)
                    {
                        newStr += entry.Key;
                    }
                }
                tempStr = "";
            }

            return newStr;
        }

        // Returns true if input string is encrypted (begins with an exclamation mark (!))
        // False if not. 
        public bool IsEncrypted(string message)
        {
            int index = (message.IndexOf(" ") == -1) ? message.Length : message.IndexOf(" ");

            string tStr = "";

            for (int j = 0; j < index; j++)
            {
                tStr += message[j];                
            }
            tStr += " ";

            if (tStr == Encrypt("!"))
            {
                return true;
            }
            else
            {
                return false;
            }

        }

        public string EngimaEncrypt(string inputMessage, int six, char dict, bool negative)
        {
            // Defining sets
            Dictionary<string, double> dictBase = new Dictionary<string, double>()
            {
                { "a", 2 },
                { "b", 3 }
            };

            char[] inputCharArray = inputMessage.ToCharArray();



            return "incomplete";
        }
    }
}
