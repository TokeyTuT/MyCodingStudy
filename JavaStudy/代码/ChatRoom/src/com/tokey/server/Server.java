package com.tokey.server;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;

public class Server {
    static Properties prop = new Properties();

    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(10001);


        BufferedInputStream bis = new BufferedInputStream(new FileInputStream("/Users/tuttokey/ChatRoom/userdata.txt"));
        prop.load(bis);
        bis.close();

        while(true){
            //来一个客户端，我就开一个进程
            Socket s = ss.accept();
            System.out.println("有客户端来连接");
            new Thread(new MyThread(s)).start();
        }


    }
}
