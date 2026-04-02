package com.tokey.ThreadPool;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class test1 {
    public static void main(String[] args) {
        ThreadPoolExecutor pool = new ThreadPoolExecutor(
                3,
                6,
                1L,
                TimeUnit.SECONDS,
                new ArrayBlockingQueue<>(3),
                new ThreadPoolExecutor.AbortPolicy()
        );

        for (int i = 0; i < 9; i++) {
            pool.submit(()-> System.out.println(Thread.currentThread().getName() + "-hello"));
        }
        System.out.println(Runtime.getRuntime().availableProcessors());
    }
}
