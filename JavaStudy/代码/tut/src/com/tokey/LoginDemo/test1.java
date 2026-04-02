package com.tokey.LoginDemo;

import java.io.*;
import java.util.List;
import java.util.Scanner;

public class test1 {
    public static void main(String[] args) throws IOException {
        File file = new File("./src/com/tokey/LoginDemo/UserData1.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        String[] split = br.readLine().split("&");
        br.close();

        String username = split[0].split("=")[1];
        String password = split[1].split("=")[1];
        int cnt = Integer.parseInt(split[2].split("=")[1]);

        if(cnt >= 3){
            System.out.println("该用户名输入错误超过三次，禁止尝试！");
        } else {
            System.out.println("请输入用户名：");
            Scanner sc1 = new Scanner(System.in);
            String usn = sc1.next();
            System.out.println("请输入密码：");
            Scanner sc2 = new Scanner(System.in);
            String pwd = sc2.next();

            if(usn.equals(username) && password.equals(pwd)){
                System.out.println("登录成功！");
            }else{
                cnt++;
                System.out.println("用户名或密码错误！");
            }
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter(file));
        bw.write("username=" + username + "&password=" + password + "&cnt=" + cnt);
        bw.close();
    }
}
