package com.tokey.net;

import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class TCPMessageReceive {
    public static void main(String[] args) throws IOException {
        // 1. ServerSocket 只需要创建一次，监听 10000 端口
        ServerSocket ss = new ServerSocket(10000);
        System.out.println("服务器已启动，等待连接...");

        while (true) { // 外层循环：不断接收新客人的连接
            // 2. 等待客户端连接（如果没有人连，程序会停在这里等）
            Socket s = ss.accept();
            System.out.println("发现一个客户端连进来了：" + s.getInetAddress());

            // 3. 获取流进行读取
            InputStreamReader isr = new InputStreamReader(s.getInputStream(), StandardCharsets.UTF_8);

            int b;
            while ((b = isr.read()) != -1) { // 内层循环：读取当前客人的消息
                System.out.print((char) b);
            }

            // 4. 当前客人断开了，关闭这个客人的 Socket，准备迎接下一个
            System.out.println("\n[提示] 当前客户端已断开。");
            s.close();
            // 注意：这里不要写 ss.close()，否则服务器就关了！
        }
    }
}