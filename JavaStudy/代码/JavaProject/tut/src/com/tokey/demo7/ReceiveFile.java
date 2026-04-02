package com.tokey.demo7;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class ReceiveFile {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(8888);

        Socket s = ss.accept();
        InputStream inputStream = s.getInputStream();
        byte[] bytes = new byte[1024 * 1024 * 5];
        int len;

        FileOutputStream fos = new FileOutputStream("/Users/tuttokey/aaa/test.mp4");
        while((len = inputStream.read(bytes)) != -1){
            fos.write(bytes, 0, len);
        }
        fos.close();

        OutputStream os = s.getOutputStream();
        os.write("传输成功".getBytes());

        ss.close();

    }
}
