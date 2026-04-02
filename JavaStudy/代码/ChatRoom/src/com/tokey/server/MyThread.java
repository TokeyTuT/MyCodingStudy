package com.tokey.server;

import java.io.*;
import java.net.Socket;
import java.util.Arrays;
import java.util.Properties;

public class MyThread extends Thread {

    Socket s;
    BufferedReader br;
    public MyThread(Socket s){
        this.s = s;
    }

    @Override
    public void run() {
        try {
            br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            String line = br.readLine();
            String[] split = line.split("&");
            System.out.println(Arrays.toString(split));
            switch (split[0]){
                case "login"-> login(split);
                case "register"->register(split);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void login(String[] split) {
        //回传的数据
        String callBack = "#";


        //校验用户名和密码
        String username = split[1].split("=")[1];
        String password = split[2].split("=")[1];

        if (!Server.prop.containsKey(username)) {
            callBack = "该用户不存在";
        }
        else if(!Server.prop.getProperty(username).equals(password)){
            callBack = "密码错误！";
        }else{
            callBack = "登录成功！";
        }

        //回传登录日志
        try {
            PrintWriter pw = new PrintWriter(s.getOutputStream());
            pw.println(callBack); // println 会自动加换行符
            pw.flush();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }


        try {
            Transfer(username);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void register(String[] split) throws IOException {

        //回传的数据
        String callBack = "注册失败";

        //写入数据
        String username = split[1].split("=")[1];
        String password = split[2].split("=")[1];

        if(Server.prop.containsKey(username)){
           callBack = "该账号已注册！";
        }
        else {
            try {
                Server.prop.put(username,password);
                FileOutputStream fos = new FileOutputStream("/Users/tuttokey/ChatRoom/userdata.txt",true);
                String in =System.lineSeparator() + username + "=" + password;
                fos.write(in.getBytes());
                fos.close();
                callBack = "注册成功！";
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        //回传数据
        try {
            OutputStream os = s.getOutputStream();
            os.write(callBack.getBytes());
            os.flush();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        Transfer(username);
    }


    //转发聊天内容
    void Transfer(String username) throws IOException {
        while(true){
            String line = br.readLine();

            System.out.println(username + ": "+ line);
            if(line.equals("exit")){
                break;
            }
        }
    }
}
