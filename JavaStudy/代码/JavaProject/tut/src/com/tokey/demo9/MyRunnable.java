package com.tokey.demo9;

public class MyRunnable implements Runnable {

    //使用 runnable 创建多线程不需要 static
    int count = 0;
    private synchronized boolean method(){
        if(count < 100){
            try {
                Thread.sleep(1);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            count++;
            System.out.println(Thread.currentThread().getName() + "在卖第" + count + "张票");
        }else{
            return true;
        }
        return false;
    }

    @Override
    public void run() {
        while(true){
            if(method()) break;
            try{
                Thread.sleep(1);
            }
            catch (InterruptedException e){
                throw new RuntimeException(e);
            }
        };
    }
}
