/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER05_H
#define CIPHER05_H
#include<stdio.h>
#include<math.h>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher05 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Derek Washburn"; }
   virtual std::string getCipherName()  { return "Hill Cipher"; }
   virtual std::string getEncryptAuth() { return "Derek Washburn"; }
   virtual std::string getDecryptAuth() { return "Derek Washburn"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
       std::string s;
      s += "GeeksForGeeks.org (2019), ";
      s += "\"Geeks For Geeks - Hill Cipher\', \n   retrieved: ";
      s += "https://www.geeksforgeeks.org/hill-cipher/";
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
      str += "   nxnMatrix <- password\n";
      str += "   vector <- plainText\n";
      str += "   cipherText = (nxnMatrix)(vector)(mod 26)\n";
      str += "   RETURN cipherText\n\n";

      // The decrypt pseudocode
      str += "invPassword = inverse(password)\n";
      str += "   vector <- cipherText\n";
      str += "   plainText = (invPassword)(vector)(mod 26)\n";
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
      float encrypted[3][1];
      std::string cipherText = plainText;
      float (*mes)[1] = getKeyMessage(plainText);
      char (*a)[3] = getPassword(password);
      
      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 1; j++)
         {
            for(int k = 0; k < 3; k++)
               {
                 encrypted[i][j] = encrypted[i][j] + a[i][k] * mes[k][j];
               }
         }
      }

      for(int i = 0; i < 3; i++)
         cipherText += ((char)(fmod(encrypted[i][0], 26) + 97));

      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      float encrypted[3][1], decrypted[3][1];
      std::string plainText = cipherText;
      float (*b)[3] = inverse(password);
      
      for(int i = 0; i < 3; i++)
      {
        encrypted[i][0] = cipherText[i];
      }

      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 1; j++)
         {
            for(int k = 0; k < 3; k++)
               decrypted[i][j] = decrypted[i][j] + b[i][k] * encrypted[k][j];
         }
      }

      for(int i = 0; i < 3; i++)
         plainText += ((char)(fmod(decrypted[i][0], 26) + 97));
      return plainText;
   }

  /**********************************************************
    * GET KEY MESSAGE
    * TODO: ADD description
    **********************************************************/
   float (*getKeyMessage(const std::string & plainText))[1]
   {
      float mes[3][1];
      for(int i = 0; i < 3; i++)
         mes[i][0] = plainText[i] - 97;
      return mes;
   }
   
   /**********************************************************
    * GET PASSWORD
    * TODO: ADD description
    **********************************************************/
   char (*getPassword(const std::string & password))[3] 
   {
      char a[3][3];
      int k = 0;
      for (int i = 0; i < 3; i++)
      {
         for (int j = 0; j < 3; j++)
         {
            a[i][j] = password[k];
            k++;
         }
      }

      return a;
   }

  /**********************************************************
    * INVERSE
    * TODO: ADD description
    **********************************************************/
   float (*inverse(const std::string & password))[3]
   {
     char (*a)[3] = getPassword(password);
      float b[3][3];
      float p, q;
      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 3; j++) 
         {
            if(i == j)
               b[i][j]=1;
            else
               b[i][j]=0;
         }
      }

      for(int k = 0; k < 3; k++) 
      {
         for(int i = 0; i < 3; i++) 
         {
            p = a[i][k];
            q = a[k][k];
            for(int j = 0; j < 3; j++) 
            {
               if(i != k) 
               {
                  a[i][j] = a[i][j]*q - p*a[k][j];
                  b[i][j] = b[i][j]*q - p*b[k][j];
               }
            }
         }
      }

      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 3; j++)
            b[i][j] = b[i][j] / a[i][i];
      }
      
      printf("\n\nInverse Matrix is:\n");
      for(int i = 0; i < 3; i++) 
      {
         for(int j = 0; j < 3; j++)
            printf("%d ", b[i][j]);
         printf("\n");
      }
      
      return b;
    }
   
};

#endif // CIPHER05_H