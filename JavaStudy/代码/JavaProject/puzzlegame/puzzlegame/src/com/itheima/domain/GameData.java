package com.itheima.domain;

import java.io.Serial;
import java.io.Serializable;
import java.util.Arrays;

public class GameData implements Serializable {
    @Serial
    private static final long serialVersionUID = -5723291830972872607L;

    private int[][] data = new int[4][4];
    private String path;
    private int x;
    private int y;
    private int step;


    public GameData(int[][] data,String path, int x, int y, int step) {
        this.path = path;
        this.data = data;
        this.x = x;
        this.y = y;
        this.step = step;
    }

    public GameData() {
    }

    public GameData(long serialVersionUID, int[][] data, String path, int x, int y, int step) {
        this.data = data;
        this.path = path;
        this.x = x;
        this.y = y;
        this.step = step;
    }

    /**
     * 获取
     * @return data
     */
    public int[][] getData() {
        return data;
    }

    /**
     * 设置
     * @param data
     */
    public void setData(int[][] data) {
        this.data = data;
    }

    /**
     * 获取
     * @return x
     */
    public int getX() {
        return x;
    }

    /**
     * 设置
     * @param x
     */
    public void setX(int x) {
        this.x = x;
    }

    /**
     * 获取
     * @return y
     */
    public int getY() {
        return y;
    }

    /**
     * 设置
     * @param y
     */
    public void setY(int y) {
        this.y = y;
    }

    /**
     * 获取
     * @return step
     */
    public int getStep() {
        return step;
    }

    /**
     * 设置
     * @param step
     */
    public void setStep(int step) {
        this.step = step;
    }

    public String toString() {
        return "data = " + Arrays.deepToString(data) + ", x = " + x + ", y = " + y + ", step = " + step + "}";
    }


    /**
     * 获取
     * @return path
     */
    public String getPath() {
        return path;
    }

    /**
     * 设置
     * @param path
     */
    public void setPath(String path) {
        this.path = path;
    }
}
