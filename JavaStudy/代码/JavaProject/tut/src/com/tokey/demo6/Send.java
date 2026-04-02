package com.tokey.demo6;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Send {
    public static void main(String[] args) throws IOException {

        Socket s = new Socket("127.0.0.1",10000);
        OutputStream os = s.getOutputStream();
        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));

        while(true) {
            Scanner sc = new Scanner(System.in);
            String str = sc.nextLine();
            os.write(str.getBytes());
            if(str.equals("exit")){
                break;
            }
            s.shutdownOutput();

            str = br.readLine();
            if(str.equals("exit")){
                break;
            }

            System.out.println(str);

        }

        s.close();
    }
}
