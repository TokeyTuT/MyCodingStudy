package com.tokey.demo10;

public class Productor extends Thread{
    public Productor(String name) {
        super(name);
    }

    @Override
    public void run() {
        while(true){
            synchronized (SharedData.lock){
                if(SharedData.count == 0){
                    break;
                }else{
                    if(SharedData.isOver == 1){
                        //桌上还有面，等待消费者吃完
                        try {
                            SharedData.lock.wait();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }else{
                        System.out.println("正在做面");
                        SharedData.isOver = 1;
                        //唤醒消费者线程吃面
                        SharedData.lock.notifyAll();
                    }
                }
            }
        }
    }
}
