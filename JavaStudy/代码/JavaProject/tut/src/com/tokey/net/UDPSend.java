package com.tokey.net;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;

public class UDPSend {
    public static void main(String[] args) throws IOException {
        //创建对象
        DatagramSocket ds = new DatagramSocket();
        //打包数据
        int port = 10086;
        byte[] bytes = "nihao".getBytes();
        InetAddress ia = InetAddress.getByName("127.0.0.1");
        DatagramPacket dp = new DatagramPacket(bytes,bytes.length,ia,port);
        //发送数据
        ds.send(dp);
        //释放资源
        ds.close();
    }
}
