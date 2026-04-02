package com.tokey.demo4;

import javax.sql.DataSource;
import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class SendMessage {
    public static void main(String[] args) throws IOException {
        //创建对象
        DatagramSocket ds = new DatagramSocket();
        int port = 12345;
        InetAddress ia = InetAddress.getByName("127.0.0.1");
        while(true){
            //打包数据
            Scanner scanner = new Scanner(System.in);
            byte[] message = scanner.nextLine().getBytes();
            DatagramPacket dp = new DatagramPacket(message,message.length,ia,port);
            //发送数据
            ds.send(dp);
            if(message.equals("886")){
                break;
            }
        }
        //释放资源
        ds.close();
    }

}
