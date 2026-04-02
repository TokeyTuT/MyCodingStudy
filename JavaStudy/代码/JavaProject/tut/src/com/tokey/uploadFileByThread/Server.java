package com.tokey.uploadFileByThread;

import java.io.*;
import java.net.Socket;
import java.util.UUID;

public class Server extends Thread{
    Socket s;
    public Server(Socket s){
        this.s = s;
    }
    @Override
    public void run() {
        try {
            InputStream is = s.getInputStream();

            String name = UUID.randomUUID().toString().replace("-", "");
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("/Users/tuttokey/JavaProject/tut/Cpy/" + name +".jpg"));

            int len;
            while((len = is.read())!=-1){
                bos.write(len);
            }
            bos.close();

            System.out.println(s.getInetAddress() + "上传了一个图片：" + name +".jpg");
            //写一个回传信息
            OutputStream os = s.getOutputStream();

            os.write("上传成功！\n".getBytes());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
