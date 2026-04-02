package com.tokey.demo11;

import java.util.concurrent.ArrayBlockingQueue;

public class Productor extends Thread {

    private ArrayBlockingQueue<String> queue;


    public Productor(ArrayBlockingQueue<String> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        while(true){
             //不断地往队列中放入面条
            try {
                queue.put("面条");
                System.out.println("生产了面条");
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }


}
