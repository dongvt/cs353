/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher01 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Abhishek Humagain"; }
   virtual std::string getCipherName()  { return "Autokey Cipher"; }
   virtual std::string getEncryptAuth() { return "Abhishek Humagain"; }
   virtual std::string getDecryptAuth() { return "Abhishek Humagain"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("P. (n.d.). Autokey Cipher.\n http://practicalcryptography.com/ciphers/classical-era/autokey/");
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
      str =  "\nencrypt(plainText, cipherKey)\n";
      str +=  "\tcipherText = \"\" \n";
      str +=  "\tfor i=0; = length(plainText); i++ \n";

      str +=  "\t\tpLetter =  (plainText[i] cast to int) - 32 \n";
      
      str +=  "\t\tif i < length(cipherKey) \n";
      str +=  "\t\t\tkLetter =  (cipherKey[i] cast to int) - 32 \n";

      str +=  "\t\t\tcipherText += ((kLetter + pLetter) % 95) + 32 \n";
      str +=  "\t\telse: \n";
      str +=  "\t\t\tkLetter =  (plainText[i-length(cipherKey)] cast to int) - 32 \n";
      str +=  "\t\t\tcipherText += ((kLetter + pLetter) % 95) + 32 \n";

      str += "\n\n\n";


      // The decrypt pseudocode
      str +=  "\ndecrypt(cipherText, cipherKey)\n";
       str +=  "\tplainText = \"\" \n";
      str +=  "\tfor i=0; = length(cipherText); i++ \n";

      str +=  "\t\tpLetter =  (cipherText[i] cast to int) - 32 \n";
      
      str +=  "\t\tif i < length(cipherKey) \n";
      str +=  "\t\t\tkLetter =  (cipherKey[i] cast to int) - 32 \n";

      str +=  "\t\t\tplainText += ((pLetter + 95 - kLetter) % 95) + 32 \n";
      str +=  "\t\telse: \n";
      str +=  "\t\t\tkLetter =  (plainText[i-length(cipherKey)] cast to int) - 32 \n";
      str +=  "\t\t\tplainText += ((pLetter + 95 - kLetter) % 95) + 32 \n";
      



      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string cipherText = "";
      // TODO - Add your code here
      for (int i = 0; i < plainText.length(); i++) {
          
          int kLetter;
          int pLetter = ((int)plainText[i]) - 32;
          
        if(i < password.length()){
          kLetter = ((int)password[i]) - 32;
          cipherText.push_back((char)(((kLetter + pLetter) % 95) + 32));
          

        }
        else {
          kLetter =  ((int)plainText[i-password.length()]) - 32;
          cipherText.push_back((char)(((kLetter + pLetter) % 95) + 32));
        }


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
      std::string plainText = "";
      // TODO - Add your code here

      for (int i = 0; i < cipherText.length(); i++) {
        int kLetter;
        int cLetter = ((int)cipherText[i])-32;
        if(i < password.length()){
          
          kLetter = ((int)password[i]) - 32;
          plainText.push_back((char)(((cLetter + 95 - kLetter) % 95) + 32));
        }
        else {
          kLetter =  ((int)plainText[i-password.length()])-32;
          plainText.push_back((char)(((cLetter + 95 - kLetter) % 95) + 32));
          
        }


      }


      return plainText;
   }
};

#endif // CIPHER01_H