package com.tokey.net;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

public class TCPSend {
    public static void main(String[] args) throws IOException {
        Socket s = new Socket("127.0.0.1",10000);

        OutputStream out = s.getOutputStream();

        out.write("你好".getBytes());

        out.close();
        s.close();

    }
}
