package com.tokey.LotteryBox;

import java.util.ArrayList;
import java.util.Collections;

public class MyThread extends Thread {

    private static ArrayList<Integer> box = new ArrayList<>();
    static{
        box.add(1000);
        box.add(800);
        box.add(500);
        box.add(300);
        box.add(200);
        box.add(50);
    }

    public MyThread() {
        super();
    }

    public MyThread(String name) {
        super(name);
    }

    @Override
    public void run() {
        ArrayList<Integer> list = new ArrayList<Integer>();

        while(true){
            synchronized (MyThread.class){
                if(box.isEmpty()){
                    break;
                }else{
                    Collections.shuffle(box);
                    int price = box.removeFirst();
                    list.add(price);
                }
            }
        }
        System.out.println(this.getName() + ":" + list);
    }
}
