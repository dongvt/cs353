/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H
#include <locale>         // std::locale, std::toupper
#include <map>
#include <algorithm>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Joshua Nestman"; }
   virtual std::string getCipherName()  { return "Numbered Key Cipher"; }
   virtual std::string getEncryptAuth() { return "Joshua Nestman"; }
   virtual std::string getDecryptAuth() { return "Joshua Nestman"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string s;
      s += "cryptogram.org (2021), ";
      s += "\"cryptogram - Numbered Key\', \n   retrieved: ";
      s += "https://www.cryptogram.org/downloads/aca.info/ciphers/NumberedKey.pdf";
      return s;
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // TODO: please format your pseudocode
      // The encrypt pseudocode
      str =  "encrypt(plainText, password)\n";
      str += "   key <- password\n";
      str += "   key <- alphabet - letters already in key\n";
      str += "   encoding<char, int> = key(letter, position)\n";
      str += "   cipherText = encoding(plainText)\n";
      str += "   RETURN cipherText\n\n";

      // The decrypt pseudocode
      str +=  "decrypt(cipherText, password)\n";
      str += "   key <- password\n";
      str += "   key <- alphabet - letters already in key\n";
      str += "   decoding<char, int> = key(letter, position)\n";
      str += "   plainText = decoding(cipherText)\n";
      str += "   RETURN plainText\n\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string key = password;
      // TODO - Add your code here
      std::string alphabet = "abcdefghijklmnopqrstuvwxyz ";
      for (int i = 0; i < key.length(); i++)
      {
        std::size_t found = alphabet.find(key[i]);
        if (found != std::string::npos)
          {
            alphabet.erase(alphabet.begin() + found);
          }
      }

      key += alphabet;

      std::map<char, int> encoding;
      int count = 0;
      for (auto letter : key)
      {
        if (encoding.find(letter) == encoding.end())
        {
          encoding.insert(std::pair<char, int>(letter, count));
          count++;
        }
      }

      std::string cipherText = "";
      for (int i = 0; i < plainText.length(); i++)
      {
        cipherText += std::to_string(encoding.find(plainText[i])->second) + " ";
      }

      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      std::string key = password;
      // TODO - Add your code here
      std::string alphabet = "abcdefghijklmnopqrstuvwxyz ";
      for (int i = 0; i < key.length(); i++)
      {
        std::size_t found = alphabet.find(key[i]);
        if (found != std::string::npos)
          {
            alphabet.erase(alphabet.begin() + found);
          }
      }

      key += alphabet;

      std::map<char, int> encoding;
      int count = 0;
      for (auto letter : key)
      {
        if (encoding.find(letter) == encoding.end())
        {
          encoding.insert(std::pair<char, int>(letter, count));
          count++;
        }
      }

      std::vector<std::string> temp; 
      std::stringstream ss(cipherText); // Turn the string into a stream. 
      std::string tok; 
 
      while(std::getline(ss, tok, ' ')) { 
        temp.push_back(tok); 
      } 

      std::string plainText = "";
      for (int i = 0; i < temp.size(); i++)
      {
        for (auto it = encoding.begin(); it != encoding.end(); ++it)
        {
          if (temp[i] == std::to_string(it->second))
          {
            plainText += it->first;
            break;
          }
        }
      }

      return plainText;
   }
};

#endif // CIPHER03_H

