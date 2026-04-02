package com.tokey.RandomNamePicker;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class test4 {
    public static void main(String[] args) throws IOException {
        File data = new File("./src/com/tokey/RandomNamePicker/student.txt");
        BufferedReader br = new BufferedReader(new FileReader(data));

        ArrayList<Student> list = new ArrayList<Student>();
        String line;

        while((line = br.readLine()) != null){
            String[] split = line.split("-");
            list.add(new Student(split[0],split[1],Integer.parseInt(split[2]),Double.parseDouble(split[3])));
        }

        br.close();

        //计算总权重 + 计算前缀和
        double[] prefix_sum = new double[list.size()];
        double weight_sum = 0.0;
        for (int i = 0; i < list.size(); i++) {
            weight_sum += list.get(i).getWeight();
            prefix_sum[i] = weight_sum;
        }

        double random = Math.random() * weight_sum;

        //二分查找
        int idx =  - Arrays.binarySearch(prefix_sum, random) - 1;
        Student stu = list.get(idx);

        //输出答案
        System.out.println(stu.getName());

        //修改权重
        stu.setWeight(stu.getWeight() / 2);

        //修改到文件当中
        BufferedWriter bw = new BufferedWriter(new FileWriter(data));
        for (Student student : list) {
            bw.write(student.toString());
            bw.newLine();
        }
        bw.close();

    }
}
