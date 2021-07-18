/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Davi Neves"; }
   virtual std::string getCipherName()  { return "Substitution Cypher"; }
   virtual std::string getEncryptAuth() { return "Davi Neves"; }
   virtual std::string getDecryptAuth() { return "Davi Neves"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://practicalcryptography.com/ciphers/classical-era/simple-substitution/");
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
      str += "\tcipherText = plainText \n";
	    str += "\tFOR EACH letter in cipherText, index is i\n";
		  str += "\t\tcipherText = lowerkey of cipherText[i] + password length\n";
      str += "\tRETURN cipherText\n\n";
      str += "\n\n\n";
      // The decrypt pseudocode
      str += "decrypt(cipherText, password)\n";
      str += "\tplainText = cipherText \n";      
      str += "\tFOR EACH letter in plainText, index is i\n";
      str += "\t\tplainText = plainText[i] - password length\n";
      str += "\tRETURN plainText\n\n";
  

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
      int shift = password.length();
      for(int i = 0; i < cipherText.length(); i++) {
         cipherText[i] = tolower(cipherText[i]);

         cipherText[i] += shift;

         if(cipherText[i] > 122){
           int offset = cipherText[i] - 122;
           cipherText[i] = 97 + offset; 
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
      std::string plainText = cipherText;
      int shift = password.length();
      for(int i = 0; i < plainText.length(); i++) {
         //cipherText[i] = tolower(cipherText[i]);

         plainText[i] -= shift;

         if(plainText[i] < 97){
          int offset = 97 - plainText[i];
          plainText[i] = 122 + offset; 
         }
               
      }
      return plainText;
   }
};

#endif // CIPHER04_H