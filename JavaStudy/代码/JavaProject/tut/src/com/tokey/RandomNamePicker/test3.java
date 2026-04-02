package com.tokey.RandomNamePicker;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.List;

public class test3 {
    public static void main(String[] args) throws IOException {
        File unredNames = new File("/Users/tuttokey/JavaStudy/tut/out/production/day1/UnredName.txt");
        File redNames = new File("/Users/tuttokey/JavaStudy/tut/out/production/day1/RedName.txt");
        List<String> unredNameList = FileUtils.readLines(unredNames,"utf-8");
        List<String> redNameList = FileUtils.readLines(redNames,"utf-8");

        if(unredNameList.isEmpty()){
            unredNameList.addAll(redNameList);
            redNameList.clear();
        }

        Collections.shuffle(unredNameList);
        String name = unredNameList.getLast();
        unredNameList.remove(name);
        redNameList.add(name);

        System.out.println(name);

        FileUtils.writeLines(redNames,redNameList);
        FileUtils.writeLines(unredNames,unredNameList);

    }
}
