//  Date Created  :-  20150410
//  Description   :-  This Java program encryptes and decryptes a password using private key

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;

public class cipher {

        void encryptPswd(String pswd, String privateKey){
                try {

                        String newpswd = "";
                        int key;
                        int i = -1;
                        int j = -1;
                        int newAscii;
                        int array[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

                        while (++i < pswd.length())
                        {
                                key = 10 + (int)(Math.random() * 90);
                                newAscii = key ^ (int)pswd.charAt(i);

                                while ( newAscii == (int)pswd.charAt(i) || array[newAscii] == 0 || array[key] == 0 ){
                                        key = 10 + (int)(Math.random() * 90);
                                        newAscii = key ^ (int)pswd.charAt(i);
                                }

                                if ( j == -1 )
                                        newpswd = newpswd + (char)newAscii + (char)key;
                                else
                                        newpswd = newpswd + (char)key + (char)newAscii;

                                j = j * -1;

                        }

                        System.out.println("Password - " + pswd);
                        System.out.println("Encrypted Password - " + newpswd);

                }
                catch(Exception e){
                        e.printStackTrace();
                }
        }

        public static void main(String args[]){

                if (args.length != 3) {
                        System.out.println("Usage :- cipher -<E|D> <password> <PRIVATE KEY filename>");
                        System.exit(1);
                }

                try {

                        File file = new File(args[2]);
                        if ( !file.exists() ){
                                System.out.println("File " + args[2] + " doesn't exist.");
                                System.exit(1);
                        }

                        if ( !file.canRead() ){
                                System.out.println("File " + args[2] + " is not readable");
                                System.exit(1);
                        }

                        BufferedReader bf = new BufferedReader(new FileReader(args[2]));
                        String privateKey = bf.readLine();

                        if ( privateKey == null ){
                                System.out.println("Error reading private key file " + args[2] + " or empty file");
                                System.exit(2);
                        }

                        if ( privateKey.length() > 8 ){
                                System.out.println("Private Key has more than 8 characters");
                                System.exit(1);
                        }


                        cipher c = new cipher();

                        /*** start encryption ***/
                        if ( args[0].equals("-E") ){

                                if ( args[1].length() > 30 ){
                                        System.out.println("Error : Password lenght is more than 30");
                                        System.exit(10);
                                }
                                c.encryptPswd(args[1], privateKey);

                        }
                        /*** end of encryption ***/

                        /*** start decryption ***/
                        else if ( args[0].equals("-D") ){



                        }
                        /*** end of decryption ***/

                        else {
                                System.out.println("Invlaid option " + args[0] + "; Valid option are -E|D");
                                System.exit(10);
                        }

                } //-end of try

                catch(IOException e){
                        e.printStackTrace();
                } //-end of catch

                System.exit(0);
        }
}
