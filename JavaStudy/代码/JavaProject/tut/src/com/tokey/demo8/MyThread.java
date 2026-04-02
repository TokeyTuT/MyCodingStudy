package com.tokey.demo8;

public class MyThread extends Thread {
    static int count = 0;

    static Object oj = new Object();

    @Override
    public void run() {
        while(true){
            synchronized(oj){
                if(count < 100){
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    count++;
                    System.out.println("正在买第" + count + "张票");
                }else{
                    break;
                }
            }
        }
    }
}
