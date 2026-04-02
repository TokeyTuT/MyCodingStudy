package com.tokey.RandomNamePicker;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.List;

public class test2 {
    public static void main(String[] args) throws IOException {
        File path = new File("/Users/tuttokey/JavaStudy/tut/out/production/day1/names.txt");
        List<String> list = FileUtils.readLines(path, "UTF-8");
        Collections.shuffle(list);
        for (int i = 0; i < 100; i++) {
            if(i == 2){
                System.out.println("卜弘光");
            }else{
                System.out.println(list.get(i).split("-")[0]);
            }
        }
    }
}
