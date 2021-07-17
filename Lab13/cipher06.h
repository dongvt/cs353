/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER06_H
#define CIPHER06_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher06 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Govert Carreno"; }
   virtual std::string getCipherName()  { return "Mlecchita vikalpa (Or KamaSutra Cipher)"; }
   virtual std::string getEncryptAuth() { return "Govert Carreno"; }
   virtual std::string getDecryptAuth() { return "Govert Carreno"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://www.civilwarsignals.org/cipher/kamasutra.html");
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
      str = "encrypt(plainText, password)\n";
	   str += "\tFOR EACH letter in plaintext, index is i\n";
		str += "\t\tLetter[i] <- password[lowerkey of letter[i] - 97] //97 substract the char value to convert into index";

      // The decrypt pseudocode
      str += "decrypt(plainText, password)\n";
      str += "\tFOR EACH letter in plaintext, index is i\n";
      str += "\tletterIndex <- 0\n";
      str += "\t\tFOR EACH letter in password, index is j\n";
      str += "\t\t\tif password[j] = plainText[i]\n";
      str += "\t\t\t\tletterIndex<-j //Get the letter index in the key\n";
      str += "\tplainText[j] <- letter + 97 //Convert the index to lowercase\n";


      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string cipherText = plainText;

      for(int i = 0; i< cipherText.length();i++){
         cipherText[i] = password[tolower(cipherText[i])- 97] ;
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
      std::string plainText = cipherText;

      for(int i = 0; i< plainText.length();i++){
         int letter = 0;
         for(int j= 0;j<password.length();j++) {
            if (password[j] == plainText[i]) {
               letter = j;
            }
         }
         plainText[i] = letter + 97;
      }
      return plainText;
   }
};

#endif // CIPHER06_H