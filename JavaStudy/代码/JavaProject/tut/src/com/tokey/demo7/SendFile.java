package com.tokey.demo7;

import java.io.*;
import java.net.Socket;

public class SendFile {
    public static void main(String[] args) throws IOException {
        File file = new File("/Users/tuttokey/aaa/savnjk/34346517618738681a12c7196dfcb9fc (1).mp4");

        Socket s = new Socket("127.0.0.1", 8888);
        OutputStream os = s.getOutputStream();

        BufferedInputStream is = new BufferedInputStream(new FileInputStream(file));
        byte[] buffer = new byte[1024 * 1024 * 5];
        int len;
        while((len = is.read(buffer)) != -1){
            os.write(buffer, 0, len);
        }

        is.close();

        //回传一个结束标识
        s.shutdownOutput();

        //接收回传信息
        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        System.out.println(br.readLine());

        s.close();
    }
}
