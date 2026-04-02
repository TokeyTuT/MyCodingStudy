package com.tokey.demo13;

public class MyThread extends Thread {
    static int num = 0;
    @Override
    public void run() {
        while(true){
            synchronized(MyThread.class){
                if (num <= 100) {
                    if(num % 2 == 1){
                        System.out.println(this.getName() + "@" + num);
                    }
                    num++;
                }else{
                    break;
                }
            }
        }
    }
}
