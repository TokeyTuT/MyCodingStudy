package com.tokey.demo11;

import java.util.concurrent.ArrayBlockingQueue;

public class Comsumer extends Thread {
    private ArrayBlockingQueue<String> queue;

    public Comsumer(ArrayBlockingQueue<String> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        while(true){
            try {
                queue.take();
                System.out.println("吃了一碗面条");
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }
    }
}
