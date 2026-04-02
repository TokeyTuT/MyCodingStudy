package com.tokey.demo5;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;

public class TCPMessageSend {
    public static void main(String[] args) throws IOException {
        Socket s = new Socket("127.0.0.1",10000);


        OutputStream os = s.getOutputStream();
        while(true) {
            Scanner sc = new Scanner(System.in);
            String msg = sc.nextLine();
            os.write(msg.getBytes());
            if(msg.equals("886"))
                break;
        }

        s.close();
    }
}
