package com.tokey.demo10;

public class Consumer extends Thread {

    public Consumer(String name) {
        super(name);
    }

    /**
     * 1.循环
     * 2.同步代码块
     * 3.检查是否到结尾（到了结尾）
     * 4.检查是否到结尾（没到结尾，执行核心代码块）
     * */
    @Override
    public void run() {
        while(true){
            synchronized (SharedData.lock){
                if(SharedData.count == 0){
                    break;
                }else{
                    if(SharedData.isOver == 0){
                        //没面了，等待厨子做
                        try {
                            SharedData.lock.wait(); //将当前线程和锁绑定
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }else{
                        //恰面
                        SharedData.count--;
                        System.out.println("还能吃" + SharedData.count + "碗面");
                        //改变面的状态
                        SharedData.isOver = 0;
                        //唤醒厨师线程继续做
                        SharedData.lock.notifyAll();
                    }
                }
            }
        }
    }
}
