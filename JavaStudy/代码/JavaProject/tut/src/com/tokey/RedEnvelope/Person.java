package com.tokey.RedEnvelope;

import java.util.Random;

public class Person extends Thread {
    private boolean flag = false;

    public Person() {
        super();
    }

    public Person(String name) {
        super(name);
    }

    @Override
    public void run() {
        synchronized (RedEnvelope.lock){
            if(RedEnvelope.number == 0){ // 已经抢完了
                System.out.println(this.getName() + "未抢到红包");
                return;
            }else{
                Random r = new Random();
                //随机抢到红包的金额
                int givenMoney = r.nextInt(RedEnvelope.totalMoney) + 1;
                RedEnvelope.totalMoney -= givenMoney;
                System.out.println(this.getName() + "抢到了" + givenMoney + "元");

                RedEnvelope.number--;
            }
        }
    }
}
