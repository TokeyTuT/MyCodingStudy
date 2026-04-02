package com.tokey.demo4;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class ReceiveMessage {
    public static void main(String[] args) throws IOException {
        // 1. 创建 Socket 对象，监听 12345 端口
        DatagramSocket ds = new DatagramSocket(12345);
        byte[] buffer = new byte[1024];

        System.out.println("接收端已启动，等待数据...");

        while (true) {
            // 2. 创建数据包容器
            DatagramPacket dp = new DatagramPacket(buffer, buffer.length);

            // 3. 阻塞等待接收
            ds.receive(dp);

            // 4. 【关键修正】：使用 dp.getLength() 获取本次接收到的真实长度
            int len = dp.getLength();
            String message = new String(buffer, 0, len);

            // 5. 打印信息
            String ip = dp.getAddress().getHostAddress();
            int port = dp.getPort();
            System.out.println("来自 " + ip + ":" + port + " 的消息: " + message);

            // 6. 退出判断
            if ("886".equals(message)) {
                break;
            }
        }

        // 7. 释放资源
        ds.close();
        System.out.println("接收端已关闭");
    }
}