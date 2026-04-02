package com.tokey.net;

import javax.print.attribute.standard.Severity;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPReceive {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(10000);
        Socket s = ss.accept();

        InputStreamReader isr = new InputStreamReader(s.getInputStream());
        int b;
        while((b = isr.read()) != - 1){
            System.out.print((char) b);
        }

        isr.close();
        ss.close();
    }
}
