package com.tokey.demo11;

import java.util.concurrent.ArrayBlockingQueue;

public class Main {
    public static void main(String[] args) {
        //创建阻塞队列，注意这个队列是共享的，所以我们要在生产者和消费者里面加上构造函数，传入 queue
        ArrayBlockingQueue<String> queue = new ArrayBlockingQueue<>(1);

        Comsumer cm = new Comsumer(queue);
        Productor pd = new Productor(queue);

        cm.start();
        pd.start();
    }
}
