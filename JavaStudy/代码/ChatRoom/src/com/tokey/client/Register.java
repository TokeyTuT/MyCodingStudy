package com.tokey.client;

import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Register {
    public Register(Socket s){

        System.out.println("请输入用户名：");
        Scanner sc1 = new Scanner(System.in);
        String username = sc1.next();

        System.out.println("请输入密码：");
        Scanner sc2 = new Scanner(System.in);
        String password = sc2.next();

        //先在本地校验是否格式是否合法
        if(username.isEmpty() || password.isEmpty()){
            System.out.println("用户名和密码不能为空！");
            return;
        }

        //上传给服务器
        String uploadData = "register&username=" + username + "&password=" + password;

        try {
            PrintWriter pw = new PrintWriter(s.getOutputStream());
            pw.println(uploadData);
            pw.flush();

            //接收回传数据
            // 客户端修改 (如果服务器不发换行符，可以用这种方式)
            BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            String callBack = br.readLine();
            System.out.println(callBack);

            //发送数据
            SendMsg(s);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }


    private void SendMsg(Socket s) throws IOException {
        PrintWriter pw = new PrintWriter(s.getOutputStream());
        while(true){
            Scanner scanner = new Scanner(System.in);
            String msg = scanner.nextLine();

            System.out.println("正在发送中......");

            //发送消息

            pw.println(msg);
            pw.flush();

            if(msg.equals("exit")){
                break;
            }
        }
        System.out.println("断开连接");
    }
}
