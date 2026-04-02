package com.tokey.uploadFileByThread;

import com.tokey.demo11.Productor;

import java.io.*;
import java.net.Socket;

public class Upload {
    public static void main(String[] args) throws IOException {
        File file = new File("/Users/tuttokey/JavaStudy/IMG_6722.JPG");

        Socket s = new Socket("127.0.0.1",10000);
        OutputStream os = s.getOutputStream();

        BufferedInputStream bis = new BufferedInputStream(new FileInputStream(file));
        int len;
        while((len = bis.read()) != -1){
            os.write(len);
        }
        bis.close();
        //打一个标记
        s.shutdownOutput();

        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        System.out.println(br.readLine());

        s.close();
    }
}
