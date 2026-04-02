package com.tokey.uploadFileByThread;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Random;
import java.util.UUID;
import java.util.concurrent.*;

public class Receive {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(10000);
        ThreadPoolExecutor pool = new ThreadPoolExecutor(
                3,
                12,
                60,
                TimeUnit.SECONDS,
                new ArrayBlockingQueue<>(2),
                Executors.defaultThreadFactory(),
                new ThreadPoolExecutor.AbortPolicy()
                );
        while(true) {
            pool.submit(new Thread(new Server(ss.accept())));
        }
    }
}
