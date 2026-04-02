package com.tokey.client;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        System.out.println("服务器已经连接成功\n" +
                "==============欢迎来到黑马聊天室================\n" +
                "1登录\n" +
                "2注册\n" +
                "请输入您的选择：");

        Scanner sc = new Scanner(System.in);
        int choice = sc.nextInt();
        Socket s = new Socket("127.0.0.1",10001);
        switch (choice) {
            case 1 -> new Login(s);
            case 2 -> new Register(s);
            default -> System.out.println("请输入正确的数字！");
        }
    }
}

