package com.tokey.RandomNamePicker;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class test1 {
    public static void main(String[] args) throws IOException {
        File path = new File("/Users/tuttokey/JavaStudy/tut/out/production/day1/names.txt");
//        List<String> list = FileUtils.readLines(path, StandardCharsets.UTF_8);
        BufferedReader br = new BufferedReader(new java.io.FileReader(path));
        String line;
        List<String> maleList = new ArrayList<>();
        List<String> femaleList = new ArrayList<>();

        while((line = br.readLine()) != null){
            String[] spilt = line.split("-");
            if(spilt[1].equals("男")){
                maleList.add(line);
            }else{
                femaleList.add(line);
            }
        }
        br.close();

        int male = 0,female = 0;
        for(int i = 0;i < 10000000;i++){
            Collections.shuffle(maleList);
            Collections.shuffle(femaleList);

            List<String> list = new ArrayList<>();
            for (int k = 0; k < 7; k++) {
                list.add(maleList.get(k));
            }
            for (int k = 0; k < 3; k++) {
                list.add(femaleList.get(k));
            }

            Collections.shuffle(list);
            String person = list.getLast();
            String[] split = person.split("-");
            if(split[1].equals("男")){
                male++;
            }else{
                female++;
            }
        }
        System.out.println(7 / 3.0);
        System.out.printf("male:female = %f\n",male / (double) female);

    }
}
