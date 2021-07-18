/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER02_H
#define CIPHER02_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher02 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Robert Jones"; }
   virtual std::string getCipherName()  { return "Vigenère Cipher"; }
   virtual std::string getEncryptAuth() { return "Robert Jones"; }
   virtual std::string getDecryptAuth() { return "Robert Jones"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("https://pages.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Base.html, , https://www.britannica.com/topic/Vigenere-cipher, https://www.cs.uri.edu/cryptography/classicalvigenere.htm");
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
      str += "Here are the pseudocode algorithms for the encrypt and decrypt methods \n";

      str =  "Encrypted = (plainText[i] + passoword[i]) modulo 26\n";

      // The decrypt pseudocode
      str += "Decypted = (plainText[i] - passoword[i] + 26) modulo 26\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * Formats and then encrypts the plain text message using
    * the Vigenère Cipher.
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
    const std::string& password)
  {
    std::string cipherText;
    std::string formattedPlainText;

    // Formats the message so that it can be encrypted.
    for (int i = 0; i < plainText.size(); i++)
    {
        if (isalnum(plainText[i]))
        {
            formattedPlainText += toupper(plainText[i]);
        }
    }

    for (int i = 0, j = 0; i < formattedPlainText.size(); i++)
    {
      // Encrypts the letter using the Vigenère Cipher.
       char letter = (formattedPlainText[i] + password[j]) % 26;

      // Finds the correct letter to use in the password for the        encryption algorithm above.
       j = (j + 1) % password.length();

      // Converts letter to ASCII value.
       letter += 'A';

       cipherText += letter;
    }

    return cipherText;
  }
            
   /**********************************************************
    * DECRYPT
    * Decrypts the cipher text message using the Vigenère Cipher.
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
    const std::string& password)
  {
    std::string plainText;

    for (int i = 0, j = 0; i < cipherText.size(); i++)
    {
      // Decrypts the message using the Vigenère Cipher
      char letter = (cipherText[i] - password[j] + 26) % 26;

      // Finds the correct letter to use in the password for the        decryption algorithm above.
      j = (j + 1) % password.length();

      // Converts letter to ASCII value
      letter += 'A';
      plainText += letter;
    }

    return plainText;
  }
};

#endif // CIPHER02_H