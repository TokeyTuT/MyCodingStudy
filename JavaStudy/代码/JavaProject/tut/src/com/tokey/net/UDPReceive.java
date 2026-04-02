package com.tokey.net;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UDPReceive {
    public static void main(String[] args) throws IOException {
        //创建对象
        DatagramSocket ds = new DatagramSocket(10086);

        //接受数据包
        byte[] buf = new byte[1024];
        DatagramPacket dp = new DatagramPacket(buf, 1024);
        ds.receive(dp);
        //解析数据包
        byte[] data = dp.getData();
        int len = dp.getLength();
        InetAddress ip = dp.getAddress();
        int port = dp.getPort();

        System.out.println("接收到数据:" + new String(data, 0, len));
        System.out.println("connect from:" + ip + ":" + port);

    }
}
