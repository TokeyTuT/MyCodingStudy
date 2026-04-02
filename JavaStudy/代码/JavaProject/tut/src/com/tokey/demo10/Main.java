package com.tokey.demo10;

public class Main {
    public static void main(String[] args) {
        Consumer cm = new Consumer("消费者");
        Productor pd = new Productor("生产者");

        cm.start();
        pd.start();
    }
}
