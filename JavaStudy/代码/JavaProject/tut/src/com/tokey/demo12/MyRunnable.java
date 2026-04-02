package com.tokey.demo12;

public class MyRunnable implements Runnable{
    int count = 0;

    @Override
    public void run() {
        while(true){
            if(method()){
                break;
            }
        }
    }

    private synchronized boolean method() {
        if(count == 1000){
            return true;
        }else{
            count++;
            System.out.println( Thread.currentThread().getName() + "正在卖出" + count + "张票");
        }
        return false;
    }
}