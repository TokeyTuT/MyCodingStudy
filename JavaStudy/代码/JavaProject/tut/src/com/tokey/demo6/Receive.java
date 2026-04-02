package com.tokey.demo6;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Receive {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(10000);



        while(true) {
            Socket s = ss.accept();
            String str;


            BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            str = br.readLine();
            if(str.equals("exit")){
                break;
            }
            System.out.println(str);


            Scanner sc = new Scanner(System.in);
            str = sc.next();

            if(str.equals("exit")){
                break;
            }
            OutputStream os = s.getOutputStream();
            os.write(str.getBytes());

        }

        ss.close();

    }
}
